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

Dictionary::Dictionary() :
    dictionary()
{}

const bool Dictionary::binarySearch(std::string word) {

    std::ifstream file;
    file.open("../Resources/words.txt");
    if (file.is_open()) {
        for(size_t i = 0; i < 276643; ++i) {
            std::string s;
            file >> s;
            dictionary.push_back(s);
        }
    }
    file.close();
    return std::binary_search(dictionary.begin(), dictionary.end(), word);

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
    Score = 0;
    int word_mult = 1;
    for(auto s : *this){
        int let_mult = 1;
        if(!s->used) {
            if (s->bonus == Space::Bonuses::DoubleLetter)
                let_mult = 2;
            else if (s->bonus == Space::Bonuses::TripleLetter)
                let_mult = 3;
            else if (s->bonus == Space::Bonuses::DoubleWord)
                word_mult *= 2;
            else if (s->bonus == Space::Bonuses::TripleWord)
                word_mult *= 3;
        }
        Score += let_mult * s->tile->getValue();
    }
    Score *= word_mult;
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
                        push_back(centerSpace);
                }
            }

        }

std::shared_ptr<Space> Board::getSpaceAt(int row, int col) const {
    if(row > 14 || col > 14 || row < 0 || col < 0) return nullptr;
    for(std::shared_ptr<Space> s : *this)
        if(s->row == row && s->col == col)
            return s;

    return nullptr;
}

std::shared_ptr<Tile> Board::getTileAt(int row, int col) const {
    auto sp_at_loc = getSpaceAt(row, col);
    if(!sp_at_loc) return nullptr;
    return sp_at_loc->tile;
}

std::vector<std::shared_ptr<Space>> Board::unsavedSpaces() const{
    std::vector<std::shared_ptr<Space>> res;
    for(auto sp : *this){
        if(!sp->used && sp->tile != nullptr)
            res.push_back(sp);
    }

    return res;
}

std::shared_ptr<Tile> Board::remove_tile(int row, int col) {
    std::shared_ptr<Tile> res = getTileAt(row, col);
    getSpaceAt(row, col)->tile = nullptr;
    return res;
}

const bool Board::insert_tile(int row, int col, std::shared_ptr<Tile> tile) {
    return getSpaceAt(row, col)->insert_Tile(tile);
}

void Board::swap_tiles(ge211::Position loc1, ge211::Position loc2) {
    auto temp = remove_tile(loc1.y, loc1.x);
    insert_tile(loc1.y, loc1.x, remove_tile(loc2.y, loc2.x));
    insert_tile(loc2.y, loc2.x, temp);
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
    for(int i = 0; i < 2; i++){
        push_back(std::make_shared<BlankTile>());
    }
}

