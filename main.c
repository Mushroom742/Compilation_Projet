#include <stdio.h>
#include <stdlib.h>
#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

int main (){
	Automate_non_deterministe* liste_automate_nd = NULL;
	Automate_non_deterministe* auto_nd = NULL;
	Automate_non_deterministe* auto_nd_act = NULL;
	Automate_non_deterministe* auto1_nd = NULL;
	Automate_non_deterministe* auto2_nd = NULL;
	Automate_deterministe* liste_automate_d = NULL;
	int choix,choix_auto1,choix_auto2,i;
	int nb_auto_nd = 0;
	int nb_auto_d = 0;
	char lettre;
	
	do{
		printf("***** Analyseur lexical ****\nQue voulez-vous faire ?\n");
		printf("(0) Quitter\n(1) Langage vide\n(2) Mot vide\n(3) Un mot\n");
		printf("(4) Réunion\n(5) Concaténation\n(6) Mise à l'étoile\n");
		printf("(7) Exécution d'un mot\n(8) Déterminisation\n(9) Minimisation\n");
		
		scanf(" %d",&choix);
		
		switch(choix){
			case 0: //quitter
				break;
			case 1: //Langage vide
				auto_nd = langage_vide();
				//ajout à la liste
				auto_nd->automate_suivant = liste_automate_nd;
				liste_automate_nd = auto_nd;
				nb_auto_nd++;
				
				printf("Automate créé :\n");
				affichage_automate_non_deterministe(auto_nd);
				
				break;
			case 2: //Mot vide
				auto_nd = mot_vide();
				//ajout à la liste
				auto_nd->automate_suivant = liste_automate_nd;
				liste_automate_nd = auto_nd;
				nb_auto_nd++;
				
				printf("Automate créé :\n");
				affichage_automate_non_deterministe(auto_nd);
				
				break;
			case 3: //Un mot
				printf("Entrez un caractère \n");
				scanf(" %c",&lettre);
				
				auto_nd = un_mot(lettre);
				//ajout à la liste
				auto_nd->automate_suivant = liste_automate_nd;
				liste_automate_nd = auto_nd;
				nb_auto_nd++;
				
				printf("Automate créé :\n");
				affichage_automate_non_deterministe(auto_nd);
				
				break;				
			case 4://reunion
				if(nb_auto_nd < 2){
					printf("Il faut au moins 2 automates non déterministes pour faire une réunion\n");
				}
				else{
					do{ //choix du 1er automate
						printf("Choisissez le 1er automate\n");
						auto_nd_act = liste_automate_nd;
						for(i=0;i<nb_auto_nd;i++){
							printf("(%d)\n",i);
							affichage_automate_non_deterministe(auto_nd_act);
							auto_nd_act = auto_nd_act->automate_suivant;
						}
						scanf(" %d",&choix_auto1);
					} while(choix_auto1 < 0 || choix_auto1 >= nb_auto_nd);
					
					do{ //choix du 2e automate
						printf("Choisissez le 2e automate\n");
						auto_nd_act = liste_automate_nd;
						for(i=0;i<nb_auto_nd;i++){
							if(i != choix_auto1){
								printf("(%d)\n",i);
								affichage_automate_non_deterministe(auto_nd_act);
							}
							auto_nd_act = auto_nd_act->automate_suivant;
						}
						scanf(" %d",&choix_auto2);
					} while(choix_auto2 < 0 || choix_auto2 >= nb_auto_nd || choix_auto2 == choix_auto1);
					
					//recherche des automates dans la liste
					auto_nd_act = liste_automate_nd;
					i = 0;
					while(auto1_nd == NULL || auto2_nd == NULL){
						if(i == choix_auto1){
							auto1_nd = auto_nd_act;
						}
						else if(i == choix_auto2){
							auto2_nd = auto_nd_act;
						}

						auto_nd_act = auto_nd_act->automate_suivant;
						i++;
					}
					
					//suppression de l'automate 2 dans la liste
					if(choix_auto2 == 0){
						liste_automate_nd = auto2_nd->automate_suivant;
					}
					else{
						auto_nd_act = liste_automate_nd;
						for(i=0;i<choix_auto2-1;i++){
							auto_nd_act = auto_nd_act->automate_suivant;
						}
						auto_nd_act->automate_suivant = auto2_nd->automate_suivant;
					}
					nb_auto_nd--;
					
					//reunion
					reunion(auto1_nd,auto2_nd);
					printf("Automate créé : \n");
					affichage_automate_non_deterministe(auto1_nd);
					
					//Remise à NULL
					auto1_nd = NULL;
					auto2_nd = NULL;
				}
					
				break;
					
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			default:
				
				break;
		}
	} while(choix != 0);

	return 0;
}
