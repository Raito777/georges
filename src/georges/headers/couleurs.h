#ifndef COULEURS_H
#define COULEURS_H

typedef struct ColorRGB {
    float r;
    float g;
    float b;
} ColorRGB;

ColorRGB createColor(float r, float g, float b);

ColorRGB addColors(ColorRGB c1, ColorRGB c2);
ColorRGB subColors(ColorRGB c1, ColorRGB c2);
ColorRGB multColors(ColorRGB c1, ColorRGB c2);

ColorRGB multColor(ColorRGB c, float a);
ColorRGB divColor(ColorRGB c, float a);

#endif