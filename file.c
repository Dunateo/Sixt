#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chained_list.h"
#include "file.h"
#include "chaine.h"
#include "initialize.h"


 maintenance* readingMaintenance(char* plateNumber, char * fileName){
     char indiceColonnes[150];
     maintenance* maintenance1 = NULL;
     maintenance* maintenance2 = NULL;
     char *chaineRecup = "";
     int nbCarac = 0;
     char **tabChaineRecup;
     char **dateMaintenace;
     int nb2 = 3;
     int nbSeparator = 0;
     int nbLines = 0;
     int i = 0;

     FILE *f = fopen(fileName, "rt");

     if(f == NULL)
     {
         printf("Impossible to open the file \n" );

     }else {

         //first scan to have the number of lines
         fscanf(f, "%d", &nbLines);
         //take the name of columns
         fscanf(f,"%s",indiceColonnes);
         //reset the char indiceColonnes because we will use it after
         strcat(indiceColonnes,"");

         while (i < nbLines) {
            fscanf(f, "%s", indiceColonnes);
            nbCarac = strlen(indiceColonnes);
            chaineRecup = malloc(sizeof(char) * nbCarac);
            strcpy(chaineRecup, indiceColonnes);
            fonct(chaineRecup, &tabChaineRecup, &nbSeparator, ';');
            i++;
            if(strcmp(plateNumber, tabChaineRecup[0]) == 0){
                 maintenance1 = malloc(sizeof(maintenance));
                 fonct(tabChaineRecup[2], &dateMaintenace, &nb2, '-');
                 maintenance1->date_maintenance.day = atoi(dateMaintenace[0]);
                 maintenance1->date_maintenance.month = atoi(dateMaintenace[1]);
                 maintenance1->date_maintenance.year = atoi(dateMaintenace[2]);
                 maintenance1->date_maintenance.hour = atoi(dateMaintenace[3]);
                 if(strcmp(tabChaineRecup[1], "CT") == 0){
                     maintenance1->type = CT;
                 } else if(strcmp(tabChaineRecup[1], "REVISION") == 0){
                     maintenance1->type = REVISION;
                 } else if(strcmp(tabChaineRecup[1], "REPAIR") == 0){
                     maintenance1->type = REPAIR;
                 } else {
                     printf("ERROR 0x800326xcF");
                 }
                 break;
            }
        }

         while (i < nbLines) {

             //dynamique allocation
             fscanf(f, "%s", indiceColonnes);
             nbCarac = strlen(indiceColonnes);
             chaineRecup = malloc(sizeof(char) * nbCarac);
             strcpy(chaineRecup, indiceColonnes);
             i++;

             //divide the line in tabs
             fonct(chaineRecup, &tabChaineRecup, &nbSeparator, ';');
             if(strcmp(plateNumber, tabChaineRecup[0]) == 0){
                 maintenance2 = malloc(sizeof(maintenance));
                 fonct(tabChaineRecup[2], &dateMaintenace, &nb2, '-');
                 maintenance2->date_maintenance.day = atoi(dateMaintenace[0]);
                 maintenance2->date_maintenance.month = atoi(dateMaintenace[1]);
                 maintenance2->date_maintenance.year = atoi(dateMaintenace[2]);
                 maintenance2->date_maintenance.hour = atoi(dateMaintenace[3]);
                 if(strcmp(tabChaineRecup[1], "CT") == 0){
                     maintenance2->type = CT;
                 } else if(strcmp(tabChaineRecup[1], "REVISION") == 0){
                     maintenance2->type = REVISION;
                 } else if(strcmp(tabChaineRecup[1], "REPAIR") == 0){
                     maintenance2->type = REPAIR;
                 } else {
                     printf("ERROR 0x800326xcF");
                 }
                 insertionMaintenace(&maintenance1, maintenance2);
             }
         }

     }
     return maintenance1;
 }

/**
 * Function to read a file and assign them to a maillon
 * @param char fileName, int typeNum 
 * typeNum is the type of enumeration 
 * @return data*
 */
