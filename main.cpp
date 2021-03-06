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
#include <iostream>
#include <cmath>
#include <png.h>

void write_png(const unsigned char *buf, int w, int h, const char *fname) {
	png_structp	sp = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,
		NULL);
	png_infop	ip = png_create_info_struct(sp);
	setjmp(png_jmpbuf(sp));

	FILE *f = fopen(fname, "wb");
	png_init_io(sp, f);
	png_set_compression_level(sp, 6);
	png_set_IHDR(sp, ip, w, h, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_set_oFFs(sp, ip, 0, 0, PNG_OFFSET_PIXEL);
	png_write_info(sp, ip);
	png_set_packing(sp);

	for (int y = 0; y < h; ++y)
		png_write_row(sp, (png_byte *)buf + (y * w * 3));

	setjmp(png_jmpbuf(sp));
	png_write_end(sp, NULL);
	png_destroy_write_struct(&sp, &ip);
	fclose(f);
}

void draw(int w, int h, const char *fname) {
	unsigned char buf[w * h * 3];

	Scene::GetInstance().Render(w, h, buf);


}

int main(/*int argc, char *argv[]*/) {
	//BlinnPhongShader red(Colour(1.f, 0.f, 0.f), Colour(1.f, 1.f, 1.f, 10.f));
	RaytraceShader red(Colour(1.f, 0.f, 0.f), Colour(0.3, 0.3, 0.3, 8.f), 0.7, 0.f);
	//BlinnPhongShader blue(Colour(0.f, 0.f, 1.f), Colour(1.f, 1.f, 1.f, 10.f));
	RaytraceShader blue(Colour(0.f, 0.f, 1.f), Colour(1.f, 1.f, 1.f, 10.f), 0.5, 0.f, 1.5, 0.08);
	BlinnPhongShader yellow(Colour(1.f, 0.5, 0.f), Colour(0.3, 0.3, 0.3, 2.f));
	RaytraceShader mirror(Colour(0.f), Colour(0.f), 1.f, 0.f);

	Sphere s1(Vec3f(2, 1.1, 0), 1.f, red);
	Sphere s2(Vec3f(2, -1.1, 0), 1.f, blue);
	Plane floor(Vec3f(0, 0, 1), -3.f, yellow);
	Plane wallL(Vec3f(0, 1, 0), -10.f, yellow);
	Plane wallR(Vec3f(0, -1, 0), -10.f, yellow);
	Plane wallB(Vec3f(-1, 0, 0), -10.f, mirror);
	Plane wallF(Vec3f(1, 0, 0), -10.f, yellow);
	Plane ceil(Vec3f(0, 0, -1), -10.f, yellow);

	Scene::GetInstance().GetShapes().push_back(&s1);
	Scene::GetInstance().GetShapes().push_back(&s2);
	Scene::GetInstance().GetShapes().push_back(&floor);
	Scene::GetInstance().GetShapes().push_back(&wallL);
	Scene::GetInstance().GetShapes().push_back(&wallR);
	Scene::GetInstance().GetShapes().push_back(&wallB);
	Scene::GetInstance().GetShapes().push_back(&wallF);
	Scene::GetInstance().GetShapes().push_back(&ceil);

	PointLight p1(Vec3f(-2, 3, 2), Colour(1.f, 1.f, 1.f), 400.f);
	PointLight p2(Vec3f(-3, -2, -2.5), Colour(0.8f, 1.f, 1.f), 100.f);

	Scene::GetInstance().GetLights().push_back(&p1);
	Scene::GetInstance().GetLights().push_back(&p2);

	Scene::GetInstance().Cam.SetLocation(Vec3f(-2.5, 0.8, 1.5));

	std::cout << "Rendering scene... ";
	std::cout.flush();

	draw(640, 480, "scene.png");

	std::cout << "done.\n";

    return 0;
}
