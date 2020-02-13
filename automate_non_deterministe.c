#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Renvoie un automate non déterministe reconnaissant le langage vide
Automate_non_deterministe* langage_vide(){
	Automate_non_deterministe* automate = malloc(sizeof(Automate_non_deterministe));
	Etat* etat = malloc(sizeof(Etat));

	etat->num = 0;
	etat->accepteur = 0;
	etat->etat_suivant = NULL;

	automate->alphabet = NULL;
	automate->nombreEtats = 1;
	automate->liste_etat = etat;
	automate->etat_initial = etat;
	automate->tab_transition = init_tab_transition(1);
	automate->automate_suivant = NULL;

	return automate;

}

//Renvoie un automate non déterministe reconnaissant le mot vide
Automate_non_deterministe* mot_vide(){
	Automate_non_deterministe* automate = malloc(sizeof(Automate_non_deterministe));
	Etat* etat = malloc(sizeof(Etat));

	etat->num = 0;
	etat->accepteur = 1;
	etat->etat_suivant = NULL;

	automate->alphabet = NULL;
	automate->nombreEtats = 1;
	automate->liste_etat = etat;
	automate->etat_initial = etat;
	automate->tab_transition = init_tab_transition(1);
	automate->automate_suivant = NULL;

	return automate;
}

//Renvoie un automate standard reconnaissant le langage composé d’un mot d’un caractère passé en paramètre
Automate_non_deterministe* un_mot(char symbole){
	Automate_non_deterministe* automate = malloc(sizeof(Automate_non_deterministe));
	Etat* etat_init = malloc(sizeof(Etat));
	Etat* etat_final = malloc(sizeof(Etat));
	Transition* transition = malloc(sizeof(Transition));
	Caractere* caractere = malloc(sizeof(Caractere));

	etat_init->num = 0;
	etat_init->accepteur = 0;
	etat_init->etat_suivant = NULL;

	etat_final->num = 1;
	etat_final->accepteur = 1;
	etat_final->etat_suivant = etat_init;

	caractere->symbole = symbole;
	caractere->numero = 0;
	caractere->caractere_suivant = NULL;

	transition->depart = etat_init;
	transition->arrivee = etat_final;
	transition->caractere = caractere;
	transition->transitionSuivante = NULL;

	automate->alphabet = caractere;
	automate->nombreEtats = 2;
	automate->liste_etat = etat_final;
	automate->etat_initial = etat_init;
	automate->tab_transition = init_tab_transition(2);
	automate->tab_transition[0] = transition;
	automate->automate_suivant = NULL;

	return automate;
}

