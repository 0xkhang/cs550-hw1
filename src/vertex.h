#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <glm/glm.hpp>
#include <vector>

class Edge;
class Triangle;

// Represents a vertex in a mesh
class Vertex
{
public:
	size_t index;  // Index of this vertex in Mesh::vertices

	glm::vec3 position;  // Object-space position
	glm::vec3 normal;  // Object-space normal

	std::vector<Edge *> edges;  // Edges adjacent to this vertex
	std::vector<Triangle *> triangles;  // Triangles adjacent to this vertex

	void compute_normal();

	Vertex();
	~Vertex();
private:
};

#endif
