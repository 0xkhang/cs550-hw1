#include "triangle.h"

#include "vertex.h"

void Triangle::compute_normal_and_area()
{
	glm::vec3 u = vertices[1]->position - vertices[0]->position;
	glm::vec3 v = vertices[2]->position - vertices[0]->position;

	glm::vec3 uxv = glm::cross(u, v);

	area = glm::length(uxv) / 2.0f;
	normal = glm::normalize(uxv);
}

Triangle::Triangle() :
	index(-1),
	vertices{nullptr, nullptr, nullptr},
	edges{nullptr, nullptr, nullptr}
{

}

Triangle::~Triangle()
{

}
