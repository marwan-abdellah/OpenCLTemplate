#ifndef IMAGEUTILITIES_H
#define IMAGEUTILITIES_H

#include "Image.h"

class ImageUtilities
{
public:
    /**
     * @brief convertRGBtoRGBA
     * Converts an RGB image to an RGBA one.
     * @param input The RGB image
     * @return The RGBA image
     */
    static Image* convertRGBtoRGBA(Image *input);

    /**
     * @brief convertRGBAtoRGB
     * Converts an RGBA image into an RGB one.
     * @param input The RGBA image
     * @return The RGB image
     */
    static Image* convertRGBAtoRGB( Image* input);
};

#endif // IMAGEUTILITIES_H
