/**
 * Le but de cet exercice est de prÃƒÆ’Ã‚Â©parer le TP buzzer (IF112).
 *
 * Les macros (justes) seront recopiÃƒÆ’Ã‚Â©s dans bit.h, et les fonctions seront
 * recopiÃƒÆ’Ã‚Â©s dans bit.c
 *
 * NOTE:
 *  - Pour dÃƒÆ’Ã‚Â©finir une macro dÃƒÆ’Ã‚Â©commentez-la, puis ajoutez votre code.
 *  - Les deux premiÃƒÆ’Ã‚Â¨res macros sont faites pour vous ÃƒÆ’Ã‚Â  titre d'exemples, par
 *    consÃƒÆ’Ã‚Â©quents, ne les changez pas.
 *
 *  - Un peu d'information sur les macros :
 *    http://www.labri.fr/perso/fmoranda/slides/cours-c.html#/26/0
 */

#include <stdio.h>
//#include <stdlib.h>


/**
 * Retourne le nombre de bits necessaire pour representer __x
 */
#define SIZE_IN_BITS(__x) (sizeof(__x) * 8)

/**
 * Retourne le bits de poit le plus faible actif dans __x (fsb)
 * NOTE:
 *  - Comme il s'agit d'une macro, son argument peut ÃƒÆ’Ã‚Âªtre ÃƒÆ’Ã‚Â©valuÃƒÆ’Ã‚Â© deux fois.
 *  - L'idÃƒÆ’Ã‚Â©e deriÃƒÆ’Ã‚Â¨re cette formule est qu'entre un nombre et son complÃƒÆ’Ã‚Â©ment
 *    ÃƒÆ’Ã‚Â  deux il n'y ÃƒÆ’Ã‚Â  qu'un seul bit ÃƒÆ’Ã‚Â  1 en commum, il s'agit du bit de
 *    poids le plus faible
 */
#define FSB(__x) ((__x) & -(__x))

/**
 * Retourne un nombre ou seul le __b-iÃƒÆ’Ã‚Â¨me est activÃƒÆ’Ã‚Â©
 *
 * Remarque: Le nombre doit ÃƒÆ’Ã‚Âªtre un `unsigned long long` !
 */
 #define BIT_SET(__b) (1ull <<__b)

/**
 * Active, inverse ou dÃƒÆ’Ã‚Â©sactive le `__b`-iÃƒÆ’Ã‚Â¨me bit de `__v`
 */
 #define BS_SET(__v, __b) ( __v | (1ull << __b) )
 #define BS_FLIP(__v, __b) (__v ^ (1ull << __b) )
 #define BS_UNSET(__v, __b) ( __v &(~(1ull << __b)) )

/**
 * DÃƒÆ’Ã‚Â©sactive le bit de poids le plus faible actif de `__v`
 */
 #define BS_UNSET_FSB(__v) ( __v ^( ((__v) & -(__v)) ) )

/**
 * Retourne le nombre de bits ÃƒÆ’Ã‚Â  1 dans un unsigned long long `n`
 *
 * RÃƒÆ’Ã‚Â©fÃƒÆ’Ã‚Â©rez-vous ÃƒÆ’Ã‚Â  l'exercice bit_count pour des idÃƒÆ’Ã‚Â©es d'algorithmes
 */
int bit_count(unsigned long long b){
    int c = 0 ;
    while (b > 0){
        b = BS_UNSET_FSB(b);
        c++ ;
    }
    return c ;
}

/**
 * Retourne l'indice du bit de poids le plus faible actif (fsb). Les indices
 * commencent ÃƒÆ’Ã‚Â  1. Cette fonction retourne zÃƒÆ’Ã‚Â©ro si aucun bit n'est activÃƒÆ’Ã‚Â©
 * c'est ÃƒÆ’Ã‚Â  dire ssi i == 0
 *
 * Cette fonction existe sous le nom `ffs` (ffsll).
 */
int fsb_pos(unsigned long long i){
    unsigned long long n = SIZE_IN_BITS(i);
    unsigned long long a = FSB(i);
    unsigned long long c =0 ;
        if (i == 0ull) {
              return 0 ;
        }
        else {
            while (c<n){
                if ((1ull << c) == a){
                     return c + 1ull ;
                }
                c = c + 1ull ;
                
            }
        }return 0;
}

/**
 * Affiche les `bits` bits de poids faible de l'entier `x` suivi d'un saut de
 * ligne ('\n').
 *
 * NOTE: Pour les gens qui veulent :
 *  - Si `bits` est nÃƒÆ’Ã‚Â©gatif seul les bits significatifs (< `bits`) seront
 *    affichÃƒÆ’Ã‚Â©s. Si le nombre `x` est zero alors il est tout de mÃƒÆ’Ã‚Âªme affichÃƒÆ’Ã‚Â©.
 */
void print_bits(unsigned long long x, int bits){
    int c = 1 ;
    int tab[bits+1] ;
    int i ;
    int n = SIZE_IN_BITS(x) ;  
    
    if (bits > n){
        bits = n ;
    }
    
    else if (bits == 0){
        printf("\n");
    }     
    else if ( x == 0ull){
        printf("0\n");
    }
    else if ( x == 1ull){
        printf("1\n");
    }
    
    else{
         
    if (bits < 0){
        bits = n + bits ;
    } 
    for (i=0 ; i< (bits) ; i++){
        tab[i] = 0 ;
    }
    
   
  
        while (c <= bits){
            if (fsb_pos(x) == c){
                tab[bits-c] = 1 ;
                x = BS_UNSET_FSB(x);
                c++;
            }
            else{
                c++;
            }         
        }
        for(i=0 ; i < bits ; i++){
        printf("%d",tab[i] );
        }
        printf("\n");
    }
}    


 /*   char tab[] = "";
    int i;
    int j;
    
    for (i=0;i<bits;i++){
            tab[i] = 0;
    }
    while (x>0ull){
        tab[bits-fsb_pos(x)] ='1';
       x =  BS_UNSET_FSB(x);
    }
    for(j=0;j<bits;j++){
        printf("%c\n", tab[j]);
        j++;
    }
}*/



/**
 * Convertit `size` octets du tableau `data`, ÃƒÆ’Ã‚Â  partir de `offset`, en leur
 * reprÃƒÆ’Ã‚Â©sentation native. Les valeurs de data sont stockÃƒÆ’Ã‚Â©s en little endian.
 *
 * Exemple: ...|0xEF|0xBE|0xAD|0xDE|...  ==> 0xDEADBEEF
 */
unsigned long long extract_littleendian2n(int size, const unsigned char *data, int offset);

/******************************************************************************
 * Ne pas toucher ÃƒÆ’Ã‚Â  ces fonctions, elles sont lÃƒÆ’Ã‚Â  pour tester vos macros
 *****************************************************************************/
#ifdef BIT_SET
unsigned long long bit_set(int b)
{
    return BIT_SET(b);
}
#endif
#ifdef BS_SET
unsigned long long bs_set(unsigned long long v, int b)
{
    return BS_SET(v, b);
}
#endif
#ifdef BS_FLIP
unsigned long long bs_flip(unsigned long long v, int b)
{
    return BS_FLIP(v, b);
}
#endif
#ifdef BS_UNSET
unsigned long long bs_unset(unsigned long long v, int b)
{
    return BS_UNSET(v, b);
}
#endif
#ifdef BS_UNSET_FSB
unsigned long long bs_unset_fsb(unsigned long long v)
{
    return BS_UNSET_FSB(v);
}
#endif
