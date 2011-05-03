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

#include "Sphere.h"
#include <iostream>

Sphere::Sphere(Vec3f location, float radius, Shader& s) : Shape(location, s), m_radius(radius) {
	//ctor
}

Sphere::~Sphere() {
	//dtor
}

bool Sphere::Intersect(const Ray& r, float& out_distance, Vec3f& out_point, Vec3f& out_normal) const {
	float f = r.GetDir().dot(m_loc);
	// early out
	if ((f + m_radius) < r.GetProjectedStart() || (f - m_radius) > r.GetProjectedEnd())
		return false;
	float d = Vec3f(m_loc - r.GetStart()).cross(Vec3f(m_loc - r.GetEnd())).length();
	d /= r.GetLength();
	if (d > m_radius)
		return false;
	float x = m_radius * sinf(acosf(d / m_radius));
	out_distance = f + x;
	out_point = r.GetStart() + r.GetDir() * out_distance;
	out_normal = Vec3f(out_point - m_loc).normalized();
	return true;
}
