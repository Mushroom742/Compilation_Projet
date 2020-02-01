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
	automate.tab_transition = NULL;

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
	automate.tab_transition = NULL;

	return automate;
}

//Renvoi un automate standard reconnaissant le langage composé d’un mot d’un caractère passé en paramètre
Automate_non_deterministe un_mot(char symbole){
	Automate_non_deterministe automate;
	int int_symbole = symbole;

	automate.alphabet = init_alphabet();
	automate.alphabet.caractere[int_symbole] = True;
	automate.nombreEtats = 2;
	automate.nombreEtatsFinaux = 1;
	automate.etat_initial = 0;
	automate.liste_etats_accepteurs = alloc_tab_etat(1);
	automate.liste_etats_accepteurs[0] = 1;
	automate.tab_transition = init_tab_transition(1);
	automate.tab_transition[0].depart = 0;
	automate.tab_transition[0].arrivee = 1;
	automate.tab_transition[0].depart = symbole;

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
Transition* init_tab_transition(int taille){
	Transition* tab_transition = NULL;
	int i;

	tab_transition = malloc(taille * sizeof(Transition));
	for(i=0;i<taille;i++){
		tab_transition[i].transitionSuivante = NULL;
	}

	return tab_transition;
}
