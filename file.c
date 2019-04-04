#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
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
  arith vehicule;
  car structTab;
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

    for(int i=0; i<=nbLines-1; i++)
    {
      nbCarac=nbCaracPerLines(fileNameExt);
      chaineRecup = (char*)malloc(sizeof(char)*nbCarac);
      tabChaineRecup = (char**)malloc(sizeof(char*)*nbSeparator-nbLines);
      if(i<1)
      {
        fseek(f,67, SEEK_SET);
      }
      fscanf(f, "%s", chaineRecup);
      fonct(chaineRecup, &tabChaineRecup, &nbSeparator);
      structTab.plate_number = malloc(sizeof(char)*10);
      structTab.brand_name = malloc(sizeof(char)*10);
      structTab.brand_model = malloc(sizeof(char)*10);
      structTab.category = malloc(sizeof(char)*10);


      structTab.plate_number = tabChaineRecup[0];
      structTab.brand_name = tabChaineRecup[1];
      structTab.brand_model = tabChaineRecup[2];
      structTab.car_year = atoi(tabChaineRecup[3]);
      structTab.km = atoi(tabChaineRecup[4]);
      structTab.category = tabChaineRecup[5];
      structTab.price = atoi(tabChaineRecup[6]);
      structTab.gearbox = atoi(tabChaineRecup[7]);

      vehicule.typ_val = CAR;
      vehicule.u.value_car = structTab;


    printf("%s\n",structTab.plate_number);
    printf("%s\n",structTab.brand_name);
    printf("%s\n",structTab.brand_model);
    printf("%d\n",structTab.car_year);
    printf("%d\n",structTab.km);
    printf("%s\n",structTab.category);
    printf("%.2f\n",structTab.price);
    printf("%d\n",structTab.gearbox);

    }

    fclose(f);
  }

  return 0;
}


int main(void)
{
  int compteur = 0;
  maillon *ptrTest;
  ptrTest = readingFile("vehicules");

}
