/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particles.h
 * Author: swl
 *
 * Created on April 15, 2016, 12:16 PM
 */

#ifndef PARTICLES_H
#define PARTICLES_H

#include "glm/glm.hpp"
#include <vector>
#include "Polygon.h"

#if defined(__APPLE_CC__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif

class Particles {
public:
    Particles();
    void render() const;
    void step(PolyVec polys, PointVec verts); // simulate one frame
private:
    struct Particle
    {
        // public:
        glm::dvec3 x;
        glm::dvec3 x_approx;
        glm::dvec3 v;
        glm::dvec3 forces;
        double mass;
        double radius;
        // void intersect(Parser parser);

        // private:
            // bool intersect_helper(dvec3 origin, dvec3 dir);
    };
    
    std::vector<Particle> particles;
};

#endif /* PARTICLES_H */

