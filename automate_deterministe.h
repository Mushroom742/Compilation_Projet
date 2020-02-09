#ifndef AUTOMATE_DETERMINISTE
#define AUTOMATE_DETERMINISTE


/* type groupe d'états défini par
 * un tablau d'états
 * le nombre d'états dabs le groupe
 * le numéro du groupe d'état
 * le groupe d'état suivant dans la liste chainée
 */
typedef struct Groupe_etat Groupe_etat;
struct Groupe_etat {
	Etat* tab_etat;
	int nb_etat;
	int numero;
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
	Groupe_etat** tab_transition;
	Automate_deterministe* automate_suivant;
};

#endif
