#ifndef OBJREADER_H
#define OBJREADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "model.h"

void getVertex(std::list<Vertex>& vertices, std::stringstream& ss);
void getFace(std::list<Face>& faces, std::stringstream& ss);
bool readObj(std::list<Model>& models);

#endif