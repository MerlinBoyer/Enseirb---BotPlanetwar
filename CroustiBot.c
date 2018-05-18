#include <errno.h>
#include <assert.h>
#include <math.h>
#include <stdio.h> /* fopen, fread, fwrite*/
#include <stdlib.h> /* malloc, exite*/
#include <string.h> /* memset */
#include <strings.h> /* ffs */
#include "planet.h"


/*********************************************************************************************************************************
    Cette fonction prend les données du statut du jeu dans stdin et les range dans les tableaux de structs correspondant
    (on range chaque planète par ordre d'arrivée dans le tableau tab_planet en lui assigant un "numéro" correspondant à son ordre,
    ce numéro étant le même que celui de l'engine et chaque fleets dans le tableau tab_fleets)
*********************************************************************************************************************************/
void status_engine(char buffer[TAILLE_BUFFER],
                  struct planet tab_planet[TAILLE_UNIVERS],
                  struct fleets tab_fleets[TAILLE_TAB_FLEETS],
                  int* indice_planet,
                  int* indice_fleet,
                  int* order,
                  int* nb_planet_tot,
                  int* nbr_fleets)
{

      if (buffer[0]=='P'){                          /*traduction des données du statut planet qu'on met des le tableau de structs planet*/
          sscanf(buffer, "P %f %f %d %d %d",
          &tab_planet[*indice_planet].x,
          &tab_planet[*indice_planet].y,
          &tab_planet[*indice_planet].owner,
          &tab_planet[*indice_planet].ships,
          &tab_planet[*indice_planet].growth);
          tab_planet[*indice_planet].numero = *order;
          (*indice_planet)++ ;
          (*order)++;
          (*nb_planet_tot)++;
      }
      if (buffer[0]=='F'){                          /*traduction des données du statut fleets qu'on met des le tableau de structs fleets*/
          sscanf(buffer, "F %d %d %d %d %d %d",
          &tab_fleets[*indice_fleet].owner,
          &tab_fleets[*indice_fleet].ships,
          &tab_fleets[*indice_fleet].source,
          &tab_fleets[*indice_fleet].destination,
          &tab_fleets[*indice_fleet].total_turns,
          &tab_fleets[*indice_fleet].remaining_turns);
          (*indice_fleet)++;
          (*nbr_fleets)++;
      }

}

/**********************************************************************************************************************************************
Cette fonction calcule la distance entre deux planètes données (source et destination)
*********************************************************************************************************************************************/
int distance(struct planet s,
             struct planet d)
{
    double x= sqrt((((d.x)-(s.x))*((d.x)-(s.x)))+(((d.y)-(s.y))*((d.y)-(s.y))));   /*calcul la distance entre s et d */
    double distance = ceil(x);
    /*printf("%f\n", distance);*/
    return (int)(distance);

}

/**********************************************************************************************************************************************
Cette fonction trie les planètes : si c'est une planète attaquable (neutre ou adverse)-> adverse_planet[]
                                  si c'est notre planète -> our_planet
*********************************************************************************************************************************************/
void triage_planet(struct planet p[TAILLE_UNIVERS],
                   int* nbr_adverse_planet,
                   int* nbr_our_planet,
                   struct planet our_planet[TAILLE_UNIVERS],
                   struct planet adverse_planet[TAILLE_UNIVERS],
                   int* nb_planet_tot,
                   int* indice_adverse_planet,
                   int* indice_our_planet)
{
  int j=0;
  int k=0;
  int l=0;

  while (j<(*nb_planet_tot)){
      if ((p[j].owner==2)||(p[j].owner==0)){
          adverse_planet[k]=p[j];
          (*indice_adverse_planet)=k;
          (*nbr_adverse_planet)++;
          k++;
      }
      if (p[j].owner==1){
          our_planet[l]=p[j];
          (*indice_our_planet)=l;
          (*nbr_our_planet)++;
          l++;
      }
      j++;
  }
}



/**********************************************************************************************************************************************
Cette fonction trie les fleets : si c'est fleets adverse (adverse)-> adverse_fleets[]
                                  si c'est our fleets -> our_fleets
*********************************************************************************************************************************************/




void triage_fleets(struct fleets f[TAILLE_UNIVERS],
                   int* nbr_adverse_fleets,
                   int* nbr_our_fleets,
                   struct fleets our_fleets[TAILLE_UNIVERS],
                   struct fleets adverse_fleets[TAILLE_UNIVERS],
                   int* nbr_fleets,
                   int* indice_adverse_fleets,
                   int* indice_our_fleets)
{
  int j=0;
  int k=0;
  int l=0;

  while (j<(*nbr_fleets)){
      if (f[j].owner==2){
          adverse_fleets[k]=f[j];
          (*indice_adverse_fleets)=k;
          (*nbr_adverse_fleets)++;
          k++;
      }
      if (f[j].owner==1){
          our_fleets[l]=f[j];
          (*indice_our_fleets)=l;
          (*nbr_our_fleets)++;
          l++;
      }
      j++;
  }
}

