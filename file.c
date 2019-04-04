#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chained_list.h"
#include "chaine.h"





int nbCaracPerLines(char *fileNameExt)
{
  int nbCarac = 0;
  FILE *f = fopen(fileNameExt, "rt");
  if(f == NULL)
  {
    printf("Impossible to open the file \n" );
  }
  else
  {
    while(fgetc(f) != '\n')
    {
      nbCarac++;
    }
  }
  return nbCarac;
}

int calculateNumberOfSeparator(char *fileNameExt)
{
  int nbCarac = 0;
  FILE *f = fopen(fileNameExt, "rt");
  if(f == NULL)
  {
    printf("Impossible to open the file \n" );
  }
  else
  {
    while(fgetc(f) != '\n')
    {
      if(fgetc(f) == ';')
      {
          nbCarac++;
      }
    }
  }
    return nbCarac;

}


maillon* readingFile(char *fileName)
{
  maillon *vehicule;
  car* structTab;
  char indiceColonnes[150];
  char *fileNameExt= " ";
  char *chaineRecup = "";
  char **tabChaineRecup;
  int fileNameLenght = strlen(fileName);
  int nbLines = 0;
  int nbCarac = 0;
  int nbSeparator = 0;
  fileNameExt = (char*)malloc(sizeof(char)*fileNameLenght);
  strcat(fileNameExt, fileName);
  strcat(fileNameExt, ".csv");
  FILE *f = fopen(fileNameExt, "rt");
  if(f == NULL)
  {
    printf("Impossible to open the file \n" );
  }
  else
  {
    fscanf(f, "%d", &nbLines);
    fscanf(f,"%s",indiceColonnes);
    strcat(indiceColonnes,"");
    for(int i=0; i<=nbLines-1; i++)
    {
        fscanf(f,"%s",indiceColonnes);
        nbCarac = strlen(indiceColonnes);
        chaineRecup = malloc(sizeof(char)*nbCarac);
        strcpy(chaineRecup,indiceColonnes);
        fonct(chaineRecup, &tabChaineRecup, &nbSeparator,';');

        printf("\nModele : %s\n", tabChaineRecup[2]);

        structTab->plate_number = malloc(sizeof(char) * 10);
        structTab->brand_name = malloc(sizeof(char) * 10);
        structTab->brand_model = malloc(sizeof(char) * 10);



        structTab->plate_number = tabChaineRecup[0];
        structTab->brand_name = tabChaineRecup[1];
        structTab->brand_model = tabChaineRecup[2];



        structTab->car_year = atoi(tabChaineRecup[3]);
        structTab->km = atoi(tabChaineRecup[4]);
        structTab->category = *tabChaineRecup[5];
        structTab->price = atoi(tabChaineRecup[6]);
        structTab->gearbox = (tabChaineRecup[7]);

        vehicule->rent->typ_val = CAR;
        vehicule->rent->u.value_car = structTab;

        printf("structTab -> Modele : %s\n\n", vehicule->rent->u.value_car->brand_model);

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


int main(void)
{
  int compteur = 0;
  maillon *ptrTest;
  ptrTest = readingFile("vehicules");

}
