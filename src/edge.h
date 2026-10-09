#ifndef _EDGE_H_
#define _EDGE_H_

#include <glm/glm.hpp>
#include <array>

class Triangle;
class Vertex;

// Represents an edge in a mesh
class Edge
{
public:
	size_t index;  // Index of this edge in Mesh::edges

	std::array<Vertex *, 2> vertices;  // This edge's vertices
	std::array<Triangle *, 2> triangles;  // Triangles adjacent to this edge

	Edge();
	~Edge();
private:
};

#endif
