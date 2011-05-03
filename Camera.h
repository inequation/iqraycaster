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

#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"

class Camera
{
	public:
		Camera();
		virtual ~Camera();

		inline Vec3f& GetLocation() { return m_loc; }
		inline void SetLocation(const Vec3f& val) { m_loc = val; }
		inline const Vec3f& GetForwardVector() const {return m_fwd;}
		inline const Vec3f& GetRightVector() const {return m_right;}
		inline const Vec3f& GetUpVector() const {return m_up;}
		inline float GetFOV() { return m_FOV; }
		inline void SetFOV(float val) { m_FOV = val; }
		inline float GetZNear() {return m_zNear;}
		inline float GetZFar() {return m_zFar;}
		inline void SetZNear(float val) {m_zNear = val;}
		inline void SetZFar(float val) {m_zFar = val;}

		Vec3f CalcViewVector(float px, float py);
	private:
		Vec3f m_loc, m_fwd, m_right, m_up;
		float m_FOV, m_zNear, m_zFar;
};

#endif // CAMERA_H