data *readingData(char indiceColonnes[150], FILE *f, int typeNum, maillon* maillonResearch, char* plateNumber){

    data *data1 = malloc(sizeof(data));
    maillon *link;
    char *chaineRecup = "";
    int nbCarac = 0;
    char **tabChaineRecup;
    int nbSeparator = 0;
        //dynamique allocation
        fscanf(f,"%s",indiceColonnes);
        nbCarac = strlen(indiceColonnes);
        chaineRecup = malloc(sizeof(char)*nbCarac);
        strcpy(chaineRecup,indiceColonnes);

        //divide the line in tabs
        fonct(chaineRecup, &tabChaineRecup, &nbSeparator,';');
          
        switch(typeNum) {
            case 0:

                data1->typ_val = CAR;
                data1->u.value_car = malloc(sizeof(car));
                data1->u.value_car->plate_number = malloc(sizeof(char) * 10);
                data1->u.value_car->brand_name = malloc(sizeof(char) * 10);
                data1->u.value_car->brand_model = malloc(sizeof(char) * 10);

                data1->u.value_car->plate_number = tabChaineRecup[0];
                data1->u.value_car->brand_name = tabChaineRecup[1];
                data1->u.value_car->brand_model = tabChaineRecup[2];

                data1->u.value_car->car_year = atoi(tabChaineRecup[3]);
                data1->u.value_car->km = atoi(tabChaineRecup[4]);
                data1->u.value_car->category = *tabChaineRecup[5];
                data1->u.value_car->price = atoi(tabChaineRecup[6]);
                data1->u.value_car->gearbox = atoi(tabChaineRecup[7])!=0 ;

                data1->u.value_car->car_maint = readingMaintenance(tabChaineRecup[0], "files/maintenances.csv");

                link = initializeHistory("files/booking.csv", maillonResearch, tabChaineRecup[0]);
                data1->u.value_car->history_rent = link->rent->u.value_hist;

                break;
            case 1:

                if(strcmp(plateNumber, tabChaineRecup[5])== 0){
                    data *data2 = malloc(sizeof(data));
                    data1->typ_val = HISTORY;
                    data1->u.value_hist = malloc(sizeof(history));
                    data2->typ_val = RESERVATION;
                    data2->u.value_reserv = malloc(sizeof(reservation));
                    data2->u.value_reserv->number = atoi(tabChaineRecup[0]);
                    link = rechercheMaillon(maillonResearch, data2);
                    data1->u.value_hist->reserv = link->rent->u.value_reserv;
                    free(data2->u.value_reserv);
                    free(data2);
                } else {
                    free(data1);
                    data1 = NULL;
                }


                break;
            case 2:

                data1->typ_val = RESERVATION;
                data1->u.value_reserv = malloc(sizeof(reservation));

                data1->u.value_reserv->number = atoi(tabChaineRecup[0]);

                char** dateTmp; int dateNB = 4;
                fonct(tabChaineRecup[1], &dateTmp, &dateNB,'-');
                data1->u.value_reserv->begining.day = atoi(dateTmp[0]);
                data1->u.value_reserv->begining.month = atoi(dateTmp[1]);
                data1->u.value_reserv->begining.year = atoi(dateTmp[2]);
                data1->u.value_reserv->begining.hour = atoi(dateTmp[3]);

                fonct(tabChaineRecup[2], &dateTmp, &dateNB,'-');
                data1->u.value_reserv->end.day = atoi(dateTmp[0]);
                data1->u.value_reserv->end.month = atoi(dateTmp[1]);
                data1->u.value_reserv->end.year = atoi(dateTmp[2]);
                data1->u.value_reserv->end.hour = atoi(dateTmp[3]);

                data1->u.value_reserv->category = *tabChaineRecup[3];

                data *data2 = malloc(sizeof(data));
                data2->typ_val = CLIENT;
                data2->u.value_client = malloc(sizeof(reservation));
                data2->u.value_client->phone_number = atoi(tabChaineRecup[4]);
                link = rechercheMaillon(maillonResearch,data2);
                data1->u.value_reserv->client_info = link->rent->u.value_client;
                free(data2->u.value_client);
                free(data2);
                break;
            case 3:

                data1->typ_val = CLIENT;
                data1->u.value_client = malloc(sizeof(client));
                data1->u.value_client->client_name = malloc(sizeof(char) * 25);
                data1->u.value_client->driving_license_type = malloc(sizeof(char) * 2);

                data1->u.value_client->client_name = tabChaineRecup[0];
                data1->u.value_client->driving_license_type = tabChaineRecup[1];
                data1->u.value_client->phone_number = atoi(tabChaineRecup[2]);
                break;
            default:
                printf("ERROR ! ENUM TYPE NOT DEFINE\n");
                break;
        }
<<<<<<< HEAD
        
        vehicule->rent->u.value_car = structTab;

        printf("structTab -> Modele : %s\n\n", vehicule->rent->u.value_car->plate_number);

        
        printf("===========\n");
        printf("%s\n", structTab->plate_number);
        printf("%s\n", structTab->brand_name);
        printf("%s\n", structTab->brand_model);
        printf("%d\n", structTab->car_year);
        printf("%d\n", structTab->km);
        printf("%c\n", structTab->category);
        printf("%.2f\n", structTab->price);
        printf("%d\n", structTab->gearbox);
        

    }

    fclose(f);
  }

  return vehicule;
}

/**
int main(void)
{
  //int compteur = 0;

  //maillon
  maillon *ptrTest = NULL;
  ptrTest = readingFile("files/vehicules",0);
  printf("\nMain:\n");
  printf("%s\n", ptrTest->rent->u.value_car->plate_number);
  printf("%s\n", ptrTest->rent->u.value_car->brand_name);
  printf("%s\n", ptrTest->rent->u.value_car->brand_model);
  printf("%d\n", ptrTest->rent->u.value_car->car_year);
  printf("%d\n", ptrTest->rent->u.value_car->km);
  printf("%c\n", ptrTest->rent->u.value_car->category);
  printf("%.2f\n", ptrTest->rent->u.value_car->price);
  printf("%d\n", ptrTest->rent->u.value_car->gearbox);

  return 0;
=======
>>>>>>> origin/master

  return data1;
}
*/