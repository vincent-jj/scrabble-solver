#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"scrabble.h"

/*
  Cette fonction ne prend pas encore en compte les mots accolés au mot posé !
*/

int points(info_mot mot, int pos_joker_1, int pos_joker_2)
{
  int valeur_lettres[26]={1,3,3,2,1,4,2,4,1,8,10,1,2,1,1,3,8,1,1,1,1,4,10,10,10,10};
  int compteur_multiplicateur = 1;
  int taille_mot_plateau = 0; // Pour connaitre la taille du mot du plateau
  int points_du_mot = 0;

  if(horizontal) // Mot horizontal
    {
      for(int i=0; i<mot.taille; i++)
	{
	  if((i == pos_joker_1) || (i == pos_joker_2)) // Joker vaut 0
	    {
	      compteur_multiplicateur = compteur_multiplicateur * plateau[mot.debut_y][mot.debut_x + i].multiplieur_mot;
	    }
	  
	  else if(!(plateau[mot.debut_y][mot.debut_x + i].disponible)) // Lettre deja sur le plateau
	    {
	      if(plateau[mot.debut_y][mot.debut_x + i].multiplieur_lettre)
		{
		  points_du_mot = points_du_mot + valeur_lettres[mot.contenu[i] - 65]; // Bonus non pris en compte
		}

	      taille_mot_plateau++;
	    } 
	  
	  else // Autres lettres bonus pris en compte
	    {
	      points_du_mot = points_du_mot + (valeur_lettres[mot.contenu[i] - 65] * plateau[mot.debut_y][mot.debut_x + i].multiplieur_lettre); // Avec bonus
	      compteur_multiplicateur = compteur_multiplicateur * plateau[mot.debut_y][mot.debut_x + i].multiplieur_mot; // On multiplie les multiplicateurs
	    }
	}
      
      points_du_mot = points_du_mot * compteur_multiplicateur;
    }

  else // Mot vertical
    {
      for(int i=0; i<mot.taille; i++)
	{
	  if((i == pos_joker_1) || (i == pos_joker_2)) // Joker vaut 0
	    {
	      compteur_multiplicateur = compteur_multiplicateur * plateau[mot.debut_y + i][mot.debut_x].multiplieur_mot;
	    }

	  else if(!plateau[mot.debut_y + i][mot.debut_x].disponible) // Lettre deja sur le plateau
	    {
	      if(plateau[mot.debut_y + i][mot.debut_x].multiplieur_lettre)
		{
		  points_du_mot = points_du_mot + valeur_lettres[mot.contenu[i] - 65]; // Bonus non pris en compte
		}

	      taille_mot_plateau++;
	    } 


	  
	  else // Autres lettres bonus pris en compte
	    {
	      points_du_mot = points_du_mot + (valeur_lettres[mot.contenu[i] - 65] * plateau[mot.debut_y + i][mot.debut_x].multiplieur_lettre);
	      compteur_multiplicateur = compteur_multiplicateur * plateau[mot.debut_y + i][mot.debut_x].multiplieur_mot; // On multiplie les multiplicateurs
	    }
	}
      
      points_du_mot = points_du_mot * compteur_multiplicateur;
    }

  if((mot.taille - taille_mot_plateau ) == 7) // Si toutes les lettres de la main sont posées alors bonus de 50
    {
      points_du_mot = points_du_mot + 50;
    }
 
  return (points_du_mot) ; // Retourne les points que rapportent le mot
}

void tri_insertion(info_mot mot, int points_faits, char lettres_possedees[], int pos_joker_1, int pos_joker_2)
{
  if(!strcmp(mode_jeu, "-n"))
    {
      for(int i=19; i>=0; i--)
	{
	  if(!meilleur_coup[0].resultat) // Si le tableau est vide
	    {
	      meilleur_coup[0].mot = mot;
	      meilleur_coup[0].resultat = points_faits;
	      strcpy(meilleur_coup[0].lettres_possedees, lettres_possedees);
	      meilleur_coup[0].pos_joker_1 = pos_joker_1;
	      meilleur_coup[0].pos_joker_2 = pos_joker_2;
	      break;
	    }
	  
	  else if(points_faits <= meilleur_coup[i].resultat && i<19) // Si le mot recontré rapporte plus de points, on place notre mot juste avant dans le tableau
	    {
	      for(int j=19; j>i+1; j--) // Pour cela il faut décaller tous les mots et score avant
		{
		  meilleur_coup[j] = meilleur_coup[j-1];
		}
	      
	      meilleur_coup[i+1].mot = mot;
	      meilleur_coup[i+1].resultat = points_faits;
	      strcpy(meilleur_coup[i+1].lettres_possedees, lettres_possedees);
	      meilleur_coup[i+1].pos_joker_1 = pos_joker_1;
	      meilleur_coup[i+1].pos_joker_2 = pos_joker_2;
	      break;
	    }
	  
	  else if(points_faits <= meilleur_coup[i].resultat && i==19) // Si le mot rapporte moins de point que le dernier mot du tableau il n'est pas mis dedans
	    {
	      break;
	    }
	  
	  else if(!i && points_faits > meilleur_coup[i].resultat) // Si le mot rapporte plus de points que le tout premier mot, alors on le place en tête
	    {
	      for(int j=19; j>i; j--)
		{
		  meilleur_coup[j] = meilleur_coup[j-1];
		}
	      
	      meilleur_coup[i].mot = mot;
	      meilleur_coup[i].resultat = points_faits;
	      strcpy(meilleur_coup[i].lettres_possedees, lettres_possedees);
	      meilleur_coup[i].pos_joker_1 = pos_joker_1;
	      meilleur_coup[i].pos_joker_2 = pos_joker_2;
	      break;
	    }
	}
    }

  else
    {
      if(points_faits >= meilleur_coup[0].resultat)
	{
	  meilleur_coup[0].mot = mot;
	  meilleur_coup[0].resultat = points_faits;
	  strcpy(meilleur_coup[0].lettres_possedees, lettres_possedees);
	  meilleur_coup[0].pos_joker_1 = pos_joker_1;
	  meilleur_coup[0].pos_joker_2 = pos_joker_2;
	}
    }
}
