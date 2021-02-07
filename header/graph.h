#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <random>
#include <numeric> // iota
#include <algorithm> //sort, none_of

#include "node.h"
#include "image.h"

class Graph {
    public:
        Graph(int width, int height);

        void addNode();
        void addNode(int x, int y);
        void addNode(int x, int y, int r);

        void makeConnections();

        void draw(Image& img) const;

    private:
        const int width_;
        const int height_;

        std::vector<Node> nodes_;
        std::mt19937 rng_;
};

#endif
