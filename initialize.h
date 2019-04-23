//
// Created by yncrea-hugo on 08/04/19.
//

#ifndef PROJECT_INITIALIZE_H
#define PROJECT_INITIALIZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chained_list.h"
#include "file.h"
#include "chaine.h"

maillon* initializeHistory(char* fileName, maillon* reservation, char *plateNumber);

#endif //PROJECT_INITIALIZE_H
