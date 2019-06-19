#include <stdlib.h>
#include <stdio.h>
#include "smartFunctions.h"
#include "calculus.h"


/**
 * [searchCar give a car free with the less mileage]
 * @param  ptrtete    [maillon **]
 * @param  Car_reserv [reservation *]
 * @param upgraded    [int *, 0 not upgraded, 1 carUpgraded by +1, 2 carUpgraded by +2, 3 none cars are available]
 * @return            [maillon *]
 */
maillon *searchCar(maillon *ptrtete, reservation* Car_reserv, int *upgraded){
	maillon *ptrtrans = ptrtete;
	maillon *carFound, *carUpgrade, *carUpgrade2;
	carFound = carUpgrade = carUpgrade2 = NULL;
	int i = 0;

	if (ptrtrans->rent->typ_val == CAR){

		//travel int the car chained list
		while(ptrtrans !=  NULL){

			//check if the car is free and if it's a car request
			if (isCarFree(ptrtrans->rent->u.value_car->history_rent) == 0 && Car_reserv->category == ptrtrans->rent->u.value_car->category){

				//check if the mileage is inferior at the carFound before
				if (i > 0 && carFound != NULL && ptrtrans->rent->u.value_car->km < carFound->rent->u.value_car->km){
					carFound = ptrtrans;
				}else if(carFound == NULL){
					carFound = ptrtrans;
				}

				ptrtrans = ptrtrans->suivant;

			}else{

				//upgrading car +1 in case of carFound is NULL
				if(isCarFree(ptrtrans->rent->u.value_car->history_rent) == 0 && Car_reserv->category+1 == ptrtrans->rent->u.value_car->category){

					//check if the mileage is inferior at the carFound before
					if (i > 0 && carUpgrade != NULL && ptrtrans->rent->u.value_car->km < carUpgrade->rent->u.value_car->km){
						carUpgrade = ptrtrans;
					}else if(carUpgrade == NULL){
						carUpgrade = ptrtrans;
					}

				}
				//upgrading car +2 in case of carUpgrade is NULL
				if (isCarFree(ptrtrans->rent->u.value_car->history_rent) == 0 && Car_reserv->category+2 == ptrtrans->rent->u.value_car->category){
						//check if the mileage is inferior at the carFound before
					if (i > 0 && carUpgrade2 != NULL && ptrtrans->rent->u.value_car->km < carUpgrade2->rent->u.value_car->km){
						carUpgrade2 = ptrtrans;
					}else if(carUpgrade2 == NULL){
						carUpgrade2 = ptrtrans;
					}

				}
				ptrtrans = ptrtrans->suivant;
			}
			i++;
		}

	}else{
		printf("It's not a car !\n");
		return 0;
	}


	//return the good car
	if (carFound == NULL){

		*upgraded = 1;
		return carUpgrade;

	}if(carUpgrade == NULL){

		*upgraded = 2;
		return carUpgrade2;

	}if(carUpgrade2 == NULL){

		*upgraded = 3;
		return carFound;

	}else{
		*upgraded = 0;
		return carFound;
	}



}

/**
 * [createTabPrediction create a tab with nbdays and nbKm]
 * @param ptrtete  [Reservation]
 * @param tabRecup [the array to get]
 */
predict *createTabPrediction(maillon *ptrTete, int *compteur){

	//initialize tabRecup
	maillon *ptrtrans = ptrTete;
	predict *tabRecup = malloc(sizeof(predict)*1);
	int cpt =0;


	//check if the ptrtete is reservation
	if (ptrtrans->rent->typ_val == RESERVATION) {


		//assignation des valeurs au tableau tabRecup
		while (ptrtrans != NULL ) {



			tabRecup[cpt].km  = ptrtrans->rent->u.value_reserv->km;
			tabRecup[cpt].jour = calculusDate(ptrtrans->rent->u.value_reserv->begining, ptrtrans->rent->u.value_reserv->end);


			printf("jour: %d\n",tabRecup[cpt].jour);
			printf("Km: %d\n",tabRecup[cpt].km);

			cpt++;
			//realloc to have more space
			tabRecup = realloc(tabRecup, (cpt+1)*sizeof(predict));

			ptrtrans = ptrtrans->suivant;
			printf("%p\n",ptrtrans );
		}
		*compteur = cpt;
		return tabRecup;
	}
}

/**
 * [milePrediction predict mile for a reservation]
 * @param  ptrTete [Reservation]
 * @param  begin   [date begin]
 * @param  end     [date end]
 * @return         [prediction]
 */
int milePrediction(maillon **ptrTete , date begin, date end){

	maillon *ptrtrans = *ptrTete;
	predict *tabVal = NULL;
	int cpt=0, valP=0, n = cpt;

	tabVal = createTabPrediction(ptrtrans,&cpt);
	valP = calculusDate(begin,end);

	//calculus for the km prediction
	for (int i = 0; i < cpt; i++) {

			valP = tabVal[n-i].km + valP;

	}


	return valP;

}
