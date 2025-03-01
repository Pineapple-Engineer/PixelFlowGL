#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <list>
#include "vertex.h"
#include "face.h"

class Model {
public:
    std::vector<Vertex> vertices;
    std::list<Face> faces;
    Vertex c;

    Model(): c(0.0f, 0.0f, 0.0f) {}
};

#endif