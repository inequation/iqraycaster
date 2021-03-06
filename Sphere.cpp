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

Sphere::Sphere(const Sphere& other) : Shape(other), m_radius(other.m_radius) {
}

Sphere::~Sphere() {
	//dtor
}

bool Sphere::Intersect(const Ray& r, float& out_distance, Vec3f& out_point, Vec3f& out_normal) const {
	float det, b, d2;
	Vec3f p = r.GetStart() - this->m_loc;
	b = -p.dot(r.GetDir());
	det = b * b - p.lengthSquared() + this->m_radius * this->m_radius;
	if (det < 0)
		return false;
	det = sqrt(det);
	out_distance = b - det;
	d2 = b + det;
	if (d2 < 0.f || d2 > r.GetLength() - this->m_radius)
		return false;
	if (out_distance < 0.f)
		out_distance = 0.f;
	out_point = r.GetStart() + r.GetDir() * out_distance;
	out_normal = Vec3f(out_point - this->m_loc).normalized();
	return true;
}
