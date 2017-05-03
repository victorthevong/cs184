#include "Parser.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
Parser::Parser() {
	this->num_vertices = 0;
	this->num_polygons = 0;
	this->polys = std::vector<Polygon>();
	this->vertices = std::vector<dvec3>();
	}


void Parser::parse(string fp) {
	std::ifstream infile(fp);
	string line;
	while (std::getline(infile, line)) { 
		if (line.c_str()[0] == 'v' and line.c_str()[1] == ' ') {
			double d1, d2, d3;
			string data = line.substr(1, line.length());
			std::istringstream iss(data);
			iss >> d1;
			iss >> d2;
			iss >> d3;
			vertices.push_back(dvec3(d1, d2, d3));
			num_vertices += 1;

		} else if (line.c_str()[0] == 'f') { 
			int f1, f2, f3;
			string delimiter1 = "//";
			string delimiter2 = " ";
  			string data = line.substr(2, line.length());

  			string token;
  			int pos;

  			pos = data.find(delimiter1);
  			token = data.substr(0, pos);
  			f1 = std::stoi(token) - 1;
  			data.erase(0, pos + delimiter1.length());

  			pos = data.find(delimiter2);
  			data.erase(0, pos + delimiter2.length());

  			pos = data.find(delimiter1);
  			token = data.substr(0, pos);
  			f2 = std::stoi(token) - 1;
  			data.erase(0, pos + delimiter1.length());

  			pos = data.find(delimiter2);
  			data.erase(0, pos + delimiter2.length());

  			pos = data.find(delimiter1);
  			token = data.substr(0, pos);
  			f3 = std::stoi(token) - 1;
  			data.erase(0, pos + delimiter1.length());
  			Polygon face = {f1, f2, f3};
  			polys.push_back(face);
  			num_polygons += 1;
		}
	}
}
void Parser::render() {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < num_polygons; i++) {
		Polygon p = polys[i];
		dvec3 v0 = vertices[p.p0];
		dvec3 v1 = vertices[p.p1];
		dvec3 v2 = vertices[p.p2];
		glVertex3d(v0[0], v0[1], v0[2]);
		glVertex3d(v1[0], v1[1], v1[2]);
		glVertex3d(v2[0], v2[1], v2[2]);	
	}
	glEnd();
}

// Compute barycentric coordinates (u, v, w) for poly triangle
// point testpoint with respect to triangle (a, b, c)

/*
Note that a decent number of values in point_in_triangle() are independent of
 testpoint—they can be cached with the triangle if necessary for speedup.
  assuming the number of triangles you have isnt overwhelming
*/

  /*
	bool Triangle::intersect(const Ray& r) const {
  
  // Part 1, Task 3: implement ray-triangle intersection
  Vector3D p0(mesh->positions[v1]), p1(mesh->positions[v2]), p2(mesh->positions[v3]);

  Vector3D e1 = p1 - p0;
  Vector3D e2 = p2 - p0;
  Vector3D s0 = r.o - p0;
  Vector3D s1 = cross(r.d, e2);
  Vector3D s2 = cross(s0, e1);

  Vector3D temp = Vector3D(dot(s2, e2), dot(s1, s0), dot(s2, r.d));

  temp /= dot(s1, e1);

  // temp(t, b1, b2) b3 = 1 - b1 - b2;

  if (temp.x < r.min_t || temp.x > r.max_t) {
    return false;
  } else {

    bool val = (temp.y >= 0) && (temp.z >= 0) && (temp.y + temp.z <= 1);

    if (val) {
      r.max_t = temp.x;
      return val;
    } else {
      return val;
    }

  }

}
  */

// dvec4 Polygon::intersect(dvec3 origin, dvec3 dir) {

// 	dvec3 a, b, c;

// 	a = vertices[p0];
// 	b = vertices[p1];
// 	c = vertices[p2];

// 	dvec3 e1 = b - a;
//   	dvec3 e2 = c - a;
//   	dvec3 s0 = origin - a;
//   	dvec3 s1 = cross(dir, e2);
//   	dvec3 s2 = cross(s0, e1);

//   	dvec3 solution = dvec3(dot(s2, e2), dot(s1, s0), dot(s2, dir));

//   	solution /= dot(s1, e1);

//   	double t = solution[0];
//   	double b1 = solution[1];
//   	double b2 = solution[2];
//   	bool isvalid = ((b1 >= 0) && (b2 >= 0) && (b1 + b2 < 1));

//   	if ()

//   	return dvec4(t,b1,b2,)

// }

// bool Polygon::point_in_triangle(Polygon poly, dvec3 testpoint){

// 	dvec3 a, b, c;

// 	a = vertices[poly.p0];
// 	b = vertices[poly.p1];
// 	c = vertices[poly.p2];

// 	dvec3 v0 = b - a, v1 = c - a, v2 = testpoint - a;

//     float d00 = dot(v0, v0);
//     float d01 = dot(v0, v1);
//     float d11 = dot(v1, v1);
//     float d20 = dot(v2, v0);
//     float d21 = dot(v2, v1);
//     float denom = d00 * d11 - d01 * d01;

//     float v = (d11 * d20 - d01 * d21) / denom;
//     float w = (d00 * d21 - d01 * d20) / denom;
//     float u = 1.0f - v - w;

//     // Check if point is in triangle
// 	return (v >= 0) && (w >= 0) && (v + w < 1);
// }
