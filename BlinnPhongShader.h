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

#ifndef BLINNPHONGSHADER_H
#define BLINNPHONGSHADER_H

#include "Shader.h"

class BlinnPhongShader : public Shader
{
	public:
		BlinnPhongShader(const Colour& diffuse, const Colour& specular);
		virtual ~BlinnPhongShader();

		Colour Sample(const Vec3f& point, const Vec3f& normal, const Vec3f& view, unsigned int& rayCounter);
	protected:
		Colour m_diff;
		Colour m_spec;
};

#endif // BLINNPHONGSHADER_H
