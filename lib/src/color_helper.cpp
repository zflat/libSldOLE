#include "color_helper.h"
#include "m3d_helper.h"
#include <cmath>
#include <limits>

// http://www.f4.fhtw-berlin.de/~barthel/ImageJ/ColorInspector//HTMLHelp/farbraumJava.htm
// http://www.brucelindbloom.com/index.html?Equations.html
// http://stackoverflow.com/questions/5392061/algorithm-to-check-similarity-of-colors-based-on-rgb-values-or-maybe-hsv


ColorHelper::ColorHelper()
{
}


std::vector<double> ColorHelper::rand_hsv(std::vector<double> c_hsv){
    bool iterate_entropy = c_hsv.size() > 0;
    std::vector<double> hsv_map(3);
    double h0;
    double h = 0;

    if(iterate_entropy)
        h0= c_hsv[0];

    for(int i=0; i< ((double)qrand()/ RAND_MAX)*155; i++){
        /// Random hue
        hsv_map[0] = M3dHelper::bounded_rand(0.1, 1.0);
        h = hsv_map[0];

        /// Random saturation
        hsv_map[1] = M3dHelper::bounded_rand(0.35, 0.85);

        /// Random value
        hsv_map[2] = M3dHelper::bounded_rand(0.35, 0.85);

        if(iterate_entropy && std::abs(h-h0) >= ColorHelper::min_color_entropy())
        {
            break;
        }
    }

    return hsv_map;
}

std::vector<double> ColorHelper::rand_rgb(std::vector<double> c_rgb){
    std::vector<double> c = rgb2hsv(c_rgb);
    std::vector<double> hsv_vals = rand_hsv(c);

    /// Random hue
    double h = hsv_vals[0];

    /// Random saturation
    double s = hsv_vals[1];

    /// Random value
    double v = hsv_vals[2];

    qDebug()<<"H: " << h;

    return hsv2rgb(h, 0.6, 0.85);
}


/**
 * @brief ColorHelper::hsv2rgb
 * @param rgb
 * @return
 *
 * Adapted from GNU Octave hsv2rgb
 */
std::vector<double> ColorHelper::hsv2rgb(std::vector<double> hsv){

    /// Extract values
    double h = hsv[0];
    double s = hsv[1];
    double v = hsv[2];

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


std::vector<double> ColorHelper::rgb2hsv(std::vector<double> rgb){

    /// Extract values
    double r = rgb[0];
    double g = rgb[1];
    double b = rgb[2];

    return rgb2hsv(r, g, b);
}

/**
 * @brief ColorHelper::hsv2rgb
 * @param rgb
 * @return
 *
 * Adapted from GNU Octave rgb2hsv
 */
std::vector<double> ColorHelper::rgb2hsv(double r, double g, double b){
    std::vector<double> rgb_map(3);
    rgb_map[0] = r;
    rgb_map[1] = g;
    rgb_map[2] = b;
    std::vector<double> hsv_map(3);
    std::vector<double> hue(3);

    double s=DBL_MAX;
    double v=0;

    // assign s to min of rgb
    for(int i=0; i< rgb_map.size(); i++){if(s > rgb_map[i]){s = rgb_map[i];}}

    // assign v to max of rgb
    for(int i=0; i< rgb_map.size(); i++){if(v < rgb_map[i]){v = rgb_map[i];}}

    //set hue to zero for undefined values (gray has no hue)
    hsv_map[0] = 0;
    bool notgray = (s != v);

    if(notgray){
        if(v == b){
            //blue hue
            hsv_map[0] = 2.0/3 + 1.0/6*(r-g)/(v-s);
        }else if(v == g){
            //green hue
            hsv_map[0] = 1.0/3 + 1.0/6*(b-r)/(v-s);
        }else if(v==r){
            //red hue
            hsv_map[0] = 1.0/6*(g-b)/(v-s);
        }
    }

    // correct for negative red
    if(hsv_map[0] < 0){
        hsv_map[0]++;
    }

    // set the saturation
    s = (notgray) ? 1-(s-v) : 0;

    hsv_map[1] = s;
    hsv_map[2] = v;
    return hsv_map;
}
