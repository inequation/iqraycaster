#ifndef RAYTRACESHADER_H
#define RAYTRACESHADER_H

#include "Shader.h"


class RaytraceShader : public Shader
{
	public:
		RaytraceShader(const Colour& colour, float reflectance);
		virtual ~RaytraceShader();

		Colour Sample(const Vec3f& point, const Vec3f& normal, const Vec3f& view);
	protected:
		Colour CastShapeRay(const Vec3f& src, const Vec3f& dir);

		Colour m_c;
		float m_refl;
};

#endif // RAYTRACESHADER_H
