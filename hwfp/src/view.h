#pragma once

#include "model.h"


class View
{
public:
    explicit View(Model const&);

    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

private:
    Model const& model_;

    const int tile_side_length_ = 35;
    const int margin_ = 2;

    ge211::Rectangle_sprite background;

    ge211::Rectangle_sprite plain_tile {{tile_side_length_,tile_side_length_}, {234, 219, 179}};
    ge211::Rectangle_sprite center_tile {{tile_side_length_,tile_side_length_}, {255, 0, 0, 255}};

    ge211::Text_sprite r {std::string(1,'R'), {"sans.ttf", 16}};

    ge211::Position board_loc_to_pos(int row, int col);

};

