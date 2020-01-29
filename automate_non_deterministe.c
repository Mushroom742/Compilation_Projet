#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

#include <stdio.h>
#include <stdlib.h>

//Renvoie un automate non déterministe reconnaissant le langage vide
Automate_non_deterministe langage_vide(){
	Automate_non_deterministe automate;
	Etat etat;

	etat.num = 0;

	automate.alphabet = init_alphabet();
	automate.liste_etat = alloc_tab_etat(1);
	automate.liste_etat[0] = etat;
	automate.etat_initial = etat;
	automate.liste_etats_accepteurs = NULL;
	automate.tab_transition = NULL;

	return automate;

}

//Renvoie un automate non déterministe reconnaissant le mot vide
Automate_non_deterministe mot_vide(){
	Automate_non_deterministe automate;
	Etat etat;

	etat.num = 0;

	automate.alphabet = init_alphabet();
	automate.liste_etat = alloc_tab_etat(1);
	automate.liste_etat[0] = etat;
	automate.etat_initial = etat;
	automate.liste_etats_accepteurs = alloc_tab_etat(1);
	automate.liste_etats_accepteurs[0] = etat;
	automate.tab_transition = NULL;

	return automate;
}

//Renvoi un automate standard reconnaissant le langage composé d’un mot d’un caractère passé en paramètre
Automate_non_deterministe un_mot(char symbole){
	Automate_non_deterministe automate;
	Etat etat_init, etat_final;
	int int_symbole = symbole;

	etat_init.num = 0;
	etat_final.num = 1;

	automate.alphabet = init_alphabet();
	automate.alphabet.caractere[int_symbole] = True;
	automate.liste_etat = alloc_tab_etat(2);
	automate.liste_etat[0] = etat_init;
	automate.liste_etat[1] = etat_final;
	automate.etat_initial = etat_init;
	automate.liste_etats_accepteurs = alloc_tab_etat(1);
	automate.liste_etats_accepteurs[0] = etat_final;
	automate.tab_transition = init_tab_transition(1);
	automate.tab_transition[etat_init.num][etat_final.num].depart = etat_init;
	automate.tab_transition[etat_init.num][etat_final.num].arrivee = etat_final;
	automate.tab_transition[etat_init.num][etat_final.num].symbole = symbole;

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

//Création d'un tableau d'état alloué dynamiquement
Etat* alloc_tab_etat(int taille){
	Etat* tab_etat = NULL;

	tab_etat = malloc(taille * sizeof(Etat));

	return tab_etat;
}

//Création d'un tableau de transitions alloué dynamiquement et initialise les états de départ à -1
Transition** init_tab_transition(int taille){
	Transition** tab_transition = NULL;
	int i,j;

	tab_transition = malloc(taille * sizeof(Transition*));
	for(i=0;i<taille;i++){
		tab_transition[i] = malloc(taille * sizeof(Transition));
		for(j=0;j<taille;j++){
			tab_transition[i][j].depart.num = -1;
		}
	}



	return tab_transition;
}
