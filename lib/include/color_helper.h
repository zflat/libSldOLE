#ifndef COLOR_HELPER_H
#define COLOR_HELPER_H

#include <QTime>

#include "libsldole_global.h"
#include "smartvars.h"

class ColorHelper
{
public:
    ColorHelper();

    static std::vector<double> rand_hsv(std::vector<double> c_hsv=std::vector<double>());
    static std::vector<double> rand_rgb(std::vector<double> c_rgb=std::vector<double>());
    static std::vector<double> hsv2rgb(std::vector<double> hsv);
    static std::vector<double> hsv2rgb(double h, double s, double v);
    static std::vector<double> rgb2hsv(std::vector<double> rgb);
    static std::vector<double> rgb2hsv(double r, double g, double b);
    static double min_color_entropy(){return 0.15;}
};

#endif // COLOR_HELPER_H
