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

const int value(char letter) {
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
Word::Word(): Score(0)
{
    for(Space s : Word)
        Score += s.tile->value;
}


Space::Space(const int row,
             const int col,
             bool used,
             Tile &tile,
             const Space::Bonuses bonus,
             bool bonus_active)
        : row(row),
        col(col),
        used(used),
        tile(std::unique_ptr<Tile>(&tile)),
        bonus(bonus),
        bonus_active(bonus_active) {}

Space::Space(const int row, const int col)
        : row(row),
        col(col),
        used(false),
        tile(nullptr),
        bonus(Space::Bonuses::None),
        bonus_active(false)
        {   }


Board::Board(const int numRows,
             const int numCols)
        : numRows(numRows),
        numCols(numCols),
        centerSpace(std::make_unique<Space>(numRows/2, numCols/2)),
        playedWords(std::vector<Word>)
{  }

Board::Board(const int numRows,
             const int numCols,
             Space &centerSpace,
             std::vector<Word> &playedWords)
        : numRows(numRows),
        numCols(numCols),
        centerSpace(std::unique_ptr<Space>(&centerSpace)),
        playedWords(playedWords)
        {  }




