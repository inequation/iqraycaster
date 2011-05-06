#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"


class Plane : public Shape
{
	public:
		Plane(const Vec3f& normal, float distanceFromOrigin, Shader& sh);
		virtual ~Plane();

		bool Intersect(const Ray& r, float& out_distance, Vec3f& out_point, Vec3f& out_normal) const;
	protected:
	private:
};

#endif // PLANE_H
