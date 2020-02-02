#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

#include <stdio.h>
#include <stdlib.h>

//TO DO : Gérer doublons dans alphabet + free des doublons

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

//Ajoute l'alphabet 2 dans l'alphabet 1
void reunion_alphabet(Caractere* alphabet1, Caractere* alphabet2){
	Caractere* caract_act1 = alphabet1;
	Caractere* caract_act2 = alphabet2;
	Caractere* tmp1 = NULL;
	Caractere* tmp2 = NULL;
	
	while(caract_act2 != NULL){
		if(caract_act1 == NULL){//alphabet1 fini
			caract_act1 = caract_act2;
			return;
		}
		
		//tri fusion
		while(caract_act1->caractere_suivant != NULL && caract_act1->caractere_suivant->symbole < caract_act2->symbole){
			caract_act1 = caract_act1->caractere_suivant;
		}
		if(caract_act1->caractere_suivant == NULL){//si fin de l'alphabet1
			caract_act1->caractere_suivant = caract_act2;
			return;
		}
		else if(caract_act1->caractere_suivant->symbole == caract_act2->symbole){//si même caractère dans les 2 alphabets
			caract_act2 = caract_act2->caractere_suivant;
		}
		else{//on ajoute le caractère 2 après le caractère 1 et on avance dans l'alphabet 2
			tmp1 = caract_act1->caractere_suivant;
			tmp2 = caract_act2->caractere_suivant;
			caract_act1->caractere_suivant = caract_act2;
			caract_act2->caractere_suivant = tmp1;
			caract_act2 = tmp2;
		}
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

//Renvoie un automate standard reconnaissant la réunion des langages des 2 automates passés en paramètre
void reunion(Automate_non_deterministe* automate1, Automate_non_deterministe* automate2){
	Etat* etat_act = NULL;
	Etat* etat_tmp = NULL;
	int i,nb_etat;
	Transition* trans_act = NULL;
	Transition* trans_tmp = NULL;
	
	
	reunion_alphabet(automate1->alphabet,automate2->alphabet);
	
	//on ajoute les états de l'automate 2 à la fin des états accepteurs de l'automate 1 et on modifie leur numéro
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
	
	//on change le nombre d'états de l'automate 1
	nb_etat = automate1->nombreEtats;
	automate1->nombreEtats = automate1->nombreEtats + automate2->nombreEtats - 1;
	
	//réallocation du tableau de transition + remplissage avec les transitions de l'automate 2
	automate1->tab_transition = (Transition**) realloc(automate1->tab_transition, automate1->nombreEtats * sizeof(Transition*));

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

}

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
