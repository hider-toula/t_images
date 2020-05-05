#include <gtk/gtk.h>
#include "image.h"

extern GtkWidget *pLabel_Nomf;
extern GtkWidget *pLabel_Res;
extern GtkWidget *pDA;

// version basique pas de pile une seule image  a la fois
image_t *cur_image;
pile_image PILE = NULL;

pile_image* createNode(){
		pile_image *P = (pile_image*)malloc(sizeof(pile_image));
		P->suivant = NULL;
		P->precedent = NULL;
		return P;
}
void pile_new_image(image_t *new_image)
	{
	char str_res[32];

	//detruire_image(cur_image);
	if(!PILE){
		PILE = createNode();
	}
	cur_image = new_image;
	gtk_label_set_text (GTK_LABEL (pLabel_Nomf), cur_image->path);
	snprintf(str_res, 32, "%ldx%ld", cur_image->w, cur_image->h);
	gtk_label_set_text (GTK_LABEL (pLabel_Res), str_res);
	gtk_widget_queue_draw_area(pDA, 0, 0, pDA->allocation.width, pDA->allocation.height);
	}

void pile_free_images()
	{
	detruire_image(cur_image);
	gtk_label_set_text (GTK_LABEL (pLabel_Nomf), "Pas d image chargee");
	gtk_label_set_text (GTK_LABEL (pLabel_Res), "Resolution Image");
	cur_image = NULL;
	gtk_widget_queue_draw_area(pDA, 0, 0, 0, 0);
	//gtk_widget_queue_draw_area(pDA, 0, 0, pDA->allocation.width, pDA->allocation.height);
	}

void pile_undo()
	{
	// non dispo das la version basique
	}

void pile_redo()
	{
	// non dispo das la version basique
	}
