#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:
    float x;
    float y;
    float z;

    Vertex(float px, float py, float pz)
        : x(px), y(py), z(pz) {}
};

#endif