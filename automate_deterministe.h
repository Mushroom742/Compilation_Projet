#ifndef AUTOMATE_DETERMINISTE
#define AUTOMATE_DETERMINISTE


/* type groupe d'états défini par
 * un tablau d'états
 * le nombre d'états dabs le groupe
 * le numéro du groupe d'état
 * s'il est accepteur(1) ou non(0)
 * le groupe d'état suivant dans la liste chainée
 */
typedef struct Groupe_etat Groupe_etat;
struct Groupe_etat {
	Etat** tab_etat;
	int nb_etat;
	int numero;
	int accepteur;
	Groupe_etat* groupe_etat_suivant;
};

/* type automate déterministe défini par
 * un alphabet (liste chainée de caractères)
 * une liste chainée de groupes d'états
 * un nombre de groupe d'état
 * un groupe d'états initial
 * un tableau de transition dont la ligne est le numéro du groupe d'état et la colonne le numéro du caractère
 * l'automate suivant dans la liste chainée
 */
typedef struct Automate_deterministe Automate_deterministe;
struct Automate_deterministe {
	Caractere* alphabet;
	Groupe_etat* liste_groupe_etat;
	int nb_groupe_etat;
	Groupe_etat* groupe_etat_initial;
	Groupe_etat*** tab_transition;
	Automate_deterministe* automate_suivant;
};

//Execute un automate déterministe sur un mot
void execution_mot(Automate_deterministe* automate, char* mot);

//Determinise un automate non déterministe et renvoie sa version déterministe
Automate_deterministe* determinisation(Automate_non_deterministe* automate_nd);

//Minimise un automate déterministe
Automate_deterministe* minimisation(Automate_deterministe* automate);

//Création d'un groupe d'état à partir d'un état
Groupe_etat* creation_groupe_etat(Etat* etat);

//Ajoute l'état au groupe d'état s'il n'existe pas déjà
void ajout_etat(Etat* etat, Groupe_etat* groupe_etat);

//Regarde si le groupe d'état est déjà présent dans la liste, si c'est le cas renvoie le match, sinon NULL
Groupe_etat* match_groupe_etat(Groupe_etat* groupe_etat,Groupe_etat* liste_groupe_etat);

//Free un groupe d'état
void free_groupe_etat(Groupe_etat* groupe_etat);

//Free un automate déterministe
void free_auto_deterministe(Automate_deterministe* automate);

//Affiche un automate déterministe
void affichage_auto_deterministe(Automate_deterministe* automate);

#endif