//Ajoute l'alphabet de l'automate 2 dans l'alphabet de l'automate 1
void reunion_alphabet(Automate_non_deterministe* automate1, Automate_non_deterministe* automate2){
	Caractere* caract_act1 = NULL;
	Caractere* caract_act2 = NULL;
	Caractere* tmp1 = NULL;
	Caractere* tmp2 = NULL;
	Transition* trans_act = NULL;
	int i,nb_etat;
	int inversion = 0;

	if(automate1->alphabet == NULL){//si pas d'alphabet 1, on prend le 2
		automate1->alphabet = automate2->alphabet;
		return;
	}
	else if(automate2->alphabet == NULL){//si pas d'alphabet 2, pas de tri à faire
		return;
	}
	else if(automate1->alphabet->symbole == automate2->alphabet->symbole){//si même caractère au début
		//dans les transitions, on remplace le caractère de l'automate 2 par celui de l'automate1
		for(i=0;i<automate2->nombreEtats;i++){
			trans_act = automate2->tab_transition[i];
			while(trans_act != NULL){
				if(trans_act->caractere == automate2->alphabet){
					trans_act->caractere = automate1->alphabet;
				}
				trans_act = trans_act->transitionSuivante;
			}
		}
		//on free ce caractère
		tmp1 = automate2->alphabet->caractere_suivant;
		free(automate2->alphabet);
		automate2->alphabet = tmp1;

		if(automate2->alphabet == NULL){
			return;
		}
	}

	if(automate1->alphabet->symbole < automate2->alphabet->symbole){//si le 1er caractère de l'alphabet 1 est plus petit que celui de l'alphabet 2
		//on rajoute le 2 dans le 1
		caract_act1 = automate1->alphabet;
		caract_act2 = automate2->alphabet;
	}
	else {//si le 1er caractère de l'alphabet 1 est plus grand que celui de l'alphabet 2
		//on rajoute le 1 dans le 2
		caract_act1 = automate2->alphabet;
		caract_act2 = automate1->alphabet;
		inversion = 1;
	}

	while(caract_act2 != NULL){

		//tri fusion
		while(caract_act1->caractere_suivant != NULL && caract_act1->caractere_suivant->symbole < caract_act2->symbole){
			caract_act1 = caract_act1->caractere_suivant;
		}
		if(caract_act1->caractere_suivant == NULL){//si fin de l'alphabet1
			caract_act1->caractere_suivant = caract_act2;
			if(inversion == 1){
				automate1->alphabet = automate2->alphabet;
			}
			return;
		}
		else if(caract_act1->caractere_suivant->symbole == caract_act2->symbole){//si même caractère dans les 2 alphabets
			//dans les transitions, on remplace le caractère du 2e automate par celui du 1er
			if(inversion == 0){
					nb_etat = automate2->nombreEtats;
				}
				else {
					nb_etat = automate1->nombreEtats;
				}
			for(i=0;i<nb_etat;i++){
				if(inversion == 0){
					trans_act = automate2->tab_transition[i];
				}
				else {
					trans_act = automate1->tab_transition[i];
				}
				while(trans_act != NULL){
					if(trans_act->caractere == caract_act2){
						trans_act->caractere = caract_act1->caractere_suivant;
					}
					trans_act = trans_act->transitionSuivante;
				}
			}
			//on free ce caractère
			tmp1 = caract_act2->caractere_suivant;
			free(caract_act2);
			caract_act2 = tmp1;
		}
		else{//on ajoute le caractère 2 après le caractère 1 et on avance dans l'alphabet 2
			tmp1 = caract_act1->caractere_suivant;
			tmp2 = caract_act2->caractere_suivant;
			caract_act1->caractere_suivant = caract_act2;
			caract_act2->caractere_suivant = tmp1;
			caract_act2 = tmp2;
		}
	}

	if(inversion == 1){
		automate1->alphabet = automate2->alphabet;
	}
}


//Création d'un tableau de listes de transitions alloué dynamiquement
Transition** init_tab_transition(int taille){
	Transition** tab_transition = NULL;
	int i;

	tab_transition = malloc(taille * sizeof(Transition*));
	for(i=0;i<taille;i++){
		tab_transition[i] = NULL;
	}

	return tab_transition;
}

//Ajoute une transition dans le tableau de transition en fonction de son état de départ
void ajout_transition(Transition* transition, Transition** tab_transition){
	Transition* transition_act = tab_transition[transition->depart->num];

	tab_transition[transition->depart->num] = transition;
	transition->transitionSuivante = transition_act;

}


//Affiche un automate
void affichage_automate_non_deterministe(Automate_non_deterministe* automate){
	int i;
	Transition* transition_act;
	Caractere* caractere_act;
	Etat* etat_act;

	printf("Alphabet :");
	caractere_act = automate->alphabet;
	while(caractere_act != NULL){
		printf(" %c,",caractere_act->symbole);
		caractere_act = caractere_act->caractere_suivant;
	}
	printf("\nNb états : %d \n",automate->nombreEtats);
	printf("Etat initial : %d \n",automate->etat_initial->num);
	printf("Etats accepteurs :");
	etat_act = automate->liste_etat;
	while(etat_act != NULL && (etat_act->accepteur == 1)){
		printf(" %d,",etat_act->num);
		etat_act = etat_act->etat_suivant;
	}
	printf("\nListe etats:");
	etat_act = automate->liste_etat;
	while(etat_act != NULL){
		printf(" %d,",etat_act->num);
		etat_act = etat_act->etat_suivant;
	}
	printf("\nTransitions :");
	for(i=0;i<automate->nombreEtats;i++){
		transition_act = automate->tab_transition[i];
		while(transition_act != NULL){
			printf(" (%d,%c,%d),",transition_act->depart->num,transition_act->caractere->symbole,transition_act->arrivee->num);
			transition_act = transition_act->transitionSuivante;
		}
	}
	printf("\n\n");
}