/**************************************************************************************************************************************************
BOT version 1.0
***************************************************************************************************************************************************/
void bot_nb_one(struct bot_order* bot_order,
                struct planet our_planet[TAILLE_UNIVERS],
                struct planet adverse_planet[TAILLE_UNIVERS],
                int nbr_our_planet,
                int nbr_adverse_planet,
                int indice_our_planet)
{
  int i=0;

  if ((nbr_our_planet!=0)&(nbr_adverse_planet!=0)){
    while(i<= indice_our_planet){
      most_attractive_planet(our_planet[i], adverse_planet, &most_attractive, nbr_adverse_planet, indice_adverse_planet);
      bot_order -> source = our_planet[i].numero;
      bot_order -> destination = most_attractive.numero;
      bot_order -> ships = ceil((our_planet[i].ships)/2.);
      printf("%d %d %d\n", bot_order->source, bot_order->destination, bot_order->ships);
      i++;
    }
  }

}



/***********************************************************************************************************************************************
Début de la stratègie
***********************************************************************************************************************************************/



/*définition de la planète à attaquer en priorité pour une de nos planètes*/
void most_attractive_planet(struct planet one_of_our_planet,
                            struct planet adverse_planet[TAILLE_UNIVERS],
                            struct planet* most_attractive,
                            int nbr_adverse_planet,
                            int indice_adverse_planet)
{

  *most_attractive = adverse_planet[0];
  if (nbr_adverse_planet > 1){
    int i  = 1;
                                                                    /*critère : (distance*defense)/croissance le plus petit */
    while(i <= indice_adverse_planet){
      if((distance(one_of_our_planet, adverse_planet[i])*(adverse_planet[i].ships)/(adverse_planet[i].growth)) <
        (distance(one_of_our_planet, (*most_attractive))*(((*most_attractive).ships)/((*most_attractive).growth)))){
          *most_attractive = adverse_planet[i];
      }
      i++;
    }
  }

}



/**********************************************************************************************************************************************
Cette fonction remet à zéro les pointeurs (tableaux et indices)
*********************************************************************************************************************************************/
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
          int* indice_our_fleets)
{
*order=0;
*nbr_our_planet=0;
*nbr_adverse_planet=0;
*indice_planet=0;
*indice_fleet=0;
*nb_planet_tot=0;
*indice_adverse_planet=0;
*indice_our_planet=0;
*nbr_fleets=0;
*nbr_adverse_fleets=0;
*nbr_our_fleets=0;
*indice_adverse_fleets=0;
*indice_our_fleets=0;

}











int main(int argc, char **argv)
{

  raz(&order,
      &nbr_our_planet,
      &nbr_adverse_planet,
      &indice_planet,
      &indice_fleet,
      &nb_planet_tot,
      &indice_adverse_planet,
      &indice_our_planet,
      &nbr_fleets,
      &nbr_adverse_fleets,
      &nbr_our_fleets,
      &indice_adverse_fleets,
      &indice_our_fleets);
  setvbuf(stdout, NULL, _IOLBF, 0);
  while (!feof(stdin))
  {
      fgets(buffer,TAILLE_BUFFER, stdin);
      if ((buffer[0]=='g') && (buffer[1]=='o'))
      {
         triage_planet(tab_planet, &nbr_adverse_planet, &nbr_our_planet, our_planet, adverse_planet, &nb_planet_tot, &indice_adverse_planet, &indice_our_planet);   /*trie les planètes*/
        /*  triage_fleets(tab_fleets, &nbr_adverse_fleets, &nbr_our_fleets, our_fleets, adverse_fleets, &nbr_fleets, &indice_adverse_fleets, &indice_our_fleets);*/

        /* most_attractive_planet(our_planet[0], adverse_planet, &most_attractive);*/
        bot_nb_one(&bot_order, our_planet, adverse_planet, nbr_our_planet, nbr_adverse_planet, indice_our_planet);
      /*   la_planete_la_plus_pres_est(our_planet, adverse_planet, tableau_des_plus_pres_pour_chaque_planet, indice_our_planet, indice_adverse_planet);*/
         /*random_bot(&bot_order, our_planet, adverse_planet, nbr_our_planet, nbr_adverse_planet);*/
      /* printf("%d %d %d\n", bot_order.source, bot_order.destination, bot_order.ships);*/
      raz(&order,
          &nbr_our_planet,
          &nbr_adverse_planet,
          &indice_planet,
          &indice_fleet,
          &nb_planet_tot,
          &indice_adverse_planet,
          &indice_our_planet,
          &nbr_fleets,
          &nbr_adverse_fleets,
          &nbr_our_fleets,
          &indice_adverse_fleets,
          &indice_our_fleets);

                printf("go\n");

      }
      status_engine(buffer, tab_planet, tab_fleets, &indice_planet, &indice_fleet, &order, &nb_planet_tot, &nbr_fleets); /*range les données du statut*/
  }
  return 0;
}
