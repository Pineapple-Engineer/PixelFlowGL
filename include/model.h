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

    Model() = default;
};

#endif