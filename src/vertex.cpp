#include "vertex.h"

#include "triangle.h"

void Vertex::compute_normal()
{
	glm::vec3 n(0.0f);
	for (Triangle *t : triangles)
		n += t->area * t->normal;
	normal = glm::normalize(n);
}

Vertex::Vertex() :
	index(-1),
	position(0.0f)
{

}

Vertex::~Vertex()
{

}
