//
// Created by christophe on 09/03/2020.
//

#include "blockchain.h"


void initBlock(Block *b, char *username){
    printf("Bonjour, %s\n", username);
    strcpy(b->auteur, username);
    printf("Saisir le nom du destinataire :\n");
    scanf("%s", b->dest);
    printf("Saisir le nom du Pokémon à échanger :\n");
    scanf("%s", b->message);

    b->nonce=0;
    setTimestamp(b);
}

void setTimestamp(Block *b){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char* str_time=(char*) malloc(sizeof(char));

    tm.tm_year+=1900;
    tm.tm_mon++;
    printf("Echange émis le : %02d-%02d-%d %02d:%02d:%02d \n", tm.tm_mday, tm.tm_mon, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec);

    sprintf(str_time, "%02d-%02d-%d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec);

    strcpy(b->timestamp, str_time);

}

void getHashValue(Block *b){
    char *s = (char *) malloc(300*sizeof(char)); //chaine servant à calculer le hash
    unsigned char *hash; //chaine contenant le futur hash
    char pow[10]; // char contenant le nonce
    char pos[2]; // char contenant la position

    strcpy(s,""); //On initialise la chaine à vide
    strcat(s, b->auteur); //On concatène les informations du bloc dans une meme chaine de caractères
    strcat(s, b->dest);
    strcat(s, b->message);
    strcat(s, b->timestamp);
    if (b->pos !=1) {
        strcat(s, b->previousHash);
    }
    strcpy(pow, "");
    sprintf(pow, "%d", b->nonce);
    strcat(s, pow);

    strcpy(pos,"");
    sprintf(pos, "%d", b->pos);
    strcat(s, pos);

    //printf("%s \n", s);

    hash = SHA256(s, strlen(s), 0); //calcul du hash à partir des infos du bloc concaténées
    strcpy(b->hash,""); //on réinitialise à vide le hash
    convertHashToString(b->hash, hash);
    free(s);
}

void convertHashToString(char *s, unsigned char *hash){
    char hexa[3]; //chaine contenant les différentes parties du hash à convertir

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        strcpy(hexa, "");
        sprintf(hexa, "%02x", hash[i]); //on concatène 1 à 1 les éléments du hash (des hexa)
        strcat(s, hexa);
    }
}

void proofOfWork(Block *b, int i){
    if (0<=i<64) {
        b->hash[i] = 1;
        while (b->hash[i] != '0') {
            b->nonce++;
            getHashValue(b);
        }
    }
    else { printf("index of the bit is out of range");
    }
}

bool checkValidity(Block *b1, Block *b2){
    //b2 est le bloc à ajouter, et b1 le bloc précédent
    bool validity=true;

    if (strcmp(b2->previousHash, b1->hash)!=0)
    {
        validity=false; //Le hash précédent du bloc ne correspond pas au hash du bloc précédent
    }

    if (b2->pos!=b1->pos+1){
        validity=false; //les index ne se suivent pas
    }

    if (strlen(b2->hash)!=2*SHA256_DIGEST_LENGTH){
        validity=false; //le hash n'est pas valide
    }

    return validity;

}

void addBlock(Blockchain *bc, char *username){
    Block *current = bc->genesis;
    Block* new = (Block *)malloc(sizeof(Block));

    if(current == NULL){
        //On regarde si la liste est vide ou non
        bc->genesis=(Block *)malloc(sizeof(Block));
        bc->genesis->pos=1;
        initBlock(bc->genesis, username);
        getHashValue(bc->genesis);
        proofOfWork(bc->genesis, POW_INDEX);

        bc->genesis->next=NULL;
        bc->size=1;
    }

    else{
        while(current->next !=NULL){
            current=current->next;
        }

        strcpy(new->previousHash,current->hash);
        new->pos=current->pos+1;
        initBlock(new, username);  //attribue les informations et le hash du bloc
        getHashValue(new);

        if (checkValidity(current, new)){
            proofOfWork(new, POW_INDEX);
            current->next=new;
            new->next=NULL;
        }

        else
        {
            printf("Le bloc n'est pas valide.\n");
        }
        bc->size++;
    }
}


void getBlock(Blockchain *bc){
    int position;
    Block *current=bc->genesis;

    printf("La blockchain possède %d blocs.\n", bc->size);
    printf("Saisir la position du bloc recherché :\n");
    scanf("%d", &position);

    if(position > bc->size){
        printf("La taille de la blockchain est insuffisante.");
    }

    else{
        for (int i=1; i<position; i++){
            current=current->next;
        }

        detailsBlock(current);
    }

}

