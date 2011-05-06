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

#include "Ray.h"
#include <limits>

Ray::Ray(const Vec3f& start, const Vec3f& end, bool initialOffset) : m_start(start), m_end(end) {
	m_dir = Vec3f(end - start);
	m_dir.normalize();
	if (initialOffset)
		m_start += m_dir * this->m_offsetEpsilon;
	m_projStart = m_dir.dot(m_start);
	m_projEnd = m_dir.dot(m_end);
	m_length = m_projEnd - m_projStart;
}

Ray::~Ray() {
}
