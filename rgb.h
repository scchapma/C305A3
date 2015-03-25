#ifndef RGB_H
#define RGB_H

#include <iostream>
#include <QWidget>

class rgb
{
public:
    rgb(){ color = (0, 0, 0);}
    rgb(int red, int green, int blue);
    rgb(const rgb & original) { *this = original;}
    ~rgb();

    void setRed(int red) { _r = red;}
    void setGreen(int green){ _g = green;}
    void setBlue(int blue){ _b = blue;}

    int _r;
    int _g;
    int _b;
    QRgb color = (_r, _g, _b);
};

#endif // RGB_H
