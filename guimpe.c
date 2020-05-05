#include <stdlib.h>
#include <gtk/gtk.h>

#include "guimpe_callback.h"
#include "pile_image.h"

GtkWidget *pLabel_Nomf;
GtkWidget *pLabel_Res;
GtkWidget *pDA;

int main(int argc, char **argv)
{
	GtkWidget *pWindow;
	GtkWidget *pVBox;
	GtkWidget *pHBox;
	GtkWidget *pMenuBar;
	GtkWidget *pMenu;
	GtkWidget *pMenuItem;
	GtkWidget *pSeparator;

	gtk_init(&argc, &argv);

	/* Creation de la fenetre */
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pWindow), "guimpe");
	gtk_window_set_default_size(GTK_WINDOW(pWindow), -1, -1);
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Creation de la GtkVBox */
	pVBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

	/**** Creation du menu ****/

	/* ETAPE 1 */
	pMenuBar = gtk_menu_bar_new();
	/** Premier sous-menu **/
	/* ETAPE 2 */
	pMenu = gtk_menu_new();
	/* ETAPE 3 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("_Ouvrir");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnOuvrir), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Enregistrer");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnEnregistrer), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("Enregistrer _Sous");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnEnregSous), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Fermer");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnFermer), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pSeparator = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pSeparator);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Quitter");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnQuitter), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	/* ETAPE 4 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("_Fichier");
	/* ETAPE 5 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
	/* ETAPE 6 */
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/** Second sous-menu **/
	/* ETAPE 2 */
	pMenu = gtk_menu_new();
	/* ETAPE 3 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("_Annuler");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnAnnuler), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Retablir");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRetablir), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	/* ETAPE 4 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("E_dition");
	/* ETAPE 5 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
	/* ETAPE 6 */
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/** Troisieme sous-menu **/
	/* ETAPE 2 */
	pMenu = gtk_menu_new();
	/* ETAPE 3 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("_Negatif");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnNegatif), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("Ro_tation");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRotation), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Luminosite");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnLuminosite), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Bruit");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnBruiter), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("_Filtre");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnFiltrer), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_mnemonic("Filtre _Median");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnMedian), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	/* ETAPE 4 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("_Image");
	/* ETAPE 5 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
	/* ETAPE 6 */
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/** Troisieme sous-menu **/
	/* ETAPE 2 */
	pMenu = gtk_menu_new();
	/* ETAPE 3 */
	pMenuItem = gtk_menu_item_new_with_mnemonic("A propos de guimpe");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnAbout), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	/* ETAPE 4 */
	pMenuItem = gtk_menu_item_new_with_label("?");
	/* ETAPE 5 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
	/* ETAPE 6 */
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/* Ajout du menu a la fenetre */
	gtk_box_pack_start(GTK_BOX(pVBox), pMenuBar, FALSE, FALSE, 0);

	// Ajout image
	// une DrawingArea
	pDA = gtk_drawing_area_new ();
	//gtk_widget_set_size_request (pDA, 100, 100);

	g_signal_connect (pDA, "expose-event", G_CALLBACK (OnExpose), (GtkWidget*) pWindow);
	gtk_box_pack_start(GTK_BOX(pVBox), pDA, FALSE, FALSE, 0);

	// Ajout labels du bas
	pHBox = gtk_hbox_new(FALSE, 0);

	pLabel_Nomf = gtk_label_new("Pas d image chargee");
	gtk_box_pack_start(GTK_BOX(pHBox), pLabel_Nomf, TRUE, FALSE, 0);

	
	pSeparator = gtk_vseparator_new();
	gtk_box_pack_start(GTK_BOX(pHBox), pSeparator, FALSE, FALSE, 0);

	pLabel_Res = gtk_label_new("Resolution Image");
	gtk_box_pack_start(GTK_BOX(pHBox), pLabel_Res, TRUE, FALSE, 0);

	gtk_box_pack_start(GTK_BOX(pVBox), pHBox, FALSE, FALSE, 2);

	// effacer historique
	pile_free_images();

	gtk_widget_show_all(pWindow);

	gtk_main();

	return EXIT_SUCCESS;
}
