#include "headers/couleurs.h"

ColorRGB createColor(float r, float g, float b){

    ColorRGB color;

    color.r = r;
    color.g = g;
    color.b = b;

    return color;

};

ColorRGB addColors(ColorRGB c1, ColorRGB c2){

    ColorRGB color;

    color.r = c1.r + c2.r;
    color.g = c1.g + c2.g;
    color.b = c1.b + c2.b;

    return color;
};

ColorRGB subColors(ColorRGB c1, ColorRGB c2){

    ColorRGB color;

    color.r = c1.r - c2.r;
    color.g = c1.g - c2.g;
    color.b = c1.b - c2.b;

    return color;

};

ColorRGB multColors(ColorRGB c1, ColorRGB c2){

    ColorRGB color;

    color.r = c1.r * c2.r;
    color.g = c1.g * c2.g;
    color.b = c1.b * c2.b;

    return color;

};

ColorRGB multColor(ColorRGB c, float a){

    ColorRGB color;

    color.r = c.r * a;
    color.g = c.g * a;
    color.b = c.b * a;

    return color;

};

ColorRGB divColor(ColorRGB c, float a){

    ColorRGB color;

    color.r = c.r / a;
    color.g = c.g / a;
    color.b = c.b / a;

    return color;

};