#ifndef AUTOMATE_NON_DETERMINISTE
#define AUTOMATE_NON_DETERMINISTE

#define TAILLE_ASCII 127

//type booleen qui peut prendre 2 valeurs False et True
typedef enum {
	False = 0,
	True = 1
} Bool;

//type état défini par un numéro
typedef struct {
	int num;
}Etat;

/* type alphabet défini par un tableau de booleens dont l'indice est le code
 * ASCII du caractère (True si le caractère est présent dans l'alphabet, 
 * False sinon)
 */
typedef struct {
	Bool caractere[TAILLE_ASCII];
} Alphabet;

/* type transition défini par un état de départ, un état d'arrivée et un
 * caractère de transition
 */
typedef struct {
	Etat depart;
	Etat arrivee;
	char symbole;
} Transition;

/* type automate non déterministe défini par
 * un alphabet
 * un tableau d'états
 * un état initial
 * un tableau d'états accepteurs
 * un tableau de transitions avec la ligne représentant l'état de départ 
 *  et la colonne l'état d'arrivée
 */
typedef struct {
	Alphabet alphabet;
	Etat* liste_etat;
	Etat etat_initial;
	Etat* liste_etats_accepteurs;
	Transition** tab_transition;
} Automate_non_deterministe;

#endif
