//
// Created by hugo on 18/06/19.
//

#include <stdlib.h>
#include <stdio.h>
#include "calculus.h"
#include "chained_list.h"
#include "initialize.h"
#include "getter.h"

char* convertDateShow(date date1){
    char* dateChar= malloc(14 * sizeof(char)) ;
    sprintf(dateChar,"%d/%d/%d:%d",date1.day,date1.month,date1.year,date1.hour);
    return dateChar;
}

maillon* rechercheReservationJour(date date1, maillon **reservation){
    maillon* ptr = *reservation;
    maillon* resultat = NULL;

    while(ptr != NULL){
        if(resultat == NULL && dateCompare(ptr->rent->u.value_reserv->begining,date1)== true && dateCompare(date1,ptr->rent->u.value_reserv->begining) == true){
            resultat = ptr;
        } else if(resultat == NULL && dateCompare(ptr->rent->u.value_reserv->begining,date1)== true && dateCompare(date1,ptr->rent->u.value_reserv->begining) == true){
            maillon* tmp = NULL;
            tmp = ptr;
            tmp->suivant = resultat;
            resultat = tmp;
        }
    }
    return resultat;
}

void returnVehicule(maillon* ptrTete,char* plate, int KM){
    data* searchCar = (data*)calloc(1, sizeof(data));
    searchCar->typ_val = CAR;
    searchCar->u.value_car = (car*)calloc(1, sizeof(car));
    searchCar->u.value_car->plate_number = (char*)calloc(strlen(plate), sizeof(char));
    strcpy(searchCar->u.value_car->plate_number, plate);
    maillon* car = rechercheMaillon(ptrTete,searchCar);
    date date1;
    date1 = actualDate();
    car->rent->u.value_car->km += KM;
    while(dateCompare(car->rent->u.value_car->history_rent->reserv->begining,date1) != true && dateCompare(date1,car->rent->u.value_car->history_rent->reserv->end)!= true){
        car->rent->u.value_hist = car->rent->u.value_hist->suivant;
    }
    car->rent->u.value_car->history_rent->reserv->km = KM;
    free(searchCar->u.value_car->plate_number);
    free(searchCar->u.value_car);
    free(searchCar);
}

data* rechercheClient(int dataSearch, int entry,maillon *reserv){
    data* searchReserv = NULL;
    data* ptrTeteHist = NULL;
    switch (entry){
        case 0:
            while (reserv != NULL){
                if(reserv->rent->u.value_reserv->client_info->phone_number == dataSearch){
                    if(ptrTeteHist == NULL){
                        ptrTeteHist = (data*)calloc(1, sizeof(data));
                        ptrTeteHist->typ_val = HISTORY;
                        ptrTeteHist->u.value_hist = (history*)calloc(1, sizeof(history));
                        ptrTeteHist->u.value_hist->reserv = reserv->rent->u.value_reserv;
                    } else {
                        searchReserv = (data*)calloc(1, sizeof(data));
                        searchReserv->typ_val = HISTORY;
                        searchReserv->u.value_hist = (history*)calloc(1, sizeof(history));
                        searchReserv->u.value_hist->reserv = reserv->rent->u.value_reserv;
                        insertionSousChaine(&ptrTeteHist,searchReserv);
                        free(searchReserv->u.value_hist);
                        free(searchReserv);
                    }
                }
                reserv = reserv->suivant;
            }
            break;
        case 1:
            searchReserv = (data *) calloc(1, sizeof(data));
            searchReserv->typ_val = HISTORY;
            searchReserv->u.value_reserv = (reservation*)calloc(1, sizeof(reservation));
            searchReserv->u.value_reserv->number = dataSearch;
            ptrTeteHist = rechercheMaillon(reserv, searchReserv)->rent;
            free(searchReserv->u.value_reserv);
            free(searchReserv);
            break;
        default:
            break;
    }
    return ptrTeteHist;
}