void detailsBlock(Block *b){
    printf("Détails du block n°%d :\n", b->pos);
    printf("Emetteur de l'échange : %s\n", b->auteur);
    printf("Destinataire : %s\n", b->dest);
    printf("Pokémon échangé : %s, le %s\n", b->message, b->timestamp);
    printf("Hash précédent : %s\n", b->previousHash);
    printf("Hashcode de l'échange : %s\n", b->hash);
}

void editBlock(Blockchain *bc, Block *b){
    bool quit=false;
    Block *current=b;
    int choice;
    unsigned char previousHash[2*SHA256_DIGEST_LENGTH+1];

    while (!quit){
        printf("Choisir la donnée à éditer :\n");
        printf("1. Destinataire\n");
        printf("2. Pokémon\n");
        printf("3. Arrêter les modifications.\n");
        printf("Votre choix :\n");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("Saisir le nouveau nom :\n");
                scanf("%s", b->dest);
                break;
            case 2:
                printf("Saisir le nouveau Pokémon :\n");
                scanf("%s", b->message);
                break;
            case 3:
                quit=true;
                break;
        }
    }

    for (int i=b->pos; i<=bc->size; i++){
        if(i != b->pos){
            strcpy(current->previousHash, previousHash); //on transfère les nouveaux hash précédents aux blocs suivant celui modifié
        }

        getHashValue(current); //on recalcule les hashs de tous les blocs à partir du bloc modifié
        proofOfWork(current, POW_INDEX);

        strcpy(previousHash, current->hash);
        if(current->next!=NULL){
            current=current->next;
        }
    }
}

void editBlockMenu(Blockchain *bc, char *username){
    int nb_echanges=0;
    int choice;
    int choice2;
    bool quit = false;
    Block *current=bc->genesis;

    if (current==NULL){
        printf("La blockchain est vide.\n");
    }

    else if(current->next == NULL){
        if (strcmp(current->auteur, username)==0) {
            printf("Il n'y qu'un bloc dans la blockchain et il est de vous.\n");
            detailsBlock(current);
            printf("Voulez-vous modifier le bloc ? (y=1/n=0)\n");
            scanf("%d", &choice2);
            if (choice2==1){
                editBlock(bc, current);
            }
        }

        else
            printf("Vous n'avez pas d'échanges reçus.");
    }

    else {
        while(current->next != NULL) {
            if(strcmp(current->auteur, username)==0)
                nb_echanges++;
            current=current->next;
        }

        if(strcmp(current->auteur, username)==0)
            nb_echanges++;

        printf("Vous avez %d échanges émis.\n", nb_echanges);
        while(!quit) {
            printf("1. Consulter ses échanges émis.\n");
            printf("2. Retour au menu principal.\n");
            printf("Votre choix : ");
            scanf("%d", &choice);
            switch (choice){
                case 1:
                    sentBlocks(bc,username,nb_echanges);
                    break;
                case 2:
                    quit=true;
                    break;
            }
        }
    }
}

void sentBlocks(Blockchain *bc, char* username, int nb_echanges){
    bool quit=false;
    int choice;
    Block *current=bc->genesis;

    while (!quit) {
        while (current->next != NULL && nb_echanges !=0) {
            if (strcmp(current->auteur, username)==0) {
                //Si on n'est pas en bout de chaine on peut proposer d'accéder au bloc suivant
                detailsBlock(current);
                printf("\n1. Bloc suivant\n");
                printf("2. Editer les informations du bloc\n");
                printf("3. Quitter le parcours de vos blocs émis.\n");
                printf("Votre choix : \n");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        current = current->next;
                        break;
                    case 2:
                        editBlock(bc,current);
                    case 3:
                        quit = true;
                        break;
                }
                nb_echanges -= 1;
            }
            else
            {
                current = current->next;
            }
        }
        if (strcmp(current->auteur, username)==0)
            detailsBlock(current);
        printf("\nVous n'avez pas d'autres échanges.\n");
        quit = true;
    }
}

