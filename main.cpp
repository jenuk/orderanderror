#include <iostream>

#include "image.h"
#include "graph.h"

int main(){
    int width = 1000, height = 1000;
    Image img(width, height);

    Graph g(width, height);
    for (int i=0; i<400; ++i) {
        g.addNode();
    }
    g.makeConnections();
    g.visit(20, 60);

    g.draw(img);

    img.write("imgs/image.ppm");

    return 0;
}
