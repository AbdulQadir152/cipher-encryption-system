#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include "cipher.h"

int main() {
    pthread_t threads[MAX_WORDS];
    sem_init(&sem, 0, 1);
    bool run_status = true;

    printf("---Welcome To Cipher Conversion System---\n");
    while (run_status) {
        printf("Enter (1) to Encrypt Message into Cipher\n");
        printf("Enter (0) to Exit\n");
        printf("------------------------------------------\n");

        int choice;
        scanf(" %d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                printf("Enter a message to encrypt: ");
                fgets(data.message, MAX_MSG_LEN, stdin);
                data.message[strcspn(data.message, "\n")] = '\0';

                printf("\nChoose Encryption Method:\n");
                printf("1. Caesar Cipher\n");
                printf("2. RSA Cipher\n");
                printf("Enter choice: ");
                scanf("%d", &data.choice);
                getchar();

                int wordCount = 0;
                char* token = strtok(data.message, " ");

                if (token == NULL) {
                    printf("Empty String:\n");
                    break;
                }

                while (token != NULL && wordCount < MAX_WORDS) {
                    WordData* wdata = malloc(sizeof(WordData));
                    wdata->index = wordCount;
                    strcpy(wdata->word, token);

                    switch (data.choice) {
                        case 1:
                            if (wordCount == 0) {
                                printf("Enter Caesar key (0-25): ");
                                scanf("%d", &data.caesarKey);
                                getchar();
                            }
                            pthread_create(&threads[wordCount], NULL, caesar_encrypt_word, wdata);
                            break;

                        case 2:
                            if (wordCount == 0) {
                                printf("Enter RSA prime p: ");
                                scanf("%d", &data.rsaP);
                                printf("Enter RSA prime q: ");
                                scanf("%d", &data.rsaQ);

                                if (data.rsaP <= 1 || data.rsaQ <= 1) {
                                    printf("p and q must be greater than 1 and prime.\n");
                                    free(wdata);
                                    goto join_threads;
                                }

                                int phi = (data.rsaP - 1) * (data.rsaQ - 1);
                                data.rsaModulus = data.rsaP * data.rsaQ;

                                printf("Euler Totient φ(n): %d\n", phi);
                                printf("Enter RSA public key (e): ");
                                scanf("%d", &data.rsaPublicKey);

                                if (gcd(data.rsaPublicKey, phi) != 1) {
                                    printf("Invalid key: e must be coprime with φ(n) = %d\n", phi);
                                    free(wdata);
                                    goto join_threads;
                                }
                                getchar();
                            }
                            pthread_create(&threads[wordCount], NULL, rsa_encrypt_word, wdata);
                            break;

                        default:
                            printf("Invalid encryption method!\n");
                            free(wdata);
                            goto join_threads;
                    }

                    token = strtok(NULL, " ");
                    wordCount++;
                }

            join_threads:
                for (int i = 0; i < wordCount; i++) {
                    pthread_join(threads[i], NULL);
                }

                printf("\nEncrypted Message:\n");
                for (int i = 0; i < wordCount; i++) {
                    printf("%s", encryptedWords[i]);
                    if (data.choice == 1) printf(" ");
                }
                printf("\n\n");

                break;
            }

            case 0:
                printf("---Thank You for using Cipher Conversion System---\n");
                run_status = false;
                break;

            default:
                printf("Invalid Input! Try Again\n");
                break;
        }
    }

    sem_destroy(&sem);
    return 0;
}
