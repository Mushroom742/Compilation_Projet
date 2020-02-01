#include <stdio.h>
#include <stdlib.h>
#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

int main (){
	Automate_non_deterministe auto_langage_vide;
	Transition transition;

	auto_langage_vide = un_mot('X',&transition);

	affichage_automate_non_deterministe(auto_langage_vide);
	
	free(auto_langage_vide.tab_transition);

	return 0;
}
