//
// Created by yncrea-hugo on 08/04/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chained_list.h"
#include "file.h"
#include "chaine.h"
#include "initialize.h"


maillon* initializeCar(char* fileName, maillon *reservation)
{

    maillon *ptrTete = malloc(sizeof(maillon));
    data *data1 = NULL;
    int nbLines = 0;
    char indiceColonnes[150];

    //file declaration
    FILE *f = fopen(fileName, "rt");

    if(f == NULL)
    {
        printf("Impossible to open the file \n" );

    }else{

        //first scan to have the number of lines
        fscanf(f, "%d", &nbLines);
        //take the name of columns
        fscanf(f,"%s",indiceColonnes);
        //reset the char indiceColonnes because we will use it after
        strcat(indiceColonnes,"");

        data1 = readingData(indiceColonnes,f,CAR, reservation,NULL);
        ptrTete = creationMaillon(data1);

        //will assign a lign of nb lines
        for(int i=1; i<nbLines; i++)
        {
            insertionValeur(readingData(indiceColonnes,f,CAR, reservation,NULL),&ptrTete);
        }
        fclose(f);
    }
    freeDataInitialize(data1);
    return ptrTete;
}

maillon* initializeClients(char* fileName)
{

    maillon *ptrTete = malloc(sizeof(maillon));
    data *data1 = NULL;
    int nbLines = 0;
    char indiceColonnes[150];

    FILE *f = fopen(fileName, "rt");

    if(f == NULL)
    {
        printf("Impossible to open the file \n" );

    }else{

        //first scan to have the number of lines
        fscanf(f, "%d", &nbLines);
        //take the name of columns
        fscanf(f,"%s",indiceColonnes);
        //reset the char indiceColonnes because we will use it after
        strcat(indiceColonnes,"");

        data1 = readingData(indiceColonnes,f,CLIENT,NULL,NULL);
        ptrTete = creationMaillon(data1);
        freeDataInitialize(data1);
        data1 = NULL;
        //will assign a lign of nb lines
        for(int i=1; i<nbLines; i++)
        {
            data1 = readingData(indiceColonnes,f,CLIENT,NULL,NULL);
            insertionValeur(data1,&ptrTete);
            freeDataInitialize(data1);
            data1 = NULL;
        }
        fclose(f);
    }

    return ptrTete;

}

maillon* initializeReservation(char* fileName, maillon* client)
{

    maillon *ptrTete = malloc(sizeof(maillon));
    data *data1 = NULL;
    int nbLines = 0;
    char indiceColonnes[150];

    FILE *f = fopen(fileName, "rt");

    if(f == NULL)
    {
        printf("Impossible to open the file \n" );

    }else{

        //first scan to have the number of lines
        fscanf(f, "%d", &nbLines);
        //take the name of columns
        fscanf(f,"%s",indiceColonnes);
        //reset the char indiceColonnes because we will use it after
        strcat(indiceColonnes,"");

        data1 = readingData(indiceColonnes,f,RESERVATION,client,NULL);
        ptrTete = creationMaillon(data1);

        //will assign a lign of nb lines
        for(int i=1; i<nbLines; i++)
        {
            insertionValeur(readingData(indiceColonnes,f,RESERVATION,client,NULL),&ptrTete);
        }
        fclose(f);
    }
    freeDataInitialize(data1);
    return ptrTete;

}


data* initializeHistory(char* fileName, maillon* reservation, char *plateNumber){

    data *data1 = NULL;
    int nbLines = 0;
    char indiceColonnes[150];
    int i=0;

    FILE *f = fopen(fileName, "rt");

    if(f == NULL)
    {
        printf("Impossible to open the file \n" );

    }else{

        //first scan to have the number of lines
        fscanf(f, "%d", &nbLines);
        reservationTotal = nbLines;
        //take the name of columns
        fscanf(f,"%s",indiceColonnes);
        //reset the char indiceColonnes because we will use it after
        strcat(indiceColonnes,"");

        while(data1 == NULL){
            data1 = readingData(indiceColonnes,f,HISTORY,reservation, plateNumber);
            i++;
            if(i>=nbLines){
                break;
            }
        }

        //will assign a lign of nb lines
        for(i; i<nbLines; i++)
        {
            insertionSousChaine(&data1,readingData(indiceColonnes,f, MAINTENANCE, NULL, plateNumber));
        }
        fclose(f);
    }
    return data1;
}

data* initializeMaintenance(char* fileName, char *plateNumber)
{
    data *data1 = NULL;
    int nbLines = 0;
    char indiceColonnes[150];
    int i=0;

    //file declaration
    FILE *f = fopen(fileName, "rt");

    if(f == NULL)
    {
        printf("Impossible to open the file \n" );

    }else{

        //first scan to have the number of lines
        fscanf(f, "%d", &nbLines);
        //take the name of columns
        fscanf(f,"%s",indiceColonnes);
        //reset the char indiceColonnes because we will use it after
        strcat(indiceColonnes,"");

        while(data1 == NULL){
            data1 = readingData(indiceColonnes,f,MAINTENANCE, NULL, plateNumber);
            i++;
            if(i>=nbLines){
                break;
            }
        }

        //will assign a lign of nb lines
        for(i; i<nbLines; i++)
        {
            insertionSousChaine(&data1,readingData(indiceColonnes,f, MAINTENANCE, NULL, plateNumber));
        }
        fclose(f);
    }
    return data1;
}

void freeDataInitialize(data* data1){
    switch (data1->typ_val) {
        case 0:
            free(data1->u.value_car->plate_number);
            free(data1->u.value_car->brand_name);
            free(data1->u.value_car->brand_model);
            free(data1->u.value_car);
            break;
        case 1:
            free(data1->u.value_hist);
            break;
        case 2:
            free(data1->u.value_reserv);
            break;
        case 3:
            free(data1->u.value_client->client_name);
            free(data1->u.value_client->driving_license_type);
            free(data1->u.value_client);
            break;
        case 4:
           free(data1->u.value_maintenance = malloc(sizeof(maintenance)));
           break;
    }
    free(data1);
}