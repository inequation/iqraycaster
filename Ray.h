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

#ifndef RAY_H
#define RAY_H

#include "math.h"

class Ray
{
	public:
		Ray(const Vec3f& start, const Vec3f& end, bool initialOffset = false);
		virtual ~Ray();

		const inline Vec3f& GetStart(void) const {return m_start;}
		const inline Vec3f& GetEnd(void) const {return m_end;}
		const inline Vec3f& GetDir(void) const {return m_dir;}
		inline float GetProjectedStart(void) const {return m_projStart;}
		inline float GetProjectedEnd(void) const {return m_projEnd;}
		inline float GetLength(void) const {return m_length;}
	private:
		Vec3f m_start;
		Vec3f m_end;
		Vec3f m_dir;
		float m_projStart, m_projEnd, m_length;

		static const float m_offsetEpsilon = 1e-4;
};

#endif // RAY_H
