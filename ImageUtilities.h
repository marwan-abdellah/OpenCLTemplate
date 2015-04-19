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
