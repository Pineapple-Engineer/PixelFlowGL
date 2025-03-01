#ifndef FACE_H
#define FACE_H

class Face {
public:
    int index1, index2, index3;

    Face(int pIndex1, int pIndex2, int pIndex3)
        : index1(pIndex1), index2(pIndex2), index3(pIndex3) {}
};

#endif