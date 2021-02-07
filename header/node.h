#ifndef NODE_H
#define NODE_H


#include <vector>
#include <cmath> // sqrt
#include <algorithm> // none_of

#include "image.h"

class Node {
    public:
        Node(int x, int y, int r);

        void addConnection(Node& other);

        double distance(const Node& other) const;

        void draw(Image& img) const;

        std::vector<Node*> adjacent_;
        std::vector<bool> visible_;

    private:
        int x_;
        int y_;
        int r_;
};

#endif
