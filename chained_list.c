//
// Created by yncrea-hugo on 26/03/19.
//

#include "chained_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @param maillon*
 */
void afficheListe(maillon *ptrTete){
    maillon *ptr = ptrTete;
    switch(ptr->rent->typ_val){
        case 0:
            printf("CAR:\n");
            break;
        case 1:
            printf("HISTORY:\n");
            break;
        case 2:
            printf("RESERVATION:\n");
            break;
        case 3:
            printf("CLIENT:\n");
            break;
        default:
            printf("ERROR ! ENUM TYPE NOT DEFINE\n");
            break;
    }
    while(ptr != NULL){
        switch(ptr->rent->typ_val){
            case 0:
                printf("%s|%s|%s|%d|%d|%f|%c\n", ptr->rent->u.value_car->brand_name,ptr->rent->u.value_car->brand_model,ptr->rent->u.value_car->plate_number,ptr->rent->u.value_car->car_year,ptr->rent->u.value_car->km,ptr->rent->u.value_car->price,ptr->rent->u.value_car->category);
                break;
            case 1:
                printf("%d\n", ptr->rent->u.value_hist->status);
                break;
            case 2:
                printf("%d|%c|%d-%d-%d %dh|%d-%d-%d %dh\n", ptr->rent->u.value_reserv->number, ptr->rent->u.value_reserv->category, ptr->rent->u.value_reserv->begining.day, ptr->rent->u.value_reserv->begining.month, ptr->rent->u.value_reserv->begining.year, ptr->rent->u.value_reserv->begining.hour, ptr->rent->u.value_reserv->end.day, ptr->rent->u.value_reserv->end.month, ptr->rent->u.value_reserv->end.year, ptr->rent->u.value_reserv->end.hour);
                break;
            case 3:
                printf("%s|%s|%d", ptr->rent->u.value_client->client_name,ptr->rent->u.value_client->driving_license_type, ptr->rent->u.value_client->phone_number);
                break;
            default:
                printf("ENUM TYPE NOT DEFINE");
        }
    }
}

// chainage
maillon* creationMaillon(data *rent){
    maillon *ptr;
    ptr = (maillon*)malloc(sizeof(maillon));
    if(ptr == NULL){
        return 1;
    }
    switch (rent->typ_val){
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
    return ptr;
}

// valeur
maillon* rechercheMaillonPrecedent(maillon *ptrTete, data *data1){
    maillon *ptr = ptrTete;
    maillon *precedent = NULL;
    switch (ptr->rent->typ_val){
        case 0:
            while(ptr != NULL && strcmp(ptr->rent->u.value_car->plate_number, data1->u.value_car->plate_number) != 0){
                precedent = ptr;
                ptr->suivant;
            }
            break;
        case 1:
            while(ptr != NULL && ptr->rent->u.value_hist->reserv->number == data1->u.value_hist->reserv->number){
                precedent = ptr;
                ptr->suivant;
            }
            break;
        case 2:
            while(ptr != NULL && ptr->rent->u.value_reserv->number == data1->u.value_reserv->number){
                precedent = ptr;
                ptr->suivant;
            }
            break;
        case 3:
            while(ptr != NULL && ptr->rent->u.value_client->phone_number == data1->u.value_client->phone_number){
                precedent = ptr;
                ptr->suivant;
            }
            break;
    }

    return precedent;
}

/* Passage par adresse pour pouvoir conserver les modifications après
 * chainage
 * */
void insertionMaillon(maillon **ptrTete, maillon *insert){
    maillon *precedent;
    precedent = rechercheMaillonPrecedent(*ptrTete, insert->rent);
    if(precedent == NULL){ // liste vide -> insertion en tête
        insert->suivant = *ptrTete;
        *ptrTete = insert;
    }
    else {
        insert->suivant = precedent->suivant;
        precedent->suivant = insert;
    }
}

// chainage + valeur
void insertionValeur(data *rent, maillon **ptrTete){
    insertionMaillon(ptrTete, creationMaillon(rent));
}

// valeur
maillon* rechercheMaillon(maillon *ptrTete, data* data1){
    maillon* ptr = ptrTete;
    switch (ptr->rent->typ_val){
        case 0:
            while(ptr != NULL && strcmp(ptr->rent->u.value_car->plate_number, data1->u.value_car->plate_number) != 0){
                ptr = ptr->suivant;
            }
            break;
        case 1:
            while(ptr != NULL && ptr->rent->u.value_hist->reserv->number == data1->u.value_hist->reserv->number){
                ptr = ptr->suivant;
            }
            break;
        case 2:
            while(ptr != NULL && ptr->rent->u.value_reserv->number == data1->u.value_reserv->number){
                ptr = ptr->suivant;
            }
            break;
        case 3:
            while(ptr != NULL && ptr->rent->u.value_client->phone_number == data1->u.value_client->phone_number){
                ptr = ptr->suivant;
            }
            break;
    }
    return ptr;
}

//chainage
void suppressionMaillon(maillon **ptrTete, maillon *del){
    maillon *precedent;
    precedent = rechercheMaillonPrecedent(*ptrTete,del->rent);
    if(precedent == NULL){ // liste vide -> insertion en tête
        *ptrTete = del->suivant;
        del->suivant = NULL;
    }
    else {
        switch (precedent->rent->typ_val){
            case 0:
                precedent->rent->u.value_car = del->suivant->rent->u.value_car;
                break;
            case 1:
                precedent->rent->u.value_hist = del->suivant->rent->u.value_hist;
                break;
            case 2:
                precedent->rent->u.value_reserv = del->suivant->rent->u.value_reserv;
                break;
            case 3:
                precedent->rent->u.value_client = del->suivant->rent->u.value_client;
                break;
        }

        del->suivant = NULL;
    }
}

// chainage + valeur
maillon* suppressionValeur(maillon *ptrTete, data* rent){
    maillon* del = rechercheMaillon(ptrTete, rent);
    suppressionMaillon(&ptrTete, del);
    return del;
}

// chainage
void suppressionListe(maillon **ptrTete){
    maillon *tmp;
    while (*ptrTete != NULL){
        tmp = *ptrTete;
        *ptrTete = (*ptrTete)->suivant;
        free(tmp);
        tmp = NULL;
    }
}

// chainage
void inversionListe(maillon **ptrTete){
    maillon *ptr, *ptrTeteInverse;
    ptrTeteInverse = NULL;
    while(*ptrTete != NULL){
        ptr = *ptrTete;
        *ptrTete = (*ptrTete)->suivant;
        ptr->suivant = ptrTeteInverse;
        ptrTeteInverse = ptr;
    }
    *ptrTete = ptrTeteInverse;

}