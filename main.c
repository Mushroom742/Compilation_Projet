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
	Automate_non_deterministe* auto7 = NULL;

	Automate_deterministe* auto6 = NULL;

	auto1 = un_mot('a');

	auto2 = un_mot('d');

	concatenation(auto1,auto2);

	auto3 = un_mot('e');

	reunion(auto1,auto3);

	mise_etoile(auto1);

	auto4 = un_mot('a');

	auto5 = un_mot('b');


	reunion(auto4,auto5);

	printf("concatenation\n");
	reunion(auto1,auto4);
	
	auto7 = un_mot('!');
	reunion(auto1,auto7);
	affichage_automate_non_deterministe(auto1);

	auto6 = determinisation(auto1);
	affichage_auto_deterministe(auto6);

	free_automate(auto1);
	free_auto_deterministe(auto6);

	return 0;
}
