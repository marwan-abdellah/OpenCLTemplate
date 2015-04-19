#ifndef IMAGE_H
#define IMAGE_H

#include "clHeaders.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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
    Image(const int width, const int height,
          const int colorDepth, const int components,
          const std::string name);

    ~Image();

    /**
     * @brief getWidth
     * @return
     */
    int getWidth(void) const;

    /**
     * @brief getHeight
     * @return
     */
    int getHeight(void) const;

    /**
     * @brief getColorDepth
     * @return
     */
    int getColorDepth(void) const;

    /**
     * @brief getNumberOfColorComponents
     * @return
     */
    int getNumberOfColorComponents(void) const;

    /**
     * @brief getNumberOfPixels
     * @return
     */
    int getNumberOfPixels(void) const;

    /**
     * @brief getName
     * @return
     */
    std::string getName(void) const;

    /**
     * @brief getPixels
     * @return
     */
    std::vector<char>* getPixels(void);

    /**
     * @brief getDataSizeInBytes
     * @return
     */
    int getDataSizeInBytes(void) const;

    /**
     * @brief savePPMImage
     * @param path
     */
    void savePPMImage(std::string path);

    /**
     * @brief getPixelArraySize
     * @return
     */
    int getPixelArraySize(void) const;

private:

    /** @brief Image width in pixels */
    int _width;

    /** @brief Image height in pixels */
    int _height;

    /** @brief Color depth (number of bits per pixel) */
    int _colorDepth;

    /** @brief Number of color components per pixel */
    int _numComponents;

    /** @brief Number of pixels in the image */
    int _numPixels;

    /** @brief Image name */
    std::string _name;

    /** @brief Image data */
    std::vector<char> _pixels;

    /** @brief The size of the image data */
    int _dataSize;

    /** @brief The size of array that contains all the pixel info. */
    int _pixelArraySize;

private:

    /**
     * @brief _loadPPMImage
     * @param fileName
     */
    void _loadPPMImage(const std::string fileName);

    /**
     * @brief _printImageDetails
     */
    void _printImageDetails(void);
};

#endif // IMAGE_H
