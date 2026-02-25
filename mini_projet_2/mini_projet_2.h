#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

//Structure représentant une couleur RGB
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Color;

//Structure représentant une image Mandelbrot
typedef struct {
    int width;
    int height;
    double Xmin;
    double Ymin;
    double Xmax;
    double Ymax;
    double scale;
    double pixwidth;
    int* convrg;   //tableau des valeurs de convergence
} mandel_pic;


mandel_pic new_mandel(int width, int height, double Xmin, double Ymin, double scale);
void compute_mandel(mandel_pic* m, mandel_pic* prev);
int interpolate(mandel_pic m, double x, double y);
void save_mandel(mandel_pic m, const char* filename);
int convergence(double x, double y);
Color palette(int c);
