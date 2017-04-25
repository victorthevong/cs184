#ifndef PLANE_H
#define PLANE_H

#include "glm/glm.hpp"
#include <vector>
#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif

class Plane {
public:
    Plane();
    double intersect();

private:
    glm::dvec3 center;
    glm::dvec3 normal;
    glm::dvec3 botleftcorner;
    glm::dvec3 topleftcorner;
    glm::dvec3 botrightcorner;
    glm::dvec3 toprightcorner;
    
};

#endif /* PLANE_H */