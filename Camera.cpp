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

#include "Camera.h"

Camera::Camera() : m_fwd(Vec3f(1, 0, 0)), m_right(Vec3f(0, 1, 0)), m_up(Vec3f(0, 0, 1)),
	m_FOV(90.f / 180.f * M_PI), m_zNear(0.1), m_zFar(1024.f) {
	//ctor
}

Camera::~Camera() {
	//dtor
}

Vec3f Camera::CalcViewVector(float px, float py) {
	return Vec3f(m_fwd * m_zNear + m_right * px + m_up * py).normalized();
}
