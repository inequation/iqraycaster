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

#include "RaytraceShader.h"
// for lists traversal
#include "Scene.h"
#include "Ray.h"

RaytraceShader::RaytraceShader(const Colour& colour, float reflectance)
	: m_c(colour), m_refl(reflectance) {
	//ctor
}

RaytraceShader::~RaytraceShader() {
	//dtor
}

Colour RaytraceShader::CastShapeRay(const Vec3f& src, const Vec3f& dir) {
	Ray r(src, dir * Scene::GetInstance().Cam.GetZFar());
	float d;
	Vec3f p, n;
	Shape *s = Scene::GetInstance().Intersect(r, d, p, n);
	if (!s)
		return Colour(0.f, 0.f, 0.f);
	return s->GetShader().Sample(p, n, dir);
}

Colour RaytraceShader::Sample(const Vec3f& point, const Vec3f& N, const Vec3f& V) {
	Colour accum(0.f, 0.f, 0.f, 0.f);

	// spawn a reflection ray
	if (m_refl > 0.f)
		accum += this->CastShapeRay(point, V - N * 2.f * N.dot(V)) * m_refl;
	// spawn a refraction ray
	//accum += Fresnel * this->CastRay(point, V - 2.f * N.dot(V) * N);
	// add in Lambert
	Vec3f L;
	float att, intensity;
	for (Scene::LightList::iterator i = Scene::GetInstance().GetLights().begin();
		i != Scene::GetInstance().GetLights().end(); ++i) {
		// diffuse
		(*i)->Sample(point, att, L);
		intensity = att * std::max(0.f, N.dot(L));
		accum += (*i)->GetColour() * m_c * intensity;
	}
	accum.Clamp();
	return accum;
}
