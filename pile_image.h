#ifndef PILE_IMAGE
#define PILE_IMAGE

#include "image.h"
typedef struct pile_image{
    image_t *image;
    struct pile_image *suivant;
    struct pile_image *precedent; 
}pile_image

void pile_new_image(image_t *new_image);
void pile_free_images();
void pile_undo();
void pile_redo();

#endif
