#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
public:
    float x, y, z;

    Vertex(float coordX, float coordY, float coordZ)
        : x(coordX), y(coordY), z(coordZ) {}
};

#endif