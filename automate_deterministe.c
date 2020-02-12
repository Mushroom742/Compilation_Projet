#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void execution_mot(Automate_deterministe* automate, char* mot){
    int i=0;
    bool error = 0, caractere_trouve = 0;
    Groupe_etat* groupe_etat_act = NULL;
    Caractere* caractere_tmp = NULL;

    //Groupe initial
    groupe_etat_act = automate->liste_groupe_etat;
    if(groupe_etat_act->numero!=automate->groupe_etat_initial->numero){
        do{
            groupe_etat_act = groupe_etat_act->groupe_etat_suivant;
        }while(groupe_etat_act->numero!=automate->groupe_etat_initial->numero);
    }

    //Pour toutes les lettres du mot
    while(mot[i]!='\0'&&error == 0){

        //On cherche le caractère dans l'alphabet
        caractere_tmp = automate->alphabet;
        caractere_trouve=0;
        while(caractere_tmp!=NULL&&caractere_trouve == 0){
            if(caractere_tmp->symbole == mot[i]){
                caractere_trouve = 1;
            }
            else{
                caractere_tmp = caractere_tmp->caractere_suivant;
            }
        }

        if (caractere_trouve == 1){
            //On retrouve la transitions et on actualise le groupe actuel
            groupe_etat_act = automate->tab_transition[groupe_etat_act->numero][caractere_tmp->numero];
        }
        i++;
    }

    //On vérifie qu'on termine sur un groupe accepteur
    if(groupe_etat_act->accepteur == 1){
        printf("L'automate reconnait le mot.\n");
    }
    else{
        printf("Impossible\n");
    }
}