//Réunion des automates 1 et 2 dans l'automate 1
void reunion(Automate_non_deterministe* automate1, Automate_non_deterministe* automate2){
	Etat* etat_act = NULL;
	Etat* etat_tmp = NULL;
	int i,nb_etat;
	Transition* trans_act = NULL;
	Transition* trans_tmp = NULL;


	reunion_alphabet(automate1,automate2);

	//ajout des etats de l'automate 2 dans l'automate 1

	if(automate1->liste_etat->accepteur == 0){ //si l'automate 1 n'a pas d'états accepteurs, on ajoute au début en modifiant les numéros
		etat_tmp = automate1->liste_etat;
		if(automate2->liste_etat == automate2->etat_initial) {
			automate1->liste_etat = automate2->liste_etat->etat_suivant;
		}
		else{
			automate1->liste_etat = automate2->liste_etat;
			automate1->liste_etat->num = automate1->liste_etat->num + automate1->nombreEtats - 1;
		}
		etat_act = automate1->liste_etat;
		for(i=0;i<automate2->nombreEtats-1;i++){
			if(etat_act->etat_suivant == automate2->etat_initial){
				etat_act->etat_suivant = automate2->etat_initial->etat_suivant;
			}
			else{
				etat_act->etat_suivant->num = etat_act->etat_suivant->num + automate1->nombreEtats - 1;
				etat_act = etat_act->etat_suivant;
			}

		}
		if(etat_act == NULL){//si automate 2 n'a qu'un état initial
			automate1->liste_etat = etat_tmp;
		}
		else{
			etat_act->etat_suivant = etat_tmp;
		}
	}

	else {

		//sinon on ajoute les états de l'automate 2 à la fin des états accepteurs de l'automate 1 et on modifie leur numéro
		etat_act = automate1->liste_etat;
		while(etat_act->etat_suivant != NULL && etat_act->etat_suivant->accepteur == 1){
			etat_act = etat_act->etat_suivant;
		}
		etat_tmp = etat_act->etat_suivant;
		etat_act->etat_suivant = automate2->liste_etat;
		for(i=0;i<automate2->nombreEtats;i++){
			if(etat_act->etat_suivant == automate2->etat_initial){
				etat_act->etat_suivant = automate2->etat_initial->etat_suivant;
			}
			else{
				etat_act->etat_suivant->num = etat_act->etat_suivant->num + automate1->nombreEtats - 1;
				etat_act = etat_act->etat_suivant;
			}

		}
		etat_act->etat_suivant = etat_tmp;
	}

	//on change le nombre d'états de l'automate 1
	nb_etat = automate1->nombreEtats;
	automate1->nombreEtats = automate1->nombreEtats + automate2->nombreEtats - 1;

	//réallocation du tableau de transition + remplissage avec les transitions de l'automate 2
	automate1->tab_transition = (Transition**) realloc(automate1->tab_transition, automate1->nombreEtats * sizeof(Transition*));
	assert(automate1->tab_transition != NULL); //vérif de la réallocation

	for(i=nb_etat;i<automate1->nombreEtats;i++){
		automate1->tab_transition[i] = NULL;
	}
	for(i=0;i<automate2->nombreEtats;i++){
		trans_act = automate2->tab_transition[i];
		if(i == automate2->etat_initial->num){//si état initial de l'automate 2
			while(trans_act != NULL){//changement de l'état départ de la transition et ajout au bon endroit
				trans_act->depart = automate1->etat_initial;
				trans_tmp = trans_act->transitionSuivante;
				ajout_transition(trans_act,automate1->tab_transition);
				trans_act = trans_tmp;
			}
		}
		else{
			while(trans_act != NULL){
				trans_tmp = trans_act->transitionSuivante;
				ajout_transition(trans_act,automate1->tab_transition);
				trans_act = trans_tmp;
			}
		}
	}

	//si état initial de l'automate 2 est accepteur, on rend l'état initial
	//accepteur de l'automate 1 et on met l'état au bon endroit dans la liste
	if(automate1->etat_initial->accepteur == 0 && automate2->etat_initial->accepteur == 1){
		automate1->etat_initial->accepteur = 1;
		etat_act = automate1->liste_etat;
		if(etat_act != automate1->etat_initial){
			while(etat_act->etat_suivant != automate1->etat_initial){
				etat_act = etat_act->etat_suivant;
			}
			etat_act->etat_suivant = automate1->etat_initial->etat_suivant;
			etat_tmp = automate1->liste_etat;
			automate1->liste_etat = automate1->etat_initial;
			automate1->etat_initial->etat_suivant = etat_tmp;
		}

	}

	free(automate2->etat_initial);
	free(automate2->tab_transition);
	free(automate2);

}

