#include "color_helper.h"

// http://www.f4.fhtw-berlin.de/~barthel/ImageJ/ColorInspector//HTMLHelp/farbraumJava.htm
// http://www.brucelindbloom.com/index.html?Equations.html
// http://stackoverflow.com/questions/5392061/algorithm-to-check-similarity-of-colors-based-on-rgb-values-or-maybe-hsv


ColorHelper::ColorHelper()
{
}


std::vector<double> ColorHelper::rand_color(){
    /// Random hue
    double h = bounded_rand(0.0, 1.0);

    /// Random saturation
    double s = bounded_rand(0.35, 0.85);

    /// Random value
    double v = bounded_rand(0.35, 0.85);

    return hsv2rgb(h, 0.6, 0.85);
}

double ColorHelper::bounded_rand(double min, double max){
    return min+((double)qrand()/ RAND_MAX)*(max-min);
}

/**
 * @brief ColorHelper::hsv2rgb
 * @param rgb
 * @return
 *
 * Adapted from GNU Octave hsv2rgb
 */
std::vector<double> ColorHelper::hsv2rgb(std::vector<double> rgb){

    /// Extract values
    double h = rgb[0];
    double s = rgb[1];
    double v = rgb[2];

    return hsv2rgb(h, s, v);
}

std::vector<double> ColorHelper::hsv2rgb(double h, double s, double v){
    std::vector<double> hsv_map(3);
    std::vector<double> hue(3);

    // red = hue-2/3 : green = hue : blue = hue-1/3
    // Apply modulo 1 for red and blue to keep within range [0, 1]
    hue[0]=(h-2.0/3) - std::floor(h-2.0/3);
    hue[1]=h;
    hue[2]=(h-1.0/3) - std::floor(h-1.0/3);

    for(int i=0; i<3; i++){
        // Prefill with v*(1-s)
        hsv_map[i]=v*(1.0-s);

        if(hue[i]< 1/6 ){
            hsv_map[i] += s*v*6*hue[i];
        }else if(hue[i] >= 1.0/6 && hue[i] < 1.0/2){
            hsv_map[i] += s*v;
        }else if(hue[i] >= 1.0/2 && hue[i] < 2.0/3){
            hsv_map[i] += s*v*(4.0-6.0*hue[i]);
        }
    }

    return hsv_map;
}