Automate_deterministe* determinisation(Automate_non_deterministe* automate_nd){
	Automate_deterministe* automate_d = malloc(sizeof(Automate_deterministe));
	Caractere* caractere_act;
	Groupe_etat* groupe_etat = NULL;
	Groupe_etat* groupe_etat_act = NULL;
	Groupe_etat* groupe_etat_match = NULL;
	Groupe_etat* groupe_etat_tmp = NULL;
	Etat* etat_act = NULL;
	Etat* etat_tmp;
	Transition* transition_act = NULL;
	Transition* transition_tmp;
	int i,j,nb_caractere;

	automate_d->alphabet = automate_nd->alphabet;
	//numérotation des caractères
	nb_caractere = 0;
	caractere_act = automate_d->alphabet;
	while(caractere_act != NULL){
		caractere_act->numero = nb_caractere;
		nb_caractere++;
		caractere_act = caractere_act->caractere_suivant;
	}

	//initialisation du 1er groupe d'état
	groupe_etat = creation_groupe_etat(automate_nd->etat_initial);

	//ajout du groupe à la liste
	automate_d->liste_groupe_etat = groupe_etat;
	automate_d->nb_groupe_etat = 1;
	automate_d->groupe_etat_initial = groupe_etat;

	//on crée la 1ère ligne du tableau de transition et on l'initialise à NULL
	automate_d->tab_transition = malloc(sizeof(Groupe_etat**));
	automate_d->tab_transition[0] = malloc(nb_caractere * sizeof(Groupe_etat*));
	for(i=0;i<nb_caractere;i++){
		automate_d->tab_transition[0][i] = NULL;
	}

	//parcours des groupes d'état
	groupe_etat_act = groupe_etat;
	while(groupe_etat_act != NULL){
		//parcours des états du groupe d'états
		for(i=0;i<groupe_etat_act->nb_etat;i++){
			etat_act = groupe_etat_act->tab_etat[i];
			if(etat_act != NULL){ //si ce n'est pas l'état mort
				//parcours des transitions de l'état
				transition_act = automate_nd->tab_transition[etat_act->num];
				while(transition_act != NULL){
					//si le groupe d'état n'existe pas
					if(automate_d->tab_transition[groupe_etat_act->numero][transition_act->caractere->numero] == NULL){
						//création du groupe d'état
						automate_d->tab_transition[groupe_etat_act->numero][transition_act->caractere->numero] = creation_groupe_etat(transition_act->arrivee);
					}
					else{//le groupe d'état existe déjà
						//on ajoute l'état au groupe d'état
						ajout_etat(transition_act->arrivee,automate_d->tab_transition[groupe_etat_act->numero][transition_act->caractere->numero]);
					}
					transition_act = transition_act->transitionSuivante;
				}
			}
			else { //état mort
				for(j=0;j<nb_caractere;j++){
					automate_d->tab_transition[groupe_etat_act->numero][j] = creation_groupe_etat(NULL);
				}
			}
		}
		//on parcourt la ligne et on regarde les nouveaux groupes d'état
		for(i=0;i<nb_caractere;i++){
			if(automate_d->tab_transition[groupe_etat_act->numero][i] == NULL){ //création de l'état mort
				automate_d->tab_transition[groupe_etat_act->numero][i] = creation_groupe_etat(NULL);
			}
			groupe_etat_match = match_groupe_etat(automate_d->tab_transition[groupe_etat_act->numero][i],automate_d->liste_groupe_etat);
			//si le groupe d'état n'est pas déjà présent, on l'ajoute à la liste
			if(groupe_etat_match == NULL){
				//ajout à la liste
				groupe_etat_tmp = groupe_etat_act->groupe_etat_suivant;
				groupe_etat_act->groupe_etat_suivant = automate_d->tab_transition[groupe_etat_act->numero][i];
				automate_d->tab_transition[groupe_etat_act->numero][i]->groupe_etat_suivant = groupe_etat_tmp;

				//changement de numéro
				automate_d->tab_transition[groupe_etat_act->numero][i]->numero = automate_d->nb_groupe_etat;

				//réallocation du tableau de transitions
				automate_d->tab_transition = realloc(automate_d->tab_transition,(automate_d->nb_groupe_etat + 1) * sizeof(Groupe_etat**));
				automate_d->tab_transition[automate_d->nb_groupe_etat] = malloc(nb_caractere * sizeof(Groupe_etat*));
				for(j=0;j<nb_caractere;j++){
					automate_d->tab_transition[automate_d->nb_groupe_etat][j] = NULL;
				}

				//changement du nombre de groupes d'état
				automate_d->nb_groupe_etat++;
			}
			else {//le groupe est déjà présent dans la liste
				//on le free
				free_groupe_etat(automate_d->tab_transition[groupe_etat_act->numero][i]);

				//on le remplace par le bon groupe
				automate_d->tab_transition[groupe_etat_act->numero][i] = groupe_etat_match;
			}
		}
		groupe_etat_act = groupe_etat_act->groupe_etat_suivant;
	}

	//tri de la liste des groupes d'état pour mettre les accepteurs en 1er
	groupe_etat_act = automate_d->liste_groupe_etat;
	while(groupe_etat_act != NULL && groupe_etat_act->groupe_etat_suivant != NULL){
		if(groupe_etat_act->groupe_etat_suivant->accepteur == 1){
			//on met le groupe suivant au début
			groupe_etat_tmp = groupe_etat_act->groupe_etat_suivant;
			groupe_etat_act->groupe_etat_suivant = groupe_etat_tmp->groupe_etat_suivant;
			groupe_etat_tmp->groupe_etat_suivant = automate_d->liste_groupe_etat;
			automate_d->liste_groupe_etat = groupe_etat_tmp;
		}
		else{
			groupe_etat_act = groupe_etat_act->groupe_etat_suivant;
		}
	}
	
	//free de l'automate non déterministe (sauf l'alphabet)
	etat_act = automate_nd->liste_etat;
	while(etat_act != NULL && etat_act->etat_suivant != NULL){
		etat_tmp = etat_act->etat_suivant;
		etat_act->etat_suivant = etat_tmp->etat_suivant;
		free(etat_tmp);
	}
	free(etat_act);

	for(i=0;i<automate_nd->nombreEtats;i++){
		transition_act = automate_nd->tab_transition[i];
		while(transition_act != NULL && transition_act->transitionSuivante != NULL){
			transition_tmp = transition_act->transitionSuivante;
			transition_act->transitionSuivante = transition_tmp->transitionSuivante;
			free(transition_tmp);
		}
		free(transition_act);
	}
	free(automate_nd->tab_transition);
	free(automate_nd);

	return automate_d;
}

