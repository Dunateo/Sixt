//
// Created by yncrea-hugo on 26/03/19.
//

#include "chained_list.h"
#include <stdlib.h>
#include <stdio.h>


void afficheListe(maillon *ptrTete){
    maillon *ptr = ptrTete;
    switch(ptr->rent.typ_val){
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
        switch(ptr->rent.typ_val){
            case 0:
                printf("%s|%s|%s;%d|%d|%f|%c\n", ptr->rent.u.value_car.brand_name,ptr->rent.u.value_car.brand_model,ptr->rent.u.value_car.plate_number,ptr->rent.u.value_car.car_year,ptr->rent.u.value_car.km,ptr->rent.u.value_car.price,ptr->rent.u.value_car.category);
                break;
            case 1:
                printf("%s|%s|%s;%d|%d|%f|%c\n", ptr->rent.u.value_car.brand_name,ptr->rent.u.value_car.brand_model,ptr->rent.u.value_car.plate_number,ptr->rent.u.value_car.car_year,ptr->rent.u.value_car.km,ptr->rent.u.value_car.price,ptr->rent.u.value_car.category);
                break;
            case 2:
                printf("%s|%s|%s;%d|%d|%f|%c\n", ptr->rent.u.value_car.brand_name,ptr->rent.u.value_car.brand_model,ptr->rent.u.value_car.plate_number,ptr->rent.u.value_car.car_year,ptr->rent.u.value_car.km,ptr->rent.u.value_car.price,ptr->rent.u.value_car.category);
                break;
            case 3:
                printf("%s|%s|%s;%d|%d|%f|%c\n", ptr->rent.u.value_car.brand_name,ptr->rent.u.value_car.brand_model,ptr->rent.u.value_car.plate_number,ptr->rent.u.value_car.car_year,ptr->rent.u.value_car.km,ptr->rent.u.value_car.price,ptr->rent.u.value_car.category);
                break;
            default:
                printf("ENUM TYPE NOT DEFINE");
        }
    }
}

/*
*Fonction de création de maillon renvoie un pointeur sur maillon
**/
maillon* creationMaillon(data *rent){
    maillon *ptr;
    ptr = (maillon*)malloc(sizeof(maillon));
    if(ptr == NULL){
        return 1;
    }

    ptr->rent = rent;
    ptr->suivant = NULL;


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
    maillon *precedent = NULL;
    //on veut inserer nos maillons en début donc pas besoins de rechercheMaillonPrecedent
    //precedent = rechercheMaillonPrecedent(*ptrTete, insert->data)

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
maillon* rechercheMaillon(maillon *ptrTete, arith* data){
    maillon* ptr = ptrTete;
    if(ptr->data->typ_val == 0){
        while(ptr != NULL && ptr->data->u.i != data->u.i){
            ptr = ptr->suivant;
        }
    } else if(ptr->data->typ_val == 1){
        while(ptr != NULL && ptr->data->u.f != data->u.f){
            ptr = ptr->suivant;
        }
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
maillon* suppressionValeur(maillon *ptrTete, arith* data){
    maillon* del = rechercheMaillon(ptrTete, data);
    suppressionMaillon(&ptrTete, del);
    return del;
}

// chainage + valeur
maillon * creationListe(void){
    maillon *ptrTete = NULL;
    arith* data;
    data = (arith*)malloc(sizeof(arith));
    int x = -1;
    while(x < 2){
        printf("entier (0) ou flotant (1) ? stop (2)\n");
        printf("-> ");
        scanf("%d",&x);
        if( x == 0){
            printf("saisir un entier :\n");
            printf("-> ");
            scanf("%d",&data->u.i);
            insertionValeur(data, &ptrTete);
        } else if(x == 1){
            printf("saisir un float :\n");
            printf("-> ");
            scanf("%f",&data->u.f);
            insertionValeur(data, &ptrTete);
        }
    }
    free(data);
    return ptrTete;
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

int main(){
    maillon *ptrTete, *del;
    arith create, suppr;
    create.typ_val = 0;
    create.u.i = 15;
    suppr.typ_val = 0;
    suppr.u.i = 15;
    printf("CREATION\n");
    ptrTete = creationListe();
    afficheListe(ptrTete);
    printf("INSERTION\n");
    insertionMaillon(&ptrTete, creationMaillon(&create));
    afficheListe(ptrTete);
    printf("SUPPRESSION & INVERSION\n");
    del = suppressionValeur(ptrTete, &suppr);
    free(del);
    inversionListe(&ptrTete);
    afficheListe(ptrTete);
    suppressionListe(&ptrTete);
    return 0;
}
