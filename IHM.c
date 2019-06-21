#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "IHM.h"
#include "calculus.h"
#include "chained_list.h"
#include "initialize.h"
#include "smartFunctions.h"



/**
 * Fonction qui permet de fermet une fenêtre pop-up
 * @param widget [description]
 * @param window [description]
 */
void closeWindow(GtkWidget *widget, gpointer window)
{
        gtk_widget_hide(GTK_WIDGET(window)); //Cache la fenêtre passée en paramêtre
}

/**
 * Fonction qui permet d'ouvrir une fenêtre en pop-up
 * @param widget [description]
 * @param window [description]
 */
void openWindow(GtkWidget *widget, gpointer window)
{
        gtk_widget_show_all(GTK_WIDGET(window)); //Permet d'afficher la fenêtre
}


void InitVar(variable*var, maillon*ptrTete) {
  var->i = 0;
  var->voiture_det = (char***) malloc(sizeof(char**)*DIM); // Nombre de voiture + 1 (car le nombre de voiture commence a 1)
  for(int j = 0; j<DIM;j++) {
    var->voiture_det[j] = (char**) malloc(sizeof(char*)*11); // Nombre d'attribut
    for(int i = 0; i<11; i++) {
      var->voiture_det[j][i] = (char*) malloc(sizeof(char)*30); // Nombre de caractère
    }
  }
  for(int i=0; i<=11; i++)
  var->label1[i] = NULL;
  var->ptr = ptrTete;
}


void initVoitureDetail(variable*var, GtkBuilder *p_builder) {

  maillon*ptr = var->ptr;
  int i = 1;
  /* Gestion de la liste de révision */
  GtkListStore *list_revision = (GtkListStore * ) gtk_builder_get_object(p_builder, "Car_revision"); //On récup-re la liste de revision


  while(ptr->suivant != NULL ){

    if(ptr->rent->u.value_car->gearbox == true)
      var->voiture_det[i][5] = "Automatic"; // gearbox
    else
      var->voiture_det[i][5] = "Manuel"; // gearbox

    strcpy(var->voiture_det[i][0], ptr->rent->u.value_car->plate_number); //plate number
    sprintf(var->voiture_det[i][1],"%c", ptr->rent->u.value_car->category);  //category
    sprintf(var->voiture_det[i][2],"%d", ptr->rent->u.value_car->km); //km
    strcpy(var->voiture_det[i][3], ptr->rent->u.value_car->brand_name); //brand
    strcpy(var->voiture_det[i][4], ptr->rent->u.value_car->brand_model); // model
    sprintf(var->voiture_det[i][6],"%d",ptr->rent->u.value_car->car_year); // years
    manage_list_revision(list_revision, var->ptr->rent->u.value_car->car_maint);//revision
    sprintf(var->voiture_det[i][8] , "%.f€", dailyPrice(ptr->rent->u.value_car->category)); // daily price
    sprintf(var->voiture_det[i][9] ,"%.f€", sellingCar(ptr->rent)); // selling price
    sprintf(var->voiture_det[i][10] ,"%.f€",ptr->rent->u.value_car->price); // purchase price

    i++;
    ptr = ptr->suivant;

  }
}


void edit_label(GtkWidget*widget, gpointer data) {

  variable*var = data;
  var->i = atoi(gtk_widget_get_tooltip_text(widget)); // pour récuperer la voiture sur laquelle on clique


  // Change le contenu du label

  gtk_label_set_text(GTK_LABEL(var->label1[0]), var->voiture_det[var->i][0]); // Remplace le label plate number
  gtk_label_set_text(GTK_LABEL(var->label1[1]), var->voiture_det[var->i][1]); // Remplace le label category
  gtk_label_set_text(GTK_LABEL(var->label1[2]), var->voiture_det[var->i][2]); // Remplace le label km
  gtk_label_set_text(GTK_LABEL(var->label1[3]), var->voiture_det[var->i][3]); // Remplace le label brand
  gtk_label_set_text(GTK_LABEL(var->label1[4]), var->voiture_det[var->i][4]); // Remplace le label model
  gtk_label_set_text(GTK_LABEL(var->label1[5]), var->voiture_det[var->i][5]); // Remplace le label gearbox
  gtk_label_set_text(GTK_LABEL(var->label1[6]), var->voiture_det[var->i][6]); // Remplace le label years
  //gtk_label_set_text(GTK_LABEL(var->label1[7]), "Revision"); // Remplace le label revision
  gtk_label_set_text(GTK_LABEL(var->label1[8]), var->voiture_det[var->i][8]); // Remplace le label daily
  gtk_label_set_text(GTK_LABEL(var->label1[9]), var->voiture_det[var->i][9]); // Remplace le label selling
  gtk_label_set_text(GTK_LABEL(var->label1[10]), var->voiture_det[var->i][10]); // Remplace le label purchase

}


