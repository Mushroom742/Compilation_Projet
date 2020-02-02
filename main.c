#include <stdio.h>
#include <stdlib.h>
#include "automate_non_deterministe.h"
#include "automate_deterministe.h"

int main (){
	Automate_non_deterministe* liste_automate = NULL;

	liste_automate = un_mot('a');

	affichage_automate_non_deterministe(liste_automate);

	free_automate(liste_automate);

	return 0;
}
