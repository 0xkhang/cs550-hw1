#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <glm/glm.hpp>
#include <array>

class Vertex;
class Edge;

// Represents a face in a triangle mesh
class Triangle
{
public:
	size_t index;  // Index of this triangle in Mesh::triangles

	glm::vec3 normal;  // Object-space normal

	float area; // Area of this triangle

	std::array<Vertex *, 3> vertices;  // This triangle's vertices
	std::array<Edge *, 3> edges;  // This triangle's edges

	void compute_normal_and_area();

	Triangle();
	~Triangle();
private:
};

#endif
