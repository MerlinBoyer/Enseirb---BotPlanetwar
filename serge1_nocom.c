/*java -jar tools/PlayGame.jar maps/map5.txt 1000 1500 log.txt "java -jar example_bots/DualBot.jar" "./JMbot" | java -jar tools/ShowGame.jar */


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

#define TAILLE_MAX 100
#define MAX_PLANET 50
#define NB_ARMIES 60
#define NUM_PLAYER 1


struct planet {
    float x;
    float y;
    int owner;
    int ships;
    int growth;
    int id;

};

struct fleet {
    int owner;
    int ships;
    int source;
    int destination;
    int total_turns;
    int remaining_turns;
    int id;

};

/*      les indices servent a incrementer les tableaux contenant les differents
        types de planetes ou flottes (alliees, ennemies...) et a connaitre leur 
        nombre pendant un tour   */ 
struct indice {   
    int indp_ally;
    int indp_ennemy;
    int indp_neutral;
    int indf_ally;
    int indf_ennemy;
};



/***********************recupere les donnees du moteur dans un buffer (sous forme d'une seule string)********************/





void listen(char buffer[]){   /*stocke dans buffer une ligne de stdout*/
    fgets(buffer, TAILLE_MAX, stdin);
}

void go(){ /*envoie go au moteur de jeu*/
    printf("go\n");
}






/*************fcts d'initialisation et de raz : *************/

void init_planets(struct planet new_planets[MAX_PLANET]){
    int i;
    for(i=0;i<=MAX_PLANET;i++){
        new_planets[i].x = 0;
        new_planets[i].y = 0;
        new_planets[i].owner = 0;
        new_planets[i].ships = 0;
        new_planets[i].growth = 0;
        new_planets[i].id = 0;
    }
}



void init_indice(struct indice* indice){
    indice->indp_ally = 0;
    indice->indp_ennemy = 0;
    indice->indp_neutral = 0;
    indice->indf_ally = 0;
    indice->indf_ennemy = 0;
}





            /*******************************************
             * Partie dediee au traitement des donnees *
             *******************************************/







/*****pour traduire le char du buffer en structures de planetes ou de fleet****/




/*      ces 2 programmes modifient les valeurs des composants des structures 
        passées en argument pour traduire la ligne stdin stockée dans le buffer
        */

void traduction_planet(char buffer[], struct planet* planete){
    sscanf(buffer, "P %f %f %d %d %d", &planete->x, &planete->y, &planete->owner, &planete->ships, &planete->growth);
}


void traduction_fleet(char buffer[], struct fleet* current_fleet){
    sscanf(buffer, "F %d %d %d %d %d %d", &current_fleet->owner, &current_fleet->ships, &current_fleet->source, &current_fleet->destination, &current_fleet->total_turns,
    &current_fleet->remaining_turns);
}






/*      copy la struct d'une planete dans une autre structure (permettra la 
        recup de certaines planetes precises)   
        */
        
        
void copy_planet(struct planet* planet_source, struct planet* planet_copy){
    planet_copy->x = planet_source->x;
    planet_copy->y = planet_source->y;
    planet_copy->owner = planet_source->owner;
    planet_copy->ships = planet_source->ships;
    planet_copy->growth = planet_source->growth;
    planet_copy->id = planet_source->id;
}

void copy_fleet(struct fleet* fleet_source, struct fleet* fleet_copy){
    fleet_copy->owner = fleet_source->owner;
    fleet_copy->ships = fleet_source->ships;
    fleet_copy->source = fleet_source->source;
    fleet_copy->destination = fleet_source->destination;
    fleet_copy->total_turns = fleet_source->total_turns;
    fleet_copy->remaining_turns = fleet_source->remaining_turns;
    fleet_copy->id = fleet_source->id;
}



/*      ce programme enregistre le contenu du buffer dans le tableau 
        correspondant (p alliees, f ennemies etc...), il utilise des pointeurs
        pour modifier durablement les tableaux du main et il incremente les
        compteurs (=les indices) de ceux-ci.
        Au final on obtient des tableaux remplis de structures et le nombre
        total de types de planetes/flottes pour le tour.        */


void game_stat(char buffer[], struct planet p_allied[MAX_PLANET], struct planet p_ennemy[MAX_PLANET], struct planet p_neutral[MAX_PLANET], struct fleet f_allied[NB_ARMIES], struct fleet f_ennemy[NB_ARMIES], int* id_planet, int* id_fleet, struct indice* indice){
    struct planet current_planet;
    struct fleet current_fleet;
    if(buffer[0] == 'P'){
        traduction_planet(buffer, &current_planet);
        current_planet.id = *id_planet;
        if(current_planet.owner == 1){
            copy_planet(&current_planet, &(p_allied[(indice->indp_ally)]));
            (indice->indp_ally)++;      /* indice de la planete en tant que 
                                           planete alliee, indique sa position 
                                           dans le tableau p_allied        */
            }
        if(current_planet.owner == 2){
            copy_planet(&current_planet, &(p_ennemy[(indice->indp_ennemy)]));
            (indice->indp_ennemy)++;
            }
        if(current_planet.owner == 0){
            copy_planet(&current_planet, &(p_neutral[(indice->indp_neutral)]));
            (indice->indp_neutral)++;
            }
        (*id_planet)++;       /*id_planet = indice reel de la planete pour le 
                                            moteur de jeu  */
        }
        
    if(buffer[0] == 'F'){
        traduction_fleet(buffer, &current_fleet);
        current_fleet.id = *id_fleet;
        if(current_fleet.owner == 1){
            copy_fleet(&current_fleet, &(f_allied[(indice->indf_ally)]));
            (indice->indf_ally)++;
            }
        if(current_fleet.owner == 2){
            copy_fleet(&current_fleet, &(f_ennemy[(indice->indf_ennemy)]));
            (indice->indf_ennemy)++;
            }
        (*id_fleet)++;      /*id_fleet = indice reel de la flotte pour le 
                                         moteur de jeu  */
        }
}







            /*****************************
             * Partie dediee aux ordres  *
             *****************************/





