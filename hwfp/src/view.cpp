#include "view.h"


const int num_of_rows = 15;
const int num_of_cols = 15;

View::View(Model& model)
    : model_(model),
    background(initial_window_dimensions(), {255, 253, 208, 255}),
    rack(rack_dims_, {121, 45, 6}),
    rack_offset_({0, initial_window_dimensions().height - (2 * margin_ + tile_side_length_)}),
    selected_tile_loc(-1)
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

    letters[' '] = ge211::Text_sprite::Builder(tile_font)
            .message(std::string(1, ' '))
            .color(ge211::Color::black())
            .build();

}



ge211::Dimensions View::initial_window_dimensions() const {
    return {margin_ + num_of_cols * (space_side_length_ + margin_),
            margin_ + num_of_rows * (space_side_length_ + margin_) +
                    (margin_ + rack_dims_.height)};

}

void View::draw(ge211::Sprite_set &set) {
    //Background
    set.add_sprite(background, {0, 0}, -10);
    set.add_sprite(rack, {0, rack_offset_.height}, -10);


    //Spaces
    set.add_sprite(center_star,
                   board_loc_to_pos(model_.board_.centerSpace->row, model_.board_.centerSpace->col),
                   1);

    for (const std::shared_ptr<Space> &sp : model_.board_) {
        ge211::Position space_pos = board_loc_to_pos(sp->row, sp->col);
        if (sp->bonus == Space::Bonuses::DoubleWord)
            set.add_sprite(dw_space, space_pos, 0);
        else if (sp->bonus == Space::Bonuses::DoubleLetter)
            set.add_sprite(dl_space, space_pos, 0);
        else if (sp->bonus == Space::Bonuses::TripleWord)
            set.add_sprite(tw_space, space_pos, 0);
        else if (sp->bonus == Space::Bonuses::TripleLetter)
            set.add_sprite(tl_space, space_pos, 0);
        else
            set.add_sprite(plain_space, space_pos, 0);


        //Drawing placed tiles
        if (sp->tile != nullptr) {
            const char sp_let = sp->tile->letter;
            set.add_sprite(tile_sprite, space_pos.down_right_by({1, 1}), 9);
            set.add_sprite(letters[sp_let],
                    space_pos.down_right_by(letter_offset_),
                    10);
            if (typeid(sp->tile) != typeid(BlankTile)) {
                set.add_sprite(points[sp_let],
                               space_pos.down_right_by(point_offset_),
                               10);
            } else {
                //yeet
            }
        }
    }


    Rack cur_rack = *model_.racks_.at(model_.currentPlayer).get();
    for(size_t i = 0; i < cur_rack.size(); i++){
        ge211::Position rack_loc_pos = rack_loc_to_pos(i);
        const char t_let = cur_rack[i]->letter;
        if(i == selected_tile_loc)
            set.add_sprite(highlight, rack_loc_pos.up_left_by({1, 1}), 8);
        set.add_sprite(tile_sprite, rack_loc_pos, 9);
        set.add_sprite(letters[t_let],
                       rack_loc_pos.down_right_by(letter_offset_),
                       10);
        if (t_let != ' ') {
            set.add_sprite(points[t_let],
                           rack_loc_pos.down_right_by(point_offset_),
                           10);
        } else {
            auto y = 9 + 1;
            //yeet
        }
    }

}

std::string View::initial_window_title() const {
    return "Words without Friends";
}

ge211::Position View::board_loc_to_pos(int row, int col) {
    return {margin_ + col * (space_side_length_ + margin_),
            margin_ + row * (space_side_length_ + margin_)};
}

ge211::Position View::rack_loc_to_pos(int ind) {
    return ge211::Position(margin_ + ind * (space_side_length_), margin_).down_right_by(rack_offset_);
}

void View::select_tile(int i) {
    if(i < model_.racks_.at(model_.currentPlayer)->size())
        selected_tile_loc = i;
    else
        selected_tile_loc = -1;
}

void View::move_tile(ge211::Position pos) {
    if(pos.x <= num_of_cols && pos.y <= num_of_rows)
        if(model_.placeTile(model_.racks_.at(model_.currentPlayer)->removeTile(selected_tile_loc),
                pos.y, pos.x))
            selected_tile_loc = -1;

}


