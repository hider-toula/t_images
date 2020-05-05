#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "pile_image.h"
#include "image.h"
#include "pgm_image.h"
#include "trans_image.h"

extern GtkWidget *pLabel_Nomf;
extern GtkWidget *pLabel_Res;
extern GtkWidget *pDA;

extern image_t *cur_image;

// affichage de l image drawing_area
void OnExpose(GtkWidget* widget, gpointer data)
	{
	if (cur_image == NULL)
		{
		gtk_widget_set_size_request (widget, 0, 0);
		gdk_draw_rectangle (	pDA->window,
									pDA->style->white_gc,
									TRUE,
									0, 0,
									pDA->allocation.width,
									pDA->allocation.height);
		}
	else
		{
		gtk_widget_set_size_request (widget, cur_image->w, cur_image->h);
		gdk_draw_gray_image (pDA->window,
									pDA->style->white_gc,
									0, 0,
									cur_image->w, cur_image->h,
									GDK_RGB_DITHER_NORMAL,
									cur_image->buff,
									cur_image->w);
		}
	}

// menu fichier

void OnOuvrir(GtkWidget* widget, gpointer data)
	{
	GtkWidget *dialog;
	GtkFileFilter *pgm_filter;

	pgm_filter = gtk_file_filter_new ();
	gtk_file_filter_set_name( pgm_filter, "*.pgm");
	gtk_file_filter_add_pattern (pgm_filter, "*.pgm");

	dialog = gtk_file_chooser_dialog_new ("Ouvrir Fichier",
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);

	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (dialog), pgm_filter);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
 		{
		char *nom_fichier;

		nom_fichier = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		// effacer historique
		pile_free_images();

		pile_new_image(charger_image_pgm(nom_fichier));

		g_free (nom_fichier);
  		}
	gtk_widget_destroy (dialog);
	}

void OnEnregistrer(GtkWidget* widget, gpointer data)
	{
	if (cur_image)
		sauver_image_pgm(cur_image->path, cur_image);
	}

void OnEnregSous(GtkWidget* widget, gpointer data)
	{
	GtkWidget *dialog;
	GtkFileFilter *pgm_filter;

	if (cur_image == NULL)
		return;
	pgm_filter = gtk_file_filter_new ();
	gtk_file_filter_set_name( pgm_filter, "*.pgm");
	gtk_file_filter_add_pattern (pgm_filter, "*.pgm");
	dialog = gtk_file_chooser_dialog_new ("Enregistrer Sous",
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_SAVE,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
				      NULL);
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
	//gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), default_folder_for_saving);
	gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "SansNom");
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (dialog), pgm_filter);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
		{
		char *nom_fichier;
		nom_fichier = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		sauver_image_pgm(nom_fichier, cur_image);
		cur_image->path= strdup(nom_fichier);
		g_free (nom_fichier);
		}
	gtk_widget_destroy (dialog);
	}

void OnFermer(GtkWidget* widget, gpointer data)
	{
	pile_free_images();
	}


void OnQuitter(GtkWidget* widget, gpointer data)
{
	GtkWidget *pQuestion;

	pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_QUESTION,
		GTK_BUTTONS_YES_NO,
		"Voulez vous vraiment\n"
		"quitter le programme?");

	switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
	{
		case GTK_RESPONSE_YES:
			gtk_main_quit();
			pile_free_images();
			break;
		case GTK_RESPONSE_NONE:
		case GTK_RESPONSE_NO:
			gtk_widget_destroy(pQuestion);
			break;
	}
}

// menu Edition

void OnAnnuler(GtkWidget* widget, gpointer data)
	{
	pile_undo();
	}

void OnRetablir(GtkWidget* widget, gpointer data)
	{
	pile_redo();
	}


// menu Image

void OnNegatif(GtkWidget* widget, gpointer data)
	{
	pile_new_image(negatif(cur_image));
	}

void OnRotation(GtkWidget* widget, gpointer data)
	{
	GtkWidget* pBoite;
	GtkWidget *pRadio90;
	GtkWidget *pRadio180;
	GtkWidget *pRadio270;

	/* Creation de la boite de dialogue */
	/* 1 bouton Valider */
	/* 1 bouton Annuler */
	pBoite = gtk_dialog_new_with_buttons("Rotation", NULL,
				GTK_DIALOG_MODAL,
				GTK_STOCK_OK,GTK_RESPONSE_OK,
				GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
				NULL);

	// Creation des boutons radio
	pRadio90 = gtk_radio_button_new_with_label(NULL, "90°");
	pRadio180 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (pRadio90),"180°");
	pRadio270 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (pRadio90),"270°");
	/* Insertion de la zone de saisie dans la boite de dialogue */
	/* Rappel : paramètre 1 de gtk_box_pack_start de type GtkBox */
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pRadio90, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pRadio180, TRUE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pRadio270, TRUE, FALSE, 0);

	/* Affichage des elements de la boite de dialogue */
	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);


	/* On lance la boite de dialogue et on recupere la reponse */
	if (gtk_dialog_run(GTK_DIALOG(pBoite)) == GTK_RESPONSE_OK)
		{
		GSList *pList;
		int angle = 270;

		/* Recuperation de la liste des boutons */
		pList = gtk_radio_button_get_group(GTK_RADIO_BUTTON(pRadio90));

		/* Parcours de la liste */
		while(pList)
			{
			/* Le bouton est il selectionne */
			if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList->data)))
				{
				// rotation
				pile_new_image(rotation(cur_image, angle));
				}
			/* NON -> on passe au bouton suivant */
			angle -= 90;
			pList = g_slist_next(pList);
			}
		}

	/* Destruction de la boite de dialogue */
	gtk_widget_destroy(pBoite);
	}

