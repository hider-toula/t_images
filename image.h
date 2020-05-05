#ifndef IMAGE_
#define IMAGE_

#define VAL(img,i,j) (img)->buff[(i)*(img)->w+(j)]

typedef struct
	{
	unsigned long w; // largeur en pixels
	unsigned long h; // hauteur en pixels
	char *path; // le chemin absolu du fichier correspondant
	unsigned char *buff; // w x h octets correspondant aux pixels
	} image_t;

image_t *creer_image();

image_t *copier_image(image_t *src);

void detruire_image(image_t *p);
#endif
