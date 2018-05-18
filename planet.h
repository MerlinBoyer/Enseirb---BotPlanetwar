#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define NB_TOURS 200
#define TAILLE_BUFFER 100
#define TAILLE_UNIVERS 50
#define TAILLE_TAB_FLEETS 1000


struct planet {            /*permet de stocker les infos du jeu dans un struct*/
  float x;
  float y;
  int owner;
  int ships;
  int growth;
  int numero;
};

struct fleets{            /* permet de stocker les infos sur les troupes qui se deplacent dans un struct*/
  int owner;
  int ships;
  int source;
  int destination;
  int total_turns;
  int remaining_turns;
};

struct bot_order{           /* ordre du bot qui va être envoyé*/
  int source;
  int destination;
  int ships;
};

char buffer[TAILLE_BUFFER];
struct bot_order bot_order;
struct planet tab_planet[TAILLE_UNIVERS];     /*tableau de structs planet*/
struct fleets tab_fleets[TAILLE_TAB_FLEETS];     /*tableau de strcuts fleets*/
struct planet our_planet[TAILLE_UNIVERS];
struct planet adverse_planet[TAILLE_UNIVERS];
int tableau_des_plus_pres_pour_chaque_planet[TAILLE_UNIVERS];
int order;
int nbr_our_planet;
int nbr_adverse_planet;
int indice_planet;
int indice_fleet;
int nb_planet_tot;
int indice_adverse_planet;
int indice_our_planet;
int nbr_fleets;
struct fleets f[TAILLE_UNIVERS];
int nbr_adverse_fleets;
int nbr_our_fleets;
struct fleets our_fleets[TAILLE_UNIVERS];
struct fleets adverse_fleets[TAILLE_UNIVERS];
int indice_adverse_fleets;
int indice_our_fleets;
struct planet most_attractive;



void status_engine(char buffer[TAILLE_BUFFER],
                  struct planet tab_planet[TAILLE_UNIVERS],
                  struct fleets tab_fleets[TAILLE_UNIVERS],
                  int* indice_planet,
                  int* indice_fleet,
                  int* order,
                  int* nb_planet_tot,
                  int* nbr_fleets);

int distance(struct planet s,
             struct planet d);

void triage_planet(struct planet p[TAILLE_UNIVERS],
                   int* nbr_adverse_planet,
                   int* nbr_our_planet,
                   struct planet our_planet[TAILLE_UNIVERS],
                   struct planet adverse_planet[TAILLE_UNIVERS],
                   int* nb_planet_tot,
                   int* indice_adverse_planet,
                   int* indice_our_planet);


void triage_fleets(struct fleets f[TAILLE_UNIVERS],
                   int* nbr_adverse_fleets,
                   int* nbr_our_fleets,
                   struct fleets our_fleets[TAILLE_UNIVERS],
                   struct fleets adverse_fleets[TAILLE_UNIVERS],
                   int* nbr_fleets,
                   int* indice_adverse_fleets,
                   int* indice_our_fleets);

void random_bot(struct bot_order* bot_order,
                struct planet our_planet[TAILLE_UNIVERS],
                struct planet adverse_planet[TAILLE_UNIVERS],
                int nbr_our_planet,
                int nbr_adverse_planet);

void raz( int* order,
          int* nbr_our_planet,
          int* nbr_adverse_planet,
          int* indice_planet,
          int* indice_fleet,
          int* nb_planet_tot,
          int* indice_adverse_planet,
          int* indice_our_planet,
          int* nbr_fleets,
          int* nbr_adverse_fleets,
          int* nbr_our_fleets,
          int* indice_adverse_fleets,
          int* indice_our_fleets);



          void bot_nb_one(struct bot_order* bot_order,
                          struct planet our_planet[TAILLE_UNIVERS],
                          struct planet adverse_planet[TAILLE_UNIVERS],
                          int nbr_our_planet,
                          int nbr_adverse_planet,
                          int indice_our_planet);




                          void most_attractive_planet(struct planet one_of_our_planet,
                                                      struct planet adverse_planet[TAILLE_UNIVERS],
                                                      struct planet* most_attractive,
                                                      int nbr_adverse_planet,
                                                      int indice_adverse_planet);


void la_planete_la_plus_pres_est(struct planet our_planet[TAILLE_UNIVERS],
                                 struct planet adverse_planet[TAILLE_UNIVERS],
                                 int tableau_des_plus_pres_pour_chaque_planet[TAILLE_UNIVERS],
                                 int indice_our_planet,
                                 int indice_adverse_planet);
