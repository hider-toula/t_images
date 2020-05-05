#include <stdlib.h>
#include "noyau.h"
#include <stdio.h>
#include <string.h>

#define TMP_STR_SIZE 128

noyau_t *creer_noyau(unsigned int dim)
	{
	// declaration du noyau
	noyau_t *ny;
	// allocation dynamique du ny 
	ny=(noyau_t *)malloc(sizeof(noyau_t));
	//allocation de coeff
	ny->coeffs=(int *)malloc(sizeof(int)*dim*dim);
	//verification de l'allocation 
	ny->dim=dim;
	if(ny==NULL){
		fprintf(stderr,"probleme d'allocation ");
		return NULL;

	}
	
	return ny;
	}

void detruire_noyau(noyau_t *pn)
	{

	free(pn->coeffs);
	free(pn);
	}

noyau_t *charger_noyau(char *nom_fichier)
	{
		FILE * fic ;
		noyau_t *ny;
		int taille=0;
		int i;

		// lecture fichier 

		fic=fopen(nom_fichier,"r");
		// verification de l'ouverture 
		if(!fic){
			fprintf(stderr,"erreur d'ouverture");
			return NULL;
		}
		fscanf(fic,"%d ",&taille);
		ny=creer_noyau(taille);

		for(i=0;i<taille*taille ; i++){
			fscanf(fic,"%d ",&ny->coeffs[i]);
			printf("noy [%d] = %d\n", i, ny->coeffs[i]);

		}
		printf("\n Le noyeau s'est bien cree ! \n");
		fclose(fic);
		

	return ny;
	}
