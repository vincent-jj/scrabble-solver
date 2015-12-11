#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scrabble.h"

/*
  recherche sur le plateau des mots présents
*/

void balayage_plateau(char lettres_possedees[])
{
  int compteur_mot_plateau = 0;
  int compteur_lettre = 0;
  int compteur = 0; // compteur de la boucle pour concatener
 
  info_mot mot_plateau[8];

  horizontal = 1; 

  for(int j=0; j<15; j++) // Balayage horizontal
    {
      for(int i=0; i<15; i++) // i abscisse (balayage des colonnes)
	{
	  if(plateau[j][i].lettre != '.') // Si on croise une lettre on commence à enregistrer les mots de la ligne
	    {
	      if(!compteur_mot_plateau) // Si c'est le premier mot plateau qu'on  croise
		{
		  mot_plateau[compteur_mot_plateau].limite_debut = 0; // Limites de disposition des mots sur le plateau pour ne pas ecraser ou sortir du plateau
		}

	      else // Si ce n'est pas le premier, la limite de debut dépend de la fin du mot précédent
		{
		  mot_plateau[compteur_mot_plateau - 1].limite_fin = i - 2;

		  mot_plateau[compteur_mot_plateau].limite_debut = mot_plateau[compteur_mot_plateau - 1].fin_x + 2;
		}

	      mot_plateau[compteur_mot_plateau].debut_x = i;
	      mot_plateau[compteur_mot_plateau].debut_y = j;

	      while(i<15 && plateau[j][i].lettre != '.') // Tant qu'on ne croise pas de '.' c'est qu'on récupére le mot du plateau
		{
		  mot_plateau[compteur_mot_plateau].contenu[compteur_lettre] = plateau[j][i].lettre; // Recuperation d'un mot de la ligne
		  compteur_lettre++;
		  i++; // Pour faire avancer la boucle 'for' avec sinon si on récupére le mot 'EAU' au prochain coup on récupéra 'AU' puis 'U'
		}

	      mot_plateau[compteur_mot_plateau].contenu[compteur_lettre] = '\0'; // Le mot a été récupéré
	      mot_plateau[compteur_mot_plateau].fin_x = i - 1; 
	      mot_plateau[compteur_mot_plateau].fin_y = mot_plateau[compteur_mot_plateau].debut_y; // Car c'est un mot horizontal

	      compteur_mot_plateau++; // Passage au mot suivant de la ligne
	      compteur_lettre = 0; // Mise à 0 pour le mot suivant
	      i--; // On décrémente car il y a eu une incrémentation en trop 
	    }
	}

      mot_plateau[compteur_mot_plateau - 1].limite_fin = 14; // Le dernier mot de la ligne est limité par la fin de la ligne (15ème cellule)

      for(int k=0; k<compteur_mot_plateau; k++) // Boucle calculant la taille de tous les mots du plateau, et les envoyant à la fonction suivante tour à tour
	{
	  mot_plateau[k].taille = strlen(mot_plateau[k].contenu);
	  recherche_mot_plateau(lettres_possedees, mot_plateau[k]);
	}

      /*
	Les mots de la ligne qui ont été récupéré, vont être concaténer avec des '.' entre deux mots pour symboliser les espaces et qui pourront correspondre à n'importe quelle lettre. Par exemple une ligne de la sorte ...A....E...S.. nous donnera 3 mots de taille 1 : A, E et S, puis A....E, A....E...S, E...S etc...
       */

      for(int k=0; k<(compteur_mot_plateau - 1); k++) // D'abord premier mot auquel on concatene les autres mots
	{
	  for(int l=k; l<(compteur_mot_plateau - 1); l++) // Pour concatener le mot suivant seul, puis ensuite le mot suivant à l'ensemble etc...
	    {
	      for(int m=(mot_plateau[l].fin_x + 1); m <= mot_plateau[l+1].fin_x; m++) // Si on est dans le mot on met la lettre sinon on met '.'
		{
		  if(m < mot_plateau[l+1].debut_x)
		    { 
		      mot_plateau[k].contenu[compteur + mot_plateau[k].taille] = '.';
		    }
		  
		  else
		    {
		      mot_plateau[k].contenu[compteur + mot_plateau[k].taille] = mot_plateau[l+1].contenu[compteur_lettre];
		      compteur_lettre++;
		    }

		  compteur++;
		}

	      mot_plateau[k].contenu[compteur + mot_plateau[k].taille] = '\0';
	      mot_plateau[k].limite_fin = mot_plateau[l+1].limite_fin; // La limite de fin devient celle du mot concatene au mot initial
	      mot_plateau[k].fin_x = mot_plateau[l+1].fin_x;

	      recherche_mot_plateau(lettres_possedees, mot_plateau[k]);
	      compteur_lettre = 0;
	    }

	  compteur = 0;
	}

      compteur_mot_plateau = 0;
    }

  horizontal = 0;

  for(int i=0; i<15; i++) // Balayage vertical se réferrer au balayage horizontal pour le fonctionnement
    {
      for(int j=0; j<15; j++)
	{
	  if (plateau[j][i].lettre != '.')
	    {
	      if(!compteur_mot_plateau)
		{
		  mot_plateau[compteur_mot_plateau].limite_debut = 0; // Limites de disposition des mots sur le plateau pour ne pas ecraser ou sortir du plateau
		}
	      
	      else
		{
		  mot_plateau[compteur_mot_plateau - 1].limite_fin = j - 2;

		  mot_plateau[compteur_mot_plateau].limite_debut = mot_plateau[compteur_mot_plateau - 1].fin_y + 2;
		}

	      mot_plateau[compteur_mot_plateau].debut_x = i;
	      mot_plateau[compteur_mot_plateau].debut_y = j;

	      while(j<15 && plateau[j][i].lettre != '.')
		{
		  mot_plateau[compteur_mot_plateau].contenu[compteur_lettre] = plateau[j][i].lettre; // Recuperation d'un mot de la ligne
		  compteur_lettre++;
		  j++;
		}

	      mot_plateau[compteur_mot_plateau].contenu[compteur_lettre] = '\0';
	      mot_plateau[compteur_mot_plateau].fin_x = mot_plateau[compteur_mot_plateau].debut_x;
	      mot_plateau[compteur_mot_plateau].fin_y = j - 1;

	      compteur_mot_plateau++; // Passage au mot suivant de la ligne
	      compteur_lettre = 0; // Mise à 0 pour le mot suivant
	      j--;
	    }
	}

      mot_plateau[compteur_mot_plateau - 1].limite_fin = 14;    

      for(int k=0; k<compteur_mot_plateau; k++)
	{
	  mot_plateau[k].taille = strlen(mot_plateau[k].contenu);
	  recherche_mot_plateau(lettres_possedees, mot_plateau[k]);
	}

      /*
	Les mots de la ligne qui ont été récupéré, vont être concaténer avec des '.' entre deux mots pour symboliser les espaces et qui pourront correspondre à n'importe quelle lettre. Par exemple une ligne de la sorte ...A....E...S.. nous donnera 3 mots de taille 1 : A, E et S, puis A....E, A....E...S, E...S etc...
       */

      for(int k=0; k<(compteur_mot_plateau - 1); k++) // D'abord premier mot auquel on concatene les autres mots
	{
	  for(int l=k; l<(compteur_mot_plateau - 1); l++) // Pour concatener le mot suivant seul, puis ensuite le mot suivant à l'ensemble etc...
	    {
	      for(int m=(mot_plateau[l].fin_y + 1); m <= mot_plateau[l+1].fin_y; m++) // Si on est dans le mot on met la lettre sinon on met '.'
		{
		  if(m < mot_plateau[l+1].debut_y)
		    { 
		      mot_plateau[k].contenu[compteur + mot_plateau[k].taille] = '.';
		    }
		  
		  else
		    {
		      mot_plateau[k].contenu[compteur + mot_plateau[k].taille] = mot_plateau[l+1].contenu[compteur_lettre];
		      compteur_lettre++;
		    }

		  compteur++;
		}

	      mot_plateau[k].contenu[compteur + mot_plateau[k].taille] = '\0';
	      mot_plateau[k].limite_fin = mot_plateau[l+1].limite_fin; // La limite de fin devient celle du mot concatene au mot initial
	      mot_plateau[k].fin_y = mot_plateau[l+1].fin_y;

	      recherche_mot_plateau(lettres_possedees, mot_plateau[k]);
	      compteur_lettre = 0;
	    }

	  compteur = 0;
	}

      compteur_mot_plateau = 0;
    }
}

