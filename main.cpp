#include <iostream>

#include "image.h"
#include "graph.h"

int main(){
    int width = 1000, height = 1000;
    Image img(width, height);

    Graph g(width, height);
    //for (int i=0; i<400; ++i) {
    //    g.addNode();
    //}
    for (int x=0; x < 29; ++x) {
        for (int y=0; y < 29; ++y) {
            g.addNode(x*33+10, y*33+10);
        }
    }
    g.makeConnections();
    g.visit(30, 60);

    g.draw(img);

    img.write("imgs/image.ppm");

    return 0;
}
