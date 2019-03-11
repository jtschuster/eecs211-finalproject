#include "view.h"


View::View(Model const& model)
    : model_(model),
    background(initial_window_dimensions(), {255, 253, 208, 255})
{

}



ge211::Dimensions View::initial_window_dimensions() const {
    return {margin_ + model_.num_of_cols_ * (tile_side_length_ + margin_),
            margin_ + model_.num_of_rows_ * (tile_side_length_ + margin_)};
}

void View::draw(ge211::Sprite_set &set) {
    set.add_sprite(background, {0,0}, -10);

}

std::string View::initial_window_title() const {
    return "Words without Friends";
}


