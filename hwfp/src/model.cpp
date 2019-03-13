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

const bool Dictionary::binarySearch(std::string word) {

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

    return Value[letter];
}

int Tile::getValue() {
    return Tile::value(this->letter);
}

Tile::Tile(const char letter) : letter(letter) {}

void Word::sumScore() {
    for(Space& s : *this){
        this->Score += s.tile->getValue();
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
    this->tile = t;
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
                        this->push_back(std::make_shared<Space>(r,c));
                    else
                        this->push_back(std::shared_ptr<Space>(this->centerSpace.get()));
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


Model::Model(int numPlayers,
             const std::unordered_map<Player, int> &Scores,
             Player currentPlayer)
             : board_(num_of_rows, num_of_cols),
             numPlayers(numPlayers),
             Scores(Scores),
             currentPlayer(currentPlayer)
             {
                 racks_[Player::P1] = std::make_shared<Rack>(Rack(Player::P1));
                 /*bag.randomize();*/
             }


const bool Model::placeTile(std::shared_ptr<Tile> tile, int row, int col) {
    std::shared_ptr<Space> spot = board_.getSpaceAt(row, col);
    spot->insert_Tile(tile);
    return true;
}
void swap(Tile t1, Tile t2) {
    char tletter = t1.letter;
    t1.letter = t2.letter;
    t2.letter = tletter;

}

void Bag::randomize() {
    Bag bag;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(bag.begin(), bag.end(), std::default_random_engine(seed));
}

const bool Rack::addTile(std::shared_ptr<Tile> tile) {
    if(this->size() == 7) return false;

    this->push_back(tile);
    return true;
}

const bool Rack::addTile(std::shared_ptr<Tile> &tile) {
    if(this->size() == 7) return false;

    return addTile(std::shared_ptr<Tile>(tile));
}

Rack::Rack(const Player player)
    : player(player) {
        this->addTile(std::make_shared<Tile>('P'));
        this->addTile(std::make_shared<Tile>('T'));
        this->addTile(std::make_shared<Tile>('W'));
        this->addTile(std::make_shared<Tile>('O'));
        this->addTile(std::make_shared<Tile>('E'));
        this->addTile(std::make_shared<Tile>('C'));
        this->addTile(std::make_shared<Tile>('Z'));
    }
