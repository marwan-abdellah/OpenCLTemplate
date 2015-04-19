/*
 * Copyright (C) 2015 Marwan Abdellah <abdellah.marwan@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#include "ImageUtilities.h"
#include "Logger.h"

/**
 * @brief ImageUtilities::convertRGBtoRGBA
 * Converts an RGB image to an RGBA one.
 * @param input The RGB image
 * @return The RGBA image
 */
Image* ImageUtilities::convertRGBtoRGBA ( Image* input)
{
    BEGIN();

    // Make sure that the input image is RGB with 3 components
    if (input->getNumberOfColorComponents() != 3)
        LOG_ERROR_ARGS("The input image [%s] is not an RGB image",
                       input->getName().c_str());

    // Create a new image with the same components
    LOG_DEBUG("Creating an output image with the same dimensions");
    Image* output = new Image(input->getWidth(), input->getHeight(),
                              input->getColorDepth(),
                              input->getNumberOfColorComponents() + 1,
                              input->getName());

    // Get a pointer to the data of both images
    LOG_DEBUG("Getting pointer to the input image data");
    std::vector<char>* inputPixels = input->getPixels();

    LOG_DEBUG("Getting pointer to the output image data");
    std::vector<char>* outputPixels = output->getPixels();

    LOG_DEBUG("Filling the output image");
    for (std::size_t i = 0; i < input->getNumberOfPixels(); i++)
    {
        outputPixels->at(i * 4 + 0) = inputPixels->at(i * 3 + 0);
        outputPixels->at(i * 4 + 1) = inputPixels->at(i * 3 + 1);
        outputPixels->at(i * 4 + 2) = inputPixels->at(i * 3 + 2);
        outputPixels->at(i * 4 + 3) = 0;
    }

    END();
    return output;
}

/**
 * @brief ImageUtilities::convertRGBAtoRGB
 * Converts an RGBA image into an RGB one.
 * @param input The RGBA image
 * @return The RGB image
 */
Image* ImageUtilities::convertRGBAtoRGB (Image *input)
{
    BEGIN();

    // Make sure that the input image is RGBA with 4 components
    if (input->getNumberOfColorComponents() != 4)
        LOG_ERROR_ARGS("The input image [%s] is not an RGBA image",
                       input->getName().c_str());

    // Create a new image with the same components
    LOG_DEBUG("Creating an output image with the same dimensions");
    Image* output = new Image(input->getWidth(), input->getHeight(),
                              input->getColorDepth(),
                              input->getNumberOfColorComponents() - 1,
                              input->getName());

    // Get a pointer to the data of both images
    LOG_DEBUG("Getting pointer to the input image data");
    std::vector<char>* inputPixels = input->getPixels();

    LOG_DEBUG("Getting pointer to the output image data");
    std::vector<char>* outputPixels = output->getPixels();

    LOG_DEBUG("Filling the output image");
    for (std::size_t i = 0; i < output->getNumberOfPixels(); i++)
    {
        outputPixels->at(i * 3 + 0) = inputPixels->at(i * 4 + 0);
        outputPixels->at(i * 3 + 1) = inputPixels->at(i * 4 + 1);
        outputPixels->at(i * 3 + 2) = inputPixels->at(i * 4 + 2);
    }

    END();
    return output;
}
