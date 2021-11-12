#include <iostream>
#include <string>
#include <vector>

#include "image.h"
#include "graph.h"

int main(int argc, char* argv[]){
    // default values
    int width = 1000, height = 1000;
    int num_starts = 30;
    int num_steps = 60;
    int distance = 33;
    int num_nodes = 400;
    bool random_layout = false;
    std::string filename("imgs/image");

    // handle command line arguments
    std::vector<std::string> args(argv, argv+argc);
    for (int i=1; i < argc; i++) {
        if (args[i] == "--help") {
            std::cout << args[0] << " "
                << "[--random_layout] "
                << "[-w WIDTH] "
                << "[-h HEIGHT] "
                << "[--starts NUMBER_OF_STARTPOINTS] "
                << "[--steps NUMBER_OF_STEPS] "
                << "[--distance DISTACE_BETWEEN_NODES] "
                << "[--num_nodes NUMBER_OF_NODES] "
                << "[-f FILENAME]" << "\n\n";

            std::cout << "random_layout produces NUMBER_OF_NODES many "
                << "random grid points anywhere on the image. "
                << "In this mode --distance has no effect." << "\n\n";

            std::cout << "--distance is the distance in pixels between two "
                << "points in the ordered version of this graph." << std::endl;
            return 0;
        }
        else if (args[i] == "--random_layout") {
            random_layout = true;
        }
        else if (i + 1 != argc) {
            if (args[i] == "-w") {
                width = std::stoi(args[i+1]);
                i++;
            }
            else if (args[i] == "-h") {
                height = std::stoi(args[i+1]);
                i++;
            }
            else if (args[i] == "--starts") {
                num_starts = std::stoi(args[i+1]);
                i++;
            }
            else if (args[i] == "--steps") {
                num_steps = std::stoi(args[i+1]);
                i++;
            }
            else if (args[i] == "--distance") {
                distance = std::stoi(args[i+1]);
                i++;
            }
            else if (args[i] == "--num_nodes") {
                random_layout = true;
                num_nodes = std::stoi(args[i+1]);
                i++;
            }
            else if (args[i] == "-f") {
                filename = args[i+1];
                i++;
            }
        }
    }

    Image img(width, height);
    Graph g(width, height);

    if (random_layout) {
        for (int i=0; i<num_nodes; ++i) {
            g.addNode();
        }
    }
    else {
        for (int x=10; x < width-10; x+=distance) {
            for (int y=10; y < height-10; y+=distance) {
                g.addNode(x, y);
            }
        }
    }
    g.makeConnections();
    g.visit(num_starts, num_steps);

    g.draw(img);

    img.write(filename + ".ppm");

    return 0;
}
