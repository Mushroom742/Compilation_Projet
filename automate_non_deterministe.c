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

