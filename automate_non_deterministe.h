#ifndef AUTOMATE_NON_DETERMINISTE
#define AUTOMATE_NON_DETERMINISTE

#define TAILLE_ASCII 128

//type booleen qui peut prendre 2 valeurs False et True
typedef enum {
	False = 0,
	True = 1
} Bool;

/* type alphabet défini par un tableau de booleens dont l'indice est le code
 * ASCII du caractère (True si le caractère est présent dans l'alphabet,
 * False sinon)
 */
typedef struct {
	Bool caractere[TAILLE_ASCII];
} Alphabet;

/* type transition défini par un état de départ, un état d'arrivée, un
 * caractère de transition et l'adresse de la transition suivante, les états
 * étant représenté par des ints.
 */
typedef struct Transition Transition;
struct Transition{
	int depart;
	int arrivee;
	char symbole;
	Transition* transitionSuivante;
};

/* type automate non déterministe défini par
 * un alphabet
 * un nombre d'états
 * un nombre d'états finaux
 * un état initial (représenté par un int)
 * une liste d'états accepteurs (représenté par des int)
 * un tableau de liste de transitions avec la ligne représentant l'état de départ
 */
typedef struct {
	Alphabet alphabet;
	int nombreEtats;
	int nombreEtatsFinaux;
	int etat_initial;
	int* liste_etats_accepteurs;
	Transition* tab_transition;
} Automate_non_deterministe;

//Renvoie un automate non déterministe reconnaissant le langage vide
Automate_non_deterministe langage_vide();

//Renvoie un automate non déterministe reconnaissant le mot vide
Automate_non_deterministe mot_vide();

//Renvoi un automate standard reconnaissant le langage composé d’un mot d’un caractère passé en paramètre
Automate_non_deterministe un_mot(char symbole);

//Initialise les cases du tableau de l'alphabet à False
Alphabet init_alphabet();

//Création d'un tableau de int alloué dynamiquement représentant les états
int* alloc_tab_etat(int taille);

//Création d'un tableau de transitions alloué dynamiquement et initialise les états de départ à -1
Transition* init_tab_transition(int taille);

#endif
