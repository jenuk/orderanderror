#include <iostream>
#include "header/image.h"

int main(){
    Image img(200, 200);
    img.drawCircleFilled(100, 100, 80, {0, 0, 0});

    img.write(std::cout);

    return 0;
}
