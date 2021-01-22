#include <stdio.h>
#include "blockchain.h"

int main (void) {
    Blockchain *bc=(Blockchain*) malloc(sizeof(Blockchain));
    char username[NAME_SIZE];


    menuLogin(bc, username);

    return 0;
}