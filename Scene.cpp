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

#include "Scene.h"
#include <limits>

Scene::Scene() {
	m_shapes.reserve(32);
	m_lights.reserve(32);
}

Scene::~Scene() {
	//dtor
}

Scene& Scene::GetInstance(void) {
	static Scene s;
	return s;
}

Shape *Scene::Intersect(const Ray& r, float& out_distance, Vec3f& out_point, Vec3f& out_normal) const {
	float d = std::numeric_limits<float>::max();
	Shape *s = NULL;
	Vec3f p, n;
	float testd;
	Vec3f testp, testn;
	for (std::vector<Shape *>::const_iterator i = m_shapes.begin(); i != m_shapes.end(); ++i) {
		if ((*i)->Intersect(r, testd, testp, testn) && testd < d) {
			s = *i;
			d = testd;
			p = testp;
			n = testn;
		}
	}
	out_distance = d;
	out_point = p;
	out_normal = n;
	return s;
}
