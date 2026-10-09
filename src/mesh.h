#ifndef _MESH_H_
#define _MESH_H_

#include <glm/glm.hpp>
#include <vector>

class Vertex;
class Edge;
class Triangle;

// Stores a triangle mesh
class Mesh
{
public:
	std::vector<Vertex *> vertices;  // Mesh vertices
	std::vector<Edge *> edges;  // Mesh edges
	std::vector<Triangle *> triangles;  // Mesh triangles
	
	float radius;  // Radius of bounding sphere
	glm::vec3 centroid;  // Centroid of mesh
	
	glm::mat4 model;  // Model matrix

	void compute_properties();

	// Constructs a mesh from a file
	Mesh(const char *file);

	~Mesh();
private:
};

#endif
