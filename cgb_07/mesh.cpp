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

#include "mesh.h"

#include "texture.h"

Mesh::Mesh(std::shared_ptr<Texture> &texture)
    : texture(texture)
{
}

void Mesh::render() const
{
    Matrix4 worldMatrix = position * rotation;

    if (texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture->id);
    }

    glPushMatrix();
    float worldMatrixF[16];
    worldMatrix.toColumnMajor(worldMatrixF);
    glMultMatrixf(worldMatrixF);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (float *)&ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (float *)&diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float *)&specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, (float *)&emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glBegin(GL_QUADS);
    for (auto vertex : vertices)
    {
        glNormal3fv((float *)&vertex.normal);
        glTexCoord2fv((float *)&vertex.texcoord);
        glVertex3fv((float *)&vertex.position);
    }
    glEnd();
    glPopMatrix();
    if (texture) glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::setPosition(const Vector3 &position)
{
    this->position = Matrix4::translate(position.x, position.y, position.z);
}

void Mesh::setRotation(const Vector3 &rotation)
{
    this->rotation = Matrix4::rotateX(rotation.x) * Matrix4::rotateY(rotation.y) * Matrix4::rotateZ(rotation.z);
}

void Mesh::setMaterial(const Color &ambient, const Color &diffuse, const Color &specular, const Color &emission, const float shininess)
{
    this->ambient[0] = static_cast<float>(ambient.r);
    this->ambient[1] = static_cast<float>(ambient.g);
    this->ambient[2] = static_cast<float>(ambient.b);
    this->ambient[3] = static_cast<float>(ambient.a);

    this->diffuse[0] = static_cast<float>(diffuse.r);
    this->diffuse[1] = static_cast<float>(diffuse.g);
    this->diffuse[2] = static_cast<float>(diffuse.b);
    this->diffuse[3] = static_cast<float>(diffuse.a);

    this->specular[0] = static_cast<float>(specular.r);
    this->specular[1] = static_cast<float>(specular.g);
    this->specular[2] = static_cast<float>(specular.b);
    this->specular[3] = static_cast<float>(specular.a);

    this->emission[0] = static_cast<float>(emission.r);
    this->emission[1] = static_cast<float>(emission.g);
    this->emission[2] = static_cast<float>(emission.b);
    this->emission[3] = static_cast<float>(emission.a);

    this->shininess = shininess;
}