//Renvoie un automate standard reconnaissant la concaténation des langages des 2 automates passés en paramètre
void concatenation(Automate_non_deterministe* automate1, Automate_non_deterministe* automate2){
	Etat* etat_act = NULL;
	Etat* etat_tmp = NULL;
	int i;
	Transition* trans_act = NULL;
	Transition* trans_tmp = NULL;
	Transition* new_trans = NULL;
	
	if(automate1->liste_etat->accepteur == 0){//pas d'état accepteur dans le 1er automate
		free_automate(automate2);
		return;
	}

	reunion_alphabet(automate1,automate2);

	//réallocation du tableau de transition + remplissage avec les transitions de l'automate 2
	automate1->tab_transition = (Transition**) realloc(automate1->tab_transition, (automate1->nombreEtats + automate2->nombreEtats - 1)* sizeof(Transition*));
	assert(automate1->tab_transition != NULL); //vérification de la réalloc

	for(i=automate1->nombreEtats;i<(automate1->nombreEtats + automate2->nombreEtats - 1);i++){
		automate1->tab_transition[i] = NULL;
	}
	
	//PRINT
	trans_act = automate2->tab_transition[automate2->etat_initial->num];
	while(trans_act != NULL){
		printf("ON A %c\n", trans_act->caractere->symbole);
		trans_act = trans_act->transitionSuivante;
	}
	//
	
	trans_act = automate2->tab_transition[automate2->etat_initial->num];
	while(trans_act != NULL){
		printf("SYMBOLE BEGIN %c\n", trans_act->caractere->symbole);
		etat_tmp = automate1->liste_etat;
		while(etat_tmp!=NULL && etat_tmp->accepteur==1){

			//On cree notre nouvelle transition puis on l'ajoute
			new_trans = malloc(sizeof(Transition));
			new_trans->depart = etat_tmp;
			new_trans->arrivee = trans_act->arrivee;
			new_trans->caractere = trans_act->caractere;
			ajout_transition(new_trans,automate1->tab_transition);
			
			//On passe à l'état suivant
			if(etat_tmp->etat_suivant!=NULL){
				etat_tmp = etat_tmp->etat_suivant;
			}
			else{
				break;
			}
		}
		
		trans_act = trans_act->transitionSuivante;
	}
	
	trans_act = automate2->tab_transition[automate2->etat_initial->num];
	while(trans_act != NULL){
		
		etat_tmp = automate1->liste_etat;
		while(etat_tmp!=NULL && etat_tmp->accepteur==1){
			
			//Si l'etat initial de l'automate2 n'est pas final, les etats finaux de l'automate1 ne le sont plus
			if(automate2->etat_initial->accepteur == 0){
				etat_tmp->accepteur = 0;
			}
			
			//On passe à l'état suivant
			if(etat_tmp->etat_suivant!=NULL){
				etat_tmp = etat_tmp->etat_suivant;
			}
			else{
				break;
			}
		}
		
		trans_tmp = trans_act->transitionSuivante;
		free(trans_act);
		trans_act = trans_tmp;
	}
	
	//ajout des etats de l'automate 2 dans l'automate 1
	if(automate1->liste_etat->accepteur == 0){ //si l'automate 1 n'a pas d'états accepteurs, on ajoute au début en modifiant les numéros
		etat_tmp = automate1->liste_etat;
		if(automate2->liste_etat == automate2->etat_initial) {
			automate1->liste_etat = automate2->liste_etat->etat_suivant;
		}
		else{
			automate1->liste_etat = automate2->liste_etat;
			automate1->liste_etat->num = automate1->liste_etat->num + automate1->nombreEtats - 1;
		}
		etat_act = automate1->liste_etat;
		for(i=0;i<automate2->nombreEtats-1;i++){
			if(etat_act->etat_suivant == automate2->etat_initial){
				etat_act->etat_suivant = automate2->etat_initial->etat_suivant;
			}
			else{
				etat_act->etat_suivant->num = etat_act->etat_suivant->num + automate1->nombreEtats - 1;
				etat_act = etat_act->etat_suivant;
			}

		}
		if(etat_act == NULL){//si automate 2 n'a qu'un état initial
			automate1->liste_etat = etat_tmp;
		}
		else{
			etat_act->etat_suivant = etat_tmp;
		}
	}

	else {

		//sinon on ajoute les états de l'automate 2 à la fin des états accepteurs de l'automate 1 et on modifie leur numéro
		etat_act = automate1->liste_etat;
		while(etat_act->etat_suivant != NULL && etat_act->etat_suivant->accepteur == 1){
			etat_act = etat_act->etat_suivant;
		}
		etat_tmp = etat_act->etat_suivant;
		etat_act->etat_suivant = automate2->liste_etat;
		for(i=0;i<automate2->nombreEtats;i++){
			if(etat_act->etat_suivant == automate2->etat_initial){
				etat_act->etat_suivant = automate2->etat_initial->etat_suivant;
			}
			else{
				etat_act->etat_suivant->num = etat_act->etat_suivant->num + automate1->nombreEtats - 1;
				etat_act = etat_act->etat_suivant;
			}

		}
		etat_act->etat_suivant = etat_tmp;
	}
	
	for(i=0;i<automate2->nombreEtats;i++){
	//On ajoute les transitions restantes à la suite de celles de l'automate1
		if(i != automate2->etat_initial->num){
			trans_act = automate2->tab_transition[i];
			while(trans_act != NULL){
				trans_tmp = trans_act->transitionSuivante;
				ajout_transition(trans_act,automate1->tab_transition);
				trans_act = trans_tmp;
			}
		}
	}

	//on change le nombre d'états de l'automate 1
	automate1->nombreEtats = automate1->nombreEtats + automate2->nombreEtats - 1;

	//suppressions de l'init de automate2
	free(automate2->etat_initial);
	free(automate2->tab_transition);
	free(automate2);
}

