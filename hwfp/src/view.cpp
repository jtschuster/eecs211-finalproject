#include "view.h"

const int num_of_rows = 15;
const int num_of_cols = 15;

View::View(Model const& model)
    : model_(model),
    background(initial_window_dimensions(), {255, 253, 208, 255})
{

}



ge211::Dimensions View::initial_window_dimensions() const {
    return {margin_ + num_of_cols * (tile_side_length_ + margin_),
            margin_ + num_of_rows * (tile_side_length_ + margin_)};
}

void View::draw(ge211::Sprite_set &set) {
    set.add_sprite(background, {0,0}, -10);

}

std::string View::initial_window_title() const {
    return "Words without Friends";
}


