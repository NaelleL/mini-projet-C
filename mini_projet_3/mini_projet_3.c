#include "mini_projet_3.h"

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
    fichier=fopen("mon_image_exo_999.ppm", "wb");

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

int sierpinski(Picture image, double x1, double y1, double taille, Color c){
    if (taille < 75){
        double x2 = x1 + taille -1;
        double y2 = y1;
        double x3 = x1 + taille/2;
        double y3 = y1 - taille * sqrt(3)/ 2;
        draw_line(image, (int)x1, (int)y1, (int)x2, (int)y2, c); 
        draw_line(image, (int)x2, (int)y2, (int)x3, (int)y3, c); 
        draw_line(image, (int)x3, (int)y3, (int)x1, (int)y1, c); 
    }
    else {
        // On fait un appelle récursif pour les 3 sous triangles
        sierpinski(image, x1, y1, taille/2, c);
        sierpinski(image, x1 + taille/2, y1, taille/2, c);
        sierpinski(image, x1 + taille/4, y1 - taille*sqrt(3)/4, taille/2, c);
    }

    return 0;
}

