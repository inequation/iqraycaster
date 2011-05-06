#ifndef RAYTRACESHADER_H
#define RAYTRACESHADER_H

#include "Shader.h"


class RaytraceShader : public Shader
{
	public:
		RaytraceShader(const Colour& diffuse, const Colour& specular,
			float reflectance, float refractance, float roughness = 0.f);
		RaytraceShader(const Colour& diffuse, const Colour& specular,
			float reflectance, float refractance, float refractCoeff, float roughness = 0.f);
		virtual ~RaytraceShader();

		Colour Sample(const Vec3f& point, const Vec3f& normal, const Vec3f& view,
			unsigned int& rayCounter);
	protected:
		Colour m_diff, m_spec;
		float m_refl, m_refr, m_rough, m_rc;
};

#endif // RAYTRACESHADER_H
