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

};