void attributVehicule(variable*var, GtkBuilder*p_builder) {

  // Attribut le label a son identifiant

  var->label1[0] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_plate_number")); // Initialisation du label plate number dans véhicule
  var->label1[1] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_category")); // Initialisation du label plate number dans véhicule
  var->label1[2] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_km")); // Initialisation du label plate number dans véhicule
  var->label1[3] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_bran")); // Initialisation du label plate number dans véhicule
  var->label1[4] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_mode")); // Initialisation du label plate number dans véhicule
  var->label1[5] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_gearbox")); // Initialisation du label plate number dans véhicule
  var->label1[6] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_years")); // Initialisation du label plate number dans véhicule
  var->label1[7] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_revision")); // Initialisation du label plate number dans véhicule
  var->label1[8] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_daily")); // Initialisation du label plate number dans véhicule
  var->label1[9] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_selling")); // Initialisation du label plate number dans véhicule
  var->label1[10] = GTK_WIDGET(gtk_builder_get_object(p_builder, "car_purchase")); // Initialisation du label plate number dans véhicule

}


void GenerateVehicule(variable*var, GtkBuilder*p_builder, maillon*ptrTete ) {
  GtkWidget*box_car = NULL; // La GtkBox contenant toute les voitures
  GtkWidget*car[DIM]; // Correspond au voiture a afficher, elle est ajouté dans box_car
  GtkWidget*tab[2];// Contient le contenu de GtkBox  de véhicule
  char number[4]; // Recupere le nombre de voiture pour le concaténer
  maillon*ptr = ptrTete;
  char*model_car;
  char*brand_car;
  int i = 1;
  char*cwd;

  cwd = (char*) malloc(sizeof(char)*60);

  cwd = getcwd(cwd, 100);

  box_car = GTK_WIDGET(gtk_builder_get_object(p_builder, "box_car")); // Permet de définir la GtkBox de véhicule

  initVoitureDetail(var, p_builder);

  while(ptr->suivant != NULL){ // Boucle selon le nombre de voiture


    model_car = (char*) malloc(sizeof(char)*(strlen(ptr->rent->u.value_car->brand_model)+1));
    brand_car = (char*) malloc(sizeof(char)*(strlen(ptr->rent->u.value_car->brand_name)+strlen(cwd)+5);
    sprintf(number,"%d",i);

    strcpy(model_car, ptr->rent->u.value_car->brand_model);

    strcpy(brand_car,cwd);
    strcat(brand_car, "/Pictures/");
    strcat(brand_car, ptr->rent->u.value_car->brand_name);
    strcat(brand_car, ".png");


    car[i] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // Param 1 : orientation, param 2 : nb de pixel qui separe les elements


    tab[0] = gtk_image_new_from_file (brand_car); // Initialise le logo de la marque
    tab[1] = gtk_label_new(model_car); // Initialise le modele de voiture
    tab[2] = gtk_button_new_with_label ("Show"); // Initialise le bouton

    gtk_widget_set_tooltip_text(tab[2], number);

    gtk_box_pack_start (GTK_BOX(car[i]),tab[0],TRUE,TRUE,1); // ajoute a la gtkBox le logo
    gtk_box_pack_start (GTK_BOX(car[i]),tab[1],TRUE,TRUE,1); // ajoute a la gtkBox le modele
    gtk_box_pack_start (GTK_BOX(car[i]),tab[2],FALSE,FALSE,0); // ajoute a la gtkBox le bouton

    gtk_container_add(GTK_CONTAINER(box_car), car[i]); // Ajoute toutes les voitures a afficher dans la GtkBox scrollable

    g_signal_connect(G_OBJECT (tab[2]), "clicked", G_CALLBACK(edit_label), var); // vérifie que le clic sur le bouton show fonctionne
    i++;
    ptr = ptr->suivant;

    free(model_car);
    free(brand_car);
    }

}


static void get_combo_box_value(GtkWidget *widget, GtkComboBoxText *combo_box[2])
{
  gchar* return_text[2];
  for(int i=0; i<2; i++)
  {
    return_text[i] = gtk_combo_box_text_get_active_text(combo_box[i]);
    printf("%s\n", return_text[i]);
  }
}
/**
 * Fonction qui permet de récupérer les dates du calendrier lors de l'ajout
 * d'une nouvelle réservation
 *
 * @param widget widget sur lequel on clique
 * @param [calendar] un tableau de deux calendrier correspondant au début et a la fin de la réservation
 */
static void get_calendar_values(GtkWidget *widget, GtkCalendar *calendar[2])
{
        guint year[2]; //On crée un tableau de deux années permettant de stocker le résultat des deux calendriers
        guint month[2]; //On crée un tableau de deux mois permettant de stocker le résultat des deux calendriers
        guint day[2]; //On crée un tableau de deux jours permettant de stocker le résultat des deux calendriers
        printf("DATES DE RESERVATION \n");
        for(int i=0; i<2; i++) //On parcours le tableau de calendrier passé en paramêtre
        {
                gtk_calendar_get_date(calendar[i],&year[i],&month[i],&day[i]); //On récupère les valeurs qui sont stockées dans year, month, day
                printf("%d\n", year[i]);
                printf("%d\n", month[i]+1);
                printf("%d\n", day[i]);
                printf("------------\n");
        }
}

/**
 * Fonction qui gère le contenu de la liste de reservation
 * @param list [description]
 */
static void manage_list_reservation(GtkWidget *widget, clicReservationCalendrier *strucTest)
{
    GtkTreeIter iter; //On crée un itérateur
    maillon *ptrTemp = strucTest->ptrTete;
    gtk_list_store_clear(strucTest->list); //On vide la liste
    bool interA, interB;
    int daysLeft, cptReserv = 0;

    //affectations list avec les réservations qui correspondent au jour cliqué sur le calendrier
    while(ptrTemp != NULL){

        interA = dateCompare(ptrTemp->rent->u.value_reserv->begining, strucTest->press);
        interB = dateCompare(strucTest->press, ptrTemp->rent->u.value_reserv->end);

        if (interA == true && interB == true){
            daysLeft = calculusDate(strucTest->press, ptrTemp->rent->u.value_reserv->end);//caculus date between
            gtk_list_store_append(strucTest->list, &iter); //On crée une nouvelle ligne vide a notre liste
            gtk_list_store_set(strucTest->list, &iter, 0, ptrTemp->rent->u.value_reserv->number, 1, daysLeft ,-1); //Et on l'initailise
            cptReserv++;
        }


        ptrTemp = ptrTemp->suivant;
    }

    //aucune réservation pour cette journée
    if (cptReserv == 0){
        gtk_list_store_append(strucTest->list, &iter); //On crée une nouvelle ligne vide a notre liste
        gtk_list_store_set(strucTest->list, &iter, 0, 0 , 1, 0 ,-1); //Et on l'initailise
    }
}

/**
 * Fonction qui gère le contenu de la liste de reservation
 * @param list [description]
 */
static void manage_list_revision(GtkListStore *list, maintenance *ptrTete)
{
    GtkTreeIter iter; //On crée un itérateur
    char date_maintenance[20];
    while(ptrTete != NULL)
    {
        sprintf(date_maintenance, "%d/%d/%d", ptrTete->date_maintenance.day, ptrTete->date_maintenance.month, ptrTete->date_maintenance.year);
        gtk_list_store_append(list, &iter); //On crée une nouvelle ligne vide a notre liste
        gtk_list_store_set(list, &iter, 0,date_maintenance,-1); //Et on l'intialise
        ptrTete = ptrTete->suivant;
    }
}

/**
 * Fonction qui gère le contenu de la list d'historique
 * @param list [description]
 */
static void manage_list_history(GtkListStore *list, maillon *ptrtete,  int *recupTReserv, int *recupTprice){

  maillon *ptrtrans = ptrtete;
  history *ptrtransH = ptrtete->rent->u.value_car->history_rent;
  maintenance *ptrMaint = ptrtrans->rent->u.value_car->car_maint;
  GtkTreeIter iter; //On crée un itérateur
  gtk_list_store_clear(list); //On vide la liste
  char dateS[25];
  int totalReserv = 0,priceEarn=0, priceCost=0, totalPrice=0;
  bool maintBool;

if (ptrtete->rent->typ_val == CAR) {

    //car while
  while (ptrtrans != NULL) {
    //reservation while
    while (ptrtransH != NULL) {
        //maint while
        priceCost = 0;

        while (ptrMaint!=NULL){
            maintBool = dateCompare(ptrtransH->reserv->end, ptrMaint->date_maintenance);
            if (maintBool == true){
                priceCost = ptrMaint->coast+priceCost;
            }
            ptrMaint = ptrMaint->suivant;
        }

        //dates and price of a reservation
      sprintf(dateS,"%d/%d/%d | %d/%d/%d", ptrtransH->reserv->begining.day, ptrtransH->reserv->begining.month, ptrtransH->reserv->begining.year, ptrtransH->reserv->end.day, ptrtransH->reserv->end.month, ptrtransH->reserv->end.year);
      priceEarn = (int )rentalPrice(ptrtrans->rent, ptrtransH->reserv);

      gtk_list_store_append(list, &iter); //On crée une nouvelle ligne vide a notre liste
      gtk_list_store_set(list, &iter, 0,priceCost,1,priceEarn,2,ptrtrans->rent->u.value_car->plate_number,3,ptrtransH->reserv->km,4,dateS, -1); //Et on l'initialise
      strcpy(dateS, "");
      totalPrice = priceEarn - priceCost +totalPrice;
      ptrtransH = ptrtransH->suivant;
      totalReserv++;
    }

    //change the car
    ptrtrans = ptrtrans->suivant;
    if (ptrtrans != NULL){
        ptrtransH = ptrtrans->rent->u.value_car->history_rent;
        ptrMaint = ptrtrans->rent->u.value_car->car_maint;
    }

  }
  //ressort la chaine de charactères total rserv
   *recupTReserv = totalReserv;
  *recupTprice = totalPrice;

}

}

/**
 * Fonction qui permet de récupérer la valeur des différents champs de formulaire
 * du pop-up "Add Reservation "
 * @param widget [description]
 * @param [name] [description]
 */
static void get_add_reservation_entry(GtkWidget *widget, GtkWidget *entry[3])
{
        const gchar *entry_text[3]; //On crée un tableau de 3 chaines dans lequel sera stocké les valeurs des champs
        printf("INFORMATION CLIENT \n");
        for(int i=0; i<3; i++) //On parcours le tableau d'entry passé en paramêtre
        {
                entry_text[i] = gtk_entry_get_text (GTK_ENTRY (entry[i])); //On récupère la valeur des différents champs
                printf ("Entry contents: %s\n", entry_text[i]);
        }
}

/**
 * Fonction qui permet de récupérer la valeur des différents champs de formulaire
 * du pop-up "Return Vehicule "
 * @param widget [description]
 * @param [name] [description]
 */
static void get_return_form_values( GtkWidget *widget, GtkWidget *entry[2] )
{
        const gchar *entry_text[2]; //On crée un tableau de 2 chaines dans lequel sera stocké les valeurs des champs
        for(int i=0; i<2; i++) //On parcours le tableau d'entry passé en paramètre
        {
                entry_text[i] = gtk_entry_get_text (GTK_ENTRY (entry[i])); //On récupère la valeur des différents champs parcourus
                printf ("Entry contents: %s\n", entry_text[i]);
        }
}

/**
 * Fonction qui permet de récupérer la valeur des différents champs de formulaire
 * de notre pop-up "Search Client"
 * @param widget [description]
 * @param [name] [description]
 */
static void get_search_client_form_values( GtkWidget *widget, GtkWidget *entry[2] )
{
        const gchar *entry_text[2]; //On crée un tableau de 2 chaines dans lequel sera stocké les valeurs des champs
        for(int i=0; i<2; i++) //On parcours le tableau d'entry passé en parmètre
        {
                entry_text[i] = gtk_entry_get_text (GTK_ENTRY (entry[i]));
                printf ("Entry contents: %s\n", entry_text[i]);
        }
}



int main (int argc, char ** argv)
{
        GtkBuilder  *  p_builder   = NULL;
        GError      *  p_err       = NULL;

        GObject *button_sell_car;

        //initialisation des maillon
        maillon *car, *customers, *reservation, *resultcar;
        customers = initializeClients("files/clients.csv");
        reservation = initializeReservation("files/booking.csv", customers);
        car = initializeCar("files/vehicules.csv", reservation);
        variable*var; // Structure affichant les details de chaque voiture
        //test console
        int prediction;
        date d,e;
        d.day = 3;
        d.year = 2019;
        d.month = 10;
        d.hour = 9;

        e.day = 23;
        e.year = 2019;
        e.month = 10;
        e.hour = 9;
        prediction = milePrediction(&reservation , d, e);
        int h;
        h = calculusDate(d,e);
        printf("Prediction %d pour %d jours \n", prediction ,h);

        /* Variables pour la fenetre de retour vehicule */
        char returnFormEntry[20];
        GtkEntry *return_form[2];
        GObject *button_return_vehicule;
        GObject *button_validate_return_vehicule;
        GObject *button_cancel_return_vehicule;
        GObject *reservation_list_return_button;
        GtkComboBoxText *reservation_dropdown[2];
        char comboBox_id[30];

        /* Variables pour l'ajout de réservation */
        char addReservationFormEntry[30];
        GtkEntry *addReservation_form[3];
        GObject *button_validate_add_reservation;
        GObject *button_cancel_add_reservation;
        GObject *button_add_reservation;
        GObject *button_search_reservation;


        /* Variables pour la recherche de client */
        char searchFormEntry[20];
        GtkEntry *search_form[2];
        GObject *button_validate_search_client;
        GObject *button_search_stop;

        /* Variables pour le calendrier principal */
        GObject *calendar[31];
        char joursCalendrier[20];
        GtkComboBoxText *date_changer[2];
        char char_date_changer[20];
        GObject *button_validate_date_changer;


        /* Variables pour le calendrier de réservation*/
        GtkCalendar *calendar_reservation[2];
        char calendar_reservation_name[25];

        char compteur[20];

        var = (variable*) malloc(sizeof(variable));


        /* Initialisation de GTK+ */
        gtk_init (&argc, &argv);

        /* Creation d'un nouveau GtkBuilder */
        p_builder = gtk_builder_new ();

        if (p_builder != NULL)
        {
                /* Chargement du XML dans p_builder */
                gtk_builder_add_from_file (p_builder, "IHM.glade", &p_err);

                if (p_err == NULL)
                {
                        /* Permet d'intialiser le pop_up d'ajout de réservation */
                        GtkWidget * pop_up_reservation_add = (GtkWidget *) gtk_builder_get_object (
                                p_builder, "reservation-add"
                                );
                        /* Permet d'initailiser le pop_up de recherche client*/
                        GtkWidget * pop_up_client_search = (GtkWidget *) gtk_builder_get_object (
                                p_builder, "client_search"
                                );

                        /* Permet d'initailiser la fenêtre principale du projet */
                        GtkWidget * main_win = (GtkWidget *) gtk_builder_get_object (
                                p_builder, "PROJET"
                                );

                        /* Permet d'initailiser la fenetre d'affichage des réservation pour les différents jours */
                        GtkWidget * reservation_list_window = (GtkWidget *) gtk_builder_get_object (
                                p_builder, "reservation_list_window"
                                );

                        /* Permet d'initailiser la fenetre de retour vehicule */
                        GtkWidget * return_vehicule = (GtkWidget * ) gtk_builder_get_object (
                                p_builder, "return_vehicule"
                                );



                        InitVar(var, car);

                        GenerateVehicule(var,p_builder, car);

                        attributVehicule(var,p_builder);
                        /* Permet d'initialiser les différents entryForm de notre fenetre
                           de retour vehicule, d'intialiser le bouton de validation et de faire
                           appel a la fonction correspondante */
                        for(int j=0; j<2; j++)
                        {
                                sprintf(compteur, "%d",j); //on crée une chaine de caractère contenant le compteur
                                strcpy(returnFormEntry, "return_form"); //on concatène les deux chaines
                                strcat(returnFormEntry, compteur); //on concatène les deux chaines
                                return_form[j]=(GtkEntry*)gtk_builder_get_object(p_builder, returnFormEntry); //on récupère les entryform de Glade
                        }
                        button_validate_return_vehicule = gtk_builder_get_object(p_builder, "return_validate_button"); //On initialise le boutton de validation
                        g_signal_connect(button_validate_return_vehicule, "clicked", G_CALLBACK(get_return_form_values), return_form); //on appelle la fonction au clic


                        /* Permet d'initialiser les différents entryForm de notre fenetre
                           de retour de réservation ainsi que les calendriers de réservation,
                           d'intialiser le bouton de validation et de faire appel a la fonction
                           correspondante */
                        for(int x=0; x<3; x++)
                        {
                                sprintf(compteur, "%d", x); //on crée une chaine de caractère contenant le compteur
                                strcpy(addReservationFormEntry, "add_reserv_entry"); //on concatène les deux chaines
                                strcat(addReservationFormEntry, compteur); //on concatène les deux chaines
                                addReservation_form[x] = (GtkEntry*)gtk_builder_get_object(p_builder, addReservationFormEntry); //on récupère les entryform de Glade
                        }
                        for(int w=0; w<2; w++)
                        {
                                sprintf(compteur, "%d",w); //on crée une chaine de caractère contenant le compteur
                                strcpy(calendar_reservation_name, "calendar_reservation"); //on concatène les deux chaines
                                strcat(calendar_reservation_name, compteur); //on concatène les deux chaines
                                calendar_reservation[w]=(GtkCalendar*)gtk_builder_get_object(p_builder, calendar_reservation_name); //on récupère les entryform de Glade

                                strcpy(comboBox_id, "reservation_add_dropdown"); //On crée une chaine de caractère contenant le compteur
                                strcat(comboBox_id, compteur); //On concatène la chaine avec le compteur
                                reservation_dropdown[w]=(GtkComboBoxText*)gtk_builder_get_object(p_builder, comboBox_id); //on récupère le combo_box

                                strcpy(char_date_changer, "date_changer"); //On crée une chane de caractère contenant le compteur
                                strcat(char_date_changer, compteur); //On concatène la chaine avec le compteur
                                date_changer[w] = (GtkComboBoxText*)gtk_builder_get_object(p_builder, char_date_changer); //on récupère le combo_box
                        }

                        button_validate_add_reservation = gtk_builder_get_object(p_builder, "add_reservation_validate_button"); //On initialise le boutton de validation
                        g_signal_connect (button_validate_add_reservation, "clicked", G_CALLBACK(get_add_reservation_entry), addReservation_form); //on appelle la fonction des entryForm au clic
                        g_signal_connect (button_validate_add_reservation, "clicked", G_CALLBACK (get_combo_box_value),reservation_dropdown); //on appelle la fonction de calendrier au clic
                        g_signal_connect (button_validate_add_reservation, "clicked", G_CALLBACK (get_calendar_values),calendar_reservation); //on appelle la fonction de calendrier au clic


                        button_validate_date_changer = gtk_builder_get_object(p_builder, "validate_date_changer"); //On initialise le boutton de validation
                        g_signal_connect(button_validate_date_changer, "clicked", G_CALLBACK(get_combo_box_value), date_changer); //On appelle la fonction de récupération de combo_box lors du clic souris


                        /* Permet d'initialiser les différents entryForm de notre fenetre
                           de recherche client d'intialiser le bouton de validation et de faire
                           appel a la fonction correspondante */
                        for(int z=0; z<2; z++)
                        {
                                sprintf(compteur, "%d", z); //on crée une chaine de caractère contenant le compteur
                                strcpy(searchFormEntry, "search_entry"); //on concatène les deux chaines
                                strcat(searchFormEntry, compteur); //on concatène les deux chaines
                                search_form[z] = (GtkEntry*)gtk_builder_get_object(p_builder, searchFormEntry); //on récupère les entryform de Glade
                        }
                        button_validate_search_client = gtk_builder_get_object(p_builder, "search_client_validate_button"); //On intialise le bouton de validation
                        g_signal_connect(button_validate_search_client, "clicked", G_CALLBACK(get_search_client_form_values), search_form); //On appelle la fonction au clic sur le bouton


                        /* Gestion des boutons */
                        button_cancel_add_reservation = gtk_builder_get_object(p_builder, "add_reservation_cancel_butto"); //Récupération du bouton d'annulation d'ajout de réservation
                        g_signal_connect (button_cancel_add_reservation, "clicked", G_CALLBACK (closeWindow), G_OBJECT(pop_up_reservation_add)); //On y associe la fonction de fermeture de fenetre

                        button_search_stop = gtk_builder_get_object(p_builder, "search_client_cancel_button"); //Récupération du bouton d'anulation de la recherche client
                        g_signal_connect(button_search_stop, "clicked", G_CALLBACK(closeWindow), G_OBJECT(pop_up_client_search)); //On y associe la fonction de fermeture de fenetre

                        button_sell_car = gtk_builder_get_object(p_builder, "sell_car_button");
                        g_signal_connect(button_sell_car, "clicked", G_CALLBACK(closeWindow), G_OBJECT(button_sell_car));

                        button_cancel_return_vehicule = gtk_builder_get_object(p_builder, "return_cancel_button"); //Récupération du bouton d'annulation de retour véhicule
                        g_signal_connect(button_cancel_return_vehicule, "clicked", G_CALLBACK(closeWindow), G_OBJECT(return_vehicule)); //On y associe la fonction de fermeture de fenêtre

                        g_signal_connect(main_win, "delete_event", gtk_main_quit, NULL); //Ferme le programme lorsqu'on clique la croix en haut à droite

                        button_add_reservation = gtk_builder_get_object(p_builder, "add_reservation_button"); //Récupération du bouton d'ajout de résérvation
                        g_signal_connect(button_add_reservation, "clicked", G_CALLBACK(openWindow), G_OBJECT(pop_up_reservation_add)); //On y associe la fonction d'ouverture du pop-up d'ajout de réservation

                        button_search_reservation = gtk_builder_get_object(p_builder, "search_reservation_button"); //Récupération du bouton de recherche client
                        g_signal_connect(button_search_reservation, "clicked", G_CALLBACK(openWindow), G_OBJECT(pop_up_client_search)); //On y associe la fonction d'ouverture de la pop-up de recherche client

                        button_return_vehicule = gtk_builder_get_object(p_builder, "return_vehicule_button"); //Récupération du bouton de renvoi de véhicule
                        g_signal_connect(button_return_vehicule, "clicked", G_CALLBACK(openWindow), G_OBJECT(return_vehicule)); //On y associe la fonction d'ouverture de la pop-up de retour véhicule

                        reservation_list_return_button = gtk_builder_get_object(p_builder, "reservation_list_return_button"); //Récupération du bouton de retour dans pop_up de liste reservation
                        g_signal_connect(reservation_list_return_button, "clicked", G_CALLBACK(closeWindow), G_OBJECT(reservation_list_window)); //On y associe la fonction de fermeture fenetre lors du clic



                        /* Gestion de la liste de reservation */
                        GtkListStore *list_reservation = (GtkListStore *) gtk_builder_get_object(p_builder, "reservation_lists"); //On récupère la liste reservation_lists

                        /* Gestion de la liste d'historique des reservations */
                        int RecupT , RecupP;
                        GtkListStore *list_price_history = (GtkListStore *) gtk_builder_get_object(p_builder, "price_history"); //On récupère la liste d'historique
                        manage_list_history(list_price_history, car,&RecupT, &RecupP);
                        printf("Price: %d\n", RecupP);
                        printf("Reserv: %d\n", RecupT);





                    clicReservationCalendrier structTest;
                    structTest.list = list_reservation;
                    //structTest->ptrTete = NULL;
                    structTest.ptrTete = reservation;
                    structTest.press.day = 3;
                    structTest.press.month = 9;
                    structTest.press.year = 2019;
                    structTest.press.hour = 9;
                    /* Boucle for qui permet d'intialiser des boutons clicables pour chaque case de notre
                    calendrier */
                    for(int i=1; i<=31; i++)
                    {
                        sprintf(compteur, "%d",i); //on crée une chaine de caractère contenant le compteur
                        strcpy(joursCalendrier, "day"); //on concatène les deux chaines
                        strcat(joursCalendrier, compteur); //on concatène les deux chaines
                        calendar[i]=gtk_builder_get_object(p_builder, joursCalendrier); //Pour chaque case, on récupère le bouton glade correspondant
                        g_signal_connect(calendar[i], "clicked", G_CALLBACK(openWindow), G_OBJECT(reservation_list_window)); //On y associe la fonction d'ouverture
                        g_signal_connect(calendar[i], "clicked", G_CALLBACK(&manage_list_reservation), &structTest);
                    }


                        /* Affichage des fenêtres */
                        gtk_widget_show_all(main_win);

                        gtk_main ();
                }
                else
                {
                        /* Affichage du message d'erreur de GTK+ */
                        g_error ("%s", p_err->message);
                        g_error_free (p_err);
                }
        }


        return EXIT_SUCCESS;
}
