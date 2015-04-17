#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#include "clHeaders.h"
#include <string>
#include <fstream>
#include <sstream>

class RGBImage
{
public:
    /**
     * @brief RGBImage
     * Load an image from file, and create it.
     * @param fileName
     */
    RGBImage(const std::string fileName);

    /**
     * @brief RGBImage
     * Create an image with specific dimensions.
     * @param width
     * @param height
     * @param name
     */
    RGBImage(const uint32_t width,
             const uint32_t height,
             const std::string name);

    ~RGBImage();

    /**
     * @brief getWidth
     * @return
     */
    uint32_t getWidth(void) const;

    /**
     * @brief getHeight
     * @return
     */
    uint32_t getHeight(void) const;

    /**
     * @brief getColorDepth
     * @return
     */
    uint32_t getColorDepth(void) const;

    /**
     * @brief getNumberOfPixels
     * @return
     */
    uint32_t getNumberOfPixels(void) const;

    /**
     * @brief getName
     * @return
     */
    std::string getName(void) const;

    /**
     * @brief getPixels
     * @return
     */
    char* getPixels(void) const;

private:

    /** @brief Image width in pixels */
    uint32_t _width;

    /** @brief Image height in pixels */
    uint32_t _height;

    /** @brief Color depth (number of bits per pixel) */
    uint32_t _colorDepth;

    /** @brief Number of pixels in the image */
    uint32_t _numPixels;

    /** @brief Image name */
    std::string _name;

    /** @brief Image data */
    char* _pixels;

private:

    /**
     * @brief _allocateImage
     */
    void _allocateImage(void);

    /**
     * @brief _loadImage
     * @param fileName
     */
    void _loadImage(const std::string fileName);
};

#endif // RGBIMAGE_H
