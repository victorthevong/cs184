#include <vector>
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif
typedef glm::dvec3 dvec3;
typedef std::string string;
typedef std::vector<dvec3> PointVec;
struct Polygon {
	int p0; // List of indices into vertex array.
	int p1;
	int p2;
};
typedef std::vector<Polygon> PolyVec;
class Parser {
	public:
		Parser();
		void parse(string fp); // Parse given obj file into vectors
		void render();
		PolyVec polys;
		PointVec vertices;
		
	private: 
		int num_vertices;
		int num_polygons;
};