/**********************************************************************/

/*ordre de lancement d'une flotte*/
void attack(struct planet* planet_source, struct planet* planet_destination, int nb_ships){
    if(planet_source->id != planet_destination->id && nb_ships <= planet_source->ships){
        printf("%d %d %d \n",planet_source->id, planet_destination->id, nb_ships);
    }
}

/* Bots operationels *
 *********************/
/* Pour le random bot, chaque planete alliee a une chance d'attaquer une planete
   aleatoire a chaque tour      */




/* toutes les planetes alliee envoient n=growth vaisseaux vers la premiere planete ennemie*/

void bot_mitraillette(struct planet p_allied[MAX_PLANET], struct planet p_ennemy[MAX_PLANET], struct indice* indice){
    int i;
    for( i=0 ; i<(indice->indp_ally) ; i++){
        attack( &(p_allied[i]), &(p_ennemy[0]), (p_allied[0]).growth);
    }
}




void random_bot(struct planet p_allied[MAX_PLANET], struct planet p_ennemy[MAX_PLANET], struct indice* indice, int id_planet_tot){
    int i;
    for(i=0 ; i<indice->indp_ally ; i++){
        int ToAttackOrToNotAttack = rand()%3;     /* =0,1 ou 2*/
        if (ToAttackOrToNotAttack == 0){    /*une chance sur 3 d'attaquer*/
            int planete_cible = rand()%id_planet_tot;
            int nb_ships = rand()%(p_allied[i].ships);
            printf("%d %d %d \n", p_allied[i].id, planete_cible, nb_ships);
        }
    }
}


void weak_sorting(struct planet pNotSorted[MAX_PLANET], struct planet pSorted[MAX_PLANET], int id_max){
    int i;
    int j;
    int id_weak = 0;
    int tmp = pNotSorted[0].ships;
    for( i=0 ; i<id_max ; i++ ){
        for( j=0; j<id_max ; j++){
            if (tmp > pNotSorted[j].ships){
                id_weak = j;
                tmp = pNotSorted[j].ships;
            }
        }
        copy_planet(&(pNotSorted[id_weak]), &(pSorted[i]));
        tmp++;
    }
}
        
    
    
void colonizeWeak(struct planet p_allied[MAX_PLANET], struct planet p_neutral[MAX_PLANET], struct indice* indice){
    struct planet neutral_sorted[MAX_PLANET];
    weak_sorting(p_neutral , neutral_sorted , indice->indp_neutral);
    int i;
    for( i=0; i<=(indice->indp_ally) ; i++){
        if( (p_allied[i].ships) >= 110){
            attack( &(p_allied[i]) , &(neutral_sorted[0]) , 10 );
        }
    }
}


void attack_all(struct planet p_allied[MAX_PLANET], struct planet p_ennemy[MAX_PLANET], struct indice* indice){
    int i;
    for( i=0 ; i<(indice->indp_ally) ; i++){
        if(p_allied[i].ships>=100){
            attack(&(p_allied[i]) , &(p_ennemy[0]) , 25);
        }
    }
}







            
void serge(struct planet p_allied[MAX_PLANET], struct planet p_ennemy[MAX_PLANET], struct planet p_neutral[MAX_PLANET], struct indice* indice){
    if(indice->indp_neutral > indice->indp_ally){
        colonizeWeak(p_allied, p_neutral, indice);
    }
    else{
        attack_all(p_allied , p_ennemy , indice);
    }
}
    


/******************************************************************************/















/*****  main : cree les el vides, boucle infinie qui lit les donnees, 
             les traduit, quand un go est detecte donne les ordres, raz les 
             indices puis print go.
*****/


int main(int argc, char *argv[]){
    setvbuf(stdout, NULL, _IOLBF, 0);
    char buffer[TAILLE_MAX];
    struct planet p_allied[MAX_PLANET];
    struct planet p_ennemy[MAX_PLANET];
    struct planet p_neutral[MAX_PLANET];
    struct fleet f_allied[NB_ARMIES];
    struct fleet f_ennemy[NB_ARMIES];
    struct indice indice;
    int id_planet = 0;
    int id_fleet = 0;
    init_indice(&indice);
    while (!feof(stdin)){
        listen(buffer);
        if (buffer[0]=='g' && buffer[1]=='o'){
            serge(p_allied, p_ennemy, p_neutral, &indice);
            init_indice(&indice);
            id_planet = 0;
            id_fleet = 0;
            go();           
        }
        else{
            game_stat(buffer, p_allied, p_ennemy, p_neutral, f_allied, f_ennemy, &id_planet, &id_fleet, &indice);
            printf("id : %d %d %d \n", indice.indp_ally, indice.indp_ennemy, indice.indp_neutral);
        }
    }
    return 0;
}















/*
main
    gets(buffer, MAX_CARAC, stdin);
    sauvegarder les donnee
    if (buffer[0] == 'g' && buffer[1] == 'o'){
        traitement des donnees
        ordres
        printf("go\n");
}
*/




/************fin******************/
