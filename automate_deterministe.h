#ifndef AUTOMATE_DETERMINISTE
#define AUTOMATE_DETERMINISTE

/* type automate déterministe défini par
 * un alphabet
 * un tableau d'états
 * un état initial
 * un tableau d'états accepteurs
 * un tableau de transitions avec la ligne représentant l'état de départ 
 *  et la colonne le code ASCII des caractères de l'alphabet. Chaque case
 *  du tableau est l'état d'arrivée.
 */
typedef struct {
	Alphabet alphabet;
	Etat* liste_etat;
	Etat etat_initial;
	Etat* liste_etats_accepteurs;
	int** tab_transition;
} Automate_deterministe;

#endif
