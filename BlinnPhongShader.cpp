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

#include "BlinnPhongShader.h"
// for light list traversal
#include "Scene.h"
#include <iostream>

BlinnPhongShader::BlinnPhongShader(const Colour& diffuse, const Colour& specular)
	: m_diff(diffuse), m_spec(specular) {
	//ctor
}

BlinnPhongShader::~BlinnPhongShader() {
	//dtor
}

Colour BlinnPhongShader::Sample(const Vec3f& point, const Vec3f& N, const Vec3f& V,
	unsigned int& rayCounter) {
	//return Colour(N * 0.5 + Vec3f(0.5));
	//return Colour(this->WorldNormalToScreenNormal(N) * 0.5 + Vec3f(0.5));
	//float dot = N.dot(V) * 0.5 + 0.5; return Colour(1 - dot, 0.f, dot);
	Colour accum(0.f, 0.f, 0.f, 0.f);
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
	accum.Clamp();
	return accum;
}
