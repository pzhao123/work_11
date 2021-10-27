#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int random_num() {
    int data = open("/dev/urandom", O_RDONLY);
    if (data == -1) {
        printf("Opening urandom error: %s\n", strerror(errno));
    }
    int num;
    int bytes_read = read(data, &num, sizeof(num));
    if (bytes_read == -1) {
        printf("Reading data error: %s\n", strerror(errno));
    }
    return num;
}

int main() {
    int a[10];
    int i;
    for (i = 0; i < 10; i++) {
        a[i] = random_num();
    }
    printf("Generating random numbers: \n");
    for (i = 0; i < 10; i++) {
        printf("\trandom %d: %d\n", i, a[i]);
    }
    printf("\n");
    printf("Writing numbers to file...\n\n");
    int copy = open("copy.txt", O_CREAT | O_WRONLY, 0600);
    if (copy == -1) {
        printf("Creating new file error: %s\n", strerror(errno));
    }
    int add = write(copy, a, sizeof(a));
    if (add == -1) {
        printf("Writing into new file error: %s\n", strerror(errno));
    }
    int new = open("copy.txt", O_RDONLY);
    if (new == -1) {
        printf("Opening new file error: %s\n", strerror(errno));
    }
    int b[10];
    printf("Reading numbers from file: \n\n");
    int get_data = read(new, b, sizeof(b));
    if (get_data == -1) {
        printf("Reading from new file error: %s\n", strerror(errno));
    }
    printf("Verification that written values were the same: \n");
    for (i = 0; i < 10; i++) {
        printf("\trandom %d: %d\n", i, b[i]);
    }
    printf("\n");
    return 0;
}