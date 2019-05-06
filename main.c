#include <stdlib.h>
#include <stdio.h>
#include "calculus.h"
#include "chained_list.h"
#include "initialize.h"

int main(int argc, char const *argv[])
{
    maillon *car, *customers, *reservation;
    customers = initializeClients("files/clients.csv");
    reservation = initializeReservation("files/booking.csv", customers);
    car = initializeCar("files/vehicules.csv", reservation);


    float price;
    price = rentalPrice(car->rent, car->rent->u.value_car->history_rent->reserv);
    printf("Rental Price: %f $\n",price);

    int days;
    days = delayTime(car->rent->u.value_car->history_rent->reserv);
    printf("Delayed Days: %d\n", days );
	return 0;
}