//Mise à l'étoile (ou fermeture itérative de Kleene) de l'automate
void mise_etoile(Automate_non_deterministe* automate){
	Etat* etat_act = NULL;
	Etat* etat_tmp = NULL;
	Transition* transition_act = NULL;
	Transition* nouvelle_transition = NULL;

	etat_act = automate->liste_etat;
	while(etat_act != NULL && etat_act->accepteur == 1){ //pour chaque état accepteur
		if(etat_act != automate->etat_initial){//sauf l'état initial (il a déjà les transitions)
			transition_act = automate->tab_transition[automate->etat_initial->num];
			while(transition_act != NULL){//on ajoute les transitions de l'état initial
				nouvelle_transition = malloc(sizeof(Transition));
				nouvelle_transition->depart = etat_act;
				nouvelle_transition->arrivee = transition_act->arrivee;
				nouvelle_transition->caractere = transition_act->caractere;
				nouvelle_transition->transitionSuivante = NULL;

				ajout_transition(nouvelle_transition,automate->tab_transition);

				transition_act = transition_act->transitionSuivante;
			}
		}

		etat_act = etat_act->etat_suivant;
	}

	//on rend l'état initial accepteur et on le met au bon endroit dans la liste
	if(automate->etat_initial->accepteur == 0){
		automate->etat_initial->accepteur = 1;
		etat_act = automate->liste_etat;
		if(etat_act != automate->etat_initial){
			while(etat_act->etat_suivant != automate->etat_initial){
				etat_act = etat_act->etat_suivant;
			}
			etat_act->etat_suivant = automate->etat_initial->etat_suivant;
			etat_tmp = automate->liste_etat;
			automate->liste_etat = automate->etat_initial;
			automate->etat_initial->etat_suivant = etat_tmp;
		}

	}
}


//free un automate
void free_automate(Automate_non_deterministe* automate){
	int i;
	Transition* transition_act;
	Transition* transition_tmp;
	Caractere* caractere_act;
	Caractere* caractere_tmp;
	Etat* etat_act;
	Etat* etat_tmp;

	caractere_act = automate->alphabet;
	while(caractere_act != NULL && caractere_act->caractere_suivant != NULL){
		caractere_tmp = caractere_act->caractere_suivant;
		caractere_act->caractere_suivant = caractere_tmp->caractere_suivant;
		free(caractere_tmp);
	}
	free(caractere_act);

	etat_act = automate->liste_etat;
	while(etat_act != NULL && etat_act->etat_suivant != NULL){
		etat_tmp = etat_act->etat_suivant;
		etat_act->etat_suivant = etat_tmp->etat_suivant;
		free(etat_tmp);
	}
	free(etat_act);

	for(i=0;i<automate->nombreEtats;i++){
		transition_act = automate->tab_transition[i];
		while(transition_act != NULL && transition_act->transitionSuivante != NULL){
			transition_tmp = transition_act->transitionSuivante;
			transition_act->transitionSuivante = transition_tmp->transitionSuivante;
			free(transition_tmp);
		}
		free(transition_act);
	}
	free(automate->tab_transition);

	free(automate);
}
