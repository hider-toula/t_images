#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "image.h"
#define TMP_STR_SIZE 256

image_t *charger_image_pgm(char *nom_fichier){
	
	FILE *f;
	image_t *img;
	unsigned int nb_niveaux_gris;
	char ligne_lue[TMP_STR_SIZE];
	enum format {BIN, ASCII} pgm_form;
	int i = 0 ;

	//verification si le fichier existe 

	if(!nom_fichier){
		return NULL ;
	}

	f = fopen(nom_fichier,"r");

	// verification si le fichier est bien ouvert 

	if(!f){
		fprintf(stderr,"\nerreur lectur fichier\n ");
		
		return NULL ;
	}

	// creation d'image 

	img = creer_image();
	img->path = strdup(nom_fichier);
	fgets(ligne_lue,TMP_STR_SIZE,f);

	// trouver le type du fichier 

	if(!strncmp(ligne_lue , "P2", 2)){
		pgm_form = ASCII;
	}else if(!strncmp(ligne_lue , "P5",2)){
		pgm_form = BIN;
	}else{
		fclose(f);
		fprintf(stderr, "\n ligne lue: %s\n Erreur fichier corrempu \n", ligne_lue);
		return NULL ; 
	}

	//recuperation de H et W 

	while(fgets(ligne_lue,TMP_STR_SIZE,f)&&(ligne_lue[0]=='#')){}

	if(sscanf(ligne_lue,"%lu %lu",&img->w,&img->h) != 2 ){
		fclose(f);
		detruire_image(img);
		return NULL;

	}

	//recuperation du niv de gris 

	while(fgets(ligne_lue,TMP_STR_SIZE,f)&&((ligne_lue[0]=='#'))){}
	if(sscanf(ligne_lue,"%u",&nb_niveaux_gris)!=1){
		fclose(f);
		detruire_image(img);
		return NULL ; 

	}
	
	// allocation de buff 

	img->buff =(unsigned char *) malloc(sizeof(unsigned char)*(img->w*img->h)) ;

	printf("\nrecuperation de l'image\n") ;
	if (pgm_form == ASCII){

		for ( i=0;i<img->w*img->h;i++ ){

			fscanf(f, "%hhu ", &img->buff[i]) ;
			//printf("\n i = %d ", i);
		}
		fclose(f);
		return img;
		
	}
	//ouverture du fichier en binaire 

	else{

		fread(img->buff,sizeof(unsigned char),img->h*img->w,f);
		fclose(f);
		return img ;

	}




	return NULL ;
}

int sauver_image_pgm(char *nom_fichier, image_t *img)
	{
		FILE *fp ;
		int i=0;
		// creation et ouverture du fichier
		printf("le fichier est ouvert "); 
		fp=fopen(nom_fichier,"w");
		// verifier si le fichier est bien crrer 
		if(!fp){
			fprintf(stderr, "le fichier n'ouvre pas");
			return 0 ;
		}
		//remplir le fichier 

		fprintf(fp,"%s","P2\n");
		fprintf(fp,"%ld %ld\n",img->w,img->h);
		fprintf(fp,"%d\n",255);

		while(i<img->w*img->h){
			//printf("la valeur de i est %d\n",i);
			fprintf(fp,"%u ",img->buff[i]);
			i++; 

		}
	fclose(fp);
	return 1;
	}