void receivedBlocksMenu(Blockchain *bc, char *username){
    int nb_echanges=0;
    int choice;
    bool quit = false;
    Block *current=bc->genesis;

    if (current==NULL){
        printf("La blockchain est vide.\n");
    }

    else if(current->next == NULL){
        if (strcmp(current->dest, username)==0) {
            printf("Il n'y qu'un bloc dans la blockchain et il vous est destiné.\n");
            detailsBlock(current);
        }

        else
            printf("Vous n'avez pas d'échanges reçus.");
    }

    else {
        while(current->next != NULL) {
            if(strcmp(current->dest, username)==0)
                nb_echanges++;
            current=current->next;
        }

        if(strcmp(current->dest, username)==0)
            nb_echanges++;

        printf("Vous avez %d échanges reçus.\n", nb_echanges);
        while(!quit) {
            printf("1. Consulter ses échanges reçus.\n");
            printf("2. Retour au menu principal.\n");
            printf("Votre choix : ");
            scanf("%d", &choice);
            switch (choice){
                case 1:
                    receivedBlocks(bc,username,nb_echanges);
                    break;
                case 2:
                    quit=true;
                    break;
            }
        }
    }
}

void receivedBlocks(Blockchain *bc, char* username, int nb_echanges) {
    bool quit=false;
    int choice;
    Block *current=bc->genesis;

    while (!quit) {
        while (current->next != NULL && nb_echanges !=0) {
            if (strcmp(current->dest, username)==0) {
                //Si on n'est pas en bout de chaine on peut proposer d'accéder au bloc suivant
                detailsBlock(current);
                printf("\n1. Bloc suivant\n");
                printf("2. Quitter le parcours de vos blocs reçus.\n");
                printf("Votre choix : \n");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        current = current->next;
                        break;
                    case 2:
                        quit = true;
                        break;
                }
                nb_echanges -= 1;
            }
            else
            {
                current = current->next;
            }
        }
        if(strcmp(current->dest, username)==0)
            detailsBlock(current);
        printf("\nVous n'avez pas d'autres échanges.\n");
        quit=true;
    }
}

void parcoursComplet(Blockchain *bc){
    bool quit=false;
    int choice;
    Block *current=bc->genesis;

    if (current==NULL){
        printf("La blockchain est vide.\n");
    }

    else{
        while (!quit) {
            detailsBlock(current);
            if(current->next!=NULL) {
                //Si on n'est pas en bout de chaine on peut proposer d'accéder au bloc suivant
                printf("\n1. Bloc suivant\n");
                printf("2. Quitter le parcours de la blockchain.\n");
                printf("Votre choix : \n");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        current = current->next;
                        break;
                    case 2:
                        quit = true;
                        break;
                }
            }

            else {
                printf("\nVous êtes arrivé à la fin de la blockchain\n");
                printf("1. Quitter le parcours de la blockchain.\n");
                printf("Votre choix : \n");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        quit = true;
                        break;
                }
            }
        }
    }
}


void loginUser(char username[NAME_SIZE]){
    printf("Veuillez saisir votre nom d'utilisateur :\n");
    scanf("%s", username);
}

void menuLogin(Blockchain *bc, char *username){
    bool quit=false;
    int choice;
    int choice2;

    while (!quit)
    {
        printf("\n");
        printf("Bienvenue dans la PokéChain, blockchain d'échange de Pokémon.\n");
        printf("Saisir une option parmi celles-ci :\n");
        printf("1. Se connecter\n");
        printf("2. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                loginUser(username);
                menuBlockchain(bc,  username);
                break;
            case 2:
                printf("Quitter cette interface, terminera le programme et resetera la blockchain.\n");
                printf("Êtes-vous sûr de vouloir quitter ? (y=1/n=0)\n");
                scanf("%d", &choice2);
                if (choice2==1){
                    strcpy(username,"");
                    quit=true;
                }
                break;
        }
    }
}

void menuBlockchain(Blockchain *bc, char *username){
    bool quit=false;
    int choice;

    while (!quit) {
        printf("\n");
        printf("Bonjour %s, bienvenue sur votre session utilisateur.\n", username);
        printf("Saisir une option parmi celles-ci :\n");
        printf("1. Effectuer un échange\n");
        printf("2. Parcourir la blockchain\n");
        printf("3. Accéder un bloc à partir de sa position.\n");
        printf("4. Voir mes échanges reçus.\n");
        printf("5. Modifier un échange émis.\n");
        printf("6. Se déconnecter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBlock(bc, username);
                break;
            case 2:
                parcoursComplet(bc);
                break;
            case 3:
                getBlock(bc);
                break;
            case 4:
                receivedBlocksMenu(bc, username);
                break;
            case 5:
                editBlockMenu(bc, username);
                break;
            case 6:
                quit = true;
                break;
        }
    }
}