#pragma once

#include "model.h"
#include "view.h"

class Controller : public ge211::Abstract_game
{
public:
    explicit Controller();


// `protected` means that GE211 (via base class `ge211::Abstract_game`)
// can access these members, but arbitrary other code cannot:
protected:
    //
    // Controller operations called by GE211
    //

    //const ge211::Position mouse_to_board(ge211::Position);

    //void on_mouse_move(ge211::Position) override;

    // These three delegate to the view:
    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

    void on_key_down(ge211::Key) override;

    int selected_tile;
    void on_mouse_down(ge211::Mouse_button, ge211::Position) override;
    const int mouse_to_rack(ge211::Position);
    const ge211::Position mouse_to_board(ge211::Position);

private:
    Model            model_;
    View             view_;

    ge211::Position  m_pos_;


};
