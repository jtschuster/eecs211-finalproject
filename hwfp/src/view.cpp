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

    for(const std::shared_ptr<Space>& sp : model_.board_) {
        set.add_sprite(plain_tile, board_loc_to_pos(sp->row, sp->col), 0);
        if(sp->tile != nullptr){
            set.add_sprite(r,
                    board_loc_to_pos(sp->row, sp->col),
                    10);
        }
    }
    set.add_sprite(center_tile,
            board_loc_to_pos(model_.board_.centerSpace->row, model_.board_.centerSpace->col),
            1);

}

std::string View::initial_window_title() const {
    return "Words without Friends";
}

ge211::Position View::board_loc_to_pos(int row, int col) {
    return ge211::geometry::Position(margin_ + col * (tile_side_length_ + margin_),
                                     margin_ + row * (tile_side_length_ + margin_));
}


