/*
===========================================================================
Copyright (C) 2011 Leszek Godlewski

This file is part of iqraycaster source code.

iqraycaster source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

iqraycaster source code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License along
with iqraycaster source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

#ifndef SHAPE_H
#define SHAPE_H

#include <cmath>
#include "Ray.h"
#include "Shader.h"

class Shape
{
	public:
		Shape(const Vec3f& location, Shader& shader);
		virtual ~Shape();

		virtual bool Intersect(const Ray& r, float& out_distance, Vec3f& out_point, Vec3f& out_normal) const = 0;

		Vec3f GetLocation(void) const {return m_loc;}
		Shader& GetShader(void) const {return m_shader;}
	protected:
		Vec3f m_loc;
		Shader& m_shader;
};

#endif // SHAPE_H
