#include <iostream>
#include "header/image.h"

int main(){
    Image img(20, 20);
    img.drawLine(2, 1, 8, 18, {0, 0, 0});
    img.drawLine(5, 5, 18, 8, {0, 0, 0});

    img.write(std::cout);

    return 0;
}
