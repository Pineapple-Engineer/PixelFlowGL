#ifndef FACE_H
#define FACE_H

using ll = unsigned long long;

class Face {
public:
    ll idx1;
    ll idx2;
    ll idx3;

    Face(ll pIdx1, ll pIdx2, ll pIdx3)
        : idx1(pIdx1), idx2(pIdx2), idx3(pIdx3) {}
};

#endif