#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#include"scrabble.h"

int tirage(char lettres_possedees[], int masque_alphabet[], int lettres_sac)
{
  srand(time(NULL));

  char alphabet[103] = "AEINEULILLOSTRANDHVZMEYE@ACPOTSIRNIVJELEMINTSXOAREETURHLDWBCTTUMGIAENSEFRQKU@ADEGBNOOAEPFRUSIEAOSEIUEA"; // @ correspond au joker

  int nombre_aleatoire = 0;
  int nombre_jokers = 0;

  for(int i=6; i>=nombre_jokers && lettres_sac; i--)
    {
      nombre_aleatoire = (rand()%102);

      if ((lettres_possedees[i]<64) || (lettres_possedees[i]>90)) // On regarde si à cette position du tableau le joueur posséde une lettre
	{
	  if (masque_alphabet[nombre_aleatoire]) // On regarde si la lettre demandée est disponible
	    {
	      if(alphabet[nombre_aleatoire] == 64) // Si c'est un joker ils sont placés en position 0 et 1 de la main
		{
		  if(lettres_possedees[nombre_jokers] >= 65 && lettres_possedees[nombre_jokers]<=90) // Si une lettre occupe déjà la place, on la met en zone libre
		    {
		      lettres_possedees[i] = lettres_possedees[nombre_jokers];
		      lettres_possedees[nombre_jokers] = 64;
		      nombre_jokers++;
		    }

		  else if(lettres_possedees[nombre_jokers] == 64) // Si c'est un joker on place le joker a la place suivante réservée aux jokers
		    {
		      nombre_jokers++;
		      
		      if(lettres_possedees[nombre_jokers] >= 65 && lettres_possedees[nombre_jokers]<=90) // Si une lettre occupe déjà la place, on la met ailleurs
			{
			  lettres_possedees[i] = lettres_possedees[nombre_jokers];
			  lettres_possedees[nombre_jokers] = 64;
			}

		      else // Sinon le joker prend sa place normalement
			{
			  lettres_possedees[nombre_jokers] = 64;
			  i++;
			}
		    }

		  else // S'il n'y a pas de jokers dans la main et que la premiere place des jokers n'est pas occupée
		    {
		      lettres_possedees[nombre_jokers] = alphabet[nombre_aleatoire];
		      nombre_jokers++;
		      i++;
		    }
		}

	      else // Si c'est une lettre normale, on la place dans la cellule où l'on se situe actuellement
		{
		  lettres_possedees[i] = alphabet[nombre_aleatoire];
		}

	      masque_alphabet[nombre_aleatoire] = 0;
	      lettres_sac--;
	    }

	  else // Si la place n'est pas disponible on passe à la cellule suivante de la main du joueur
	    {
	      i++;
	    }
	}
    }

  lettres_possedees[7] = '\0';

  return lettres_sac;
}

