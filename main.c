#include <stdio.h>
#include <stdlib.h>
#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

int main (){
	Automate_non_deterministe* liste_automate_nd = NULL;
	Automate_non_deterministe* auto_nd_act = NULL;
	Automate_non_deterministe* auto1_nd = NULL;
	Automate_non_deterministe* auto2_nd = NULL;
	Automate_deterministe* liste_automate_d = NULL;
	Automate_deterministe* auto_d_act = NULL;
	Automate_deterministe* auto_d = NULL;
	int choix,choix_auto1,choix_auto2,i;
	int nb_auto_nd = 0;
	int nb_auto_d = 0;
	char lettre;
	char mot[100];
	
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
				auto1_nd = langage_vide();
				//ajout à la liste
				auto1_nd->automate_suivant = liste_automate_nd;
				liste_automate_nd = auto1_nd;
				nb_auto_nd++;
				
				printf("Automate créé :\n");
				affichage_automate_non_deterministe(auto1_nd);
				
				//Remise à NULL
				auto1_nd = NULL;
				
				break;
			case 2: //Mot vide
				auto1_nd = mot_vide();
				//ajout à la liste
				auto1_nd->automate_suivant = liste_automate_nd;
				liste_automate_nd = auto1_nd;
				nb_auto_nd++;
				
				printf("Automate créé :\n");
				affichage_automate_non_deterministe(auto1_nd);
				
				//Remise à NULL
				auto1_nd = NULL;
				
				break;
			case 3: //Un mot
				printf("Entrez un caractère \n");
				scanf(" %c",&lettre);
				
				auto1_nd = un_mot(lettre);
				//ajout à la liste
				auto1_nd->automate_suivant = liste_automate_nd;
				liste_automate_nd = auto1_nd;
				nb_auto_nd++;
				
				printf("Automate créé :\n");
				affichage_automate_non_deterministe(auto1_nd);
				
				//Remise à NULL
				auto1_nd = NULL;
				
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
					
			case 5: //concaténation
				if(nb_auto_nd < 2){
					printf("Il faut au moins 2 automates non déterministes pour faire une concaténation\n");
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
					
					//concaténation
					concatenation(auto1_nd,auto2_nd);
					printf("Automate créé : \n");
					affichage_automate_non_deterministe(auto1_nd);
					
					//Remise à NULL
					auto1_nd = NULL;
					auto2_nd = NULL;
				}
					
				break;
			case 6: //mise à l'étoile
				if(nb_auto_nd < 1){
					printf("Il faut au moins 1 automate non déterministe pour faire une mise à l'étoile\n");
				}
				else{
					do{ //choix de l'automate
						printf("Choisissez l'automate\n");
						auto_nd_act = liste_automate_nd;
						for(i=0;i<nb_auto_nd;i++){
							printf("(%d)\n",i);
							affichage_automate_non_deterministe(auto_nd_act);
							auto_nd_act = auto_nd_act->automate_suivant;
						}
						scanf(" %d",&choix_auto1);
					} while(choix_auto1 < 0 || choix_auto1 >= nb_auto_nd);
					
					//recherche des automates dans la liste
					auto_nd_act = liste_automate_nd;
					i = 0;
					while(auto1_nd == NULL){
						if(i == choix_auto1){
							auto1_nd = auto_nd_act;
						}
						auto_nd_act = auto_nd_act->automate_suivant;
						i++;
					}
					
					//mise à l'étoile
					mise_etoile(auto1_nd);
					printf("Automate créé : \n");
					affichage_automate_non_deterministe(auto1_nd);
					
					//Remise à NULL
					auto1_nd = NULL;
				}
					
				break;
				
			case 7: //exécution d'un mot
				if(nb_auto_d < 1){
					printf("Il faut au moins 1 automate déterministe pour réaliser l'exécution d'un mot\n");
				}
				else{
					do{ //choix de l'automate
						printf("Choisissez l'automate\n");
						auto_d_act = liste_automate_d;
						for(i=0;i<nb_auto_d;i++){
							printf("(%d)\n",i);
							affichage_auto_deterministe(auto_d_act);
							auto_d_act = auto_d_act->automate_suivant;
						}
						scanf(" %d",&choix_auto1);
					} while(choix_auto1 < 0 || choix_auto1 >= nb_auto_d);
					
					//recherche de l'automate dans la liste
					auto_d_act = liste_automate_d;
					i = 0;
					while(auto_d == NULL){
						if(i == choix_auto1){
							auto_d = auto_d_act;
						}
						auto_d_act = auto_d_act->automate_suivant;
						i++;
					}
					
					//entrée du mot
					printf("Entrez le mot\n");
					scanf(" %s",mot);
					
					//execution du mot
					execution_mot(auto_d,mot);
					
					//Remise à NULL
					auto_d = NULL;
				}
					
				break;
				
			case 8: //déterminisation
				if(nb_auto_nd < 1){
					printf("Il faut au moins 1 automate non déterministe pour faire une déterminisation\n");
				}
				else{
					do{ //choix de l'automate
						printf("Choisissez l'automate\n");
						auto_nd_act = liste_automate_nd;
						for(i=0;i<nb_auto_nd;i++){
							printf("(%d)\n",i);
							affichage_automate_non_deterministe(auto_nd_act);
							auto_nd_act = auto_nd_act->automate_suivant;
						}
						scanf(" %d",&choix_auto1);
					} while(choix_auto1 < 0 || choix_auto1 >= nb_auto_nd);
					
					//recherche de l'automate dans la liste
					auto_nd_act = liste_automate_nd;
					i = 0;
					while(auto1_nd == NULL){
						if(i == choix_auto1){
							auto1_nd = auto_nd_act;
						}
						auto_nd_act = auto_nd_act->automate_suivant;
						i++;
					}
					
					//determinisation
					auto_d = determinisation(auto1_nd);
					printf("Automate créé : \n");
					affichage_auto_deterministe(auto_d);
					
					//ajout à la liste
					auto_d->automate_suivant = liste_automate_d;
					liste_automate_d = auto_d;
					nb_auto_d++;
					
					//PENSER A FREE L'AUTOMATE NON DETERMINISTE ?
					
					//Remise à NULL
					auto_d = NULL;
					auto1_nd = NULL;
				}
					
				break;
				
			case 9: //minimisation
				if(nb_auto_d < 1){
					printf("Il faut au moins 1 automate déterministe pour faire la minimisation\n");
				}
				else{
					do{ //choix de l'automate
						printf("Choisissez l'automate\n");
						auto_d_act = liste_automate_d;
						for(i=0;i<nb_auto_d;i++){
							printf("(%d)\n",i);
							affichage_auto_deterministe(auto_d_act);
							auto_d_act = auto_d_act->automate_suivant;
						}
						scanf(" %d",&choix_auto1);
					} while(choix_auto1 < 0 || choix_auto1 >= nb_auto_d);
					
					//recherche de l'automate dans la liste
					auto_d_act = liste_automate_d;
					i = 0;
					while(auto_d == NULL){
						if(i == choix_auto1){
							auto_d = auto_d_act;
						}
						auto_d_act = auto_d_act->automate_suivant;
						i++;
					}
					
					//minimisation
					minimisation(auto_d);
					
					
					//Remise à NULL
					auto_d = NULL;
				}
					
				break;
			default:
				printf("Le choix n'est pas dans la liste\n");
				
				break;
		}
	} while(choix != 0);
	
	//free liste automate non deterministe
	if(liste_automate_nd != NULL){
		auto_nd_act = liste_automate_nd;
		while(auto_nd_act->automate_suivant != NULL){
			auto1_nd = auto_nd_act->automate_suivant;
			auto_nd_act->automate_suivant = auto1_nd->automate_suivant;
			free_automate(auto1_nd);
		}
		free_automate(auto_nd_act);
	}
	
	//free liste automate deterministe
	if(liste_automate_d != NULL){
		auto_d_act = liste_automate_d;
		while(auto_d_act->automate_suivant != NULL){
			auto_d = auto_d_act->automate_suivant;
			auto_d_act->automate_suivant = auto_d->automate_suivant;
			free_auto_deterministe(auto_d);
		}
		free_auto_deterministe(auto_d_act);
	}

	return 0;
}
