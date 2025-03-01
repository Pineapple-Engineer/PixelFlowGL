#ifndef OBJREADER_H
#define OBJREADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "model.h"
using std::cout;

namespace objr {

void getObjVertex(std::list<Vertex>& vertices, std::stringstream& ss);
void getObjFace(std::list<Face>& faces, std::stringstream& ss);
bool readObj(std::list<Model>& models);

}

#endif