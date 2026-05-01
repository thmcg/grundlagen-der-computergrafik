/**
 * Grundlagen der Computergrafik
 * Copyright © 2021-2026 Tobias Reimann
 * Copyright © 2024 Lukas Scheurer: Rewritten in C++
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#define STB_IMAGE_IMPLEMENTATION

#include "texture.h"

#include <stb_image.h>

#include <stdexcept>

Texture::Texture(const std::string &filename)
    : filename(filename)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (!data)
    {
        throw std::runtime_error("Failed to load texture " + filename);
    }

    GLenum format;
    if (channels == 3)
    {
        format = GL_RGB;
    }
    else if (channels == 4)
    {
        format = GL_RGBA;
    }
    else
    {
        stbi_image_free(data);
        throw std::runtime_error("Unsupported channel count in texture " + filename);
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}