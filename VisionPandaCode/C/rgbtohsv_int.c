
#include <stdlib.h>
#include <stdio.h>

#include "rgbtohsv_int.h"

#define MIN3(x,y,z)  ((y) <= (z) ? \
                         ((x) <= (y) ? (x) : (y)) \
                     : \
                         ((x) <= (z) ? (x) : (z)))

#define MAX3(x,y,z)  ((y) >= (z) ? \
                         ((x) >= (y) ? (x) : (y)) \
                     : \
                         ((x) >= (z) ? (x) : (z)))

struct rgb_color {
    uint8_T r, g, b;    /* Channel intensities between 0 and 255 */
};

struct hsv_color {
    uint8_T hue;        /* Hue degree between 0 and 255 */
    uint8_T sat;        /* Saturation between 0 (gray) and 255 */
    uint8_T val;        /* Value between 0 (black) and 255 */
};

extern void rgbtohsv_wrapper_int(uint8_T *hsvm, uint8_T *rgbm){  
    int32_T idx;
    int32_T n1 = {480*640};
    int32_T n2 = {n1*2};
    int32_T n3 = {n1+n2};
    struct rgb_color rgb;
    struct hsv_color hsv;
    
    for(idx=0;idx<n1;idx++){
        rgb.r = *rgbm++;
        rgb.g = *(rgbm+n1);
        rgb.b = *(rgbm+n2);
        hsv = rgbtohsv_int(rgb);
        *hsvm++    = hsv.hue;
        *(hsvm+n1) = hsv.sat;
        *(hsvm+n2) = hsv.val;
    }
}   

struct hsv_color rgbtohsv_int(struct rgb_color rgb) {
    struct hsv_color hsv;
    uint8_T rgb_min, rgb_max;

    rgb_min = MIN3(rgb.r, rgb.g, rgb.b);
    rgb_max = MAX3(rgb.r, rgb.g, rgb.b);
    
    if((rgb_max-rgb_min)==0){
        return hsv;
    }else if(rgb_max==0){
        return hsv;
    }
    
    /* Compute hue */
    if (rgb_max == rgb.r) {
        hsv.hue = 0 + 43*(rgb.g - rgb.b)/(rgb_max - rgb_min);
    } else if (rgb_max == rgb.g) {
        hsv.hue = 85 + 43*(rgb.b - rgb.r)/(rgb_max - rgb_min);
    } else /* rgb_max == rgb.b */ {
        hsv.hue = 171 + 43*(rgb.r - rgb.g)/(rgb_max - rgb_min);
    }
    hsv.val = rgb_max;
    hsv.sat = 255*(long)(rgb_max - rgb_min)/rgb_max;
    return hsv;
}
