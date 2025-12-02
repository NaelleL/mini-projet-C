#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct{
        unsigned char r;
        unsigned char g;
        unsigned char b;
}Pixels;

typedef struct{
    char signature[4];
    int largeur;
    int hauteur;
    int intensite;
    Pixels* image;
}Pixmap;

int convergence(float x, float y);

