#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

#include <stdio.h>
#include <stdlib.h>

Automate_deterministe* determinisation(Automate_non_deterministe* automate_nd){
	Automate_deterministe* automate_d = malloc(sizeof(Automate_deterministe));
	Caractere* caractere_act;
	Groupe_etat* groupe_etat = NULL;
	Groupe_etat* groupe_etat_act = NULL;
	Etat* etat_act = NULL;
	Transition* transition_act = NULL;
	int i,nb_caractere;
	
	automate_d->alphabet = automate_nd->alphabet;
	//numérotation des caractères
	nb_caractere = 0;
	caractere_act = automate_d->alphabet;
	while(caractere_act != NULL){
		caractere_act->numero = nb_caractere;
		nb_caractere++;
		caractere_act = caractere_act->caractere_suivant;
	}
	
	//initialisation du 1er groupe d'état
	groupe_etat = creation_groupe_etat(automate_nd->etat_initial);
	
	//ajout du groupe à la liste
	automate_d->liste_groupe_etat = groupe_etat;
	automate_d->nb_groupe_etat = 1;
	automate_d->groupe_etat_initial = groupe_etat;
	
	//on crée la 1ère ligne du tableau de transition et on l'initialise à NULL
	automate_d->tab_transition = malloc(sizeof(Groupe_etat**));
	automate_d->tab_transition[0] = malloc(nb_caractere * sizeof(Groupe_etat*));
	for(i=0;i<nb_caractere;i++){
		automate_d->tab_transition[0][i] = NULL;
	}
	
	//parcours des groupes d'état
	groupe_etat_act = groupe_etat;
	while(groupe_etat_act != NULL){
		//parcours des états du groupe d'états
		for(i=0;i<groupe_etat_act->nb_etat;i++){
			etat_act = groupe_etat_act->tab_etat[i];
			//parcours des transitions de l'état
			transition_act = automate_nd->tab_transition[etat_act->num];
			while(transition_act != NULL){
				//si le groupe d'état n'existe pas
				if(automate_d->tab_transition[groupe_etat_act->numero][transition_act->caractere->numero] == NULL){
					//création du groupe d'état
					groupe_etat = creation_groupe_etat(transition_act->arrivee);
					automate_d->tab_transition[groupe_etat_act->numero][transition_act->caractere->numero] = groupe_etat;
				}
				else{//le groupe d'état existe déjà
					//on ajoute l'état au groupe d'état
					ajout_etat(transition_act->arrivee,automate_d->tab_transition[groupe_etat_act->numero][transition_act->caractere->numero]);
				}
				transition_act = transition_act->transitionSuivante;
			}
		}
		//on parcourt la ligne et on regarde les nouveaux groupes d'état
		
		groupe_etat_act = groupe_etat_act->groupe_etat_suivant;
	}
	
	return automate_d;
}


//Création d'un groupe d'état à partir d'un état
Groupe_etat* creation_groupe_etat(Etat* etat){
	Groupe_etat* groupe_etat = malloc(sizeof(Groupe_etat));
	
	groupe_etat->tab_etat = malloc(sizeof(Etat*));
	groupe_etat->tab_etat[0] = etat;
	groupe_etat->nb_etat = 1;
	groupe_etat->numero = 0;
	groupe_etat->accepteur = etat->accepteur;
	groupe_etat->groupe_etat_suivant = NULL;
	
	return groupe_etat;
}


//Ajoute l'état au groupe d'état s'il n'existe pas déjà
void ajout_etat(Etat* etat, Groupe_etat* groupe_etat){
	int i = 0;
	int ok = 0;
	Etat* etat_tmp = NULL;

	while(i < groupe_etat->nb_etat && ok == 0){
		if(etat == groupe_etat->tab_etat[i]){//si l'état est déjà dans le groupe
			return;
		}
		else if(groupe_etat->tab_etat[i]->num > etat->num){//si le numéro de l'état est plus grand que l'état à ajouter
			//on ajoute une case au tableau d'état et on mémorise le rang d'ajout
			groupe_etat->tab_etat = (Etat**) realloc(groupe_etat->tab_etat,(groupe_etat->nb_etat + 1) * sizeof(Etat*));
			ok = 1;
		}
		else{
			i++;
		}
	}
	
	//on rend le groupe accepteur s'il contient un état accepteur
	if(groupe_etat->accepteur == 0 && etat->accepteur == 1){
		groupe_etat->accepteur = 1;
	}
	
	for(i=i;i<groupe_etat->nb_etat+1;i++){//on ajoute l'état dans le tableau et on décale la fin du tableau
		etat_tmp = groupe_etat->tab_etat[i];
		groupe_etat->tab_etat[i] = etat;
		etat = etat_tmp;
	}
	
	groupe_etat->nb_etat++;
	
	return;
}
	