void generateur_plateau()
{
  for (int j=0; j<15; j++)
    {
      for(int i=0; i<15; i++)
	{
	  plateau[i][j].lettre='.';
	  plateau[i][j].multiplieur_lettre = 1;
	  plateau[i][j].multiplieur_mot = 1;
	  plateau[i][j].disponible = 1;
	}
    }

  // Creation du masque des cases spéciales mot compte double/triple

  for (int j=1; j<5; j++)
    {
      for(int i=1; i<5;i++)
	{
	  if (i==j) 
	    {
	      plateau[i][j].multiplieur_mot=2 ;  // Diagonale
      	      plateau[i][14-j].multiplieur_mot=2 ; // Diagonale opposée
	    }
	}
    }

  for (int i=10; i<14; i++) 
    {
      for(int j=10; j<14; j++) 
	{
	  if (i==j) 
	    {
	      plateau[i][j].multiplieur_mot=2 ;	    
	      plateau[i][14-j].multiplieur_mot=2 ;
	    }
	} 
    }
  
  plateau[7][7].multiplieur_mot=2;
  plateau[0][0].multiplieur_mot=3;
  plateau[14][14].multiplieur_mot=3;
  plateau[0][7].multiplieur_mot=3 ;
  plateau[7][0].multiplieur_mot=3 ;
  plateau[14][0].multiplieur_mot=3;
  plateau[0][14].multiplieur_mot=3;
  plateau[14][7].multiplieur_mot=3;
  plateau[7][14].multiplieur_mot=3 ;

  // Creation du masque des cases spéciales lettre compte double/triple

  for(int i = 1; i < 13; i += 4) 
    {
      plateau[i][5].multiplieur_lettre=3 ;
      plateau[i][9].multiplieur_lettre=3 ;
    }
  
  for (int j = 1; j < 13; j += 4) 
    {
      plateau[5][j].multiplieur_lettre = 3;
      plateau[9][j].multiplieur_lettre = 3;
    }
  
  plateau[3][0].multiplieur_lettre = 2;
  plateau[0][3].multiplieur_lettre = 2;
  plateau[6][2].multiplieur_lettre = 2;
  plateau[6][6].multiplieur_lettre = 2;
  plateau[2][6].multiplieur_lettre = 2;
  plateau[7][3].multiplieur_lettre = 2;
  plateau[3][7].multiplieur_lettre = 2;
  miroir(plateau);
}

void miroir() // Permet de ne pas taper toutes les cases spéciales lettre compte double/triple à la main en faisant des opérations de symétrie
{
  for (int i=0; i<8; i++)
    {
      for(int j=0; j<8; j++)
	{
	  plateau[14-i][14-j].multiplieur_lettre = plateau[i][j].multiplieur_lettre;
	  plateau[14-i][j].multiplieur_lettre = plateau[i][j].multiplieur_lettre;
	  plateau[i][14-j].multiplieur_lettre = plateau[i][j].multiplieur_lettre;
	}         
    }
}  
