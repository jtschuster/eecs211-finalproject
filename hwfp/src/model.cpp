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




