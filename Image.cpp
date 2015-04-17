#include "Image.h"
#include "Logger.h"

/**
 * @brief Image::Image
 * @param width
 * @param height
 * @param colorDepth
 * @param components
 * @param name
 */
Image::Image(const uint32_t width,
             const uint32_t height,
             const uint32_t colorDepth,
             const uint32_t components,
             const std::string name) :
    _width(width),
    _height(height),
    _numComponents(components),
    _colorDepth(colorDepth),
    _name(name)
{
    _numPixels = _width * _height;
    _dataSize = _numPixels * _numComponents;
}

Image::Image(const std::string fileName)
{
    _loadPPMImage(fileName);
}

/**
 * @brief RGBImage::_loadPPMImage
 * @param fileName
 */
void Image::_loadPPMImage(const std::string fileName)
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
        if (headerString.empty()) continue;
        if (headerString[0] != '#') break;
    }

    // Read the dimensions of the image
    std::stringstream dataString (headerString);
    dataString >> _width;
    dataString >> _height;

    // Get the color depth of the image
    stream >> _colorDepth;

    if (_colorDepth != 255)
        LOG_ERROR("Wrong color depth");

    // Skip until end of line
    std::string skippable;
    getline(stream, skippable);

    // PPM image has always 3 components
    _numComponents = 3;
    _dataSize = _width * _height * _numComponents;

    // Allocate an array and fill it with the data from the stream
    _pixels = new char[_dataSize];
    stream.read(_pixels, _dataSize);

    END();
}

/**
 * @brief RGBImage::getWidth
 * @return
 */
uint32_t Image::getWidth( void ) const { return _width; }


/**
 * @brief Image::getHeight
 * @return
 */
uint32_t Image::getHeight( void ) const { return _height; }


/**
 * @brief RGBImage::getColorDepth
 * @return
 */
uint32_t Image::getColorDepth(void) const { return _colorDepth; }


/**
 * @brief RGBImage::getNumberOfColorComponents
 * @return
 */
uint32_t Image::getNumberOfColorComponents(void) const
{
    return _numComponents;
}

/**
 * @brief RGBImage::getNumberOfPixels
 * @return
 */
uint32_t Image::getNumberOfPixels( void ) const { return _numPixels; }


/**
 * @brief RGBImage::getName
 * @return
 */
std::string Image::getName( void ) const { return _name; }


/**
 * @brief RGBImage::getPixels
 * @return
 */
char* Image::getPixels( void ) const { return _pixels; }


/**
 * @brief Image::getDataSizeInBytes
 * @return
 */
uint32_t Image::getDataSizeInBytes(void) const { return _dataSize; }


/**
 * @brief Image::~Image
 */
Image::~Image()
{
    BEGIN();

    delete [] _pixels;

    END();
}

