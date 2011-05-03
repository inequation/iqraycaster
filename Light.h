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

#ifndef LIGHT_H
#define LIGHT_H

#include "Colour.h"

class Light
{
	public:
		Light(const Colour& c);
		virtual ~Light();

		const Colour& GetColour() const { return m_colour; }

		virtual void Sample(const Vec3f& dst, float& out_attenuation, Vec3f& out_lightVector) const = 0;
	protected:
		Colour m_colour;
};

#endif // LIGHT_H
