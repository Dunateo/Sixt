//
// Created by yncrea-hugo on 26/03/19.
//

#ifndef PROJET_CHAINED_LIST_H
#define PROJET_CHAINED_LIST_H

typedef struct date{
    int day;
    int year;
    int month;
    int hour;
}date;

typedef struct client{
    char *client_name;
    char *driving_license_type;
    int phone_number;
}client;

typedef struct maintenance{
    date technical_control;
    date revision;
    date last_reparation;
}maintenance;

typedef struct car{
    char *plate_number;
    char *brand_name;
    char *brand_model;
    int car_year;
    int km;
    char category;
    float price;
    maintenance *car_maint;

}car;

typedef struct reservation{
    int number;
    date begining;
    date end;
    char category;
    client* client_info;

}reservation;

typedef struct history{
    reservation* reserv;
    char *plate_number;
    int number;
}history;

//functions pointers
enum type {CAR,RESERVATION,CLIENT,HISTORY};
typedef struct data{
    enum type typ_val; //indique ce qu'il y a dans u
    union{
        car* value_car;
        history* value_hist;
        reservation* value_reserv;
        client* value_client;
    }u;
}data;


typedef struct maillon{
    data *rent;
    struct maillon *suivant;
}maillon;

#endif //PROJET_CHAINED_LIST_H
