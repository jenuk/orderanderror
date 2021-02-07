#include "image.h"

Image::Image(int width, int height) : width_(width), height_(height) {
    Pixel white = {255, 255, 255}; 
    this->data_ = std::vector<Pixel>(width*height, white);
}

void Image::write(std::string filename) const {
    std::ofstream file(filename);
    this->write(file);
    file.close();
}


void Image::write(std::ostream& out) const {
    out << "P6" << "\n";
    out << this->width_ << " " << this->height_ << "\n";
    out << 255 << "\n";

    for (int y=0; y<this->height_; ++y) {
        for (int x=0; x<this->width_; ++x) {
            for (int c=0; c<3; ++c){
                out << (char) (*this)(x, y, c);
            }
        }
    }

    out << std::endl;
}

const Pixel& Image::operator()(int x, int y) const {
    return this->data_[x + y*this->width_];
}

Pixel& Image::operator()(int x, int y) {
    return this->data_[x + y*this->width_];
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
    if ((0 <= x) and (x < this->width_)
            and (0 <= y) and (y < this->height_)){
        (*this)(x, y) = px;
    }
}


void Image::drawLineVertical(int x, int y0, int y1, Pixel color) {
    for (int y=y0; y<=y1; ++y) {
        this->setPixel(x, y, color);
    }
}


void Image::drawLineHorizontal(int x0, int x1, int y, Pixel color) {
    for (int x=x0; x<=x1; ++x) {
        this->setPixel(x, y, color);
    }
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


void Image::drawCircle(int x0, int y0, int r, Pixel color) {
    int x = 0;
    int y = r;
    int d = 1 - r;

    while (x <= y) {
        this->setPixel(x0 + x, y0 + y, color);
        this->setPixel(x0 - x, y0 + y, color);
        
        this->setPixel(x0 + x, y0 - y, color);
        this->setPixel(x0 - x, y0 - y, color);

        this->setPixel(x0 + y, y0 + x, color);
        this->setPixel(x0 - y, y0 + x, color);
        
        this->setPixel(x0 + y, y0 - x, color);
        this->setPixel(x0 - y, y0 - x, color);

        if (d < 0) {
            d += 2*x + 3;
            ++x;
        } else {
            d += 2*x - 2*y + 5;
            ++x;
            --y;
        }
    }
}


void Image::drawCircleFilled(int x0, int y0, int r, Pixel color) {
    int x = 0;
    int y = r;
    int d = 1 - r;

    while (x <= y) {
        this->drawLineHorizontal(x0 - x, x0 + x, y0 + y, color);
        this->drawLineHorizontal(x0 - x, x0 + x, y0 - y, color);
        this->drawLineHorizontal(x0 - y, x0 + y, y0 + x, color);
        this->drawLineHorizontal(x0 - y, x0 + y, y0 - x, color);

        if (d < 0) {
            d += 2*x + 3;
            ++x;
        } else {
            d += 2*x - 2*y + 5;
            ++x;
            --y;
        }
    }
}


void Image::fill(int x, int y, Pixel color) {
    const Pixel empty = (*this)(x, y);
    std::deque<std::array<int, 2>> queue;
    queue.push_back({x, y});

    std::array<int, 2> current;
    while (queue.size() > 0) {
        current = queue.front();
        queue.pop_front();

        x = current[0];
        y = current[1];
        if ((*this)(x, y) == empty) {
            (*this)(x, y) = color;
            if ((x > 0) and ((*this)(x - 1, y) == empty)){
                queue.push_back({x - 1, y});
            }
            if ((x + 1 < this->width_) and ((*this)(x + 1, y) == empty))
                queue.push_back({x + 1, y});
            if ((y > 0) and ((*this)(x, y - 1) == empty))
                queue.push_back({x, y - 1});
            if ((y + 1 < this->height_) and ((*this)(x, y + 1) == empty))
                queue.push_back({x, y + 1});
        }
    }
}
