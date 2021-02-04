#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <deque>

typedef std::array<uint8_t, 3> Pixel;

class Image {
    public:
        Image(int width, int height);

        Pixel& operator()(int x, int y);
        const Pixel& operator()(int x, int y) const;
        uint8_t& operator()(int x, int y, int c);
        const uint8_t& operator()(int x, int y, int c) const;

        void write(std::ostream& out) const;
        void write(std::string filename) const;

        void setPixel(int x, int y, Pixel px);
        void drawLine(int x0, int y0, int x1, int y1, Pixel color);
        void drawCircle(int x0, int y0, int r, Pixel color);
        void drawCircleFilled(int x0, int y0, int r, Pixel color);
        void fill(int x, int y, Pixel color);


    private:
        const int width;
        const int height;
        std::vector<Pixel> data;

        void drawLineVertical(int x, int y0, int y1, Pixel color);
        void drawLineHorizontal(int x0, int x1, int y, Pixel color);
        void drawLineLow(int x0, int y0, int x1, int y1, Pixel color);
        void drawLineHigh(int x0, int y0, int x1, int y1, Pixel color);
};
