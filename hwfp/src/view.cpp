#include "view.h"


const int num_of_rows = 15;
const int num_of_cols = 15;

View::View(Model const& model)
    : model_(model),
    background(initial_window_dimensions(), {255, 253, 208, 255})
{
    for(char cc = 'A'; cc <= 'Z'; cc++){
        letters[cc] = ge211::Text_sprite::Builder(tile_font)
                .message(std::string(1,cc))
                .color(ge211::Color::black())
                .build();
        points[cc] = ge211::Text_sprite::Builder(point_font)
                .message(std::to_string(Tile::value(cc)))
                .color(ge211::Color::black())
                .build();
    }

}



ge211::Dimensions View::initial_window_dimensions() const {
    return {margin_ + num_of_cols * (space_side_length_ + margin_),
            margin_ + num_of_rows * (space_side_length_ + margin_)};
}

void View::draw(ge211::Sprite_set &set) {
    set.add_sprite(background, {0,0}, -10);

    for(const std::shared_ptr<Space>& sp : model_.board_) {
        ge211::Position space_pos = board_loc_to_pos(sp->row, sp->col);
        if(sp->bonus == Space::Bonuses::DoubleWord)
            set.add_sprite(dw_space, space_pos, 0);
        else if (sp->bonus == Space::Bonuses::DoubleLetter)
            set.add_sprite(dl_space, space_pos, 0);
        else if (sp->bonus == Space::Bonuses::TripleWord)
            set.add_sprite(tw_space, space_pos, 0);
        else if (sp->bonus == Space::Bonuses::TripleLetter)
            set.add_sprite(tl_space, space_pos, 0);
        else
            set.add_sprite(plain_space, space_pos, 0);
        if(sp->tile != nullptr){
            const char sp_let = sp->tile->letter;
            set.add_sprite(tile_sprite, space_pos.down_right_by({1, 1}),9);
            set.add_sprite(letters[sp_let],
                    space_pos.down_right_by(letter_offset_),
                    10);
            set.add_sprite(points[sp_let],
                    space_pos.down_right_by(point_offset_),
                    10);
        }
    }
    set.add_sprite(center_star,
            board_loc_to_pos(model_.board_.centerSpace->row, model_.board_.centerSpace->col),
            1);

}

std::string View::initial_window_title() const {
    return "Words without Friends";
}

ge211::Position View::board_loc_to_pos(int row, int col) {
    return ge211::geometry::Position(margin_ + col * (space_side_length_ + margin_),
                                     margin_ + row * (space_side_length_ + margin_));
}