void Bag::randomize() {
    std::linear_congruential_engine<unsigned int, 3144, 97814, 148829> rng;
    rng.seed((unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 71053);
    for(size_t i = 0; i < size(); i++){
        std::iter_swap(begin() + i, begin() + (rng() % size()));
    }
}

std::shared_ptr<Tile> Bag::removeTile() {
    if(empty()) return nullptr;
    std::shared_ptr<Tile> t = Bag::back();
    pop_back();
    return t;
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

void Rack::shuffle() {
    std::linear_congruential_engine<unsigned int, 4843, 103984, 273829> rng;
    rng.seed((unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() % 34688);
    for(size_t i = 0; i < size(); i++){
        std::iter_swap(begin() + i, begin() + (rng() % size()));
    }
}

void Rack::refill(Bag &bag) {
    int start_size = (int)size();
    for(int i = 0; i < max_size_ - start_size; i++){
        if(!addTile(bag.removeTile()))
            return;
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
              if(numPlayers > 4)
                  numPlayers = 4;
              if(numPlayers < 2)
                  numPlayers = 2;
              initialize(numPlayers);
}

Player Model::num_to_Player(int l) {
    return num_to_player_map[l % 4];
}

Player Model::next_Player(Player p){
    return num_to_Player((player_to_num_map.at(p) + 1) % numPlayers);
}

void Model::initialize(const int numPlayers) {
    bag.randomize();
    for(int i = 0; i < numPlayers; i++){
        Player this_player = num_to_Player(i);
        racks_[this_player] = std::make_shared<Rack>(this_player);
        racks_[this_player]->refill(bag);
        Scores[this_player] = 0;
    }
}

void Model::shuffle_current_rack() {
    racks_[currentPlayer]->shuffle();
}

const bool Model::placeTile(std::shared_ptr<Tile> tile, int row, int col) {
    if(row > num_of_rows || col > num_of_cols) return false;
    std::shared_ptr<Space> spot = board_.getSpaceAt(row, col);
    spot->insert_Tile(tile);
    return true;
}

void Model::endTurn() {
    //Construct all the Words


    if(isMoveValid()){
        std::vector<Word> move_words;
        auto orientate = getOrientation();
        if(orientate != Orient::Single) {
            auto mn = findWord(findFirst()->row, findFirst()->col, orientate);
            mn.sumScore();
            move_words.push_back(mn);
        }
        for (auto sp : board_.unsavedSpaces()) {
            if (orientate != Orient::Vertical) {
                auto wd = findWord(sp->row, sp->col, Orient::Vertical);
                if (wd.size() > 1) {
                    wd.sumScore();
                    move_words.push_back(wd);
                }
            }
            if (orientate != Orient::Horizontal) {
                auto wd = findWord(sp->row, sp->col, Orient::Horizontal);
                if (wd.size() > 1) {
                    wd.sumScore();
                    move_words.push_back(wd);
                }
            }

        }



        Scores[currentPlayer] += scoreMove(move_words);
        for(auto sp : board_.unsavedSpaces()) {
            sp->used = true;
        }
        racks_.at(currentPlayer)->refill(bag);
        currentPlayer = next_Player(currentPlayer);

        firstMove = false;
    }


}

const bool Model::checkGameOver() const{
    Bag bag;
    for(auto i : racks_){
        if (i.second->empty()) return true;
    }
    auto t = bag.removeTile();
    if(t == nullptr) return true;
    else {
        bag.push_back(t);
        return false;
    }
}

Player Model::getWinner() const {
    Player best = Player::P1;
    for(auto p : Scores){
        if(p.second > Scores.at(best))
            best = p.first;
    }
    return best;
}

const bool Word::isValid(Dictionary& dictionary) const {
    return (dictionary.binarySearch(word_convert()));
}

std::string Word::word_convert() const {
    std::string word;
    for (auto s : *this) {
        word += s->tile->letter;
    }
    return word;
}


const bool Rack::operator==(Rack & R1) {
    if (size() == R1.size()) {
        for (auto s : *this) {
            for (size_t j = 0; j < size(); ++j) {
                if (s->letter != R1[j]->letter)
                return false;
            }
        }
    }
    return true;
}

const bool Rack::exactMatch(Rack & R1, Rack & R2) {
    if (R1.size() == R2.size()) {
        for (size_t i = 0; i < R1.size(); ++i) {
            if (R1[i]->letter != R2[i]->letter)
                return false;
        }
        return true;
    } else {
        return false;
    }
}


const bool Model::isMoveValid() const {

    if (!checkAdjacent() && !firstMove) return false;

    Orient orientate = getOrientation();
    if (orientate == Orient::Invalid) return false;

    if (firstMove &&
        !vector_contains<std::shared_ptr<Space>>(board_.unsavedSpaces(),board_.centerSpace))
        return false;
    if(firstMove &&
        ((orientate == Orient::Horizontal && findLast()->col - findFirst()->col != board_.unsavedSpaces().size() - 1) ||
        (orientate == Orient::Vertical && findLast()->row - findFirst()->row != board_.unsavedSpaces().size() - 1)))
            return false;

    auto temp_dict = Dictionary();

    if (orientate != Orient::Single &&
        !findWord(findFirst()->row, findFirst()->col, orientate).isValid(temp_dict)) return false;
    for (auto sp : board_.unsavedSpaces()) {
        if (orientate == Orient::Horizontal) {
            auto wd = findWord(sp->row, sp->col, Orient::Vertical);
            if (!wd.isValid(temp_dict) && wd.size() != 1) return false;
        } else {
            auto wd = findWord(sp->row, sp->col, Orient::Horizontal);
            if (!wd.isValid(temp_dict) && wd.size() != 1) return false;
        }
    }

    return true;
}

const Model::Orient Model::getOrientation() const {
    Orient guess = Orient::Invalid;
    if(board_.unsavedSpaces().size() == 1)
        return Orient::Single;
    ge211::Position origin {findFirst()->row,
                            findFirst()->col};
    for(auto sp : board_.unsavedSpaces()){
        if(!(sp->row == origin.x && sp->col == origin.y)) {
            if (guess == Orient::Invalid) {
                if(sp->row == origin.x)
                    guess = Orient::Horizontal;
                else if(sp->col == origin.y)
                    guess = Orient::Vertical;
            }
            else if ((sp->row == origin.x && guess == Orient::Vertical) ||
                    (sp->col == origin.y && guess == Orient::Horizontal)) {
                return Orient::Invalid;
            }
        }
    }

    return guess;
}

const bool Model::checkAdjacent() const {
    for(auto sp : board_.unsavedSpaces()){
        if(sp->row > 0 && board_.getSpaceAt(sp->row - 1, sp->col)->used) return true;
        if(sp->row < 14 && board_.getSpaceAt(sp->row + 1, sp->col)->used) return true;
        if(sp->col > 0 && board_.getSpaceAt(sp->row, sp->col - 1)->used) return true;
        if(sp->col < 14 && board_.getSpaceAt(sp->row, sp->col + 1)->used) return true;
    }
    return false;
}

const std::shared_ptr<Space> Model::findFirst() const {
    auto sps = board_.unsavedSpaces();
    std::shared_ptr<Space> best = sps[1];
    if(sps.size() == 1) return best;
    for(auto sp : sps){
        if(sp->row <= best->row && sp->col <= best->col)
            best = sp;
    }
    return best;
}

const std::shared_ptr<Space> Model::findLast() const {
    auto sps = board_.unsavedSpaces();
    std::shared_ptr<Space> best = sps[1];
    if(sps.size() == 1) return best;
    for(auto sp : sps){
        if(sp->row >= best->row && sp->col >= best->col)
            best = sp;
    }
    return best;
}

Word Model::findWord(int row, int col, Model::Orient dir) const {
    Word res;
    if(board_.getTileAt(row, col) != nullptr) {
        if(dir == Orient::Horizontal) {
            while (board_.getTileAt(row, col) != nullptr) {
                col--;
            }
            col++;
            while(board_.getTileAt(row, col) != nullptr) {
                res.push_back(board_.getSpaceAt(row, col++));
            }
        } else if (dir == Orient::Vertical) {
            while (board_.getTileAt(row, col) != nullptr) {
                row--;
            }
            row++;
            while(board_.getTileAt(row, col) != nullptr) {
                res.push_back(board_.getSpaceAt(row++, col));
            }
        }
    }

    return res;
}

int Model::scoreMove(std::vector<Word> &words) {
    int sum = 0;
    for(auto &w : words){
        sum += w.Score;
    }
    if(racks_[currentPlayer]->size() == 0) sum += 50; // Scrabble Bonus
    return sum;
}


