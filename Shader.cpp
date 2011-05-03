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

#include "Shader.h"
#include "Scene.h"

Shader::Shader()
{
	//ctor
}

Shader::~Shader()
{
	//dtor
}

Vec3f Shader::WorldNormalToScreenNormal(const Vec3f& in) {
	return Vec3f(
		in.dot(Scene::GetInstance().Cam.GetRightVector()),
		in.dot(Scene::GetInstance().Cam.GetUpVector()),
		in.dot(Scene::GetInstance().Cam.GetForwardVector())
	);
}
