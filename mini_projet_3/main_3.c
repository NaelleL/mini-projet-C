#include "mini_projet_3.h"

int main() {

    // Creer une image de 10x10 exo 1 et 2
    //Picture image1 = new_pic(10, 10);
    Picture image1 = new_pic(400, 350);
    Color rouge = {255, 0, 0};
    Color bleu = {0, 0, 255};
    Color vert = {0, 255, 0};
    Color magenta = {255, 0, 255};
    Color cyan = {0, 255, 255};

/* //Exo 1
    set_pixel(image1, 0, 0, vert); // en haut à gauche
    set_pixel(image1, 9, 0, vert); // en haut à droite
    set_pixel(image1, 0, 9, vert); // bas gauche 
    set_pixel(image1, 9, 9, vert); // bas droite
*/
/* //Exo 2
    draw_line(image1, 2, 2, 7, 7, rouge);   
    draw_line(image1, 2, 7, 7, 2, bleu);   
    draw_line(image1, 1, 2, 1, 7, vert);   
    draw_line(image1, 8, 2, 8, 7, vert);   
    draw_line(image1, 2, 1, 7, 1, magenta); 
    draw_line(image1, 2, 8, 7, 8, magenta);
*/
    //sierpinski(image1, 0, 349, 400, magenta);
    //sierpinski_div(image1, 0, 349, 400, magenta);
    sierpinski(image1, 0, 349, 400, magenta);

    save_pic(image1);
    return 0;
}