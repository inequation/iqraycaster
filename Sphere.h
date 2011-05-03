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

#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"


class Sphere : public Shape
{
	public:
		Sphere(Vec3f location, float radius, Shader& s);
		Sphere(const Sphere& other);
		virtual ~Sphere();
		float GetRadius() { return m_radius; }
		void SetRadius(float val) { m_radius = val; }

		bool Intersect(const Ray& r, float& out_distance, Vec3f& out_point, Vec3f& out_normal) const;
	protected:
		float m_radius;
};

#endif // SPHERE_H