void OnScrollbarChange(GtkWidget *pWidget, gpointer data)
{
	gchar* sLabel;
	gint iValue;

	/* Recuperation de la valeur de la scrollbar */
	iValue = gtk_range_get_value(GTK_RANGE(pWidget));
	/* Creation du nouveau label */
	sLabel = g_strdup_printf("%d %%", iValue);
	/* Modification du label */
	gtk_label_set_text(GTK_LABEL(data), sLabel);
	/* Liberation memoire */
	g_free(sLabel);
}

void OnLuminosite(GtkWidget* widget, gpointer data)
	{
	GtkWidget* pBoite;
	GtkWidget *pLabel;
	GtkWidget *pScrollbar;
	GtkObject *Adjust;
	
	/* Creation de la boite de dialogue */
	/* 1 bouton Valider */
	/* 1 bouton Annuler */
	pBoite = gtk_dialog_new_with_buttons("Luminosite", NULL,
					GTK_DIALOG_MODAL,
					GTK_STOCK_OK,GTK_RESPONSE_OK,
					GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
					NULL);

	 /* Label d'affichage de valeur */
	pLabel = gtk_label_new("100 %");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pLabel, FALSE, FALSE, 0);
	/* Creation d un GtkAdjustment */
	Adjust = gtk_adjustment_new(0, 0, 201, 1, 10, 1);
	gtk_adjustment_set_value(GTK_ADJUSTMENT(Adjust), 100);
	/* Creation d une scrollbar horizontale*/
	pScrollbar = gtk_hscrollbar_new(GTK_ADJUSTMENT(Adjust));
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pScrollbar, TRUE, TRUE, 0);
	/* Connexion du signal pour modification de l affichage */
	g_signal_connect(G_OBJECT(pScrollbar), "value-changed", G_CALLBACK(OnScrollbarChange), (GtkWidget*)pLabel);
	/* Affichage des elements de la boite de dialogue */
	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);

	if (gtk_dialog_run(GTK_DIALOG(pBoite)) == GTK_RESPONSE_OK)
		pile_new_image(modifier_lumin(cur_image, gtk_range_get_value(GTK_RANGE(pScrollbar))));

	/* Destruction de la boite de dialogue */
	gtk_widget_destroy(pBoite);
	}

void OnBruiter(GtkWidget* widget, gpointer data)
	{
	GtkWidget* pBoite;
	GtkWidget *pScale;

	/* Creation de la boite de dialogue */
	/* 1 bouton Valider */
	/* 1 bouton Annuler */
	pBoite = gtk_dialog_new_with_buttons("bruiter", NULL,
					GTK_DIALOG_MODAL,
					GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
					GTK_STOCK_OK,GTK_RESPONSE_OK,
					NULL);

	/* Creation du widget GtkHScale */
   pScale = gtk_hscale_new_with_range(0, 100, 1);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pScale, FALSE, FALSE, 0);
	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);

	if (gtk_dialog_run(GTK_DIALOG(pBoite)) == GTK_RESPONSE_OK)
		pile_new_image(bruiter_image(cur_image, gtk_range_get_value(GTK_RANGE(pScale))));

	/* Destruction de la boite de dialogue */
	gtk_widget_destroy(pBoite);
	}

void OnFiltrer(GtkWidget* widget, gpointer data)
	{
	GtkWidget *dialog;
	GtkFileFilter *pgm_filter;

	pgm_filter = gtk_file_filter_new ();
	gtk_file_filter_set_name( pgm_filter, "*.txt");
	gtk_file_filter_add_pattern (pgm_filter, "*.txt");

	dialog = gtk_file_chooser_dialog_new ("Ouvrir Filtre",
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);

	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (dialog), pgm_filter);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
 		{
		char *nom_fichier;
		noyau_t *noy;

		nom_fichier = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		noy = charger_noyau(nom_fichier);

		pile_new_image(convoluer(cur_image, noy));
		g_free (nom_fichier);
  		}
	gtk_widget_destroy (dialog);
	}

void OnMedian(GtkWidget* widget, gpointer data)
	{
	pile_new_image(filtrer_median(cur_image));
	}


// menu A propos

void OnAbout(GtkWidget* widget, gpointer data)
{
	GtkWidget *pAbout;

	pAbout = gtk_message_dialog_new (GTK_WINDOW(data),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK,
		"Li215 mini projet image\n"
		"Universite Pierre et Marie Curie");

	gtk_dialog_run(GTK_DIALOG(pAbout));

	gtk_widget_destroy(pAbout);
}
