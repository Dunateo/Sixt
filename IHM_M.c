#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "calculus.h"
#include "chained_list.h"
#include "initialize.h"
#define DIM 100


typedef struct variable {
  char***voiture_det;
  GtkWidget*label1[11];
  int i;
  maillon*ptr;
}variable;

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


static void cb_ok (GtkWidget * p_wid, gpointer p_data)
{
  GtkWidget   * p_dialog  = NULL;
  const char  * p_text    = p_data;


  if (p_text != NULL)
  {
    p_dialog = gtk_message_dialog_new (
      NULL,
      GTK_DIALOG_MODAL,
      GTK_MESSAGE_INFO,
      GTK_BUTTONS_OK,
      p_text
    );


    gtk_dialog_run (GTK_DIALOG (p_dialog));
    gtk_widget_destroy (p_dialog);
  }
}


static void cb_quit (GtkWidget * p_wid, gpointer p_data)
{
  gtk_main_quit ();
}


void print_hello(GtkWidget*widget, gpointer data) {

  variable*var = data;
  var->i = atoi(gtk_widget_get_tooltip_text(widget)); // pour récuperer la voiture sur laquelle on clique
}

void initVoitureDetail(variable*var) {

  maillon*ptr = var->ptr;
  int i = 1;

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
    //var->voiture_det[i][7] = "plate"; // revision
    sprintf(var->voiture_det[i][8] , "%.f€", dailyPrice(ptr->rent->u.value_car->category)); // daily price
    sprintf(var->voiture_det[i][9] ,"%.f€", sellingCar(ptr->rent)); // selling price
    sprintf(var->voiture_det[i][10] ,"%.f€",ptr->rent->u.value_car->price); // purchase price

    i++;
    ptr = ptr->suivant;

  }
}

void edit_label(GtkWidget*widget, gpointer data) {

  variable*var = data;
  maillon*ptr = var->ptr;
  var->i = atoi(gtk_widget_get_tooltip_text(widget)); // pour récuperer la voiture sur laquelle on clique

  // Contient les attributs






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

  initVoitureDetail(var);

  while(ptr->suivant != NULL){ // Boucle selon le nombre de voiture


    model_car = (char*) malloc(sizeof(char)*(strlen(ptr->rent->u.value_car->brand_model)+1));
    brand_car = (char*) malloc(sizeof(char)*(strlen(ptr->rent->u.value_car->brand_name)+55));
    sprintf(number,"%d",i);

    strcpy(model_car, ptr->rent->u.value_car->brand_model);

    strcpy(brand_car,cwd);
    strcat(brand_car, "/Pictures/");
    strcat(brand_car, ptr->rent->u.value_car->brand_name);
    strcat(brand_car, ".png");








    /*  printf("\n\n\n%s\n\n", brand_car);*/

    car[i] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // Param 1 : orientation, param 2 : nb de pixel qui separe les elements


    tab[0] = gtk_image_new_from_file (brand_car); // Initialise le logo de la marque
    tab[1] = gtk_label_new(model_car); // Initialise le modele de voiture
    tab[2] = gtk_button_new_with_label ("Show"); // Initialise le bouton

    gtk_widget_set_tooltip_text(tab[2], number);

    gtk_box_pack_start (GTK_BOX(car[i]),tab[0],TRUE,TRUE,1); // ajoute a la gtkBox le logo
    gtk_box_pack_start (GTK_BOX(car[i]),tab[1],TRUE,TRUE,1); // ajoute a la gtkBox le modele
    gtk_box_pack_start (GTK_BOX(car[i]),tab[2],FALSE,FALSE,0); // ajoute a la gtkBox le bouton

    gtk_container_add(GTK_CONTAINER(box_car), car[i]); // Ajoute toutes les voitures a afficher dans la GtkBox scrollable

    g_signal_connect(G_OBJECT (tab[2]), "clicked", G_CALLBACK(print_hello), var); // vérifie que le clic sur le bouton show fonctionne
    g_signal_connect(G_OBJECT (tab[2]), "clicked", G_CALLBACK(edit_label), var); // vérifie que le clic sur le bouton show fonctionne
    i++;
    ptr = ptr->suivant;

    free(model_car);
    free(brand_car);
    }

}


int main (int argc, char ** argv)
{
  GtkBuilder  *  p_builder   = NULL;
  GError      *  p_err       = NULL;

  variable*var; // Structure affichant les details de chaque voiture
  maillon*ptrCar;
  maillon*ptrClient;
  maillon*ptrReservation;

  /* Initialisation de GTK+ */
  gtk_init (& argc, & argv);

  /* Creation d'un nouveau GtkBuilder */
  p_builder = gtk_builder_new ();


  if (p_builder != NULL)
  {

    /* Chargement du XML dans p_builder */
    gtk_builder_add_from_file (p_builder, "IHM.glade", & p_err);

    var = (variable*) malloc(sizeof(variable));

    ptrClient = initializeClients("files/clients.csv");
    ptrReservation = initializeReservation("files/booking.csv", ptrClient);
    ptrCar = initializeCar("files/vehicules.csv", ptrReservation);

    InitVar(var, ptrCar);

    GenerateVehicule(var,p_builder, ptrCar);

    attributVehicule(var,p_builder);


    if (p_err == NULL)
    {
      /* 1.- Recuparation d'un pointeur sur la fenetre. */
      GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
        p_builder, "PROJET"
      );


      gtk_widget_show_all (p_win);
      gtk_main ();

    }
    else
    {
      /* Affichage du message d'erreur de GTK+ */
      g_error ("%s", p_err->message);
      g_error_free (p_err);
    }
  }

  printf("Fermeture de la fenetre.\n");
  gtk_main_quit();
  return EXIT_SUCCESS;
}
