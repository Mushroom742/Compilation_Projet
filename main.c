#include <stdio.h>
#include <stdlib.h>
#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

int main (){
	Automate_non_deterministe automate;

	automate = un_mot('a');

	affichage_automate_non_deterministe(automate);
	
	//free(auto_langage_vide.tab_transition);

	return 0;
}
