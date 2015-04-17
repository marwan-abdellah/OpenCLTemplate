#include "RGBImage.h"

RGBImage::RGBImage(const uint32_t width,
                   const uint32_t height,
                   const std::string name) :
    _width( width ),
    _height( height ),
    _name( name)
{
    _numPixels = _width * _height;
}


/**
 * @brief RGBImage::getWidth
 * @return
 */
uint32_t RGBImage::getWidth( void ) const { return _width; }


/**
 * @brief RGBImage::getHeight
 * @return
 */
uint32_t RGBImage::getHeight( void ) const { return _height; }


/**
 * @brief RGBImage::getNumberOfPixels
 * @return
 */
uint32_t RGBImage::getNumberOfPixels( void ) const
{
    return _numPixels;
}


/**
 * @brief RGBImage::getName
 * @return
 */
std::string RGBImage::getName( void ) const { return _name; }


/**
 * @brief RGBImage::getPixels
 * @return
 */
char* RGBImage::getPixels( void ) const { return _pixels; }


RGBImage::~RGBImage()
{

}

