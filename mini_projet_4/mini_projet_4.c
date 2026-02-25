#include "mini_projet_4.h"

//On crée une nouvelle image blanche de taille width x height
Picture new_pic(int width, int height) {
    Picture image1;
    image1.signature[0] = 'P';
    image1.signature[1] = '6';
    image1.signature[2] = '\0';
    image1.width = width;
    image1.height = height;
    image1.intensite = 255; 

    //On alloue dynamiquement de la place en mémoire pour les pixels
    image1.pixels = (Color *)malloc(image1.height * image1.width * sizeof(Color));

    //On initialise tous les pixels à blanc
    for( int i = 0; i < image1.height; i++){
        for(int j = 0; j < image1.width; j++){
            image1.pixels[i*width +j].r = 255;
            image1.pixels[i*width +j].g = 255;
            image1.pixels[i*width +j].b = 255;
        }
    }

    return image1;
}

int save_pic(Picture image1) {
    FILE* fichier= NULL;
    fichier=fopen("mon_image_6.ppm", "wb");

    fprintf(fichier, "%s", image1.signature);
    fprintf(fichier, "\n");
    fprintf(fichier, "%d", image1.width);
    fprintf(fichier, "\n");
    fprintf(fichier, "%d", image1.height);
    fprintf(fichier, " ");
    fprintf(fichier, "%d", image1.intensite);
    fprintf(fichier, "\n");

    //On écrit chaque pixel dans le fichier
    for(int i = 0; i<image1.height * image1.width; i++){
        fwrite(&image1.pixels[i].r, 1, 1, fichier);
        fwrite(&image1.pixels[i].g, 1, 1, fichier);
        fwrite(&image1.pixels[i].b, 1, 1, fichier);
    }
    free(image1.pixels);
    fclose(fichier);
    return 0;
}

//On modifie la couleur d'un pixel aux coordonnées x y
int set_pixel(Picture image , int x, int y, Color c){
    image.pixels[y* image.width + x].r = c.r;
    image.pixels[y* image.width + x].g = c.g;
    image.pixels[y* image.width + x].b = c.b;
    return 0;
}

//On dessine une ligne entre x1 y1 et x2 y2 avec couleur c
int draw_line(Picture image, int x1, int y1, int x2, int y2, Color c) {
    int n = nbr_pixel(x1, y1, x2, y2);
    if (n <= 1) {
        set_pixel(image, x1, y1, c);
        return 0;
    }
    //Pour chaque point entre x1 y1 et x2 y2 on calcule les coordonnées et on dessine le pixel
    for(int i = 0; i < n; i++) {
        float x = ((double)(x2 - x1)/(n-1)) *i + x1;
        float y = ((double)(y2 - y1)/(n-1)) *i + y1;
        set_pixel(image, (int)x, (int)y, c);
    }
    return 0;
}


//On calcule le nombre de pixels nécessaires pour dessiner une ligne entre deux points
int nbr_pixel(int x1, int y1, int x2, int y2){
    int x = abs(x1-x2); //On prend la valeur absolu
    int y = abs(y1-y2);
    int n = fmax(x, y) +1 ;//On prend le max entre x et y
    return n;
}

//On lit un fichier contenant des segments et on les dessine sur l'image
int draw_from_file(Picture image , char* filename){
    FILE* fichier= NULL;
    fichier = fopen(filename, "r");
    //On vérifie que le fichier s'est bien ouvert
    if(fichier == NULL){
        printf("Erreur ouverture fichier\n");
        return 1;
    }

    float x1, y1, x2, y2; //On déclare les variables pour stocker les coordonnées
    //On définit la couleur noire pour tracer les segments
    Color noir;
    noir.r = 0;
    noir.g = 0;
    noir.b = 0;

    //Tant qu'on peut lire 4 flottants dans le fichier
    while(fscanf(fichier, "%f %f %f %f", &x1, &y1, &x2, &y2) == 4){

        //On dessine la ligne correspondant aux coordonnées lues
        draw_line(image,
                  (int)x1, (int)y1,
                  (int)x2, (int)y2,
                  noir);
    }
    fclose(fichier);
    return 0;
}

//On lit un fichier et on crée une liste chaînée de segments
Vector* read_vector_file(char* filename){

    FILE* fichier = NULL;
    fichier = fopen(filename, "r");
    //On vérifie l'ouverture du fichier
    if(fichier == NULL){
        printf("Erreur ouverture fichier\n");
        return NULL;
    }

    Vector* premier = NULL; //Premier élément de la liste
    Vector* nouveau = NULL; //Pour chaque nouvel élément
    double x1, y1, x2, y2; //Coordonnées d'un segment

    //Lecture des segments tant qu'il y en a
    while(fscanf(fichier, "%lf %lf %lf %lf", &x1, &y1, &x2, &y2) == 4){

        //Création d'un nouveau segment
        nouveau = (Vector*)malloc(sizeof(Vector));
        //On remplit les coordonnées
        nouveau->x1 = x1;
        nouveau->y1 = y1;
        nouveau->x2 = x2;
        nouveau->y2 = y2;
        //On insère le segment en tête de liste
        nouveau->next = premier;
        premier = nouveau;
    }

    //On ferme le fichier
    fclose(fichier);

    return premier;
}

//On dessine tous les segments d'une liste chaînée sur une image
int draw_vector(Vector* liste, Picture image, Color c){
    Vector* courant = liste; //On commence par le premier élément

    //Tant qu'on n'a pas atteint la fin de la liste
    while(courant != NULL){
        //On dessine la ligne correspondant au segment courant
        draw_line(image,
                  (int)courant->x1, (int)courant->y1,
                  (int)courant->x2, (int)courant->y2,
                  c);
        //On passe au segment suivant
        courant = courant->next;
    }

    return 0;
}

//On met à l'échelle tous les segments d'une liste chaînée
void scale_vector(Vector* liste, double scale){
    Vector* courant = liste; //On commence par le premier segment

    //Tant qu'on n'a pas atteint la fin de la liste
    while(courant != NULL){
        //On multiplie chaque coordonnée par le facteur scale
        courant->x1 *= scale;
        courant->y1 *= scale;
        courant->x2 *= scale;
        courant->y2 *= scale;
        //On passe au segment suivant
        courant = courant->next;
    }
}

//On déplace tous les segments d'une liste chaînée selon le vecteur (dx, dy)
void shift_vector(Vector* liste, double dx, double dy){
    Vector* courant = liste; //On commence par le premier segment
    //Tant qu'on n'a pas atteint la fin de la liste
    while(courant != NULL){
        //On ajoute dx et dy à chaque coordonnée
        courant->x1 += dx;
        courant->y1 += dy;
        courant->x2 += dx;
        courant->y2 += dy;
        //On passe au segment suivant
        courant = courant->next;
    }
}

//On applique un effet miroir horizontal à tous les segments d'une liste chaînée
void flip_vector(Vector* liste){
    Vector* courant = liste; //On commence par le premier segment
    //Tant qu'on n'a pas atteint la fin de la liste
    while(courant != NULL){
        //On inverse le signe des coordonnées x
        courant->x1 = -courant->x1;
        courant->x2 = -courant->x2;
        //On passe au segment suivant
        courant = courant->next;
    }
}