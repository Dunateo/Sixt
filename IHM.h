#include <gtk/gtk.h>
#include "chained_list.h"
#define DIM 100


typedef struct clicReservationCalendrier{
    GtkListStore *list;
    maillon *ptrTete;
    date press;
}clicReservationCalendrier;

typedef struct variable {
  char***voiture_det;
  GtkWidget*label1[11];
  int i;
  maillon*ptr;
}variable;

void closeWindow(GtkWidget *widget, gpointer window);
void openWindow(GtkWidget *widget, gpointer window);
static void get_combo_box_value(GtkWidget *widget, GtkComboBoxText *combo_box[2]);
static void get_calendar_values(GtkWidget *widget, GtkCalendar *calendar[2]);
static void manage_list_reservation(GtkWidget *widget, clicReservationCalendrier *strucTest);
static void manage_list_revision(GtkListStore *list, maintenance *ptrTete);
static void manage_list_history(GtkListStore *list, maillon *ptrtete, int *recupTReserv, int *recupTprice);
static void get_add_reservation_entry(GtkWidget *widget, GtkWidget *entry[3]);
static void get_return_form_values( GtkWidget *widget, GtkWidget *entry[2]);
static void get_search_client_form_values( GtkWidget *widget, GtkWidget *entry[2]);
int main_ihm (int argc, char ** argv);
void InitVar(variable*var, maillon*ptrTete);
void initVoitureDetail(variable*var, GtkBuilder *p_builder);
void edit_label(GtkWidget*widget, gpointer data) ;
void attributVehicule(variable*var, GtkBuilder*p_builder);
void GenerateVehicule(variable*var, GtkBuilder*p_builder, maillon*ptrTete );
