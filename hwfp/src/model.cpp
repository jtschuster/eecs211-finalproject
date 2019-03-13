#include "model.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

const int num_of_rows = 15;
const int num_of_cols = 15;

template<class T>
bool vector_contains(std::vector<T> vec, T val) {
    for(T t : vec) {
        if (t == val)
            return true;

    }
    return false;
}

const bool Dictionary::binarySearch(std::string) {

    std::string word;
    std::ifstream file("words.txt");
    if (file.is_open()) {
        std::vector <std::string> dictionary;

        for(size_t i = 0; i < 276643; ++i) {
            file >> dictionary[i];
        }
    }

    return (std::binary_search(dictionary.begin(), dictionary.end(), word));

}

int Tile::value(char letter) {
    std::map <char, int> Value;
    Value.insert(std::pair<char, int>('A', 1));
    Value.insert(std::pair<char, int>('B', 3));
    Value.insert(std::pair<char, int>('C', 3));
    Value.insert(std::pair<char, int>('D', 2));
    Value.insert(std::pair<char, int>('E', 1));
    Value.insert(std::pair<char, int>('F', 4));
    Value.insert(std::pair<char, int>('G', 2));
    Value.insert(std::pair<char, int>('H', 4));
    Value.insert(std::pair<char, int>('I', 1));
    Value.insert(std::pair<char, int>('J', 8));
    Value.insert(std::pair<char, int>('K', 5));
    Value.insert(std::pair<char, int>('L', 1));
    Value.insert(std::pair<char, int>('M', 3));
    Value.insert(std::pair<char, int>('N', 1));
    Value.insert(std::pair<char, int>('O', 1));
    Value.insert(std::pair<char, int>('P', 3));
    Value.insert(std::pair<char, int>('Q', 10));
    Value.insert(std::pair<char, int>('R', 1));
    Value.insert(std::pair<char, int>('S', 1));
    Value.insert(std::pair<char, int>('T', 1));
    Value.insert(std::pair<char, int>('U', 1));
    Value.insert(std::pair<char, int>('V', 4));
    Value.insert(std::pair<char, int>('W', 4));
    Value.insert(std::pair<char, int>('X', 8));
    Value.insert(std::pair<char, int>('Y', 4));
    Value.insert(std::pair<char, int>('Z', 10));
    Value.insert(std::pair<char, int>(' ', 0));

    return Value[letter];
}

BlankTile::BlankTile()
    : Tile(' ', 0) {}

int Tile::getValue() {
    return t_value;
}

Tile::Tile(const char letter, const int val)
    : letter(letter),
    t_value(val == -1 ? value(letter) : 0) {}

void Word::sumScore() {
    for(Space& s : *this){
        Score += s.tile->getValue();
    }
}


Word::Word()
: Score(0)
{ sumScore();}


Space::Space(Space& s) :
        Space(
                s.row,
                s.col,
                s.used,
                std::shared_ptr<Tile>(s.tile),
                s.bonus_active
                )
{ }

Space::Space(const int row,
             const int col,
             bool used,
             std::shared_ptr<Tile> tile,
             bool bonus_active)
        : row(row),
        col(col),
        used(used),
        bonus(Bonuses::None),
        tile(tile),
        bonus_active(bonus_active)
{
   //Double Word
   if(vector_contains(double_word, {row, col}))
       bonus = Bonuses::DoubleWord;
   //Double Letter
   if(vector_contains(double_letter, {row, col}))
       bonus = Bonuses::DoubleLetter;
   //Triple Word
   if(vector_contains(triple_word, {row, col}))
       bonus = Bonuses::TripleWord;
   //Triple Letter
   if(vector_contains(triple_letter, {row, col}))
       bonus = Bonuses::TripleLetter;

}

const bool Space::insert_Tile(std::shared_ptr<Tile> t) {
    tile = t;
    return true;
}

Space::Bonuses Space::get_bonus(std::shared_ptr<Space> s) const {
    return s->bonus;
}



