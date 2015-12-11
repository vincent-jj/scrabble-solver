#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"scrabble.h"

info_meilleur meilleur_coup[20]; // Voir scrabble.h pour le detail de la structure

int compteur_arret = 10; // Pour arrêter le jeu au bout de 10 tours d'affilé sans jouer (impossibilité de continuer à jouer)

int horizontal = 1; // On balaye verticalement si horizontal = 0, horizontalement sinon

char dico[TAILLE_DICO][TAILLE_MAX]; // Dico chargé en mémoire

char mode_jeu[3]; // Si l'option '-n' n'est pas passé, rien ne sert de faire la liste des 20 meilleurs mots pour économiser des actions

int main(int argc, char **argv)
{
  if((argc > 1 && !strcmp(argv[1], "-n")) || (argc > 2 && (!strcmp(argv[1], "-n") || !strcmp(argv[2], "-n"))))
    {
      strcpy(mode_jeu, "-n");
    }

  int choix = 0; // Si choix reste à 0 (cas ou l'argument -n n'a pas été passé), la meilleure solution sera tjrs choisie
  
  int lettres_sac = 102; // Lettres disponibles dans le sac
  
  int compteur_tour = 1;

  int masque_alphabet[102]; // Initialisation du masque alphabet
  
  charger_dico(); // Dico en mémoire
  generateur_plateau(); // Creation du plateau
  
  for (int i=0; i<102; i++)
    {
      masque_alphabet[i] = 1; // La valeur 1 indique une lettre disponible
    }
  
  for(int i=0; i<20; i++)
    {
      meilleur_coup[i].mot.contenu[0] = '\0'; // Mot vide car pas de meilleur mot au debut
      meilleur_coup[i].resultat = 0;
    }
  
  char lettres_possedees[TAILLE_MAX]="       "; // Main vide initialement
  
  while(meilleur_coup[choix].resultat == 0) // Tant qu'on a pas pu jouer au premier tour le programme reste dans cette boucle
    {
      if((argc > 1 && !strcmp(argv[1], "-m")) || (argc > 2 && (!strcmp(argv[1], "-m") || !strcmp(argv[2], "-m")))) // Pour éviter les 'segmentation fault'
	{
	  lettres_sac = tirage_manuel(lettres_possedees, lettres_sac); // Distribution manuelle de la main du joueur
	}
      
      else
	{
	  lettres_sac = tirage(lettres_possedees, masque_alphabet, lettres_sac); // Création de la main du joueur
	}
      
      printf("Tour numero : %d ! Il reste %d lettres !\n \n", compteur_tour, lettres_sac);
      
      printf("Main du joueur : %s \n \n", lettres_possedees);
      
      premier_mot(lettres_possedees); // Premier tour, pose du premier mot
      
      if((argc > 1 && !strcmp(argv[1], "-n")) || (argc > 2 && (!strcmp(argv[1], "-n") || !strcmp(argv[2], "-n")))) // Pour éviter les 'segmentation fault'
	{
	  liste_meilleurs_mots(); // Liste des 20 meilleurs mots (ou moins)

	  printf("Veuillez entrer le numéro associé au mot que vous voulez poser : \n");
	  scanf("%d", &choix);

	  while(getchar() != '\n') // Pour purger le buffer
	    {
	      
	    }
	}      
      
      affichage_score(choix);
      
      placer_mot(choix); // Placement du mot sur le plateau de jeu
      
      lettres_sac = retirer_lettres_utilisees(lettres_possedees, masque_alphabet, lettres_sac, choix); // Fin du premier tour
      
      printf("Appuyez sur entrée pour continuer. \n");
      
      while(getchar() != '\n') // Fonction permettant d'attendre le joueur
	{
	  
	}  
      
      compteur_tour++;
    }
  
  while(lettres_sac && compteur_arret) // Le jeu s'arrête quand il n'y a plus de lettres dans le sac, ou que le joueur ne peut plus jouer
    {
      enregistrer_grille(); // Enregistre la grille pour effectuer du debuggage si besoin

      choix = 0; // Réinitialisation du choix, utile dans le cas où l'argument '-n' a été passé
      
      for(int i=0; i<20; i++) // Réinitialisation des meilleurs mots
	{
	  meilleur_coup[i].mot.contenu[0] = '\0'; 
	  meilleur_coup[i].resultat = 0;
	  meilleur_coup[i].pos_joker_1 = -1;
	  meilleur_coup[i].pos_joker_2 = -1;
	}

      if((argc > 1 && !strcmp(argv[1], "-m")) || (argc > 2 && (!strcmp(argv[1], "-m") || !strcmp(argv[2], "-m")))) // Pour éviter les 'segmentation fault'
	{
	  lettres_sac = tirage_manuel(lettres_possedees, lettres_sac); // Distribution manuelle de la main du joueur
	}
      
      else
	{
	  lettres_sac = tirage(lettres_possedees, masque_alphabet, lettres_sac); // Création de la main du joueur
	}
      
      printf("Tour numero : %d ! Il reste : %d lettres !\n \n", compteur_tour, lettres_sac);
      
      printf("Main du joueur : %s \n \n", lettres_possedees);
      
      balayage_plateau(lettres_possedees); // Fonction principale cherchant le meilleur mot
      
      if((argc > 1 && !strcmp(argv[1], "-n")) || (argc > 2 && (!strcmp(argv[1], "-n") || !strcmp(argv[2], "-n")))) // Pour éviter les 'segmentation fault'
	{
	  liste_meilleurs_mots();  // Liste des 20 meilleurs mots (ou moins)

	  printf("Veuillez entrer le numéro associé au mot que vous voulez poser : \n");
	  scanf("%d", &choix);

	  while(getchar() != '\n') // Pour purger le buffer
	    {
	      
	    }
	}
      
      affichage_score(choix);
      
      placer_mot(choix);
      
      lettres_sac = retirer_lettres_utilisees(lettres_possedees, masque_alphabet, lettres_sac, choix); // Fin du tour
      
      compteur_tour++; // Fin du tour
      
      printf("Appuyez sur entrée pour continuer. \n");
      
      while(getchar() != '\n')
	{
	  
	}
    }
  
  return 0;
}

