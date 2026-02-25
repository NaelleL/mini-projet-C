#include "mini_projet_2.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    int width = 300;
    int height = 200;

    double Xmin = -0.743643887037151;
    double Ymin = 0.13182590420533;
    double scale = 0.01;

    char filename[50];

    for(int i = 0; i <= 10; i++) {

        //Création de l'image
        mandel_pic m = new_mandel(width, height, Xmin, Ymin, scale);
        //Calcul des valeurs de convergence
        compute_mandel(&m, NULL);
        //Nom du fichier
        sprintf(filename, "zoom_%02d.ppm", i);
        //Sauvegarde
        save_mandel(m, filename);
        free(m.convrg);
        //Réduction de l'échelle pour zoomer
        scale = scale * 0.5;
    }

    return 0;
}
