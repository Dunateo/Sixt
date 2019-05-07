#include "chained_list.h"

float sellingCar(data *val);
float checkRentPrice(float constClass, int nbday);
int calculusDate(date begining, date end);
int delayTime(reservation *Car_reserv);
float rentalPrice(data *val, reservation *Car_reserv);
int isCarFree(history **ptrtete);
date actualDate();
maillon *searchCar(maillon **ptrtete, reservation* Car_reserv, int *upgraded);