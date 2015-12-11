#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"scrabble.h"

void placer_mot(int choix)
{
  if(strcmp(meilleur_coup[choix].mot.contenu, "") != 0)
    {
      if(meilleur_coup[choix].mot.debut_y != meilleur_coup[choix].mot.fin_y) // Si mot vertical
	{
	  for(int i=0; i<meilleur_coup[choix].mot.taille; i++)
	    {
	      plateau[meilleur_coup[choix].mot.debut_y + i][meilleur_coup[choix].mot.debut_x].lettre = meilleur_coup[choix].mot.contenu[i]; // On pose la lettre
	      plateau[meilleur_coup[choix].mot.debut_y + i][meilleur_coup[choix].mot.debut_x].disponible = 0; // La case est occupée

 	      if((i == meilleur_coup[choix].pos_joker_1) || (i == meilleur_coup[choix].pos_joker_2)) // Si c'est un joker
		{
		  plateau[meilleur_coup[choix].mot.debut_y + i][meilleur_coup[choix].mot.debut_x].multiplieur_lettre = 0; // On tue la valeur de la case
		}
	    }
	}
      
      else // Si mot horizontal
	{
	  for(int i=0; i<meilleur_coup[choix].mot.taille; i++)
	    {
	      plateau[meilleur_coup[choix].mot.debut_y][meilleur_coup[choix].mot.debut_x + i].lettre = meilleur_coup[choix].mot.contenu[i];
	      plateau[meilleur_coup[choix].mot.debut_y][meilleur_coup[choix].mot.debut_x + i].disponible = 0;

	      if((i == meilleur_coup[choix].pos_joker_1) || (i == meilleur_coup[choix].pos_joker_2))
		{
		  plateau[meilleur_coup[choix].mot.debut_y][meilleur_coup[choix].mot.debut_x + i].multiplieur_lettre = 0;
		}
	    }
	}
      
      for(int i=0; i<15; i++)
	{
	  for(int j=0; j<15; j++)
	    {
	      printf("%c ", plateau[i][j].lettre);
	    }
	  
	  printf("\n");
	}
    }
}
