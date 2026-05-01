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

#include "cube.h"

Cube::Cube(const std::shared_ptr<Texture> &texture)
    : Mesh(texture)
{
    Vector3 p1(-1, -1, 1);
    Vector3 p2( 1, -1, 1);
    Vector3 p3( 1,  1, 1);
    Vector3 p4(-1,  1, 1);
    Vector3 normal(0, 0, 1);
    Vector2 t1(0, 0);
    Vector2 t2(1, 0);
    Vector2 t3(1, 1);
    Vector2 t4(0, 1);

    Matrix4 rotations[6] = {
        Matrix4::identity(),
        Matrix4::rotateY(deg2rad( 90.0)),
        Matrix4::rotateY(deg2rad(180.0)),
        Matrix4::rotateY(deg2rad(270.0)),
        Matrix4::rotateX(deg2rad( 90.0)),
        Matrix4::rotateX(deg2rad(-90.0)),
    };
    for (const auto &r : rotations)
    {
        Vector3 n = (r * Vector4(normal, 0)).xyz();
        vertices.emplace_back((r * Vector4(p1, 1)).xyz(), n, t1);
        vertices.emplace_back((r * Vector4(p2, 1)).xyz(), n, t2);
        vertices.emplace_back((r * Vector4(p3, 1)).xyz(), n, t3);
        vertices.emplace_back((r * Vector4(p4, 1)).xyz(), n, t4);
    }
}