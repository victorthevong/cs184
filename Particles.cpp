/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particles.cpp
 * Author: swl
 * 
 * Created on April 15, 2016, 12:16 PM
 */

#include "Particles.h"
#include "math.h"
#include <vector>
const double GRAV_CONST = .0000000000000001; // Gravitational constant
const double PARTICLE_RAD = 0.05;
const double VOLUME_DENSITY = .001; //In g / mm^3
const double render_step = 3;


Particles::Particles() 
{
    int nx = 10;
    int ny = 10;
    int nz = 10;
    float d = 0.1;
    
    // Mass = dW*dH*dD*rho /(W*H*D)
    double mass = (4.0 / 3.0) * M_PI * pow(PARTICLE_RAD, 3.0) * VOLUME_DENSITY / (nx*nz*ny);
    for(int x=0; x<nx; x++)
    {
        for(int y=0; y<ny; y++)
        {
            for(int z=0; z<nz; z++)
            {  
                Particle par;
                par.p = glm::dvec3((x+0.5-nx*0.5)*d, (y+0.5)*d-1.0, (z+0.5-nz*0.5)*d);
                par.forces = glm::dvec3(0, 0, 0);
                par.mass = mass;
                par.radius = PARTICLE_RAD;
                particles.push_back(par);
            }
        }
    }
}

void Particles::render() const
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0};
    glShadeModel (GL_SMOOTH);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glColor4f(0.2, 0.5, 0.8, .3);
    glColorMaterial(GL_FRONT, GL_SPECULAR);
    glColor4f(0.9, 0.9, 0.9, .3);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.2, 0.5, 0.8, .3);
    
    for(const Particle &par : particles)
    {    
        
        glPushMatrix();
        glTranslatef(par.p.x, par.p.y, par.p.z);
        glutSolidSphere(PARTICLE_RAD, 10, 10);
        glPopMatrix();
    }
    
    glPopAttrib();
}

void Particles::step() {

    //Plane test_plane = Plane(points);
    for (Particle &par : particles) { 
        // Add in gravitational force
        par.forces[1] -= GRAV_CONST*par.mass;
    }

    for (Particle &par : particles) {
        par.p += par.v * render_step;
        par.v += (1.0 / par.mass) * par.forces * render_step; 
    }
}

// void Particle::intersect(Parser parser) {

//     for (Polygon poly: parser.polys) {



//     }

// bool Particle::intersect_helper(dvec3 origin, dvec3 dir) {
    
// }

// }