Board::Board(const int numRows,
             const int numCols)
        : numRows(numRows),
        numCols(numCols),
        centerSpace(std::make_shared<Space>(numRows/2, numCols/2)),
        playedWords(std::vector<Word>{})
        {
            for(int r = 0; r < numRows; r++) {
                for(int c = 0; c < numCols; c++) {
                    if(r != numRows/2 || c != numCols/2)
                        push_back(std::make_shared<Space>(r,c));
                    else
                        push_back(std::shared_ptr<Space>(centerSpace.get()));
                }
            }

        }

std::shared_ptr<Space> Board::getSpaceAt(int row, int col) const {
    for(std::shared_ptr<Space> s : *this)
        if(s->row == row && s->col == col)
            return s;

    return nullptr;
}

std::shared_ptr<Tile> Board::getTileAt(int row, int col) const {
    return getSpaceAt(row,col)->tile;
}


Bag::Bag()
: let_quants(std::map<char, int>()) {
    {
        let_quants['A'] = 9;
        let_quants['B'] = 2;
        let_quants['C'] = 2;
        let_quants['D'] = 4;
        let_quants['E'] = 12;
        let_quants['F'] = 2;
        let_quants['G'] = 3;
        let_quants['H'] = 2;
        let_quants['I'] = 9;
        let_quants['J'] = 1;
        let_quants['K'] = 1;
        let_quants['L'] = 4;
        let_quants['M'] = 2;
        let_quants['N'] = 6;
        let_quants['O'] = 8;
        let_quants['P'] = 2;
        let_quants['Q'] = 1;
        let_quants['R'] = 6;
        let_quants['S'] = 4;
        let_quants['T'] = 6;
        let_quants['U'] = 4;
        let_quants['V'] = 2;
        let_quants['W'] = 2;
        let_quants['X'] = 1;
        let_quants['Y'] = 2;
        let_quants['Z'] = 1;
    }


    for(char c = 'A'; c <= 'Z'; c++) {
        for (int i = 1; i <= let_quants[c]; i++) {
            push_back(std::make_shared<Tile>(c));
        }
    }
    for(int i = 0; i < 4; i++){
        push_back(std::make_shared<BlankTile>());
    }
}

void Bag::randomize() {
    std::linear_congruential_engine<unsigned int, 3144, 97814, 1438829> rng;
    rng.seed((unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 71053);
    for(size_t i = 0; i < size(); i++){
        std::iter_swap(begin() + i, begin() + (rng() % 102));
    }
}

std::shared_ptr<Tile> Bag::removeTile() {
    if(empty()) return nullptr;
    return back();
}

const bool Rack::addTile(std::shared_ptr<Tile> tile) {
    if(size() == 7 || tile == nullptr) return false;

    push_back(tile);
    return true;
}

std::shared_ptr<Tile> Rack::removeTile(int loc) {
    std::shared_ptr<Tile> tile = at(loc);
    std::iter_swap(begin() + loc, --end());
    pop_back();
    return tile;
}

void Rack::refill(Bag &bag) {
    int start_size = (int)size();
    for(int i = 0; i < max_size_ - start_size; i++){
        if(!addTile(bag.removeTile()))
            return;
        bag.pop_back();
    }
}

Rack::Rack(const Player player)
    : player(player) { }


Model::Model(int numPlayers,
             const std::unordered_map<Player, int> &Scores,
             Player currentPlayer)
        : board_(num_of_rows, num_of_cols),
          numPlayers(numPlayers),
          Scores(Scores),
          bag(Bag()),
          currentPlayer(currentPlayer)
{
    bag.randomize();
    racks_[Player::P1] = std::make_shared<Rack>(Rack(Player::P1));
    racks_[Player::P1]->refill(bag);
}

const bool Model::placeTile(std::shared_ptr<Tile> tile, int row, int col) {
    if(row > num_of_rows || col > num_of_cols) return false;
    std::shared_ptr<Space> spot = board_.getSpaceAt(row, col);
    spot->insert_Tile(tile);
    return true;
}