int tirage_manuel(char lettres_possedees[], int lettres_sac)
{
  static int alphabet[27] = {2,9,2,2,3,15,2,2,2,8,1,1,5,3,6,6,2,1,6,6,6,6,2,1,1,1,1};
  int compteur = 0;
  char lettre;

  while(compteur != 7)
    {
      printf("Nombre de lettres dans le sac : %d, Main du joueur : %s, Entrez une lettre ! \n", lettres_sac, lettres_possedees);

      if(lettres_possedees[compteur] >= 64 && lettres_possedees[compteur] <= 90) // On vérifie que la place n'est pas occupée par une lettre
	{
	  printf("La cellule est occupée par la lettre : %c, si vous ne voulez pas l'enlever tapez entrée ! \n", lettres_possedees[compteur]);
	}

      scanf("%c", &lettre);
      
      if(lettre == 27 && compteur) // Touche 'suppr'
	{
	  compteur--; // On supprime la lettre précédente
	  alphabet[lettres_possedees[compteur]-64]++; // La lettre est remise dans le sac
	  lettres_sac++;
	  lettres_possedees[compteur] = ' ';
	}
      
      else if(lettre == ' ') // Pour ne pas avoir à mettre de lettres
	{
	  if(lettres_possedees[compteur] >= 64 && lettres_possedees[compteur] <= 90)
	    {
	      alphabet[lettres_possedees[compteur]-64]++;
	      lettres_sac++;
	    }

	  lettres_possedees[compteur] = ' ';
	  compteur++;
	}
      
      else if(lettre >= 97 && lettre <= 122)
	{
	  lettre = lettre - 32;

	  if(alphabet[(lettre - 64)]) // Si c'en est un et que la lettre est encore disponible
	    {
	      if(lettres_possedees[compteur] >= 64 && lettres_possedees[compteur] <= 90)
		{
		  alphabet[lettres_possedees[compteur]-64]++;
		  lettres_sac++;
		}
	      
	      
	      lettres_possedees[compteur] = lettre;
	      alphabet[(lettre - 64)]--;
	      lettres_sac--;
	      compteur++;
	    }
	  
	  else // Si la lettre n'est plus disponible
	    {
	      printf("Lettre plus disponible !\n \n");
	    }
	}

      else if(lettre == '\n')
	{
	  compteur++;
	}

      else if(lettre < 64 || lettre > 90)  // Si le caractère tapé n'est pas une lettre majuscule
	{
	  printf("Lettre non-existente ! \n\n");
	}
      
      else if(alphabet[(lettre - 64)]) // Si c'en est un et que la lettre est encore disponible
	{
	  if((compteur > 1 && lettre == 64) || (compteur && lettres_possedees[0] != 64 && lettre == 64))
	    {
	      printf("Les jokers doivent être placé en première et deuxième position dans la main du joueur !\n");
	    }
	  
	  else
	    {
	      if(lettres_possedees[compteur] >= 64 && lettres_possedees[compteur] <= 90)
		{
		  alphabet[lettres_possedees[compteur]-64]++;
		  lettres_sac++;
		}


	      lettres_possedees[compteur] = lettre;
	      alphabet[(lettre - 64)]--;
	      lettres_sac--;
	      compteur++;
	    } 
	}
      
      else // Si la lettre n'est plus disponible
	{
	  printf("Lettre plus disponible !\n \n");
	}
      
      if(lettre != '\n')
	{
	  while(getchar() != '\n') // On vide le buffer
	    {
	      
	    }
	}
    }
  
  return lettres_sac;
}

int retirer_lettres_utilisees(char lettres_possedees[], int masque_alphabet[], int lettres_sac, int choix)
{
  int taille_lettres_possedees;

  if(!meilleur_coup[choix].resultat) // Cas ou l'ordi n'a pas pu jouer, les lettres sont jetees
    {
      char alphabet[103] = "AEINEULILLOSTRANDHVZMEYE@ACPOTSIRNIVJELEMINTSXOAREETURHLDWBCTTUMGIAENSEFRQKU@ADEGBNOOAEPFRUSIEAOSEIUEA";
  
      for(int i=0; i<7; i++)
	{
	  for(int j=0; j<103; j++)
	    {
	      if((alphabet[j] == lettres_possedees[i]) && !masque_alphabet[j]) // Les lettres sont replacés dans le sac car le joueur n'a pas pu jouer
	      {
		lettres_possedees[i] = ' ';
		masque_alphabet[j] = 1;
		lettres_sac++;
		break;
	      }
	    } 
	}

      compteur_arret--; // Le joueur n'a pas pu jouer, si jamais cela arrive 10 fois d'affilé le jeu s'arrete
    }

  else // Cas ou l'ordinateur a joué, les lettres utilisees sont jetees
    {
      strcpy(lettres_possedees, meilleur_coup[choix].lettres_possedees);
      taille_lettres_possedees = strlen(lettres_possedees);

      for(int i=0; i<meilleur_coup[choix].mot.taille; i++)
	{
	  for(int j=(taille_lettres_possedees-1); j>=0; j--)
	    { 
	      if((lettres_possedees[j] == meilleur_coup[choix].mot.contenu[i])) // On supprime les lettres en main presentes dans le mot
		{
		  lettres_possedees[j] = ' ';
		  break;
		}

	      else if(lettres_possedees[j] == 64) // Si aucune lettre de la main ne permet de jouer la lettre du mot, on retire le joker
		{
		  lettres_possedees[j] = ' ';
		  break;
		}
	    }    
	}

      compteur_arret = 10; // Ce compteur permet d'éviter de tomber dans une boucle infini si jamais les lettres dans le sac ne permettent plus de jouer
    }
  
  lettres_possedees[7] = '\0'; // La main du joueur est de 7 lettres
  
  printf("Main du joueur : %s \n \n", lettres_possedees);

  return lettres_sac;
}
