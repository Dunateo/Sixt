#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include "calculus.h"
#include "chained_list.h"
#include "initialize.h"





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
