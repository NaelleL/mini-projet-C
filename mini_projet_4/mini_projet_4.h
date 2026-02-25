#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Structure représentant une couleur RGB
typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

typedef struct{
    char signature[4];
    int width;
    int height;
    int intensite;
    Color* pixels;
} Picture;

//Structure représentant un segment avec pointeur vers le suivant
typedef struct vector{
    double x1;
    double y1;
    double x2;
    double y2;
    struct vector* next;
} Vector;


Picture new_pic(int width, int height);
int save_pic(Picture image);
int set_pixel(Picture image, int x, int y, Color c);
int draw_line(Picture image, int x1, int y1, int x2, int y2, Color c);
int nbr_pixel(int x1, int y1, int x2, int y2);
int draw_from_file(Picture image, char* filename);
Vector* read_vector_file(char* filename);
int draw_vector(Vector* liste, Picture image, Color c);
void scale_vector(Vector* liste, double scale);
void shift_vector(Vector* liste, double dx, double dy);
void flip_vector(Vector* liste);