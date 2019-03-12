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
    /*switch (key.code()){
        case 'r':
            model_.placeTile(std::make_shared<Tile>('R'), 8, 2);
            break;
        case 'q':
            model_.placeTile(std::make_shared<Tile>('Q'), 11, 4);
            break;
        case 'a':
            model_.placeTile(std::make_shared<Tile>('A'), 0, 5);
            break;
        case 'p':
            model_.placeTile(std::make_shared<Tile>('P'), 2, 3);
            break;
        case 'm':
            model_.placeTile(std::make_shared<Tile>('M'), 2, 2);
            break;
        case 'w':
            model_.placeTile(std::make_shared<Tile>('W'), 10, 14);
            break;
        case 'o':
            model_.placeTile(std::make_shared<Tile>('O'), 5, 8);
            break;
        case 'b':
            model_.placeTile(std::make_shared<Tile>('B'), 7, 7);
            break;
    }*/
    if(key.code() <= 'd' && key.code() >= 'a')
        model_.placeTile(std::make_shared<Tile>(key.code() - 32), 3, 3);
    if(key.code() <= 'h' && key.code() >= 'e')
        model_.placeTile(std::make_shared<Tile>(key.code() - 32), 8, 12);
    if(key.code() <= 'm' && key.code() >= 'i')
        model_.placeTile(std::make_shared<Tile>(key.code() - 32), 7, 0);
    if(key.code() <= 's' && key.code() >= 'n')
        model_.placeTile(std::make_shared<Tile>(key.code() - 32), 5, 9);
    if(key.code() <= 'z' && key.code() >= 't')
        model_.placeTile(std::make_shared<Tile>(key.code() - 32), 7, 7);

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


