#include <stdio.h>
#include <stdlib.h>
#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

int main (void){
	Automate_non_deterministe auto_langage_vide;

	auto_langage_vide = mot_vide();

	printf(" num état : %d \n",auto_langage_vide.liste_etat[0].num);
	printf(" num état accepteur: %d \n",auto_langage_vide.liste_etats_accepteurs[0].num);

	free(auto_langage_vide.liste_etat);
	free(auto_langage_vide.liste_etats_accepteurs);

	return 0;
}
