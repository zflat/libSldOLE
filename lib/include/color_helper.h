#ifndef COLOR_HELPER_H
#define COLOR_HELPER_H

#include <QTime>

#include "libsldole_global.h"
#include "smartvars.h"

class ColorHelper
{
public:
    ColorHelper();

    static std::vector<double> rand_color();
    static std::vector<double> hsv2rgb(std::vector<double> rgb);
    static std::vector<double> hsv2rgb(double h, double s, double v);
    static double bounded_rand(double min, double max);
};

#endif // COLOR_HELPER_H
