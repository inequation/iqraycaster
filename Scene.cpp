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
#include <iostream>

Scene::Scene() : m_airRefract(1.f) {
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

Shape *Scene::Intersect(const Ray& r, Vec3f *out_point, Vec3f *out_normal, Shape *omit, float *out_distance) const {
	float d = std::numeric_limits<float>::max();
	Shape *s = NULL;
	Vec3f p, n;
	float testd;
	Vec3f testp, testn;
	for (ShapeList::const_iterator i = m_shapes.begin(); i != m_shapes.end(); ++i) {
		if ((*i) == omit)
			continue;
		if ((*i)->Intersect(r, testd, testp, testn) && testd < d) {
			s = *i;
			d = testd;
			p = testp;
			n = testn;
		}
	}
	if (out_distance)
		*out_distance = d;
	if (out_point)
		*out_point = p;
	if (out_normal)
		*out_normal = n;
	return s;
}

void Scene::Render(int width, int height, unsigned char *framebuffer) {
	const float pw = this->Cam.GetZNear() * tanf(this->Cam.GetFOV() * 0.5);
	const float ph = pw * (float)height / (float)width;
	Vec3f view, target, p, n;
	Shape *s;
	float px, py;
	for (int y = 0; y < height; ++y) {
		py = 2.f * ((float)y / (height - 1) - 0.5) * ph;
		for (int x = 0; x < width; ++x) {
			px = 2.f * ((float)x / (width - 1) - 0.5) * pw;
			view = this->Cam.CalcViewVector(px, py);
			target = this->Cam.GetLocation() + view * this->Cam.GetZFar();
			s = this->Intersect(Ray(this->Cam.GetLocation(), target), &p, &n);
			if (!s) {
				framebuffer[(y * width + x) * 3 + 0] = 0;
				framebuffer[(y * width + x) * 3 + 1] = 0;
				framebuffer[(y * width + x) * 3 + 2] = 0;
				continue;
			}
			const Colour& work = s->GetShader().Sample(p, n, view, s);
			framebuffer[(y * width + x) * 3 + 0] = work.X() * 255.f;
			framebuffer[(y * width + x) * 3 + 1] = work.Y() * 255.f;
			framebuffer[(y * width + x) * 3 + 2] = work.Z() * 255.f;
		}
	}
}
