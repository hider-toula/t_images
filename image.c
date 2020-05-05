#include<stdlib.h>
#include<string.h>
#include "image.h"
#include <stdio.h>

image_t *creer_image(){

	//creatioin d'image 
	image_t *image ; 
	// allocation de memoire 
	image = (image_t *)malloc(sizeof(image_t));
	// verfication de l'allocation 
	if(!image){
		fprintf(stderr,"\nprobleme allocation \n" );
		return NULL ;
	}
	
	image->h = 0;
	image->w = 0;
	image->path = NULL;
	image->buff = NULL;


	return image ;

}

image_t *copier_image(image_t *src){
	// verification de la src si elle est null 
	if(!src){
		fprintf(stderr,"\nproblme dans src \n");
		return NULL; 
	}
	// creation d'image copy 
	image_t *copy = creer_image();
	// verification si on a bien crreie copy 
	if(copy){
		// on copie l'image 
		copy->h = src->h;
		copy->w = src->w;
		copy->buff = malloc(sizeof(unsigned char)*(copy->h*copy->w) );
		copy->buff = memcpy(copy->buff,src->buff,copy->h*copy->w);
		copy->path = strdup(src->path);

		return copy ; 
	}

	return NULL;
}

void detruire_image(image_t *p){
	if(!p){
		return; 
	}
	free(p->buff);
	free(p->path);
	free(p);



}
