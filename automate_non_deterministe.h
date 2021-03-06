#ifndef AUTOMATE_NON_DETERMINISTE
#define AUTOMATE_NON_DETERMINISTE

/* type caractère défini par un symbole, un numéro et le caractere suivant dans la liste
 */
typedef struct Caractere Caractere;
struct Caractere {
	char symbole;
	int numero;
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

//Ajoute l'alphabet de l'automate 2 dans l'alphabet de l'automate 1
void reunion_alphabet(Automate_non_deterministe* automate1, Automate_non_deterministe* automate2);

//Création d'un tableau de listes de transitions alloué dynamiquement
Transition** init_tab_transition(int taille);

//Ajoute une transition dans le tableau de transition en fonction de son état de départ
void ajout_transition(Transition* transition, Transition** tab_transition);

//Affiche un automate non déterministe
void affichage_automate_non_deterministe(Automate_non_deterministe* automate);

//Réunion des automates 1 et 2 dans l'automate 1
void reunion(Automate_non_deterministe* automate1, Automate_non_deterministe* automate2);

//Concaténation des automates 1 et 2 dans l'automate 1
void concatenation(Automate_non_deterministe* automate1, Automate_non_deterministe* automate2);

//Mise à l'étoile (ou fermeture itérative de Kleene) de l'automate
void mise_etoile(Automate_non_deterministe* automate);

//Free un automate non déterministe
void free_automate(Automate_non_deterministe* automate);

#endif