//minimise un automate déterministe
void minimisation(Automate_deterministe* automate){
    Automate_deterministe* automate_m = malloc(sizeof(Automate_deterministe));

    int i,j,k;
    int nb_caractere = 0;
    int nb_etat=0;
    int ok = 0;

    Etat* etat_act = NULL;

    Groupe_etat* new_groupe = NULL;

    Groupe_etat* groupe_etat_act = automate->liste_groupe_etat;
    Groupe_etat* groupe_etat_tmp = NULL;
    Groupe_etat* tmp = NULL;
    Caractere* caractere_act = NULL;
    caractere_act = automate->alphabet;
    while(caractere_act!=NULL){
        nb_caractere++;
        caractere_act = caractere_act->caractere_suivant;
    }

    //Premiere ligne : init
    //Derniere ligne : Bilan
    int** tab = malloc((nb_caractere+2)*sizeof(int*));
    for(i=0;i<nb_caractere+2;i++){
        tab[i] = malloc(automate->nb_groupe_etat*sizeof(int));
    }

    automate_m->tab_transition = malloc(automate->nb_groupe_etat*sizeof(Groupe_etat**));
    for(i=0;i<automate->nb_groupe_etat;i++){
        automate_m->tab_transition[i] = malloc(nb_caractere*sizeof(Groupe_etat*));
    }

    //On transforme nos groupe d'etats en etats, et on stock la premiere initialisation
    i=0;
    while(groupe_etat_act!=NULL){
        etat_act = malloc(sizeof(Etat));
        if(groupe_etat_act->accepteur==1){
            etat_act->accepteur = 1;
            tab[0][groupe_etat_act->numero] = 0;
        }
        else{
            etat_act->accepteur = 0;
            tab[0][groupe_etat_act->numero] = 1;
        }
        etat_act->etat_suivant = NULL;
        etat_act->num = groupe_etat_act->numero;
        if(new_groupe == NULL){
			new_groupe = creation_groupe_etat(etat_act);
		}
		else{
			ajout_etat(etat_act,new_groupe);
		}
        groupe_etat_act = groupe_etat_act->groupe_etat_suivant;
        i++;
    }

    while (ok==0) {

        //On remplis les transitions de notre tableau
        for(i=0;i<nb_caractere;i++){
            for(j=0;j<new_groupe->nb_etat;j++){
                tab[i+1][j] = tab[0][new_groupe->tab_etat[automate->tab_transition[j][i]->numero]->num];
            }
        }

        //Initialisation du bilan
        for(i=0;i<new_groupe->nb_etat;i++){
            tab[nb_caractere+1][i] = -1;
        }

        //Bilan
        for(i=0;i<new_groupe->nb_etat;i++){
            //On compare avec les colonnes precedentes
            if(i==0){
                tab[nb_caractere+1][i]=nb_etat;
                nb_etat++;
            }
            for(j=0;j<i;j++){
                if(tab[0][j]==tab[0][i]){
                    tab[nb_caractere+1][i]=tab[nb_caractere+1][j];
                    for(k=1;k<nb_caractere;k++){
                        if(tab[k][i]!=tab[k][j]){
                            //Si on remarque une colonne qui diffère avec la même initialisation
                            tab[nb_caractere+1][i]=nb_etat;
                            nb_etat++;
                            j=i;
                            break;
                        }
                    }
                }
                else{
                    tab[nb_caractere+1][i]=nb_etat;
                    nb_etat++;
                    break;
                }
            }

        }

        ok=1;
        //On compare initialisation et bilan
        for(i=0;i<new_groupe->nb_etat;i++){
            if(tab[0][i]!=tab[nb_caractere+1][i]){
                ok=0;
            }
        }

        /*for(i=0;i<nb_caractere+2;i++){
            for(j=0;j<new_groupe->nb_etat;j++){
                printf("%d ", tab[i][j]);
            }
            printf("\n");
        }*/

        //Si il faut une étape supplémentaire, on remplace la ligne d'initialisation par celle du bilan
        if(ok==0){
            for(i=0;i<new_groupe->nb_etat;i++){
                tab[0][i] = tab[nb_caractere+1][i];
            }
            nb_etat = 0;
        }
    }

    //Création du nouvel automate
    automate_m->alphabet = automate->alphabet;
    automate_m->nb_groupe_etat = nb_etat;
    automate_m->automate_suivant = automate->automate_suivant;
    etat_act = NULL;

    groupe_etat_act = automate->liste_groupe_etat;
    automate_m->liste_groupe_etat = creation_groupe_etat(etat_act);
    groupe_etat_tmp = automate_m->liste_groupe_etat;

    //Etats
    while(groupe_etat_act!=NULL){
        if(groupe_etat_act==automate->groupe_etat_initial){
            automate_m->groupe_etat_initial = creation_groupe_etat(etat_act);
            automate_m->groupe_etat_initial->numero = tab[0][groupe_etat_act->numero];
        }
        if(groupe_etat_act->accepteur==1){
            groupe_etat_tmp->accepteur = 1;
        }
        groupe_etat_tmp->numero = tab[0][groupe_etat_act->numero];
        tmp = automate_m->liste_groupe_etat;
        while(tmp!=NULL){
            tmp=tmp->groupe_etat_suivant;
        }

        groupe_etat_tmp->numero = tab[0][groupe_etat_act->numero];
        groupe_etat_act = groupe_etat_act->groupe_etat_suivant;
        if(groupe_etat_act!=NULL){
            groupe_etat_tmp->groupe_etat_suivant = creation_groupe_etat(etat_act);
            groupe_etat_tmp = groupe_etat_tmp->groupe_etat_suivant;
        }
    }

    //Transitions
    for(i=0;i<automate->nb_groupe_etat;i++){
        for(j=0;j<nb_caractere;j++){
            groupe_etat_act = automate_m->liste_groupe_etat;
            ok=0;
            while(ok==0){
                if(tab[j+1][i]==groupe_etat_act->numero){
                    automate_m->tab_transition[i][j] = groupe_etat_act;
                    ok=1;
                }
                groupe_etat_act = groupe_etat_act->groupe_etat_suivant;
            }
        }
    }


    /*for(i=0;i<nb_caractere+2;i++){
        free(tab[i]);
    }
    free(tab);

    groupe_etat_act = automate->liste_groupe_etat;
	while(groupe_etat_act != NULL && groupe_etat_act->groupe_etat_suivant != NULL){
		groupe_etat_tmp = groupe_etat_act->groupe_etat_suivant;
		groupe_etat_act->groupe_etat_suivant = groupe_etat_tmp->groupe_etat_suivant;
		free_groupe_etat(groupe_etat_tmp);
	}
	free_groupe_etat(groupe_etat_act);

    free_groupe_etat(automate->groupe_etat_initial);*/

	/*for(i=0;i<automate->nb_groupe_etat;i++){
		free(automate->tab_transition[i]);
	}
	free(automate->tab_transition);
	free(automate);

    free_groupe_etat(new_groupe);*/
    
    *automate = *automate_m;

}

