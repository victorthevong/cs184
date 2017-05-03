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
#include "Parser.h"

const double GRAV_CONST = .0000001; // Gravitational constant
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
                par.x = glm::dvec3((x+0.5-nx*0.5)*d, (y+10)*d-1.0, (z+0.5-nz*0.5)*d);
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
    glColor4f(0.2, 0.5, 0.8, 1);
    glColorMaterial(GL_FRONT, GL_SPECULAR);
    glColor4f(0.9, 0.9, 0.9, 1);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.2, 0.5, 0.8, 1);
    
    for(const Particle &par : particles)
    {    
        
        glPushMatrix();
        glTranslatef(par.x.x, par.x.y, par.x.z);
        glutSolidSphere(PARTICLE_RAD, 10, 10);
        glPopMatrix();
    }
    
    glPopAttrib();
}

void Particles::step(std::vector<Polygon> polys, std::vector<glm::dvec3> verts) {

    //Plane test_plane = Plane(points);
    for (Particle &par : particles) { 
        // Add in gravitational force
        par.forces[1] -= GRAV_CONST*par.mass;
    }

    for (Particle &par : particles) {
        par.v += (1.0 / par.mass) * par.forces * render_step; 
        par.x_approx = par.x + (par.v * render_step);
    }
    // Collision Check
    for (Particle &par : particles) {
        
        for (Polygon poly : polys) {

            dvec3 origin = par.x;
            dvec3 dir = par.x_approx - par.x;

            dvec3 a, b, c;

            a = verts[poly.p0];
            b = verts[poly.p1];
            c = verts[poly.p2];

            dvec3 e1 = b - a;
            dvec3 e2 = c - a;
            dvec3 s0 = origin - a;
            dvec3 s1 = cross(dir, e2);
            dvec3 s2 = cross(s0, e1);

            dvec3 solution = dvec3(dot(s2, e2), dot(s1, s0), dot(s2, dir));

            solution /= dot(s1, e1);

            double t = solution[0];
            double b1 = solution[1];
            double b2 = solution[2];
            bool isvalid = ((b1 >= 0) && (b2 >= 0) && (b1 + b2 < 1));

            dvec3 intersect_pt = origin + (dir*t);
            double delta = length(par.x_approx - origin) - length(intersect_pt - origin);

            if (isvalid && delta > 0) {
                par.x_approx = intersect_pt;
            } 

        }

        par.x = par.x_approx;
        
    }

}

// void Particle::intersect(Parser parser) {

//     for (Polygon poly: parser.polys) {

//     }

// }

// bool Particle::intersect_helper(dvec3 origin, dvec3 dir) {
    
// }

// }





