#include <stdio.h>
#include <stdlib.h>
#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

int main (){
	Automate_non_deterministe* liste_automate = NULL;
	Automate_non_deterministe* auto1 = NULL;
	Automate_non_deterministe* auto2 = NULL;
	Automate_non_deterministe* auto3 = NULL;
	Automate_non_deterministe* auto4 = NULL;
	Automate_non_deterministe* auto5 = NULL;
	
	Automate_deterministe* auto6 = NULL;

	auto1 = un_mot('a');
	affichage_automate_non_deterministe(auto1);

	auto2 = un_mot('b');
	affichage_automate_non_deterministe(auto2);

	concatenation(auto1,auto2);
	affichage_automate_non_deterministe(auto1);
	
	auto3 = un_mot('b');
	affichage_automate_non_deterministe(auto3);
	
	reunion(auto1,auto3);
	affichage_automate_non_deterministe(auto1);
	mise_etoile(auto1);
	affichage_automate_non_deterministe(auto1);
	
	auto4 = un_mot('c');
	affichage_automate_non_deterministe(auto4);
	auto5 = mot_vide();
	affichage_automate_non_deterministe(auto5);
	
	reunion(auto4,auto5);
	affichage_automate_non_deterministe(auto4);
	concatenation(auto1,auto4);
	affichage_automate_non_deterministe(auto1);
	
	auto6 = determinisation(auto1);
	affichage_auto_deterministe(auto6);

	free_automate(auto1);
	free_auto_deterministe(auto6);

	return 0;
}
