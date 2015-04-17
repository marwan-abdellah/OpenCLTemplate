#include "RGBImage.h"
#include "Logger.h"

/**
 * @brief RGBImage::RGBImage
 * @param width
 * @param height
 * @param name
 */
RGBImage::RGBImage(const uint32_t width,
                   const uint32_t height,
                   const std::string name) :
    _width( width ),
    _height( height ),
    _name( name)
{
    _numPixels = _width * _height;
}

RGBImage::RGBImage(const std::string fileName)
{
    _loadImage(fileName);
}

/**
 * @brief RGBImage::_loadImage
 * @param fileName
 */
void RGBImage::_loadImage(const std::string fileName)
{
    BEGIN();
    LOG_INFO_ARGS("Loading a binary image from [%s]", fileName.c_str());
    std::ifstream stream(fileName, std::ios::binary);

    // Get the header string
    std::string headerString;
    stream >> headerString;

    if (headerString != "P6")
        LOG_ERROR_ARGS("Wrong header string [%s]", headerString.c_str());

    // Skip comments
    for (;;)
    {
        getline(stream, headerString);

        if (headerString.empty())
            continue;

        if (headerString [0] != '#')
            break;
    }

    // Read the dimensions of the image
    std::stringstream dataString (headerString);
    dataString >> _width;
    dataString >> _height;

    // Get the color depth of the image
    stream >> _colorDepth;

    if (_colorDepth != 255)
        LOG_ERROR("Wrong color depth");

    {
        // Skip until end of line
        std::string skippable;
        getline(stream, skippable);
    }

    _pixels = new char[_width * _height * 3];
    stream.read(_pixels, _width * _height * 3);
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
 * @brief RGBImage::getColorDepth
 * @return
 */
uint32_t RGBImage::getColorDepth(void) const
{
    return _colorDepth;
}


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

