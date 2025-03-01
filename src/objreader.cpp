#include "../include/objreader.h"

namespace objr {

void getObjVertex(std::vector<Vertex>& vertices, std::stringstream& ss) {
    float coordX, coordY, coordZ;
    ss >> coordX;
    ss >> coordY;
    ss >> coordZ;
    vertices.push_back(Vertex(coordX, coordY, coordZ));
}

void getObjFace(std::list<Face>& faces, std::stringstream& ss) {
    int index1, index2, index3;
    ss >> index1;
    ss >> index2;
    ss >> index3;
    --index1; --index2; --index3;
    faces.push_back(Face(index1, index2, index3));
}

bool readObj(std::list<Model>& models) {
    std::ifstream file("../models/Orbital.obj", std::ios::in);
    if(file.fail()) {
        cout << "[ERROR] Couldn't open the file\n";
        return false;
    }

    std::string line;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type;
        ss >> type; // Read the first token (o, v, f)

        if(type == "o") {
            models.push_back(Model());
        } 
        else if(type == "v") {
            getObjVertex(models.back().vertices, ss);
        } 
        else if(type == "f") {
            getObjFace(models.back().faces, ss);
        }
    }

    file.close();
    return true;
}

}