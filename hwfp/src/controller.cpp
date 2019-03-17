#include "controller.h"

using namespace ge211;



Controller::Controller()
        : model_(2)
        , view_(model_)
        , m_pos_(0,0)
{ }

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites);
}

Dimensions Controller::initial_window_dimensions() const
{

    auto t = view_.initial_window_dimensions();
    return t;
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_key_down(ge211::Key key) {

    if(view_.awaiting_letter){
        if(key.code() >= 'a' && key.code() <= 'z')
            view_.choose_blank(key.code() - 32);
    } else {
        if (key.code() == '\n' || key.code() == '\r') {
            model_.endTurn();
            if(model_.checkGameOver())
                view_.end_game();
        }

        if (key.code() == 's')
            model_.shuffle_current_rack();

        if (key.code() == 'q')
            view_.end_game();

    }
}

// TODO: Add or remove if necessary

void Controller::on_mouse_down(ge211::Mouse_button, ge211::Position pos) {
    if(!view_.game_over && !view_.awaiting_letter && pos.x < view_.board_dims_.width) {

        if (pos.y >= view_.rack_offset_.height) // Clicked on rack
            if (view_.selected_tile_pos != ge211::Position(-1, -1)) // selected tile on board
                view_.move_tile(mouse_to_rack(pos));
            else if (mouse_to_rack(pos) == view_.selected_tile_loc) // clicked on already selected tile
                view_.select_tile(-1);
            else // clicked on another tile, switch selection
                view_.select_tile(mouse_to_rack(pos));
        else if (pos.y < view_.board_dims_.height) {
            if (view_.selected_tile_loc >= 0 || //there is a tile selected on the rack OR
                view_.selected_tile_pos != ge211::Position(-1, -1)) //there is a tile selected on the board
                view_.move_tile(mouse_to_board(pos)); // move rack tile to board, or move around board tile
            else {  //select a tile on board
                view_.select_tile(mouse_to_board(pos));
            }
        }
    }

}

const int Controller::mouse_to_rack(ge211::Position pos) {
    return (pos - view_.rack_offset_).x/(view_.tile_side_length_ + view_.margin_);
}

const ge211::Position Controller::mouse_to_board(ge211::Position pos) {
    return {pos.x/(view_.space_side_length_ + view_.margin_),
            pos.y/(view_.space_side_length_ + view_.margin_)};
}

void Controller::on_start() {
    background_color = {153, 0, 0};
}



