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
#include <iostream>

RaytraceShader::RaytraceShader(const Colour& diffuse, const Colour& specular,
	float reflectance, float refractance, float roughness)
	: m_diff(diffuse), m_spec(specular), m_refl(reflectance), m_refr(refractance),
	m_rough(roughness), m_rc(Scene::GetInstance().GetAirRefractCoeff()) {
}

RaytraceShader::RaytraceShader(const Colour& diffuse, const Colour& specular,
	float reflectance, float refractance, float refractCoeff, float roughness)
	: m_diff(diffuse), m_spec(specular), m_refl(reflectance), m_refr(refractance),
	m_rough(roughness), m_rc(refractCoeff) {
}

RaytraceShader::~RaytraceShader() {
	//dtor
}

Colour RaytraceShader::Sample(const Vec3f& point, const Vec3f& N, const Vec3f& V,
	unsigned int& rayCounter) {
	Colour accum(0.f, 0.f, 0.f, 0.f);

	// add in Blinn-Phong
	Vec3f L, H;
	float att, intensity;
	for (Scene::LightList::iterator i = Scene::GetInstance().GetLights().begin();
		i != Scene::GetInstance().GetLights().end(); ++i) {
		// diffuse
		if (!(*i)->Sample(point, att, L))
			continue;
		intensity = att * std::max(0.f, L.dot(N));
		accum += (*i)->GetColour() * m_diff * intensity;
		// specular
		H = Vec3f(L + V).normalized();
		intensity = att * pow(std::max(0.f, H.dot(N)), m_spec.W());
		accum += (*i)->GetColour() * m_spec * intensity;
	}

	if (++rayCounter < Scene::GetInstance().GetRayDepthLimit()) {
		// spawn a reflection ray
		if (m_refl > 0.f) {
			Vec3f dir = V - N * 2.f * N.dot(V) + Vec3f::random() * m_rough;
			dir.normalize();
			Ray r(point, point + dir * Scene::GetInstance().Cam.GetZFar(), true);
			Vec3f p, n;
			Shape *s = Scene::GetInstance().Intersect(r, &p, &n);
			if (s)
				accum += s->GetShader().Sample(p, n, dir, rayCounter) * m_refl;
		}
		// spawn a refraction ray
		if (m_refr > 0.f) {
			//accum += Fresnel * this->CastRay(point, V - 2.f * N.dot(V) * N);
		}
	}

	accum.Clamp();
	return accum;
}
