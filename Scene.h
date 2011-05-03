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

#ifndef SCENE_H
#define SCENE_H

#include <vector>

// base classes
#include "Shader.h"
#include "Shape.h"
#include "Light.h"
#include "Camera.h"

// detail classes
#include "Sphere.h"
#include "PointLight.h"
#include "BlinnPhongShader.h"

class Scene
{
	public:
		typedef std::vector<Light *> LightList;
		typedef std::vector<Shape *> ShapeList;

		LightList& GetLights() { return m_lights; }
		ShapeList& GetShapes() { return m_shapes; }

		Shape *Intersect(const Ray& r, float& out_distance, Vec3f& out_point, Vec3f& out_normal) const;

		Camera Cam;

		static Scene& GetInstance(void);
	private:
		Scene();
		virtual ~Scene();

		LightList m_lights;
		ShapeList m_shapes;
};

#endif // SCENE_H
