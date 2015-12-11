#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"scrabble.h"

void premier_mot(char lettres_possedees[]) // Respecte une regle particulière : le mot doit passer par la case centrale
{
  info_mot mot;

  for(int i=0; i<TAILLE_DICO; i++)
    {
      strcpy(mot.contenu, dico[i]);
      mot.taille = strlen(mot.contenu);

      for(int j=1; j<8; j++) // On teste toutes les positions faisant passer le mot par la case centrale
	{
	  if((j + mot.taille) >= 8)
	    {
	      mot.debut_x = j;
	      mot.debut_y = 7;
	      mot.fin_x = j + mot.taille;
	      mot.fin_y = mot.debut_y;

	      mot_realisable(mot, lettres_possedees);
	    }
	}
    }
}

void recherche_mot_plateau(char lettres_possedees[], info_mot mot_plateau)
{
  info_mot mot;

  int compteur_correct; // Pour trouver les mots qui contiennent le mot déjà présent sur le plateau
  int compteur; // Compteur pour mixer lettres_possedees avec les lettres du mot_plateau

  int taille_lettres_possedees = strlen(lettres_possedees);

  int limite = mot_plateau.limite_fin - mot_plateau.limite_debut + 1; // Espace disponible pour le mot a poser
  mot_plateau.taille = strlen(mot_plateau.contenu);

  if(horizontal && (mot_plateau.taille > 1)) // Horizontal de taille superieur a 1
    {
      for(int i=0; i<=mot_plateau.debut_x; i++) // 0 pour mot_plateau en préfixe
	{
	  for(int j=0; j<TAILLE_DICO; j++)
	    {
	      strcpy(mot.contenu, dico[j]);
	      
	      compteur_correct = 0;

	      mot.taille = strlen(mot.contenu);
	      mot.debut_x = mot_plateau.debut_x - i;
	      mot.debut_y = mot_plateau.debut_y;
	      mot.fin_y = mot_plateau.fin_y; // Car c'est un mot horizontal
	      mot.fin_x = (mot.debut_x + mot.taille - 1);
	      
	      /* La condition suivante vérifie que le mot créé est bien nouveau (ce n'est pas juste le mot plateau au même endroit...) et qu'il rentre dans l'espace disponible et qu'il se finit après ou au même endroit que le mot plateau */

	      if((mot.taille > mot_plateau.taille) && (mot.taille <= limite) && (mot.fin_x >= mot_plateau.fin_x))
		{
		  for(int k=0; k<(mot_plateau.taille-1); k++)
		    {
		      /* La condition suivante vérifie que le début du mot n'est pas trop loin du début du mot plateau, que le début du mot est bien supérieur à la limite de début, que le mot plateau est bien inclus dedans */

		      if(((mot_plateau.debut_x - mot.debut_x) <= mot.taille) && (mot.debut_x >= mot_plateau.limite_debut) && ((mot.contenu[k+i] == mot_plateau.contenu[k]) || (mot_plateau.contenu[k] == '.')) && ((mot.contenu[k+i+1] == mot_plateau.contenu[k+1]) || (mot_plateau.contenu[k+1] == '.')))
			{
			  compteur_correct++;
			}
		      else
			{
			  break;
			}
		    }
		  
		  /* La condition suivante vérifie que le mot plateau est bien inclus dans le mot, et que la fin du mot ne déborde pas sur la limite de fin */ 

		  if (compteur_correct == (mot_plateau.taille-1) && (mot.fin_x <= mot_plateau.limite_fin))
		    { 
		      compteur = 0;

		      if((mot.taille - mot_plateau.taille) == 1) // Si le mot créé n'est que de taille +1, on peut construire un mot orthogonalement
			{
			  for(int k=0; k<taille_lettres_possedees; k++)
			    {
			      if(((mot.debut_x == mot_plateau.debut_x) && ((mot.contenu[mot.taille -1] == lettres_possedees[k]) || (lettres_possedees[k] == '@'))) || ((mot.fin_x == mot_plateau.fin_x) && ((mot.contenu[0] == lettres_possedees[k]) || (lettres_possedees[k] == '@')))) // On verifie qu'on peut construire le mot dans un premier temps
				{
				  mot_orthogonal(mot, mot_plateau, lettres_possedees);
				  break;
				}
			    }
			}		      		      

		      for(int k=0; k<mot_plateau.taille; k++)
			{
			  if(mot_plateau.contenu[k] != '.') // On enregistre les lettres du mot plateau dans la main du joueur
			    {
			      lettres_possedees[7+compteur] = mot_plateau.contenu[k];
			      compteur++;
			    }
			}
		  
		      lettres_possedees[7+compteur] = '\0';

		      mot_realisable(mot, lettres_possedees); // Puis on vérifie que le mot est posable, c'est à dire si on a toutes les lettres pour
		    }
		}
	    }
	}
    }
  
  if(!horizontal && (mot_plateau.taille > 1)) // Vertical de taille superieur a 1, pour le fonctionnement se référrer au premier cas
    {
      for(int i=0; i<=mot_plateau.debut_y; i++)
	{
	  for(int j=0; j<TAILLE_DICO; j++)
	    {
	      strcpy(mot.contenu, dico[j]);

	      compteur_correct = 0;

	      mot.taille = strlen(mot.contenu);
	      mot.debut_x = mot_plateau.debut_x;
	      mot.fin_x = mot_plateau.fin_x;
	      mot.debut_y = mot_plateau.debut_y - i;
	      mot.fin_y = (mot.debut_y + mot.taille - 1);

	      if((mot.taille > mot_plateau.taille) && (mot.taille <= limite) && (mot.fin_y >= mot_plateau.fin_y))
		{
		  for(int k=0; k<(mot_plateau.taille-1); k++)
		    {
		      if(((mot_plateau.debut_y - mot.debut_y) <= mot.taille) && (mot.debut_y >= mot_plateau.limite_debut) && ((mot.contenu[k+i] == mot_plateau.contenu[k]) || (mot_plateau.contenu[k] == '.')) && ((mot.contenu[k+i+1] == mot_plateau.contenu[k+1]) || (mot_plateau.contenu[k+1] == '.')))
			{
			  compteur_correct++;
			}
		      else
			{
			  break;
			}
		    }
		  
		  if (compteur_correct == (mot_plateau.taille-1) && (mot.fin_y <= mot_plateau.limite_fin))
		    { 
		      compteur = 0;
		     
		      if((mot.taille - mot_plateau.taille) == 1)
			{
			  for(int k=0; k<taille_lettres_possedees; k++)
			    {
			      if(((mot.debut_y == mot_plateau.debut_y) && (mot.contenu[mot.taille -1] == lettres_possedees[k])) || ((mot.fin_y == mot_plateau.fin_y) && (mot.contenu[0] == lettres_possedees[k])))
				{
				  mot_orthogonal(mot, mot_plateau, lettres_possedees); // Verifie s'il est possible de creer un mot perpendiculaire au mot
				  break;
				}
			    }
			}		      

		      for(int k=0; k<mot_plateau.taille; k++)
			{
			  if(mot_plateau.contenu[k] != '.')
			    {
			      lettres_possedees[7+compteur] = mot_plateau.contenu[k];
			      compteur++;
			    }
			}
		      
		      lettres_possedees[7+compteur] = '\0';		

		      mot_realisable(mot, lettres_possedees);
		    }
		}
	    }
	}
    }

  if(horizontal && (mot_plateau.taille == 1)) // Horizontal de taille 1, pour le fonctionnement se référrer au premier cas
    {
      for(int j=0; j<TAILLE_DICO; j++)
	{
	  strcpy(mot.contenu, dico[j]);

	  mot.taille = strlen(mot.contenu);
	  
	  for(int i=0; (mot.taille <= limite) && (i<mot.taille); i++)
	    {
	      mot.debut_x = mot_plateau.debut_x - i;
	      mot.debut_y = mot_plateau.debut_y;
	      mot.fin_y = mot_plateau.fin_y;

	      if((mot.debut_x >= mot_plateau.limite_debut) && (mot.contenu[i] == mot_plateau.contenu[0])) // Vérifie que le mot_plateau est inclus dans le mot
		{
		  mot.fin_x = (mot.debut_x + mot.taille - 1);

		  if (mot.fin_x <= mot_plateau.limite_fin) // Verifie si mot sort du plateau
		    { 
		      if((mot.taille - mot_plateau.taille) == 1)
			{
			  for(int k=0; k<taille_lettres_possedees; k++)
			    {
			      if(((mot.debut_x == mot_plateau.debut_x) && (mot.contenu[mot.taille -1] == lettres_possedees[k])) || ((mot.fin_x == mot_plateau.fin_x) && (mot.contenu[0] == lettres_possedees[k])))
				{
				  mot_orthogonal(mot, mot_plateau, lettres_possedees); // Verifie s'il est possible de creer un mot perpendiculaire au mot
				  break;
				}
			    }
			}

		      for(int k=0; k<mot_plateau.taille; k++)
			{
			  lettres_possedees[7+k] = mot_plateau.contenu[k];
			}
		      
		      lettres_possedees[7+mot_plateau.taille] = '\0';		      		      
		      mot_realisable(mot, lettres_possedees);
		    }
		}
	    }
	}
    }

  if(!horizontal && (mot_plateau.taille == 1)) // Vertical de taille 1, pour le fonctionnement se référrer au premier cas
    {
      for(int j=0; j<TAILLE_DICO; j++)
	{
	  strcpy(mot.contenu, dico[j]);

	  mot.taille = strlen(mot.contenu);

	  for(int i=0; (mot.taille <= limite) && (i<mot.taille); i++) // i correspond à la position de la lettre du plateau dans le mot placé
	    {
	      mot.debut_y = mot_plateau.debut_y - i;
	      mot.debut_x = mot_plateau.debut_x;
	      mot.fin_x = mot_plateau.fin_x;

	      if((mot.debut_y >= mot_plateau.limite_debut) && (mot.contenu[i] == mot_plateau.contenu[0])) // Vérifie que le mot_plateau est inclus dans le mot
		{
		  mot.fin_y = (mot.debut_y + mot.taille - 1);

		  if (mot.fin_y <= mot_plateau.limite_fin) // Verifie si mot sort du plateau
		    {
		      if((mot.taille - mot_plateau.taille) == 1)
			{
			  for(int k=0; k<taille_lettres_possedees; k++)
			    {
			      if(((mot.debut_y == mot_plateau.debut_y) && (mot.contenu[mot.taille -1] == lettres_possedees[k])) || ((mot.fin_y == mot_plateau.fin_y) && (mot.contenu[0] == lettres_possedees[k])))
				{
				  mot_orthogonal(mot, mot_plateau, lettres_possedees); // Verifie s'il est possible de creer un mot perpendiculaire au mot
				  break;
				}
			    }
			}		      

		      for(int k=0; k<mot_plateau.taille; k++)
			{
			  lettres_possedees[7+k] = mot_plateau.contenu[k];
			}
		      
		      lettres_possedees[7+mot_plateau.taille] = '\0';		   		      
		      mot_realisable(mot, lettres_possedees);
		
		    }
		}
	    }
	}
    }
}

