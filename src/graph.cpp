#include "graph.h"

Graph::Graph(int width, int height) : width_(width), height_(height), nodes_() {
    std::random_device rd;
    unsigned seed = rd();
    this->rng_ = std::mt19937(seed);
}

void Graph::addNode(int x, int y, int r) {
    this->nodes_.push_back(Node(x, y, r));
}

void Graph::addNode(int x, int y) {
    std::uniform_int_distribution<int> dist_r(5, 13);
    this->addNode(x, y, dist_r(this->rng_));
}

void Graph::addNode() {
    std::uniform_int_distribution<int> dist_x(10, this->width_-10);
    std::uniform_int_distribution<int> dist_y(10, this->height_-10);
    std::uniform_int_distribution<int> dist_r(5, 13);
    this->addNode(dist_x(this->rng_), dist_y(this->rng_), dist_r(this->rng_));
}

void Graph::makeConnections() {
    int n = this->nodes_.size();
    std::vector<std::vector<double>> dist_mat(n, std::vector<double>(n, 0.0));
    std::vector<int> inds(n);
    std::iota(std::begin(inds), std::end(inds), 0);
    std::vector<std::vector<int>> smallest(n, inds);

    for (int i = 0; i < n; ++i) {
        for (int j=i+1; j < n; ++j) {
            dist_mat[i][j] = this->nodes_[i].distance(this->nodes_[j]);
            dist_mat[j][i] = dist_mat[i][j];
        }
        
        std::sort(std::begin(smallest[i]), std::end(smallest[i]),
                [&dist_mat, &i](int x, int y) -> bool {
                    return dist_mat[i][x] < dist_mat[i][y];
                });
    }

    std::uniform_int_distribution<int> dice(0, 10);
    for (int i=0; i < n; ++i) {
        std::vector<int> choosen = {};
        choosen = {1,2,3,4,5};
        //while (choosen.size() < 3) {
        //    int cand = dice(this->rng_);
        //    if (std::none_of(choosen.begin(), choosen.end(),
        //                [&cand](int x) -> bool {return cand == x;})) {
        //        choosen.push_back(cand);
        //    }
        //}
        for (auto ind : choosen) {
            this->nodes_[i].addConnection(this->nodes_[smallest[i][ind]]);
        }
    }
}

void Graph::draw(Image& img) {
    for (auto node : this->nodes_) {
        node.draw(img);
    }
    

    std::uniform_real_distribution<float> dist_real(0.5f, 0.8f);
    float s = dist_real(this->rng_);
    dist_real = std::uniform_real_distribution<float>(0.6f, 0.9f);
    float v = dist_real(this->rng_);
    dist_real = std::uniform_real_distribution<float>(0.0f, 360.0f);
    std::uniform_real_distribution<float> dist_jitter(-0.2f, 0.2f);
    //std::uniform_int_distribution<uint8_t> dist_color(0, 255);
    int h = 20;

    img.fill(0, 0, {255*v, 255*v, 255*v});

    Pixel color;
    Pixel empty = {255, 255, 255};
    for (int y=0; y<this->height_; ++y) {
        for (int x=0; x<this->width_; ++x) {
            if (img(x, y) == empty) {
                color = hsv_to_rgb(h, //dist_real(this->rng_),
                        s + dist_jitter(this->rng_),
                        v + dist_jitter(this->rng_));
                h = (h + 1) % 360;
                //color = {dist_color(this->rng_),
                //    dist_color(this->rng_),
                //    dist_color(this->rng_)};
                img.fill(x, y, color);
            }
        }
    }
}


void Graph::visit(unsigned num_steps, unsigned duration_step) {
    std::uniform_int_distribution<int> dist(0,0);
    Node* current = nullptr;
    int ind;

    for (unsigned k=0; k < num_steps; ++k) {
        dist = std::uniform_int_distribution<int>(0, this->nodes_.size()-1);
        current = &(this->nodes_[dist(this->rng_)]);

        for (unsigned l=0; l < duration_step; ++l) {
            dist = std::uniform_int_distribution<int>(0, current->adjacent_.size()-1);
            ind = dist(this->rng_);
            current->visible_[ind] = true;
            current = current->adjacent_[ind];
        }
    }
}
