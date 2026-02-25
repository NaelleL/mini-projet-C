#include "mini_projet_4.h"

int main() {
    /*
    // 1ère image de 500x500 partie 1
    //Picture image = new_pic(500, 500);
    //draw_from_file(image, "cat.txt");
    //save_pic(image);

    //1ère image de 500x500 partie 2
    Picture image = new_pic(500, 500);

    //On lit le fichier cat.txt et on crée la liste chaînée de segments
    Vector* liste = read_vector_file("cat.txt");


    //On définit la couleur noire pour tracer les segments
    Color noir;
    noir.r = 0;
    noir.g = 0;
    noir.b = 0;


    //partie 3.2 On crée une copie de la liste pour le chat miroir
    Vector* miroir = NULL;
    Vector* courant = liste;

    //Copie des segments de liste vers miroir
    while(courant != NULL){
        Vector* nouveau = (Vector*)malloc(sizeof(Vector));
        nouveau->x1 = courant->x1;
        nouveau->y1 = courant->y1;
        nouveau->x2 = courant->x2;
        nouveau->y2 = courant->y2;
        nouveau->next = miroir;
        miroir = nouveau;
        courant = courant->next;
    }

    //On réduit les deux figures à 50% de leur taille
    scale_vector(liste, 0.5);
    scale_vector(miroir, 0.5);

    flip_vector(miroir);

    // On déplace le chat original (regard à droite) vers la gauche
    shift_vector(liste, 20, 150);


    // On déplace le chat miroir (regard à gauche) vers la droite
    shift_vector(miroir, 450, 150);

    //On dessine les deux chats sur l'image
    draw_vector(liste, image, noir);
    draw_vector(miroir, image, noir);

    //On sauvegarde l'image finale
    save_pic(image);

    //Libération mémoire pour les deux listes
    courant = liste;
    Vector* suivant = NULL;
    while(courant != NULL){
        suivant = courant->next;
        free(courant);
        courant = suivant;
    }

    courant = miroir;
    while(courant != NULL){
        suivant = courant->next;
        free(courant);
        courant = suivant;
    }

    */

    //On lit le fichier kang.txt et on crée la liste chaînée de segments
    Vector* base = read_vector_file("kang.txt");

    //Couleur noire
    Color noir;
    noir.r = 0;
    noir.g = 0;
    noir.b = 0;

    // Image 500x500
    Picture image = new_pic(500, 500);

    //On parcourt les lignes
    for(int ligne = 0; ligne < 5; ligne++){
        for(int col = 0; col < 5; col++){          //les colonnes

            Vector* copie = NULL;
            Vector* courant = base;

            //On copie la figure de base
            while(courant != NULL){
                Vector* nouveau = (Vector*)malloc(sizeof(Vector));
                nouveau->x1 = courant->x1;
                nouveau->y1 = courant->y1;
                nouveau->x2 = courant->x2;
                nouveau->y2 = courant->y2;
                nouveau->next = copie;
                copie = nouveau;
                courant = courant->next;
            }

            //Si la ligne est impaire alors on applique un miroir
            if(ligne % 2 == 1){
                flip_vector(copie);
                shift_vector(copie, 50 + 100*col, 100*ligne);
            }
            else{
                shift_vector(copie, 100*col, 100*ligne);
            }
            draw_vector(copie, image, noir);

            //On libère la mémoire de la copie
            courant = copie;
            while(courant != NULL){
                Vector* suivant = courant->next;
                free(courant);
                courant = suivant;
            }
        }
    }
    save_pic(image);
    return 0;
    
}
