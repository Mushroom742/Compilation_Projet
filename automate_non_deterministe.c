#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

#include <stdio.h>
#include <stdlib.h>

//TO DO : MODIFIER 3 FONCTIONS DE BASE AVEC NOUVELLE STRUCTURE

//Renvoie un automate non déterministe reconnaissant le langage vide
Automate_non_deterministe langage_vide(){
	Automate_non_deterministe automate;
	Etat* etat = malloc(sizeof(Etat*));

	etat->num = 0;
	etat->accepteur = 0;
	etat->etat_suivant = NULL;

	automate.alphabet = NULL;
	automate.nombreEtats = 1;
	automate.liste_etat = etat;
	automate.etat_initial = etat;
	automate.tab_transition = init_tab_transition(1);

	return automate;

}

//Renvoie un automate non déterministe reconnaissant le mot vide
Automate_non_deterministe mot_vide(){
	Automate_non_deterministe automate;
	Etat* etat = malloc(sizeof(Etat*));

	etat->num = 0;
	etat->accepteur = 1;
	etat->etat_suivant = NULL;

	automate.alphabet = NULL;
	automate.nombreEtats = 1;
	automate.liste_etat = etat;
	automate.etat_initial = etat;
	automate.tab_transition = init_tab_transition(1);

	return automate;
}

//Renvoie un automate standard reconnaissant le langage composé d’un mot d’un caractère passé en paramètre
Automate_non_deterministe un_mot(char symbole){
	Automate_non_deterministe automate;
	Etat* etat_init = malloc(sizeof(Etat*));
	Etat* etat_final = malloc(sizeof(Etat*));
	Transition* transition = malloc(sizeof(Transition*));
	Caractere* caractere = malloc(sizeof(Caractere*));

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

	automate.alphabet = caractere;
	automate.nombreEtats = 2;
	automate.liste_etat = etat_final;
	automate.etat_initial = etat_init;
	automate.tab_transition = init_tab_transition(2);
	automate.tab_transition[0] = transition;

	return automate;
}

//A MODIFIER (laisse le moi)
//Renvoie la réunion de 2 alphabets
/*Alphabet reunion_alphabet(Alphabet alphabet1, Alphabet alphabet2){
	Alphabet alphabet;
	int i;

	for(i=0;i<TAILLE_ASCII;i++){
		alphabet.caractere[i] = alphabet1.caractere[i] | alphabet2.caractere[i];
	}

	return alphabet
}*/


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
	/*Transition* transition_act = tab_transition[transition->depart];

	tab_transition[transition->depart] = transition;
	transition->transitionSuivante = transition_act;*/

}


//Affiche un automate
void affichage_automate_non_deterministe(Automate_non_deterministe automate){
	int i;
	Transition* transition_act;
	Caractere* caractere_act;
	Etat* etat_act;

	printf("Alphabet :");
	caractere_act = automate.alphabet;
	while(caractere_act != NULL){
		printf(" %c,",caractere_act->symbole);
		caractere_act = caractere_act->caractere_suivant;
	}
	printf("\nNb états : %d \n",automate.nombreEtats);
	printf("Etat initial : %d \n",automate.etat_initial->num);
	printf("Etats accepteurs :");
	etat_act = automate.liste_etat;
	while(etat_act != NULL && (etat_act->accepteur == 1)){
		printf(" %d,",etat_act->num);
		etat_act = etat_act->etat_suivant;
	}
	printf("\nTransitions :");
	for(i=0;i<automate.nombreEtats;i++){
		transition_act = automate.tab_transition[i];
		while(transition_act != NULL){
			printf(" (%d,%c,%d),",transition_act->depart->num,transition_act->caractere->symbole,transition_act->arrivee->num);
			transition_act = transition_act->transitionSuivante;
		}
	}
	printf("\n");
}

//A MODIFIER
//Renvoie un automate standard reconnaissant la réunion des langages des 2 automates passés en paramètre
Automate_non_deterministe reunion(Automate_non_deterministe automate1, Automate_non_deterministe automate2){
	Automate_non_deterministe automate;
	int i;

	/*automate.alphabet = reunion_alphabet(automate1.alphabet,automate2.alphabet);
	automate.nombreEtats = automate1.nombreEtats + automate2.nombreEtats - 1;
	automate.etat_initial = 0;
	automate.nombreEtatsFinaux = automate1.nombreEtatsFinaux + automate2.nombreEtatsFinaux;
	automate.liste_etats_accepteurs = alloc_tab_etat(automate.nombreEtatsFinaux);
	for(i=0;i<automate.nombreEtatsFinaux;i++){
		if(i<automate1.nombreEtatsFinaux){
			automate.liste_etats_accepteurs[i] = automate1.liste_etats_accepteurs[i];
		}
		else {
			automate.liste_etats_accepteurs[i] = automate2.liste_etats_accepteurs[i - automate1.nombreEtatsFinaux] + automate1.nombreEtatsFinaux;
		}
	}*/





}
