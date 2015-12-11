#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"scrabble.h"

/* Il est important de savoir que le dico contient des 'faux' mots de type ' \n' ou '\0'...*/

void charger_dico()
{
  FILE* dico_scrabble = NULL;
  dico_scrabble = fopen("dicoScrabble.txt", "r");

  if(dico_scrabble == NULL) // Problème lors de l'ouverture du dictionnaire
    {
      printf("Dico non present dans le dossier courant. \n");
      exit(-1);
    }

  for(int i=0; (i<TAILLE_DICO) && (feof(dico_scrabble) == 0); i++) // Balayge du dico
    {
      fgets(dico[i], TAILLE_MAX, dico_scrabble); // Récupération de la ligne entière
      dico[i][strlen(dico[i]) - 2] = '\0'; // On tronque la fin du mot car par exemple le mot 'AA' sera 'AA \n\0', en tronquant on supprime ' \n'
    }
  
    fclose(dico_scrabble);
}
