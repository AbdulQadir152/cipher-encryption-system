#ifndef CIPHER_H
#define CIPHER_H

#include <semaphore.h>

#define MAX_MSG_LEN 1024
#define MAX_WORDS 100

typedef long long int ll;

typedef struct {
    char message[MAX_MSG_LEN];
    int caesarKey;
    int rsaPublicKey;
    int rsaModulus;
    int rsaP, rsaQ;
    int choice;
} EncryptionData;

typedef struct {
    int index;
    char word[128];
} WordData;

// Extern declarations for global variables
extern EncryptionData data;
extern sem_t sem;
extern char encryptedWords[MAX_WORDS][512];

// Function prototypes
ll modularExponential(ll base, ll exp, ll mod);
int gcd(int a, int b);
void* caesar_encrypt_word(void* arg);
void* rsa_encrypt_word(void* arg);

#endif