//Création d'un groupe d'état à partir d'un état
Groupe_etat* creation_groupe_etat(Etat* etat){
	Groupe_etat* groupe_etat = malloc(sizeof(Groupe_etat));

	groupe_etat->tab_etat = malloc(sizeof(Etat*));
	if(etat != NULL){
		groupe_etat->tab_etat[0] = etat;
		groupe_etat->accepteur = etat->accepteur;
	}
	else {
		groupe_etat->tab_etat[0] = NULL;
		groupe_etat->accepteur = 0;
	}
	groupe_etat->nb_etat = 1;
	groupe_etat->numero = 0;
	groupe_etat->groupe_etat_suivant = NULL;

	return groupe_etat;
}


//Ajoute l'état au groupe d'état s'il n'existe pas déjà
void ajout_etat(Etat* etat, Groupe_etat* groupe_etat){
	int i = 0;
	int ok = 0;
	Etat* etat_tmp = NULL;

	while(i < groupe_etat->nb_etat && ok == 0){
		if(etat == groupe_etat->tab_etat[i]){//si l'état est déjà dans le groupe
			return;
		}
		else if(groupe_etat->tab_etat[i]->num > etat->num){//si le numéro de l'état est plus grand que l'état à ajouter
			//on ajoute une case au tableau d'état et on mémorise le rang d'ajout
			groupe_etat->tab_etat = (Etat**) realloc(groupe_etat->tab_etat,(groupe_etat->nb_etat + 1) * sizeof(Etat*));
			ok = 1;
		}
		else{
			i++;
		}
	}

	//on rend le groupe accepteur s'il contient un état accepteur
	if(groupe_etat->accepteur == 0 && etat->accepteur == 1){
		groupe_etat->accepteur = 1;
	}

	for(i=i;i<groupe_etat->nb_etat+1;i++){//on ajoute l'état dans le tableau et on décale la fin du tableau
		etat_tmp = groupe_etat->tab_etat[i];
		groupe_etat->tab_etat[i] = etat;
		etat = etat_tmp;
	}

	groupe_etat->nb_etat++;

	return;
}

