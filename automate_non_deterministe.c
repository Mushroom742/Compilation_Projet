#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

#include <stdio.h>
#include <stdlib.h>

//Renvoie un automate non déterministe reconnaissant le langage vide
Automate_non_deterministe langage_vide(){
	Automate_non_deterministe automate;

	automate.alphabet = init_alphabet();
	automate.nombreEtats = 1;
	automate.nombreEtatsFinaux = 0;
	automate.etat_initial = 0;
	automate.liste_etats_accepteurs = NULL;
	automate.tab_transition = init_tab_transition(1);

	return automate;

}

//Renvoie un automate non déterministe reconnaissant le mot vide
Automate_non_deterministe mot_vide(){
	Automate_non_deterministe automate;

	automate.alphabet = init_alphabet();
	automate.nombreEtats = 1;
	automate.nombreEtatsFinaux = 1;
	automate.etat_initial = 0;
	automate.liste_etats_accepteurs = alloc_tab_etat(1);
	automate.liste_etats_accepteurs[0] = 0;
	automate.tab_transition = init_tab_transition(1);

	return automate;
}

/*Renvoie un automate standard reconnaissant le langage composé d’un mot d’un caractère passé en paramètre
 * néessite également une transition (vide) en paramètre pour l'ajouter dans le tableau de transitions sans la perdre*/
Automate_non_deterministe un_mot(char symbole,Transition* nouvelle_transition){
	Automate_non_deterministe automate;
	int int_symbole = symbole;

	automate.alphabet = init_alphabet();
	automate.alphabet.caractere[int_symbole] = True;
	automate.nombreEtats = 2;
	automate.nombreEtatsFinaux = 1;
	automate.etat_initial = 0;
	automate.liste_etats_accepteurs = alloc_tab_etat(1);
	automate.liste_etats_accepteurs[0] = 1;
	automate.tab_transition = init_tab_transition(2);
	
	nouvelle_transition->depart = 0;
	nouvelle_transition->arrivee = 1;
	nouvelle_transition->symbole = symbole;
	
	ajout_transition(nouvelle_transition,automate.tab_transition);

	return automate;
}

//Initialise les cases du tableau de l'alphabet à False
Alphabet init_alphabet(){
	Alphabet alphabet;
	int i;

	for(i=0;i<TAILLE_ASCII;i++){
		alphabet.caractere[i] = False;
	}

	return alphabet;
}

//Création d'un tableau d'état alloué dynamiquement représentant les états
int* alloc_tab_etat(int taille){
	int* tab_etat = NULL;

	tab_etat = malloc(taille * sizeof(int));

	return tab_etat;
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
	Transition* transition_act = tab_transition[transition->depart];
	
	tab_transition[transition->depart] = transition;
	transition->transitionSuivante = transition_act;
	
}


//Affiche un automate
void affichage_automate_non_deterministe(Automate_non_deterministe automate){
	int i;
	Transition* transition_act;
	
	printf("Nb états : %d \n",automate.nombreEtats);
	printf("Etat initial : %d \n",automate.etat_initial);
	printf("Etats accepteurs :");
	for(i=0;i<automate.nombreEtatsFinaux;i++){
		printf(" %d,",automate.liste_etats_accepteurs[i]);
	}
	printf("\nTransitions :");
	for(i=0;i<automate.nombreEtats;i++){
		transition_act = automate.tab_transition[i];
		while(transition_act != NULL){
			printf(" (%d,%c,%d),",transition_act->depart,transition_act->symbole,transition_act->arrivee);
			transition_act = transition_act->transitionSuivante;
		}
	}
	printf("\n");
}
	
	
