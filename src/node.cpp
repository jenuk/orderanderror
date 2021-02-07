#include "../header/node.h"

Node::Node(int x, int y, int r) : x_(x), y_(y), r_(r), adjacent_() {}

void Node::draw(Image& img) const {
    img.drawCircle(this->x_, this->y_, this->r_, {0, 0, 0});

    for (auto node_ptr : this->adjacent_) {
        img.drawLine(this->x_, this->y_, node_ptr->x_, node_ptr->y_, {0, 0, 0});
    }
}

double Node::distance(const Node& other) const{
    int dx = this->x_ - other.x_;
    int dy = this->y_ - other.y_;
    return std::sqrt(dx*dx + dy*dy);
}


void Node::addConnection(Node& other) {
    if (std::none_of(this->adjacent_.begin(), this->adjacent_.end(),
                [&other](Node* third) {return &other == third;})) {
        this->adjacent_.push_back(&other);
        other.adjacent_.push_back(this);
    }
}
