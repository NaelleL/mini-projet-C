#include "mini_projet.h"


#include <complex.h>
#include <math.h>


// fonction pour remplir des données que j'ai fais en supplement 
void remplir_donnees(Pixmap donnees_image[], int *n) {
    int nb;
    printf("Remplir (bah pour l'instant on veux que 1) ");
    scanf("%d", &nb);

    for (int i = 0; i < nb; i++) {

        printf("signature : ");

        scanf("%s", donnees_image[*n].signature);

        printf("largeur : ");
        scanf("%d", &donnees_image[*n].largeur);

        printf("hauteur : ");
        scanf("%d", &donnees_image[*n].hauteur);

        printf("intensite : ");
        scanf("%d", &donnees_image[*n].intensite);

        (*n)++;
    }
}
// fonction pour afficher des données précedement rempli que j'ai fais en supplement 
void afficher_donnees(Pixmap donnees_image[], int n){
    if (n==0){
        printf("Oups pas d'image pour l'instant");
    }
    else{
        for (int i =0; i<n; i++){
            printf ("signature: %s, largeur: %d, hauteur: %d, intensite: %d", donnees_image[i].signature, donnees_image[i].largeur, donnees_image[i].hauteur, donnees_image[i].intensite);
        }

    }
}

void dessiner_cercle(Pixmap image1){
    int cercle_x = image1.largeur / 2;
    int cercle_y = image1.hauteur / 2;
    int rayon = 100; // car le diamètre est 200

    for (int y = 0; y < image1.hauteur; y++) {  // je regarde chaque pixel un par un 
        for (int x = 0; x < image1.largeur; x++) {
            if (((x - cercle_x)*(x - cercle_x) + (y - cercle_y)*(y - cercle_y)) <= rayon*rayon) { // formule equation du cercle
                // cercle de couleur rouge 
                image1.image[y*image1.largeur + x].r = 255;
                image1.image[y*image1.largeur + x].g = 0;
                image1.image[y*image1.largeur + x].b = 0;
            } else {
                // fond de couleur blanc pour faire le drapeau de mon pays préféré :)
                image1.image[y*image1.largeur + x].r = 255;
                image1.image[y*image1.largeur + x].g = 255;
                image1.image[y*image1.largeur + x].b = 255;
            }
        }
    }

}

void pixel_carre(Pixmap image1){
    for (int i=0; i<image1.hauteur*image1.largeur; ++i){  //Question 1
        image1.image[i].r=122;
        image1.image[i].g=56;
        image1.image[i].b=200;
    }

}

int convergence(float x, float y) {
    float complex z = x + y * I; //complex qui sert à representer des nombres complexes, I c'est la racine carré de -1 
    float complex u = z;
    int iterations_maximum = 85;
    
    for (int i = 0; i < iterations_maximum; i++) {
        if (cabs(u) >= 2.0) return i + 1; // cabs(u) c'est le module de u
        u = u * u + z;
    }
    return 0;
}

void createMandelbrot(Pixmap pixmap, float x1, float y1, float x2, float y2) {
    for (int j = 0; j < pixmap.hauteur; j++) {
        for (int i = 0; i < pixmap.largeur; i++) {
            float x = x1 + (x2 - x1) * i / (pixmap.largeur - 1); // coordone x qui est le pixel i
            float y = y1 + (y2 - y1) * j / (pixmap.hauteur - 1); // coordone y qui est le pixel j

            int c = convergence(x, y);
            int g = 3 * c;    
            if (g > 255) {          
                g = 255;           
            }
            pixmap.image[j * pixmap.largeur + i].r = 54;
            pixmap.image[j * pixmap.largeur + i].g = g; //met la valeur qu'on viens de calculer dans le pixel vert
            pixmap.image[j * pixmap.largeur + i].b = 73;
        }
    }
}



int main() {
    int n =0;
    //Pixmap image1 = {"P6", 10, 10, 255, (Pixels*)malloc(image1.hauteur*image1.largeur*sizeof(Pixels))}; //Question 1
    //Pixmap image1 = {"P6", 600, 400, 255, (Pixels*)malloc(image1.hauteur*image1.largeur*sizeof(Pixels))}; //Question 2
    Pixmap image1 = {"P6", 900, 600, 255, (Pixels*)malloc(image1.hauteur*image1.largeur*sizeof(Pixels))}; //Question 3
    
    double x = 0.3;
    double y = 0.5;

    //pixel_carre(image1); //Question 1
    //dessiner_cercle(image1); //Question 2
    createMandelbrot(image1, -2.0, -1.0, 1.0, 1.0); //Question 3

    FILE* fichier= NULL;
    fichier=fopen("mon_image1.ppm", "w");
    char espace[2]="\n";

    fprintf(fichier, "%s", image1.signature);
    fprintf(fichier, "\n");
    fprintf(fichier, "%d", image1.largeur);
    fprintf(fichier, "\n");
    fprintf(fichier, "%d", image1.hauteur);
    fprintf(fichier, " ");
    fprintf(fichier, "%d", image1.intensite);
    fprintf(fichier, "\n");

    for(int i = 0; i<image1.hauteur * image1.largeur; i++){
        fwrite(&image1.image[i].r, 1, 1, fichier);
        fwrite(&image1.image[i].g, 1, 1, fichier);
        fwrite(&image1.image[i].b, 1, 1, fichier);
    }

    free(image1.image);

    fclose(fichier);


    return 0;
}
