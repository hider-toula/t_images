#ifndef GUIMPE_CALLBACK
#define GUIMPE_CALLBACK

void OnExpose(GtkWidget* widget, gpointer data);

void OnOuvrir(GtkWidget* widget, gpointer data);
void OnEnregistrer(GtkWidget* widget, gpointer data);
void OnEnregSous(GtkWidget* widget, gpointer data);
void OnFermer(GtkWidget* widget, gpointer data);
void OnQuitter(GtkWidget* widget, gpointer data);
void OnAbout(GtkWidget* widget, gpointer data);

void OnAnnuler(GtkWidget* widget, gpointer data);
void OnRetablir(GtkWidget* widget, gpointer data);

void OnNegatif(GtkWidget* widget, gpointer data);
void OnRotation(GtkWidget* widget, gpointer data);
void OnLuminosite(GtkWidget* widget, gpointer data);
void OnBruiter(GtkWidget* widget, gpointer data);
void OnFiltrer(GtkWidget* widget, gpointer data);
void OnMedian(GtkWidget* widget, gpointer data);

// gestion de la pile image
void free_images();

#endif
