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
#include <OpenImageIO/imageio.h>
#include <iostream>
#include <cmath>

OIIO_NAMESPACE_USING

void draw(int w, int h, const char *fname) {
	unsigned char buf[w * h * 3];

	Scene::GetInstance().Render(w, h, buf);

	ImageOutput *out = ImageOutput::create(fname);
	if (!out)
		return;
	ImageSpec spec(w, h, 3, TypeDesc::UINT8);
	out->open(fname, spec);
	out->write_image(TypeDesc::UINT8, buf);
	out->close();
	delete out;
}

int main(/*int argc, char *argv[]*/) {
	//BlinnPhongShader red(Colour(1.f, 0.f, 0.f), Colour(1.f, 1.f, 1.f, 10.f));
	BlinnPhongShader blue(Colour(0.f, 0.f, 1.f), Colour(1.f, 1.f, 1.f, 10.f));
	RaytraceShader red(Colour(1.f, 0.f, 0.f), 0.6);
	//RaytraceShader blue(Colour(0.f, 0.f, 1.f), 0.6);

	Sphere s1(Vec3f(3, 1.3, 0), 1.f, red);
	Sphere s2(Vec3f(2, -0.7, 0), 1.f, blue);

	PointLight p1(Vec3f(-3, 5, 10), Colour(1.f, 1.f, 1.f), 400.f);
	PointLight p2(Vec3f(-3, -5, -10), Colour(0.8f, 1.f, 1.f), 100.f);

	Scene::GetInstance().GetShapes().push_back(&s1);
	Scene::GetInstance().GetShapes().push_back(&s2);
	Scene::GetInstance().GetLights().push_back(&p1);
	Scene::GetInstance().GetLights().push_back(&p2);

	std::cout << "Rendering scene... ";
	std::cout.flush();

	draw(640, 480, "scene.png");

	std::cout << "done.\n";

    return 0;
}