//Regarde si le groupe d'état est déjà présent dans la liste, si c'est le cas renvoie le match, sinon NULL
Groupe_etat* match_groupe_etat(Groupe_etat* groupe_etat,Groupe_etat* liste_groupe_etat){
	Groupe_etat* groupe_etat_act = liste_groupe_etat;
	int match,i;

	//on parcourt la liste
	while(groupe_etat_act != NULL){
		if(groupe_etat_act->nb_etat == groupe_etat->nb_etat && groupe_etat_act->accepteur == groupe_etat->accepteur){
			match = 1;
			i = 0;
			//on parcourt les états tant qu'il y a correspondance
			while(i < groupe_etat->nb_etat && match == 1){
				if(groupe_etat_act->tab_etat[i] != groupe_etat->tab_etat[i]){
					match = 0;
				}
				i++;
			}
			if(match == 1){
				return groupe_etat_act;
			}
		}

		groupe_etat_act = groupe_etat_act->groupe_etat_suivant;
	}

	return NULL;
}


//Free un groupe d'état
void free_groupe_etat(Groupe_etat* groupe_etat){
	free(groupe_etat->tab_etat);
	free(groupe_etat);
}

//Free un automate déterministe
void free_auto_deterministe(Automate_deterministe* automate){
	int i;
	Groupe_etat* groupe_etat_act = NULL;
	Groupe_etat* groupe_etat_tmp = NULL;
	Caractere* caractere_act = NULL;
	Caractere* caractere_tmp = NULL;
	
	caractere_act = automate->alphabet;
	while(caractere_act != NULL && caractere_act->caractere_suivant != NULL){
		caractere_tmp = caractere_act->caractere_suivant;
		caractere_act->caractere_suivant = caractere_tmp->caractere_suivant;
		free(caractere_tmp);
	}
	free(caractere_act);

	groupe_etat_act = automate->liste_groupe_etat;
	while(groupe_etat_act != NULL && groupe_etat_act->groupe_etat_suivant != NULL){
		groupe_etat_tmp = groupe_etat_act->groupe_etat_suivant;
		groupe_etat_act->groupe_etat_suivant = groupe_etat_tmp->groupe_etat_suivant;
		free_groupe_etat(groupe_etat_tmp);
	}
	free_groupe_etat(groupe_etat_act);

	for(i=0;i<automate->nb_groupe_etat;i++){
		free(automate->tab_transition[i]);
	}
	free(automate->tab_transition);
	free(automate);
}


//Affiche un automate déterministe
void affichage_auto_deterministe(Automate_deterministe* automate){
	int i,j,nb_caractere;
	Caractere* caractere_act;
	Groupe_etat* groupe_etat_act;

	printf("Alphabet :");
	caractere_act = automate->alphabet;
	while(caractere_act != NULL){
		printf(" %c,",caractere_act->symbole);
		caractere_act = caractere_act->caractere_suivant;
	}
	printf("\nNb états : %d \n",automate->nb_groupe_etat);
	printf("Etat initial : %d \n",automate->groupe_etat_initial->numero);
	printf("Etats accepteurs :");
	groupe_etat_act = automate->liste_groupe_etat;
	while(groupe_etat_act != NULL && (groupe_etat_act->accepteur == 1)){
		printf(" %d,",groupe_etat_act->numero);
		groupe_etat_act = groupe_etat_act->groupe_etat_suivant;
	}
	printf("\nListe etats:");
	groupe_etat_act = automate->liste_groupe_etat;
	while(groupe_etat_act != NULL){
		printf(" %d,",groupe_etat_act->numero);
		groupe_etat_act = groupe_etat_act->groupe_etat_suivant;
	}
	printf("\nTableau de transitions :\n ");
	caractere_act = automate->alphabet;
	nb_caractere = 0;
	while(caractere_act != NULL){
		printf(" %c",caractere_act->symbole);
		nb_caractere++;
		caractere_act = caractere_act->caractere_suivant;
	}
	printf("\n");
	for(i=0;i<automate->nb_groupe_etat;i++){
		printf("%d ",i);
		for(j=0;j<nb_caractere;j++){
			printf("%d ",automate->tab_transition[i][j]->numero);
		}
		printf("\n");
	}
	printf("\n\n");
}
