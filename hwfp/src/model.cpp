#include "model.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

const int num_of_rows = 15;
const int num_of_cols = 15;


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
        Space {
                s.row,
                s.col,
                s.used,
                std::shared_ptr<Tile>(s.tile),
                s.bonus,
                s.bonus_active
        }
{ }

Space::Space(const int row,
             const int col,
             bool used,
             std::shared_ptr<Tile> tile,
             const Space::Bonuses bonus,
             bool bonus_active)
        : row(row),
        col(col),
        used(used),
        tile(tile),
        bonus(bonus),
        bonus_active(bonus_active) {}

const bool Space::insert_Tile(std::shared_ptr<Tile> t) {
    this->tile = t;
    return true;
}


Board::Board(const int numRows,
             const int numCols)
        : numRows(numRows),
        numCols(numCols),
        centerSpace(std::make_unique<Space>(numRows/2, numCols/2)),
        playedWords(std::vector<Word>{})
        {
            for(int r = 0; r < numRows; r++) {
                for(int c = 0; c < numCols; c++) {
                    if(r != numRows/2 || c != numCols/2)
                        this->push_back(std::make_unique<Space>(r,c));
                    else
                        this->push_back(std::unique_ptr<Space>(this->centerSpace.get()));
                }
            }
        }

std::shared_ptr<Space> Board::getSpaceAt(int row, int col) const {
    for(std::shared_ptr<Space> s : *this)
        if(s->row == row && s->col == col)
            return s;

}


Model::Model(int numPlayers,
             const std::unordered_map<Player, int> &Scores,
             Player currentPlayer)
             : board_(num_of_rows, num_of_cols),
             numPlayers(numPlayers),
             Scores(Scores),
             currentPlayer(currentPlayer)
             {bag.randomize();}


const bool Model::placeTile(std::shared_ptr<Tile> tile, int row, int col) {
    std::shared_ptr<Space> spot = board_.getSpaceAt(row, col);
    spot->insert_Tile(tile);
    return true;
}


void Bag::randomize() {
    Bag bag;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(bag.begin(), bag.end(), std::default_random_engine(seed));
}