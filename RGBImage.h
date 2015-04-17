#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#include "clHeaders.h"
#include <string>

class RGBImage
{
public:
    RGBImage(const uint32_t width,
             const uint32_t height,
             const std::string name);

    ~RGBImage();

    /**
     * @brief getWidth
     * @return
     */
    uint32_t getWidth( void ) const;

    /**
     * @brief getHeight
     * @return
     */
    uint32_t getHeight( void ) const;

    /**
     * @brief getNumberOfPixels
     * @return
     */
    uint32_t getNumberOfPixels( void ) const;

    /**
     * @brief getName
     * @return
     */
    std::string getName( void ) const;

    /**
     * @brief getPixels
     * @return
     */
    char* getPixels( void ) const;

private:
    /** @brief */
    const uint32_t _width;

    /** @brief */
    const uint32_t _height;

    /** @brief */
    uint32_t _numPixels;

    /** @brief */
    const std::string _name;

    /** @brief */
    char* _pixels;

private:
    void _allocateImage();


};

#endif // RGBIMAGE_H
