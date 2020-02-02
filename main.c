#include <stdio.h>
#include <stdlib.h>
#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

int main (){
	Automate_non_deterministe* liste_automate = NULL;
	Automate_non_deterministe* auto1 = NULL;
	Automate_non_deterministe* auto2 = NULL;

	auto1 = un_mot('a');
	affichage_automate_non_deterministe(auto1);
	
	auto2 = un_mot('a');
	affichage_automate_non_deterministe(auto2);
	
	reunion(auto1,auto2);
	affichage_automate_non_deterministe(auto1);
	
	free_automate(auto1);

	return 0;
}
