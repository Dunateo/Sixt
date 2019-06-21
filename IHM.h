#include <gtk/gtk.h>
#include "chained_list.h"


typedef struct clicReservationCalendrier{
    GtkListStore *list;
    maillon *ptrTete;
    date clicJour;
}clicReservationCalendrier;

typedef struct getJourCalendrier{
  GtkComboBoxText *dropdown[2];
  date clicJour;
}getJourCalendrier;

void closeWindow(GtkWidget *widget, gpointer window);
void openWindow(GtkWidget *widget, gpointer window);
static void get_combo_box_value(GtkWidget *widget, GtkComboBoxText *combo_box[2]);
static void get_calendar_values(GtkWidget *widget, GtkCalendar *calendar[2]);
static void manage_list_reservation(GtkWidget *widget, clicReservationCalendrier *strucTest);
static void manage_list_revision(GtkListStore *list, maintenance *ptrTete);
static void manage_list_history(GtkListStore *list, maillon *ptrtete);
static void get_add_reservation_entry(GtkWidget *widget, GtkWidget *entry[3]);
static void get_return_form_values( GtkWidget *widget, GtkWidget *entry[2]);
static void get_search_client_form_values( GtkWidget *widget, GtkWidget *entry[2]);
int main_ihm (int argc, char ** argv);