void mot_realisable(info_mot mot,char lettres_possedees[])
{
  int compteur_validite = 0;
  int absence = 0;
  int taille_lettres_possedees = strlen(lettres_possedees);

  int points_faits = 0;

  int pos_joker_1 = -1, pos_joker_2 = -1;

  int masque[taille_lettres_possedees];
  
  for (int i=0; i<taille_lettres_possedees; i++)
    {
      masque[i] = 0; // Mise à zero du masque (lettres non utilisées)
    }    
  
  for(int i=0; i < mot.taille; i++)
    {
      absence = 0;
      
      for(int j=taille_lettres_possedees-1; j>=0; j--) // Recherche lettres
	{
	  if(j>= 7) // Si c'est des lettres associées au mot du plateau
	    {
	      if(horizontal)
		{
		  if((mot.contenu[i] == lettres_possedees[j]) && (masque[j] != 1) && !plateau[mot.debut_y][mot.debut_x + i].disponible) 
		    {
		      masque[j] = 1; // Lettre plus utilisable
		      compteur_validite = compteur_validite + 1;
		      break; // Passe a la lettre suivante
		    }
	      
		  else
		    {
		      absence = absence + 1; // Pour l'instant la lettre n'a pas été trouvée dans la main du joueur
		    }
		}
	      
	      else
		{
		  if((mot.contenu[i] == lettres_possedees[j]) && (masque[j] != 1) && !plateau[mot.debut_y + i][mot.debut_x].disponible) 
		    {
		      masque[j] = 1; // Lettre plus utilisable
		      compteur_validite = compteur_validite + 1;
		      break; // Passe a la lettre suivante
		    }
	      
		  else
		    {
		      absence = absence + 1; // Pour l'instant la lettre n'a pas été trouvée dans la main du joueur
		    }
		}
	    }
	  
	  else // Si c'est une lettre de la main du joueur
	    {
	      if((mot.contenu[i] == lettres_possedees[j]) && (masque[j] != 1))
		{
		  masque[j] = 1; // Lettre plus utilisable
		  compteur_validite = compteur_validite + 1;
		  break; // Passe a la lettre suivante
		}
	      
	      else if ((lettres_possedees[j] == 64) && (masque[j] != 1)) // Si aucune lettre n'a été utilisé jusque la on doit utiliser le joker
		{
		  masque[j] = 1;
		  compteur_validite = compteur_validite + 1;
		  
		  if(pos_joker_1 == -1) // Le joker est utilisable, on enregistre sa position dans le mot
		    {
		      pos_joker_1 = i;
		    }
		  
		  else if(pos_joker_2 == -1)
		    {
		      pos_joker_2 = i;
		    }
		}
	      
	      else
		{
		  absence = absence + 1;  // Pour l'instant la lettre n'a pas été trouvée dans la main du joueur
		}
	    }	  
	}
      
      if (absence == taille_lettres_possedees) // Lettre non possedee
	{
	  break;
	}
    }

  if ((compteur_validite == mot.taille) && mot.taille) // La deuxieme condition permet d'enlever les mots correspondant à espace+entre qui sont de taille 0
    {
      if(mot_adjacent(mot, &points_faits, pos_joker_1, pos_joker_2)) // On verifie que les mots adjacents existent
	{
	  points_faits = points_faits + points(mot, pos_joker_1, pos_joker_2); // Calcul du gain

	  tri_insertion(mot, points_faits, lettres_possedees, pos_joker_1, pos_joker_2); // Insertion du mot dans le tableau des meilleurs mots
	}
    }

  lettres_possedees[7] = '\0'; // On réduit la main du joueur aux 7 lettres initiales pour la suite
}

