#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "cipher.h"

EncryptionData data;
sem_t sem;
char encryptedWords[MAX_WORDS][512];

ll modularExponential(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void* caesar_encrypt_word(void* arg) {
    WordData* wdata = (WordData*)arg;
    char* word = wdata->word;
    int shift = data.caesarKey % 26;

    for (int i = 0; word[i] != '\0'; i++) {
        char ch = word[i];
        if (isupper(ch)) {
            word[i] = ((ch - 'A' + shift) % 26) + 'A';
        } else if (islower(ch)) {
            word[i] = ((ch - 'a' + shift) % 26) + 'a';
        }
    }

    sem_wait(&sem);
    strcpy(encryptedWords[wdata->index], word);
    sem_post(&sem);

    free(wdata);
    pthread_exit(NULL);
}

void* rsa_encrypt_word(void* arg) {
    WordData* wdata = (WordData*)arg;
    char* word = wdata->word;
    char encrypted[512] = "";
    char buffer[32];

    for (int i = 0; word[i] != '\0'; i++) {
        ll m = (unsigned char)word[i];
        ll c = modularExponential(m, data.rsaPublicKey, data.rsaModulus);
        sprintf(buffer, "%lld ", c);
        strcat(encrypted, buffer);
    }

    sem_wait(&sem);
    strcpy(encryptedWords[wdata->index], encrypted);
    sem_post(&sem);

    free(wdata);
    pthread_exit(NULL);
}
