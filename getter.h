//
// Created by hugo on 18/06/19.
//

#ifndef SIXT_GETTER_H
#define SIXT_GETTER_H

#include "chained_list.h"

char* convertDateShow(date date1);
maillon* rechercheReservationJour(date date1, maillon **reservation);
void returnVehicule(maillon* ptrTete,char* plate, int KM);
data* rechercheClient(int dataSearch, int entry, maillon *reserv);

#endif //SIXT_GETTER_H
