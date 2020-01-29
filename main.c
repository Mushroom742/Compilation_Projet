#include <stdio.h>
#include <stdlib.h>
#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

int main (void){
	Automate_non_deterministe auto_langage_vide;
	int i;

	auto_langage_vide = un_mot('X');

	printf(" num état : %d \n",auto_langage_vide.liste_etat[0].num);
	printf(" num état : %d \n",auto_langage_vide.liste_etat[1].num);
	printf(" num état initial : %d\n",auto_langage_vide.etat_initial.num);
	printf(" num état accepteur: %d \n",auto_langage_vide.liste_etats_accepteurs[0].num);

	for(i=0;i<2;i++){
		if(auto_langage_vide.tab_transition[auto_langage_vide.etat_initial.num][i].depart.num!=-1){
			printf(" Transition 1 init: %d \n",auto_langage_vide.tab_transition[auto_langage_vide.etat_initial.num][i].depart.num);
			printf(" Transition 1 arrivee: %d \n",auto_langage_vide.tab_transition[auto_langage_vide.etat_initial.num][i].arrivee.num);
			printf(" Transition 1 symbole: %c \n",auto_langage_vide.tab_transition[auto_langage_vide.etat_initial.num][i].symbole);
		}
	}

	free(auto_langage_vide.liste_etat);
	free(auto_langage_vide.liste_etats_accepteurs);

	for(i=0;i<1;i++){
		free(auto_langage_vide.tab_transition[i]);
	}
	free(auto_langage_vide.tab_transition);

	return 0;
}
