//
// Created by yncrea-hugo on 26/03/19.
//

#include "chained_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
                printf("%d\n", ptr->rent->u.value_hist->number);
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
maillon* rechercheMaillonPrecedent(maillon *ptrTete, arith *data){
    maillon *ptr = ptrTete;
    maillon *precedent = NULL;
    if(ptr->data->typ_val == 0){
        while(ptr != NULL && ptr->data->u.i < data->u.i){
            precedent = ptr;
            ptr = ptr->suivant;
        }
    } else if(ptr->data->typ_val == 1){
        while(ptr != NULL && ptr->data->u.f < data->u.f){
            precedent = ptr;
            ptr = ptr->suivant;
        }
    }

    return precedent;
}

/* Passage par adresse pour pouvoir conserver les modifications après
 * chainage
 * */
void insertionMaillon(maillon **ptrTete, maillon *insert){
    maillon *precedent;
    precedent = rechercheMaillonPrecedent(*ptrTete, insert->data);
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
void insertionValeur(arith* data, maillon **ptrTete){
    insertionMaillon(ptrTete, creationMaillon(data));
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
    precedent = rechercheMaillonPrecedent(*ptrTete,del->data);
    if(precedent == NULL){ // liste vide -> insertion en tête
        *ptrTete = del->suivant;
        del->suivant = NULL;
    }
    else {
        if(precedent->data->typ_val == 0){
            precedent->data->u.i = del->suivant;
        } else if(precedent->data->typ_val == 1){
            precedent->data->u.f = del->suivant->data->u.f;
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