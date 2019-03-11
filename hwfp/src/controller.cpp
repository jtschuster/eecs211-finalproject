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
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_key_down(ge211::Key key) {
    if(key.code() == 'r')
        model_.placeTile(std::make_shared<Tile>('r'), 8, 2);
}

// TODO: Add or remove if necessary

/*void Controller::on_mouse_move(Position pos) {
    m_pos_ = pos;
}

void Controller::on_mouse_down(ge211::Mouse_button, ge211::Position pos) {

    if(model_.find_move(mouse_to_board(pos))){
        std::cout << mouse_to_board(pos).x << ", " << mouse_to_board(pos).y << std::endl;
        model_.play_move(mouse_to_board(pos));

    }
}

const ge211::Position Controller::mouse_to_board(ge211::Position pos) {
    return {pos.x/36, pos.y/36};
}*/


