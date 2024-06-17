// no_race_condition.c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define LOOPS 1000000

int account_balance = 1000;
pthread_mutex_t account_mutex = PTHREAD_MUTEX_INITIALIZER;

void *deposit(void *arg) {
    int amount = *((int *)arg);
    for (int i = 0; i < LOOPS; i++) {
        pthread_mutex_lock(&account_mutex);
        account_balance += amount;
        pthread_mutex_unlock(&account_mutex);
    }
    return NULL;
}

void *withdraw(void *arg) {
    int amount = *((int *)arg);
    for (int i = 0; i < LOOPS; i++) {
        pthread_mutex_lock(&account_mutex);
        account_balance -= amount;
        pthread_mutex_unlock(&account_mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int deposit_amount = 10;
    int withdraw_amount = 10;

    pthread_create(&thread1, NULL, deposit, &deposit_amount);
    pthread_create(&thread2, NULL, withdraw, &withdraw_amount);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    int expected_balance = 1000 + LOOPS * (deposit_amount - withdraw_amount);
    printf("Account balance: %d\n", account_balance);
    if (account_balance != expected_balance) {
        printf("Error: Expected account balance is %d, but got %d\n", expected_balance, account_balance);
    } else {
        printf("Account balance is correct.\n");
    }

    pthread_mutex_destroy(&account_mutex);

    return 0;
}
