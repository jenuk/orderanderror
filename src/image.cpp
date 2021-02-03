#include "../header/image.h"

Image::Image(int width, int height) : width(width), height(height) {
    Pixel white = {255, 255, 255}; 
    this->data = std::vector<Pixel>(width*height, white);
}

void Image::write(std::string filename) const {
    std::ofstream file(filename);
    this->write(file);
    file.close();
}


void Image::write(std::ostream& out) const {
    out << "P6" << "\n";
    out << this->width << " " << this->height << "\n";
    out << 255 << "\n";

    for (int y=0; y<this->height; ++y) {
        for (int x=0; x<this->width; ++x) {
            for (int c=0; c<3; ++c){
                out << (char) (*this)(x, y, c);
            }
        }
    }

    out << std::endl;
}

const Pixel& Image::operator()(int x, int y) const {
    return this->data[x + y*this->width];
}

Pixel& Image::operator()(int x, int y) {
    return this->data[x + y*this->width];
}


const uint8_t& Image::operator()(int x, int y, int c) const{
    // test values
    return (*this)(x, y)[c];
}

uint8_t& Image::operator()(int x, int y, int c) {
    // test values
    return (*this)(x, y)[c];
}


void Image::setPixel(int x, int y, Pixel px) { 
    // test values
    (*this)(x, y) = px;
}


void Image::drawLineLow(int x0, int y0, int x1, int y1, Pixel color) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int dir_y = 1;
    if (dy < 0) {
        dir_y = -1;
        dy = -dy;
    }

    int D = 2*dy - dx;
    
    for (int x = x0, y = y0; x <= x1; ++x){
        this->setPixel(x, y, color);
        if (D > 0) {
            D -= 2*dx;
            y += dir_y;
        }
        D += 2*dy;
    }
}


void Image::drawLineHigh(int x0, int y0, int x1, int y1, Pixel color) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int dir_x = 1;
    if (dx < 0) {
        dir_x = -1;
        dx = -dx;
    }

    int D = 2*dx - dy;
    
    for (int x = x0, y = y0; y <= y1; ++y){
        this->setPixel(x, y, color);
        if (D > 0) {
            D -= 2*dy;
            x += dir_x;
        }
        D += 2*dx;
    }
}



void Image::drawLine(int x0, int y0, int x1, int y1, Pixel color) {
    // test in range
    int dx = x1 - x0;
    int dy = y1 - y0;
    dx = (dx > 0) ? dx : -dx;
    dy = (dy > 0) ? dy : -dy;

    if (dy < dx) {
        if (x0 < x1) {
            this->drawLineLow(x0, y0, x1, y1, color);
        }
        else {
            this->drawLineLow(x1, y1, x0, y0, color);
        }
    }
    else {
        if (y0 < y1) {
            this->drawLineHigh(x0, y0, x1, y1, color);
        }
        else {
            this->drawLineHigh(x1, y1, x0, y0, color);
        } 
    }
}
