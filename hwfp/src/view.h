#pragma once

#include "model.h"


class View
{

    friend class Controller;

public:
    explicit View(Model&);

    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    void select_tile(int);
    void select_tile(ge211::Position);
    void move_tile(ge211::Position);
    void move_tile(int);

    void designate_blank(ge211::Position bpos);
    void choose_blank(char let);

    void end_game();
    const bool game_over = false;

private:
    Model& model_;

    const int space_side_length_ = 35;
    const int tile_side_length_ = space_side_length_ - 2;

    const int margin_ = 2;
    const ge211::Dimensions letter_offset_ = {4, -2};
    const ge211::Dimensions point_offset_ = {19, 18};
    const ge211::Dimensions space_dims_ = {space_side_length_,space_side_length_};
    const ge211::Dimensions board_dims_;
    const ge211::Dimensions endgame_offset_ = 5 * space_dims_;

    ge211::Rectangle_sprite background;

    const ge211::Dimensions rack_dims_ = {margin_ + (tile_side_length_ + margin_) * 7,
                                          2 * margin_ + tile_side_length_};
    const ge211::Dimensions rack_offset_;
    ge211::Rectangle_sprite rack;
    int selected_tile_loc;
    ge211::Position selected_tile_pos;

    void clear_selection();

    ge211::Font tile_font {"RobotoMono-Regular.ttf", 26};
    ge211::Font point_font {"RobotoMono-Regular.ttf", 12};
    ge211::Font poppins_font {"Poppins-Regular.ttf", 18};

    bool awaiting_letter = false;
    ge211::Position blank_pos = {-1,-1};

    ge211::Rectangle_sprite plain_space {space_dims_, {234, 219, 179}};
    ge211::Rectangle_sprite dw_space {space_dims_, {246, 179, 176}};
    ge211::Rectangle_sprite tw_space {space_dims_, {232, 58, 48}};
    ge211::Rectangle_sprite dl_space {space_dims_, {183, 212, 240}};
    ge211::Rectangle_sprite tl_space {space_dims_, {43, 130, 212}};


    ge211::Image_sprite center_star {"star.png"};
    ge211::Rectangle_sprite tile_sprite {{tile_side_length_, tile_side_length_}, {255, 255, 240}};
    ge211::Rectangle_sprite highlight {{tile_side_length_ + 2, tile_side_length_ + 2}, {255, 198, 26}};
    ge211::Rectangle_sprite blank_pick {space_dims_, {66, 240, 66, 128}};

    ge211::Text_sprite player_info;
    ge211::Rectangle_sprite game_over_box {{5 * (space_side_length_ + margin_),
                                            5 * (space_side_length_ + margin_)},
                                           {191, 128, 255}};
    ge211::Text_sprite game_over_text = ge211::Text_sprite::Builder(poppins_font)
            .color(ge211::Color::black())
            .message("Game over!\nYour score is")
            .build();

    std::unordered_map<char, ge211::Text_sprite> letters;
    std::unordered_map<char, ge211::Text_sprite> points;



    ge211::Position board_loc_to_pos(int row, int col);

    ge211::Position rack_loc_to_pos(int ind);

};

