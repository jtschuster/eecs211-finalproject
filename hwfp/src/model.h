#pragma once

#include <ge211.h>
#include <map>

//
// Constants:
//



ge211::Dimensions const space_dims = {30, 30};
int const space_margins = 5;
std::string const dictionary_path;
enum Player {
    P1,
    P2,
    P3,
    P4
};

struct Tile {
    // letter on a tile
    const char letter;

    // value of tile's letter
    const int value;

};

struct Dictionary : std::vector<std::string> {

private:

    // Length of the dictionary
    const int length_;

public:

    // Checks if a string is in the dictionary
    const bool binarySearch(std::string);
};

struct BlankTile : Tile {

    char letter;
    const int value = 0;
};

struct Space {

    // different score bonuses a space can give
    enum Bonuses {
        DoubleWord,
        TripleWord,
        DoubleLetter,
        TripleLetter,
        None
    };

    // Stores the position of the space
    const int row;
    const int col;

    // Whether a space's tile has been used in a valid move
    bool used;

    // What tile is on a space, nullptr if no tile on space
    Tile tile;

    // What bonus the space gives
    Bonuses const bonus;

    // Whether the bonus is active
    bool bonus_active;

    // Tries to put the passed tile
    const bool insert_Tile(Tile&);

};

struct Word : std::vector<Space> {
    // Score with active multipliers
    int const Score;

    // Checks if a word is in the dictionary
    const bool isValid(Dictionary&) const;
};

struct Bag : std::vector<Tile> {
    // Shuffles the bag around
    void randomize();
};

struct Rack : std::vector<Tile> {

private:

    // Most number of tiles allowed on a Rack
    int max_size_ = 7;

public:

    // The owner of the rack
    const Player player;

    // Shuffle the tiles order on the Rack
    void shuffle();

    // Refill the Rack from the Bag
    void refill(Bag& bag);

    // Exchanges tiles with the Bag
    void exchange(Bag& bag);

    // Take the tile off the rack (presumably onto board)
    void removeTile(Tile& tile);

    // Puts a tile on the rack, returns false if no room
    const bool addTile(Tile& tile);

    // Given a Player identifier, get the Rack belonging to that player
    static Rack& getPlayerRack(Player p);
};



struct Board : std::vector<Space> {
    // Number of rows and columns in a board
    const int numRows;
    const int numCols;

    // The space in the center of the board
    const Space& centerSpace;

    // A vector of all the words that have already been played and thus points scored for
    std::vector<Word> playedWords;

    // Return the tile at a location on the board;
    Tile& getTileAt(int row, int col) const;

    // Gets the tiles on the board but not yet played
    std::vector<Space&> unsavedSpaces();
};


class Model {
    // Number of Players
    int numPlayers;

    // Stores each player's score
    std::map<Player, int> Scores;

    // Whose turn it is
    Player currentPlayer;

    // Places a tile on the board
    const bool placeTile(Tile&);

    // Sets up the players racks and the game
    void initialize(int numPlayers);

    // Ends the current turn
    Player endTurn();

private:
    // HELPER FUNCTIONS

    // Checks for game over conditions
    const bool checkGameOver() const;

    // Sums up scores at the end of the game
    const std::map<Player, int> finalScore();

    // Checks if a move is valid
    const bool isMoveValid() const;

    // Gets the score of a move
    int scoreMove();
};
