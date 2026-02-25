#include "mini_projet_2.h"

//On creer une fonction qui calcule le nombre d’itérations pour un point (x,y)
int convergence(double x, double y) {

    double complex z = x + y * I;
    double complex u = 0; 
    int max = 1000;

    for(int i = 0; i < max; i++) {
        u = u * u + z;
        if(cabs(u) >= 2.0) { //la distance à l'origine du nombre complexe u dans le plan
            return i;
        }
    }

    return 0; 
}

//Palette de couleurs
Color palette(int c) {
    Color col;
    c = c % 1785;

    if(c <= 255) { col.red=c; col.green=0; col.blue=0; }
    else if(c <= 510) { col.red=255; col.green=c-255; col.blue=0; }
    else if(c <= 765) { col.red=765-c; col.green=255; col.blue=0; }
    else if(c <= 1020) { col.red=0; col.green=255; col.blue=c-765; }
    else if(c <= 1275) { col.red=0; col.green=1275-c; col.blue=255; }
    else if(c <= 1530) { col.red=c-1275; col.green=0; col.blue=255; }
    else { col.red=255; col.green=0; col.blue=1785-c; }

    return col;
}

//On creer une nouvelle image Mandelbrot
mandel_pic new_mandel(int width, int height, double Xmin, double Ymin, double scale) {
    mandel_pic m;
    m.width = width;
    m.height = height;
    m.Xmin = Xmin;
    m.Ymin = Ymin;
    m.scale = scale;
    m.Xmax = Xmin + scale * 3.0;
    m.Ymax = Ymin + scale * 3.0 * height / width;
    m.pixwidth = scale * 3.0 / width;
    m.convrg = malloc(width * height * sizeof(int));
    return m;
}

//On fais le calcul des valeurs de convergence
void compute_mandel(mandel_pic* m, mandel_pic* prev) {
    for(int j = 0; j < m->height; j++) {
        for(int i = 0; i < m->width; i++) {
            double x = m->Xmin + i * m->pixwidth;
            double y = m->Ymin + j * m->pixwidth;
            int val = -1;

            //interpolation avec l'image précédente 
            if(prev != NULL && rand() >= RAND_MAX / 100)
                val = interpolate(*prev, x, y);

            if(val == -1)
                val = convergence(x, y);

            m->convrg[j * m->width + i] = val;
        }
    }
}

//Interpolation simple 
int interpolate(mandel_pic m, double x, double y) {
    if(x < m.Xmin || x > m.Xmax || y < m.Ymin || y > m.Ymax)
        return -1;

    int i = (int)((x - m.Xmin) / m.pixwidth);
    int j = (int)((y - m.Ymin) / m.pixwidth);

    if(i < 0 || i >= m.width-1 || j < 0 || j >= m.height-1)
        return -1;

    int c1 = m.convrg[j * m.width + i];
    int c2 = m.convrg[j * m.width + i + 1];
    int c3 = m.convrg[(j + 1) * m.width + i];
    int c4 = m.convrg[(j + 1) * m.width + i + 1];

    if(c1 == c2 && c1 == c3 && c1 == c4)
        return c1;

    return -1;
}

//Sauvegarde au format PPM
void save_mandel(mandel_pic m, const char* filename) {
    FILE* f = fopen(filename, "wb");
    if(!f) return;

    fprintf(f, "P6\n%d %d\n255\n", m.width, m.height);

    for(int i = 0; i < m.width * m.height; i++) {
        Color c = palette(m.convrg[i] * 5); //multiplier pour effet
        fwrite(&c.red, 1, 1, f);
        fwrite(&c.green, 1, 1, f);
        fwrite(&c.blue, 1, 1, f);
    }

    fclose(f);
}
