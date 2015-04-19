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
Image::Image(const int width,
             const int height,
             const int colorDepth,
             const int components,
             const std::string name) :
    _width(width),
    _height(height),
    _numComponents(components),
    _colorDepth(colorDepth),
    _name(name)
{
    _numPixels = _width * _height;
    _pixelArraySize = _numPixels * _numComponents;
    _dataSize = _pixelArraySize * sizeof(char);
    _pixels.resize(_dataSize);

    _printImageDetails();
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
    _numPixels = _width * _height;
    _pixelArraySize = _numPixels * _numComponents;
    _dataSize = _pixelArraySize * sizeof(char);

    _pixels.resize(_dataSize);
    stream.read(reinterpret_cast<char*> (_pixels.data()), _dataSize);

    // Print image details
    _printImageDetails();

    END();
}

/**
 * @brief RGBImage::getWidth
 * @return
 */
int Image::getWidth( void ) const { return _width; }


/**
 * @brief Image::getHeight
 * @return
 */
int Image::getHeight( void ) const { return _height; }


/**
 * @brief RGBImage::getColorDepth
 * @return
 */
int Image::getColorDepth(void) const { return _colorDepth; }


/**
 * @brief RGBImage::getNumberOfColorComponents
 * @return
 */
int Image::getNumberOfColorComponents(void) const
{
    return _numComponents;
}

/**
 * @brief RGBImage::getNumberOfPixels
 * @return
 */
int Image::getNumberOfPixels( void ) const { return _numPixels; }


/**
 * @brief RGBImage::getName
 * @return
 */
std::string Image::getName( void ) const { return _name; }


/**
 * @brief RGBImage::getPixels
 * @return
 */
std::vector<char> *Image::getPixels( void )
{
    std::vector<char>* ptrPixels = &_pixels;
    return ptrPixels;
}


/**
 * @brief Image::getDataSizeInBytes
 * @return
 */
int Image::getDataSizeInBytes(void) const { return _dataSize; }


/**
 * @brief Image::savePPMImage
 * @param path
 */
void Image::savePPMImage(std::string path)
{
    BEGIN();
    LOG_INFO_ARGS("Saving the image to [%s]", path.c_str());

    std::ofstream stream(path, std::ios::binary);

    stream << "P6\n";
    stream << _width << " " << _height << std::endl;
    stream << _colorDepth << std::endl;

    LOG_INFO("Writing the image to disk");
    stream.write(_pixels.data(), _dataSize);

    END();
}


/**
 * @brief Image::_printImageDetails
 */
void Image::_printImageDetails(void)
{
    BEGIN();

    std::stringstream stream;
    stream << std::endl;
    stream << "\t Name: " << _name << std::endl;
    stream << "\t Width x Height: " << _width << " x " << _height << std::endl;
    stream << "\t Number components " << _numComponents << std::endl;
    stream << "\t Pixel array size " << _pixelArraySize << std::endl;
    stream << "\t Color depth " << _colorDepth << std::endl;
    LOG_INFO_ARGS("Image details %s", stream.str().c_str());

    END();
}


/**
 * @brief Image::getPixelArraySize
 * @return
 */
int Image::getPixelArraySize(void) const { return _pixelArraySize; }

/**
 * @brief Image::~Image
 */
Image::~Image()
{

}

