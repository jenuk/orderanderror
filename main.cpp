#include <iostream>

#include "header/image.h"
#include "header/graph.h"

int main(){
    int width = 500, height = 500;
    Image img(width, height);

    Graph g(width, height);
    for (int i=0; i<100; ++i) {
        g.addNode();
    }
    g.makeConnections();

    g.draw(img);

    img.write(std::cout);

    return 0;
}
