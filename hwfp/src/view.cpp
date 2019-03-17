#include "view.h"


const int num_of_rows = 15;
const int num_of_cols = 15;

View::View(Model& model)
    : model_(model),
    background(initial_window_dimensions(), {255, 253, 208}),
    rack(rack_dims_, {121, 45, 6}),
    board_dims_({num_of_cols * (space_side_length_ + margin_),
                num_of_rows * (space_side_length_ + margin_)}),
    rack_offset_({0, initial_window_dimensions().height - (2 * margin_ + tile_side_length_)}),
    selected_tile_loc(-1),
    selected_tile_pos(ge211::Position(-1, -1))
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
        ge211::Position space_pos = board_loc_to_pos(sp->row, sp->col); // Raw position
        ge211::Position space_loc = ge211::Position(sp->col, sp->row); // Position adjusted to board rows and cols
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
            if(space_loc == selected_tile_pos)
                set.add_sprite(highlight, space_pos, 8);
            set.add_sprite(tile_sprite, space_pos.down_right_by({1, 1}), 9);
            set.add_sprite(letters[sp_let],
                    space_pos.down_right_by(letter_offset_),
                    10);
            if (sp->tile->t_value != 0) {
                set.add_sprite(points[sp_let],
                               space_pos.down_right_by(point_offset_),
                               10);
            } else if(awaiting_letter && space_loc == blank_pos)
                set.add_sprite(blank_pick, space_pos, 11);
        }
    }


    Rack cur_rack = *model_.racks_.at(model_.currentPlayer).get();
    for(int i = 0; i < cur_rack.size(); i++){
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
        }
    }

    // Current Player Indicator
    //set.add_sprite()

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

void View::clear_selection() {
    selected_tile_pos = {-1 , -1};
    selected_tile_loc = -1;
}

void View::select_tile(ge211::Position pos) {
    if(model_.board_.getTileAt(pos.y, pos.x) != nullptr && !model_.board_.getSpaceAt(pos.y, pos.x)->used) {
        clear_selection();
        selected_tile_pos = pos;
    } else
        clear_selection();
}

void View::select_tile(int i) {
    if(i < model_.racks_.at(model_.currentPlayer)->size() && i >= 0) {
        clear_selection();
        selected_tile_loc = i;
    } else {
        clear_selection();
    }
}

void View::move_tile(ge211::Position pos) {
    if(pos.x <= num_of_cols && pos.y <= num_of_rows) {
        if (selected_tile_loc != -1) { // Tile that is moving is on rack
            if(!model_.board_.getSpaceAt(pos.y, pos.x)->used) {
                std::shared_ptr<Tile> temp (model_.board_.remove_tile(pos.y, pos.x));
                if(temp != nullptr && temp->t_value == 0){ // blank tile reset
                    temp->letter = ' ';
                }
                if (model_.placeTile(model_.racks_.at(model_.currentPlayer)->removeTile(selected_tile_loc),
                                     pos.y, pos.x)) {
                    model_.racks_.at(model_.currentPlayer)->addTile(temp);
                    if(model_.board_.getTileAt(pos.y, pos.x)->t_value == 0)
                        designate_blank(pos);
                    clear_selection();
                }
            }
        } else {
            if(!model_.board_.getSpaceAt(pos.y, pos.x)->used) {
                model_.board_.swap_tiles(selected_tile_pos, pos);
            }
            clear_selection();
        }
    }
}

void View::move_tile(int i) {
    auto cur_rack = model_.racks_.at(model_.currentPlayer);
    if(i >= cur_rack->size() && i < 7 && i >= 0) {
        cur_rack->addTile(
                model_.board_.remove_tile(selected_tile_pos.y, selected_tile_pos.x));
        if(cur_rack->back()->t_value == 0)
            cur_rack->back()->letter = ' ';
    }

    clear_selection();
}


void View::designate_blank(ge211::Position bpos) {
    awaiting_letter = true;
    blank_pos = bpos;
}

void View::choose_blank(char let) {
    awaiting_letter = false;
    model_.board_.getTileAt(blank_pos.y, blank_pos.x)->letter = let;
    blank_pos = {-1, -1};
}