int mot_adjacent(info_mot mot, int *points_faits, int pos_joker_1, int pos_joker_2) // Pour voir si en placant le mot, les mots crees autour existent
{
  int compteur = 0; // Deplacement vertical pour mot horizontal, déplacement horizontal pour mot vertical
  int compteur_lettre = 0;

  info_mot mot_construit;

  mot_construit.taille = 0;

  if(horizontal) // Horizontal
    {
      horizontal = 0; // Mot construit sera vertical, il faut donc passer en vertical pour le calcul des points et revenir en horizontal à la fin

      for(int k=mot.debut_x; k <= mot.fin_x; k++) // On balaye chaque lettre du mot et on regarde ce qu'il y a autour
	{
	  if((mot.debut_y > 0) && (plateau[mot.debut_y][k].disponible != 0) && (plateau[mot.debut_y - 1][k].disponible == 0))
	    {
	      compteur = mot.debut_y - 1; // Le debut du mot adjacent n'est pas parmis les lettres posées pour construire le mot il faut remonter le mot adjacent

	      while((compteur >= 0) && (plateau[compteur][k].lettre != '.')) // Deplacement au debut du mot adjacent
		{
		  compteur--;
		}

	      compteur++; // pour corriger la décrémentation de trop
	      
	      mot_construit.debut_y = compteur;
	      mot_construit.debut_x = k;
	      
	      while((compteur < 15) && ((plateau[compteur][k].lettre != '.') || (compteur == mot.debut_y))) // Puis recuperation de ce mot pour l'analyser
		{
		  if(compteur == mot.debut_y) // Si on est au mot a placé, alors celui-ci n'est pas encore sur le plateau d'ou la condition
		    {
		      mot_construit.contenu[compteur_lettre] = mot.contenu[k - mot.debut_x];
		    }

		  else
		    {
		      mot_construit.contenu[compteur_lettre] = plateau[compteur][k].lettre;
		    }

		  compteur++;
		  compteur_lettre++;
		}
	      
	      mot_construit.contenu[compteur_lettre] = '\0';
	      mot_construit.taille = strlen(mot_construit.contenu);
	    }
	  
	  else if((mot.debut_y != 14) && (plateau[mot.debut_y][k].disponible != 0) && (plateau[mot.debut_y + 1][k].disponible == 0))
	    {
	      compteur = mot.debut_y; // Le debut du mot adjacent est une lettre du mot posé
	      
	      mot_construit.debut_x = k;
	      mot_construit.debut_y = mot.debut_y;
	      
	      while((compteur < 15) && ((plateau[compteur][k].lettre != '.') || (compteur == mot.debut_y))) // Recuperation du mot pour l'analyser
		{
		  if(compteur == mot.debut_y)
		    {
		      mot_construit.contenu[compteur_lettre] = mot.contenu[k - mot.debut_x];
		    }

		  else
		    {
		      mot_construit.contenu[compteur_lettre] = plateau[compteur][k].lettre;
		    }

		  compteur_lettre++;
		  compteur++;
		}
	      
	      mot_construit.contenu[compteur_lettre] = '\0';
	      mot_construit.taille = strlen(mot_construit.contenu);
	    }

	  for(int i=0; mot_construit.taille && (i<TAILLE_DICO); i++) // Analyse du mot adjacent pour voir s'il existe
	    {
	      if(strcmp(mot_construit.contenu, dico[i]) == 0)
		{
		  if(((k-mot.debut_x) == pos_joker_1) || ((k-mot.debut_x) == pos_joker_2)) // Pour prendre en compte le joker dans le calcul des points
		    {
		      *points_faits = *points_faits + points(mot_construit, mot.debut_y-mot_construit.debut_y, mot.debut_y-mot_construit.debut_y);
		    }

		  else
		    {
		      *points_faits = *points_faits + points(mot_construit, -1, -1);
		    }

		  break;
		}

	      else if((i == TAILLE_DICO - 1) && (strcmp(mot_construit.contenu, dico[i]) != 0))
		{
		  horizontal = 1;
		  return 0; // Le mot adjacent n'existe pas, ca ne sert à rien de continuer, le mot ne pourra pas être posé
		}	    
	    }
	  
	  mot_construit.contenu[0] = '\0';
	  mot_construit.taille = strlen(mot_construit.contenu);
	  compteur_lettre = 0;
	}

      horizontal = 1; // Repassage en horizontal pour la suite

      return 1;
    }

  else // Vertical (se réferrer à l'horizontal pour le fonctionnement !)
    {
      horizontal = 1; // Mot construit sera horizontal, il faut donc passer en horizontal pour le calcul des points et revenir en vertical à la fin

      for(int k=mot.debut_y; k <= mot.fin_y; k++)
	{
	  if((mot.debut_x > 0) && (plateau[k][mot.debut_x].disponible != 0) && (plateau[k][mot.debut_x - 1].disponible == 0))
	    {
	      compteur = mot.debut_x - 1;

	      while((compteur >= 0) && (plateau[k][compteur].lettre != '.'))
		{
		  compteur--;
		}

	      compteur++;
	      
	      mot_construit.debut_x = compteur;
	      mot_construit.debut_y = k;
	      
	      while((compteur < 15) && ((plateau[k][compteur].lettre != '.') || (compteur == mot.debut_x)))
		{
		  if(compteur == mot.debut_x)
		    {
		      mot_construit.contenu[compteur_lettre] = mot.contenu[k - mot.debut_y];
		    }

		  else
		    {
		      mot_construit.contenu[compteur_lettre] = plateau[k][compteur].lettre;
		    }	
	 
		  compteur++;
		  compteur_lettre++;
		}
	      
	      mot_construit.contenu[compteur_lettre] = '\0';
	      mot_construit.taille = strlen(mot_construit.contenu);
	    }
	  
	  else if((mot.debut_x < 14) && (plateau[k][mot.debut_x].disponible != 0) && (plateau[k][mot.debut_x + 1].disponible == 0))
	    {
	      compteur = mot.debut_x;
	      
	      mot_construit.debut_y = k;
	      mot_construit.debut_x = mot.debut_x;
	      
	      while((compteur < 15) && ((plateau[k][compteur].lettre != '.') || (compteur == mot.debut_x)))
		{
		  if(compteur == mot.debut_x)
		    {
		      mot_construit.contenu[compteur_lettre] = mot.contenu[k - mot.debut_y];
		    }

		  else
		    {
		      mot_construit.contenu[compteur_lettre] = plateau[k][compteur].lettre;
		    }		  

		  compteur_lettre++;
		  compteur++;
		}
	      
	      mot_construit.contenu[compteur_lettre] = '\0';
	      mot_construit.taille = strlen(mot_construit.contenu);
	    }
	     
	  for(int i=0; (mot_construit.taille) && (i<TAILLE_DICO); i++)
	    {
	      if(strcmp(mot_construit.contenu, dico[i]) == 0)
		{
		  if(((k-mot.debut_y) == pos_joker_1) || ((k-mot.debut_y) == pos_joker_2)) // Pour prendre en compte le joker dans le calcul des points
		    {
		      *points_faits = *points_faits + points(mot_construit, mot.debut_x-mot_construit.debut_x, mot.debut_x-mot_construit.debut_x);
		    }

		  else
		    {
		      *points_faits = *points_faits + points(mot_construit, -1, -1);
		    }

		  break;
		}

	      else if((i == TAILLE_DICO - 1) && (strcmp(mot_construit.contenu, dico[i]) != 0))
		{
		  horizontal = 0;
		  return 0;
		}	    
	    }
	  
	  mot_construit.contenu[0] = '\0';
	  mot_construit.taille = strlen(mot_construit.contenu);
	  compteur_lettre = 0;
	}

      horizontal = 0;

      return 1;
    }
}