void affichage_score(int choix)
{
  if(!(meilleur_coup[choix].mot.debut_y == meilleur_coup[choix].mot.fin_y)) // Mot placé horizontalement
    {
      printf("Numéro : %2d, Gain : %3d, Mot : %s, Position : %2d%c \n", choix, meilleur_coup[choix].resultat, meilleur_coup[choix].mot.contenu, meilleur_coup[choix].mot.debut_x+1, meilleur_coup[choix].mot.debut_y+65);
    }
  
  else // Mot placé verticalement
    {
      printf("Numéro : %2d, Gain : %3d, Mot : %s, Position : %c%2d \n", choix, meilleur_coup[choix].resultat, meilleur_coup[choix].mot.contenu, meilleur_coup[choix].mot.debut_y+65, meilleur_coup[choix].mot.debut_x+1);
    }
}

void liste_meilleurs_mots()
{
  for(int i=0; i<20; i++)
    {
      if(!meilleur_coup[i].resultat) // Arrêt de la boucle si à partir du ième élément il n'y a plus de possibilités
	{
	  break;
	}
      
      else
	{
	  affichage_score(i);
	}
    }
}

void enregistrer_grille()
{
  FILE *grille = NULL;
  grille = fopen("grille.txt", "w");
  
  for(int i=0; i<15; i++)
    {
      for(int j=0; j<15; j++)
	{
	  fprintf(grille, "plateau[%d][%d].lettre = '%c';\n", j, i, plateau[j][i].lettre);
	  fprintf(grille, "plateau[%d][%d].disponible = %d;\n", j, i, plateau[j][i].disponible);
	}
    }
  
  fclose(grille);
}
