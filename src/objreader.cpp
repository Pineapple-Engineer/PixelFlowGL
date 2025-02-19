#include "../include/objreader.h"

void getVertex(std::vector<Vertex>& vertices, std::stringstream& ss) {
    // std::cout << "[INFO] Creating a new Vertex...\n";
    float x, y, z;
    ss >> x;
    ss >> y;
    ss >> z;
    vertices.push_back(Vertex(x, y, z));
}

void getFace(std::list<Face>& faces, std::stringstream& ss) {
    // std::cout << "[INFO] Creating a new Face...\n";
    ll idx1, idx2, idx3;
    ss >> idx1;
    ss >> idx2;
    ss >> idx3;
    --idx1; --idx2; --idx3;
    faces.push_back(Face(idx1, idx2, idx3));
}

bool readObj(std::list<Model>& models) {
    std::ifstream file("models/Man_Mesh.obj", std::ios::in);
    if(file.fail()) {
        std::cout << "[ERROR] Couldn't open the file\n";
        return false;
    }

    std::string line;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type;
        ss >> type; // Read the first token (o, v, f)

        if(type == "o") {
            // std::cout << "[INFO] Creating a new Model...\n";
            models.push_back(Model());
        } else if(type == "v") {
            getVertex(models.back().vertices, ss);
        } else if(type == "f") {
            getFace(models.back().faces, ss);
        }
    }

    file.close();
    return true;
}