void mot_orthogonal(info_mot mot, info_mot mot_plateau, char lettres_possedees[])
{
  if(horizontal) // Si on est en mode horizontal, alors on passe en mode vertical
    {
      horizontal = 0;

      int compteur = mot.debut_y;
      int taille_mot_dico = 0;
      info_mot mot_orthogonal;
      int abscisse;
      int pos_lettre_ajoutee;

      if(mot_plateau.debut_x == mot.debut_x) // Si le début du mot posé est confondu avec celui du mot plateau, le mot orthogonal sera placé à la fin
	{
	  abscisse = mot.fin_x;
	  pos_lettre_ajoutee = mot.taille - 1;
	}

      else // Sinon il sera placé au tout début du mot
	{
	  abscisse = mot.debut_x;
	  pos_lettre_ajoutee = 0;
	}

      while((plateau[compteur][abscisse].lettre == '.') && (compteur > 0)) // On cherche la place que pourra occuper le mot sur la ligne
	{
	  compteur--;
	} 

      if(!compteur) // Si on est au bord du plateau, le mot pourra être posé jusqu'au bord
	{
	  mot.limite_debut = 0;
	}

      else // Si on a recontré un autre mot sur la ligne, le mot ne devra pas le gener, on doit donc eviter la lettre et l'espace libre juste à coté
	{
	  mot.limite_debut = compteur + 2;
	  compteur = compteur + 2;
	}

      while((plateau[compteur][abscisse].lettre == '.') && (compteur < 15))
	{
	  compteur++;
	}

      if(compteur == 15)  // Si on est au bord du plateau, le mot pourra être posé jusqu'au bord
	{
	  mot.limite_fin = 14;
	}

      else  // Si on a recontré un autre mot sur la ligne, le mot ne devra pas le gener, on doit donc eviter la lettre et l'espace libre juste à coté
	{
	  mot.limite_fin = compteur - 2;
	}

      for(int i=0; i<TAILLE_DICO; i++)
	{
	  taille_mot_dico = strlen(dico[i]);

	  if(taille_mot_dico <= (mot.limite_fin - mot.limite_debut + 1) && taille_mot_dico) // Si la taille du mot rentre dans les bornes c'est bon
	    {
	      for(int j=0; j<taille_mot_dico; j++)
		{
		  if((dico[i][j] == mot.contenu[pos_lettre_ajoutee]) && ((mot.debut_y - j) >= mot.limite_debut) && ((mot.debut_y + taille_mot_dico - j - 1) <= mot.limite_fin) && (taille_mot_dico <= 7))
		    {
		      strcpy(mot_orthogonal.contenu, dico[i]);
		      mot_orthogonal.debut_y = mot.debut_y - j;
		      mot_orthogonal.fin_y = mot.debut_y + taille_mot_dico - j - 1;
		      mot_orthogonal.debut_x = abscisse;
		      mot_orthogonal.fin_x = abscisse;
		      mot_orthogonal.taille = taille_mot_dico;

		      mot_realisable(mot_orthogonal, lettres_possedees); // Si le mot est réalisable, on calcule son gain ...
		    }
		}
	    }
	}

      horizontal = 1;
    }

  else // Si on est en mode vertical, alors on passe en mode horizontal, pour le fonctionnement se référrer au cas précédent
    {
      horizontal = 1;

      int compteur = mot.debut_x;
      int taille_mot_dico = 0;
      info_mot mot_orthogonal;
      int ordonnee;
      int pos_lettre_ajoutee;

      if(mot_plateau.debut_y == mot.debut_y)
	{
	  ordonnee = mot.fin_y;
	  pos_lettre_ajoutee = mot.taille - 1;
	}

      else
	{
	  ordonnee = mot.debut_y;
	  pos_lettre_ajoutee = 0;
	}

      while((plateau[ordonnee][compteur].lettre == '.') && (compteur > 0)) // On cherche la place que pourra occuper le mot sur la ligne
	{
	  compteur--;
	} 

      if(!compteur) // Si on est au bord du plateau, le mot pourra être posé jusqu'au bord
	{
	  mot.limite_debut = 0;
	}

      else // Si on a recontré un autre mot sur la ligne, le mot ne devra pas le gener, on doit donc eviter la lettre et l'espace libre juste à coté
	{
	  mot.limite_debut = compteur + 2;
	  compteur = compteur + 2;
	}

      while((plateau[ordonnee][compteur].lettre == '.') && (compteur < 15))
	{
	  compteur++;
	}

      if(compteur == 15)  // Si on est au bord du plateau, le mot pourra être posé jusqu'au bord
	{
	  mot.limite_fin = 14;
	}

      else  // Si on a recontré un autre mot sur la ligne, le mot ne devra pas le gener, on doit donc eviter la lettre et l'espace libre juste à coté
	{
	  mot.limite_fin = compteur - 2;
	}

      for(int i=0; i<TAILLE_DICO; i++)
	{
	  taille_mot_dico = strlen(dico[i]);

	  if(taille_mot_dico <= (mot.limite_fin - mot.limite_debut + 1) && taille_mot_dico)
	    {
	      for(int j=0; j<taille_mot_dico; j++)
		{
		  if((dico[i][j] == mot.contenu[pos_lettre_ajoutee]) && ((mot.debut_x - j) >= mot.limite_debut) && ((mot.debut_x + taille_mot_dico - j - 1) <= mot.limite_fin) && (taille_mot_dico <= 7))
		    {
		      strcpy(mot_orthogonal.contenu, dico[i]);
		      mot_orthogonal.debut_x = mot.debut_x - j;
		      mot_orthogonal.fin_x = mot.debut_x + taille_mot_dico - j - 1;
		      mot_orthogonal.debut_y = ordonnee;
		      mot_orthogonal.fin_y = ordonnee;
		      mot_orthogonal.taille = taille_mot_dico;

		      mot_realisable(mot_orthogonal, lettres_possedees);
		    }
		}
	    }
	}

      horizontal = 0;
    }
}

