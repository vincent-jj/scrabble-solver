#define TAILLE_MAX 24
#define TAILLE_DICO 386265

typedef struct info_mot info_mot;
struct info_mot
{
  char contenu[TAILLE_MAX];
  int debut_x;
  int debut_y;
  int fin_x;
  int fin_y;
  int taille;
  int limite_debut;
  int limite_fin;
};

typedef struct surface_jeu surface_jeu;
struct surface_jeu
{
  char lettre;
  int multiplieur_lettre;
  int multiplieur_mot;
  int disponible;
};

typedef struct info_meilleur info_meilleur;
struct info_meilleur
{
  info_mot mot;
  int resultat;
  char lettres_possedees[TAILLE_MAX];
  int pos_joker_1;
  int pos_joker_2;
};

char dico[TAILLE_DICO][TAILLE_MAX];

info_meilleur meilleur_coup[20];
char mode_jeu[3];

int compteur_arret;

int horizontal;
surface_jeu plateau[15][15];

void charger_dico();

int tirage(char lettres_possedees[], int masque_alphabet[], int lettres_sac);
int tirage_manuel(char lettres_possedees[], int lettres_sac);
int retirer_lettres_utilisees(char lettres_possedees[], int masque_alphabet[], int lettres_sac, int choix);

void balayage_plateau(char lettres_possedees[]);
void generateur_plateau();
void miroir();

void premier_mot(char lettres_possedees[]);
void recherche_mot_plateau(char lettres_possedees[], info_mot mot_plateau);
void mot_realisable(info_mot mot, char lettres_possedees[]);
int mot_adjacent(info_mot mot, int *points_faits, int pos_joker_1, int pos_joker_2);
void mot_orthogonal(info_mot mot, info_mot mot_plateau, char lettres_possedees[]);

int points(info_mot mot, int pos_joker_1, int pos_joker_2);
void tri_insertion(info_mot mot, int points_faits, char lettres_possedees[], int pos_joker_1, int pos_joker_2);

void placer_mot(int choix);

void affichage_score(int choix);
void liste_meilleurs_mots();
void enregistrer_grille();
