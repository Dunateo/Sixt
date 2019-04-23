#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include "calculus.h"
#include "chained_list.h"

/**
 * [isCarFree Check if the Car is free to rent]
 * @param  ptrtete [maillon **]
 * @return int     [0 CAR FREE, 1 CAR NOT FREE, 2 NOT A CAR]
 */
int isCarFree(maillon **ptrtete){

	if(*(ptrtete->rent->type_val) == 0){




	}
	else{
		printf("It's not a car!\n");
		return 2;

	}
}

float rentalPrice(data *val, reservation Car_reserv){
	float price;
	struct tm begin,end;
	begin.tm_mday = Car_reserv.begining.day;
	begin.tm_mon = 
	begin.tm_hour = 
	begin.tm_year =
		

	if(*(ptrtete->rent->type_val) == 0){


		switch(val->value_car->category){
			case 'A':

			break;
			case 'B':
			break;
			case 'C':
			break;

		}

	}
	else{
		printf("It's not a car!\n");
		return 0;

	}	

	return price;
}

/**
 * [sellingCar give a price for selling a car]
 * @param  val [take a data]
 * @return int [price of a car]
 */
float sellingCar(data *val){
	float prix = 0;
	int annee;
	//time
	time_t t; 
	time(&t);

	if (val->type_val == 0)
	{	

		annee = t.tm_year - val->value_car->car_year;

		switch(val->value_car->category){

			case 'A':

					if (annee == 1){
						prix = val->value_car->price - (val->value_car->price*30)/100;

					}else if (annee == 2 && annee == 3){

						prix = val->value_car->price - (val->value_car->price*15)/100;

					}else if (annee >= 3 && annee < 11){

						prix = val->value_car->price - (val->value_car->price*(12-annee))/100;
					}
					else if (annee >= 11){

						prix = val->value_car->price - (val->value_car->price*(2))/100;

					}
				
			break;

			case 'B':
				if (annee == 1){
						prix = val->value_car->price - (val->value_car->price*25)/100;

					}else if (annee == 2 && annee == 3){

						prix = val->value_car->price - (val->value_car->price*15)/100;

					}else if (annee >= 3 && annee < 11){

						prix = val->value_car->price - (val->value_car->price*(12-annee))/100;
					}
					else if (annee >= 11){

						prix = val->value_car->price - (val->value_car->price*(2))/100;

					}
			break;

			case 'C':
				if (annee == 1){
						prix = val->value_car->price - (val->value_car->price*20)/100;

					}else if (annee == 2 && annee == 3){

						prix = val->value_car->price - (val->value_car->price*15)/100;

					}else if (annee >= 3 && annee < 11){

						prix = val->value_car->price - (val->value_car->price*(12-annee))/100;
					}
					else if (annee >= 11){

						prix = val->value_car->price - (val->value_car->price*(2))/100;

					}
			break;

		}

		return prix;

	}else{
		printf("It's not a car!\n");
		return 0;
	}

}