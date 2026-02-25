#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
}Picture;

Picture new_pic(int width, int height);
int save_pic(Picture image1);
int set_pixel(Picture image, int x, int y, Color c);
int draw_line(Picture image, int x1, int y1, int x2, int y2, Color c);
int nbr_pixel(int x1, int y1, int x2,  int y2);
int sierpinski(Picture image, double x1, double y1, double taille, Color c);
int sierpinski_div(Picture image, double x1, double y1, double taille, Color c);