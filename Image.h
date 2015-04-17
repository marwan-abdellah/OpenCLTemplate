#ifndef IMAGE_H
#define IMAGE_H

#include "clHeaders.h"
#include <string>
#include <fstream>
#include <sstream>

class Image
{
public:
    /**
     * @brief Image
     * Load an image from file, and create it.
     * @param fileName
     */
    Image(const std::string fileName);

    /**
     * @brief Image
     * @param width
     * @param height
     * @param colorDepth
     * @param components
     * @param name
     */
    Image(const uint32_t width, const uint32_t height,
          const uint32_t colorDepth, const uint32_t components,
          const std::string name);

    ~Image();

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
     * @brief getNumberOfColorComponents
     * @return
     */
    uint32_t getNumberOfColorComponents(void) const;

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

    /**
     * @brief getDataSizeInBytes
     * @return
     */
    uint32_t getDataSizeInBytes(void) const;

private:

    /** @brief Image width in pixels */
    uint32_t _width;

    /** @brief Image height in pixels */
    uint32_t _height;

    /** @brief Color depth (number of bits per pixel) */
    uint32_t _colorDepth;

    /** @brief Number of color components per pixel */
    uint32_t _numComponents;

    /** @brief Number of pixels in the image */
    uint32_t _numPixels;

    /** @brief Image name */
    std::string _name;

    /** @brief Image data */
    char* _pixels;

    /** @brief The size of the image data */
    uint32_t _dataSize;

private:

    /**
     * @brief _loadPPMImage
     * @param fileName
     */
    void _loadPPMImage(const std::string fileName);
};

#endif // IMAGE_H
