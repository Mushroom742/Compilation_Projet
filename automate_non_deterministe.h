#ifndef AUTOMATE_NON_DETERMINISTE
#define AUTOMATE_NON_DETERMINISTE

#define TAILLE_ASCII 128

/* type caractère défini par un symbole et le caractere suivant dans la liste
 */
typedef struct Caractere Caractere;
struct Caractere {
	char symbole;
	Caractere* caractere_suivant;
};

//type état défini par un numéro, s'il est accepteur (1) ou non (0) et l'état suivant dans la liste
typedef struct Etat Etat;
struct Etat {
	int num;
	int accepteur;
	Etat* etat_suivant;
};

/* type transition défini par un état de départ, un état d'arrivée, un
 * caractère de transition et l'adresse de la transition suivante.
 */
typedef struct Transition Transition;
struct Transition{
	Etat* depart;
	Etat* arrivee;
	Caractere* caractere;
	Transition* transitionSuivante;
};

/* type automate non déterministe défini par
 * un alphabet (liste chainée de caractères)
 * un nombre d'états
 * une liste chainée d'états (les états accepteurs en premier)
 * un état initial
 * un tableau de listes chainées de transitions avec l'indice de la ligne représentant l'état de départ
 */
typedef struct Automate_non_deterministe Automate_non_deterministe;
struct Automate_non_deterministe {
	Caractere* alphabet;
	int nombreEtats;
	Etat* liste_etat;
	Etat* etat_initial;
	Transition** tab_transition;
	Automate_non_deterministe* automate_suivant;
};

//Renvoie un automate non déterministe reconnaissant le langage vide
Automate_non_deterministe* langage_vide();

//Renvoie un automate non déterministe reconnaissant le mot vide
Automate_non_deterministe* mot_vide();

//Renvoie un automate standard reconnaissant le langage composé d’un mot d’un caractère passé en paramètre
Automate_non_deterministe* un_mot(char symbole);

//Renvoie la réunion de 2 alphabets
//Alphabet reunion_alphabet(Alphabet alphabet1, Alphabet alphabet2);

//Création d'un tableau de transitions alloué dynamiquement
Transition** init_tab_transition(int taille);

//Ajoute une transition dans le tableau de transition en fonction de son état de départ
void ajout_transition(Transition* transition, Transition** tab_transition);

//Affiche un automate
void affichage_automate_non_deterministe(Automate_non_deterministe* automate);

//Renvoie un automate standard reconnaissant la réunion des langages des 2 automates passés en paramètre
Automate_non_deterministe reunion(Automate_non_deterministe automate1, Automate_non_deterministe automate2);

//free un automate
void free_automate(Automate_non_deterministe* automate);

#endif
