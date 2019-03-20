
/*
Car structure that list all the informations concerning the car.
*/
typedef struct car{
	char *plate_number;
	char *brand_name;
	char *brand_model;
	int car_year;
	int km;
	char category;
	float price;
  bool gearbox;
	maintenance *car_maint;

}car;

/*
Basic date structure
*/
typedef struct date{
	int day;
	int year;
	int month;
	int hour;
}date;

/*
Reservation strucutre that list all the informations concerning the
reservation of each car. (Reservation number, dates, ...)
*/
typedef struct reservation{
	int number;
	date begining;
	date end;
	char category;
	client client_info;
}reservation;

/*
Client strucutre which allows us to have informations about the client who
reserved a vehicule.
*/
typedef struct client{
	char *client_name;
	char *driving_license_type;
	int phone_number;
}client;


/*
History structure that is used to list all the reservations concerning a specific
vehicule
*/
typedef struct history{
	reservation reserv;
	char *plate_number;
	int number;
}history;

/*
Maintenance structure that list all the date of the different maintenance that
have been done on the vehicule
*/
typedef struct maintenance{
	date technical_control;
	date revision;
	date last_reparation;
}maintenance;


//enumeration that we use for our pointed functions
enum type {CAR,RESERVATION,CLIENT,HISTORY};

/*
*/
typedef struct arith{
  enum type typ_val; //indique ce qu'il y a dans u
  union{
    car value_car;
    history value_hist;
		reservation value_reserv;
		client value_client;
  }u;
}arith;

/*
Maillons structure that allows us to create a chained list according to what
the arith structure contains.
*/
typedef struct maillon{
  arith *data;
  struct maillon *suivant;
}maillon;
