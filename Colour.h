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

#ifndef COLOUR_H
#define COLOUR_H

#include "math.h"

const float Byte2Float = 1.f / 255.f;

class Colour : public Tuple4<float>
{
	public:
		Colour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		Colour(unsigned char r, unsigned char g, unsigned char b);
		Colour(float r, float g, float b, float a);
		Colour(float r, float g, float b);
		Colour(const Colour& c) : Tuple4<float>(c) {}
		Colour(const Tuple4<float>& t) : Tuple4<float>(t) {}
		virtual ~Colour();

		inline void Clamp() {
			M_ARR[0] = std::min(1.f, std::max(0.f, M_ARR[0]));
			M_ARR[1] = std::min(1.f, std::max(0.f, M_ARR[1]));
			M_ARR[2] = std::min(1.f, std::max(0.f, M_ARR[2]));
			M_ARR[3] = std::min(1.f, std::max(0.f, M_ARR[3]));
		}
};

#endif // COLOUR_H
