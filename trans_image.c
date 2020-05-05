#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "noyau.h"
#include <math.h>

image_t *negatif(image_t *src)
	{	
		int i;
		//creation d'une copie de l'image

		image_t *dest ; 
		dest=creer_image();

		// copier l'image

		dest->h=src->h;
		dest->w=src->w;
		dest->path=strdup(src->path);
		dest->buff=malloc(sizeof(unsigned char)*(dest->h*dest->w));
		// fair le negative 

		for(i=0;i<dest->h*dest->w;i++){
			dest->buff[i]=255-src->buff[i];
		}

	
	return dest;
	}

image_t *rotation(image_t *src, int angle)
	{
		int i;
		int j;
		//creation d'une copie de l'image

		image_t *dest ; 
		dest=creer_image();

		// copier l'image

		dest->h=src->w;
		dest->w=src->h;
		dest->path=strdup(src->path);
		dest->buff=malloc(sizeof(unsigned char)*(dest->h*dest->w));
		// fair le negative 
		if(angle==90){
		for(i=0;i<src->h;i++){
			for(j=0;j<src->w;j++){
				VAL(dest,src->w-j-1,i)=VAL(src,i,j);

			}
			
			
		}
		}
	return dest;
	}

image_t *modifier_lumin(image_t *src, int pourcent)
	{
		int i;
		//creation d'une copie de l'image

		image_t *dest ; 
		dest=creer_image();

		// copier l'image

		dest->h=src->h;
		dest->w=src->w;
		dest->path=strdup(src->path);
		dest->buff=malloc(sizeof(unsigned char)*(dest->h*dest->w));
		// augmenter la lum 

		for(i=0;i<dest->h*dest->w;i++){
			dest->buff[i]=(unsigned char )src->buff[i]*pourcent/100;
			if(dest->buff[i]>255){
				dest->buff[i]=255; 
			}
		}

	return dest;
	}

image_t *bruiter_image(image_t *src, int pourcent)
	{
		int i;
		int proba ; 
		//creation d'une copie de l'image

		image_t *dest ; 
		dest=creer_image();

		// copier l'image

		dest->h=src->h;
		dest->w=src->w;
		dest->path=strdup(src->path);
		dest->buff=malloc(sizeof(unsigned char)*(dest->h*dest->w));
		// bruiter  

		for(i=0;i<dest->h*dest->w;i++){
			dest->buff[i]=src->buff[i];
			proba=rand()%100;
			if(proba<pourcent){
				dest->buff[i]=255;
			}	
		}

	return dest ;
	}

image_t *filtrer_median(image_t *src)
	{
	return NULL;
	}

image_t *convoluer(image_t *src, noyau_t *pn)
	{
		int i, j ;
		int k1 ,k2 ;
		int dim2 = floor(pn->dim/2);

		if(!pn){
			printf("\n le NOYEAU est NULL\n");
		}
		unsigned int dim = pn->dim;
		int somme=0;
		int coef=0 ;
		image_t  *dest;
		//dest = creer_image() ;
		for(i=0;i<pn->dim*pn->dim;i++){
			coef+=pn->coeffs[i];
			if(coef==0){
				coef=1;
			}
		}
		dest=creer_image();
		dest=copier_image(src);
		for(i=0;i<src->h;i++){
			for(j=0;j<src->w;j++){
				// on fixe un pixel 
				somme = 0;
				for(k1=-dim2;k1<=dim2;k1++){
					for(k2=-dim2;k2<=dim2;k2++){
						// on parcour la matrice 
						int def1 = i+k1;
						int def2 = j+k2;

						// on gere le ka des extemités 
						if(def1<0){
							def1=0;
						}
						if(def1>=src->h){
							def1=src->h-1;

						}
						if(def2<0){
							def2=0;
						}
						if(def2>=src->w){
							def2=src->w-1;

						}

						somme+=VAL(src,def1,def2)*NOY(pn, k1+dim2, k2+dim2);
						// printf("Val[%d, %d] est %d\n", def1, def2, VAL(src, def1, def2));
					}
				}
				//printf("k1 = %d , k2 = %d\n", k1, k2);
				somme = (int)(somme/(float)coef);
				if(somme<0)somme=-somme;
				if(somme>255)somme=255;
				printf("\n%d\n",somme);
				VAL(dest, i, j)=somme;
			}
			
		}

	return dest;
	}
