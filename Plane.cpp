#include "Plane.h"

Plane::Plane(const Vec3f& normal, float distanceFromOrigin, Shader& sh) : Shape(normal, sh) {
	m_loc.W() = distanceFromOrigin;
}

Plane::~Plane() {
	//dtor
}

bool Plane::Intersect(const Ray& r, float& out_distance, Vec3f& out_point, Vec3f& out_normal) const {
	float d1, d2;

	d1 = m_loc.dot(r.GetStart()) - m_loc.W();
	d2 = m_loc.dot(r.GetEnd()) - m_loc.W();
	if (d1 * d2 > 0.f)
		return false;
	out_normal = m_loc;
	out_point = r.GetStart() + r.GetDir() * r.GetLength() * -d1 / (d2 - d1);
	out_distance = Vec3f(out_point - r.GetStart()).length();
	return true;
}
