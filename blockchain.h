//
// Created by christophe on 09/03/2020.
//

#ifndef PROJETBLOCKCHAIN_BLOCKCHAIN_H
#define PROJETBLOCKCHAIN_BLOCKCHAIN_H
#define NAME_SIZE 50 // taille maximale d'un nom
#define POW_INDEX 5 //indice du bit étudié dans la Proof of Work

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <openssl/sha.h>

#endif //PROJETBLOCKCHAIN_BLOCKCHAIN_H

typedef struct _block
{
    int		pos; //position dans la chaine
    int     nonce; //entier utilisé pour la Proof of Work
    char    auteur[NAME_SIZE];
    char    dest[NAME_SIZE];
    char    message[NAME_SIZE];
    char    timestamp[20]; //format JJ-MM-AAAA HH-MM-SS (19 caractères + 1 à cause du sprintf)
    unsigned char hash[2*SHA256_DIGEST_LENGTH+1]; //utilisation de la méthode de hashage SHA-256
    unsigned char previousHash[2*SHA256_DIGEST_LENGTH]; //hash du bloc précédent
    struct _block *next;
} Block;

typedef struct _blockchain
{
    int size; //nombre de blocs dans la blockchain
    Block *genesis; //premier bloc de la blockchain
}Blockchain;

void loginUser(char username[NAME_SIZE]);
void initBlock(Block *b, char *username);
void getHashValue(Block *b);
void setTimestamp(Block *b);
void convertHashToString(char *s, unsigned char *hash);
void addBlock(Blockchain *bc, char *username);
bool checkValidity(Block *b1, Block *b2);
void proofOfWork(Block *b, int i);

void parcoursComplet(Blockchain *bc);
void getBlock(Blockchain *bc);
void receivedBlocks(Blockchain *bc, char* username, int nb_echanges);
void detailsBlock(Block *b);
void editBlock(Blockchain *bc, Block *b);
void sentBlocks(Blockchain *bc, char* username, int nb_echanges);

void menuLogin(Blockchain *bc, char *username);
void menuBlockchain(Blockchain *bc, char *username);
void receivedBlocksMenu(Blockchain *bc, char *username);
void editBlockMenu(Blockchain *bc, char *username);