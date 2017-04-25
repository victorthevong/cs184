#include "Plane.h"
#include "math.h"

Plane::Plane() {

	vertices = std::vector<glm::dvec3>();

}

Plane::Plane(const vector<glm::dvec3> &v) {
	vertices = std::vector<glm::dvec3>();

	for(glm::dvec3 vec : v){
		vertices.push_back(vec);
	}

}

bool Plane::intersect(dvec3 vec) {

	//return  vertices[1] dot (vec - vertices[0]) <= 0

}