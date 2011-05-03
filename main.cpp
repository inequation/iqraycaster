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

void draw() {
	const int w = 640;
	const int h = 480;
	unsigned char buf[w * h * 3];

	const float pw = Scene::GetInstance().Cam.GetZNear() * tanf(Scene::GetInstance().Cam.GetFOV() * 0.5);
	const float ph = pw * (float)h / (float)w;
	Vec3f view, target, p, n;
	Shape *s;
	float px, py, d;
	for (int y = 0; y < h; ++y) {
		py = 2.f * ((float)y / (h - 1) - 0.5) * ph;
		for (int x = 0; x < w; ++x) {
			px = 2.f * ((float)x / (w - 1) - 0.5) * pw;
			view = Scene::GetInstance().Cam.CalcViewVector(px, py);
			target = Scene::GetInstance().Cam.GetLocation() + view * Scene::GetInstance().Cam.GetZFar();
			s = Scene::GetInstance().Intersect(Ray(Scene::GetInstance().Cam.GetLocation(), target), d, p, n);
			if (!s) {
				buf[(y * w + x) * 3 + 0] = 0;
				buf[(y * w + x) * 3 + 1] = 0;
				buf[(y * w + x) * 3 + 2] = 0;
				continue;
			}
			const Colour& work = s->GetShader().Sample(p, n, view);
			buf[(y * w + x) * 3 + 0] = work.X() * 255.f;
			buf[(y * w + x) * 3 + 1] = work.Y() * 255.f;
			buf[(y * w + x) * 3 + 2] = work.Z() * 255.f;
		}
	}

	ImageOutput *out = ImageOutput::create("scene.png");
	if (!out)
		return;
	ImageSpec spec(640, 480, 3, TypeDesc::UINT8);
	out->open("scene.png", spec);
	out->write_image(TypeDesc::UINT8, buf);
	out->close();
	delete out;
}

int main(int argc, char *argv[]) {
	BlinnPhongShader red(Colour(1.f, 0.f, 0.f), Colour(1.f, 1.f, 1.f, 10.f));
	BlinnPhongShader blue(Colour(0.f, 0.f, 1.f), Colour(1.f, 1.f, 1.f, 10.f));

	Sphere s1(Vec3f(7.5, 1, 0), 3.f, red);
	Sphere s2(Vec3f(13, -2, 2), 5.f, blue);

	PointLight p1(Vec3f(-3, 5, 10), Colour(1.f, 1.f, 1.f), 400.f);
	PointLight p2(Vec3f(-3, -5, -10), Colour(0.8f, 1.f, 1.f), 100.f);

	Scene::GetInstance().GetShapes().push_back(&s1);
	Scene::GetInstance().GetShapes().push_back(&s2);
	Scene::GetInstance().GetLights().push_back(&p1);
	Scene::GetInstance().GetLights().push_back(&p2);

	std::cout << "Rendering scene... ";
	std::cout.flush();

	draw();

	std::cout << "done.\n";

    return 0;
}
