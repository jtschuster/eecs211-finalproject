#pragma once

#include <ge211.h>
#include <map>
#include <unordered_map>

//
// Constants:
//


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

    Tile(char letter);

// value of tile's letter
    static int value(char letter);

    int getValue();


};

struct Dictionary : std::vector<std::string> {

    /// Constructor
    //Dictionary(std::string);
private:

    // Length of the dictionary
    const int length_;

public:


    // Checks if a string is in the dictionary
    const bool binarySearch(std::string);

    std::vector <std::string> dictionary;
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

    Space(int row,
            int col,
            bool used = false,
            std::shared_ptr<Tile> tile = std::shared_ptr<Tile>(),
            Bonuses bonus = Bonuses::None,
            bool bonus_active = false);


    Space(Space&);

    // Stores the position of the space
    const int row;
    const int col;

    // Whether a space's tile has been used in a valid move
    bool used;

    // What tile is on a space, nullptr if no tile on space
    std::shared_ptr<Tile> tile;

    // What bonus the space gives
    Bonuses const bonus;

    // Whether the bonus is active
    bool bonus_active;

// Tries to put the passed tile
    const bool insert_Tile(std::shared_ptr<Tile>);

};

struct Word : std::vector<Space> {

    // Score with active multipliers
    int Score;

private:
    void sumScore();

public:

    Word();

    Word& operator=(const Word&) = delete;


// Checks if a word is in the dictionary
    const bool isValid(Dictionary&) const;


};

struct Bag : std::vector<Tile> {

    Bag() {
        std::map<char, int> start;
        start.insert(std::pair<char, int>('A', 9));
        start.insert(std::pair<char, int>('B', 2));
        start.insert(std::pair<char, int>('C', 2));
        start.insert(std::pair<char, int>('D', 4));
        start.insert(std::pair<char, int>('E', 12));
        start.insert(std::pair<char, int>('F', 2));
        start.insert(std::pair<char, int>('G', 3));
        start.insert(std::pair<char, int>('H', 2));
        start.insert(std::pair<char, int>('I', 9));
        start.insert(std::pair<char, int>('J', 1));
        start.insert(std::pair<char, int>('K', 1));
        start.insert(std::pair<char, int>('L', 4));
        start.insert(std::pair<char, int>('M', 2));
        start.insert(std::pair<char, int>('N', 6));
        start.insert(std::pair<char, int>('O', 8));
        start.insert(std::pair<char, int>('P', 2));
        start.insert(std::pair<char, int>('Q', 1));
        start.insert(std::pair<char, int>('R', 6));
        start.insert(std::pair<char, int>('S', 4));
        start.insert(std::pair<char, int>('T', 6));
        start.insert(std::pair<char, int>('U', 4));
        start.insert(std::pair<char, int>('V', 2));
        start.insert(std::pair<char, int>('W', 2));
        start.insert(std::pair<char, int>('X', 1));
        start.insert(std::pair<char, int>('Y', 2));
        start.insert(std::pair<char, int>('Z', 1));
    }


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

    // Exchanges tiles with the Bag, returns false if not enough tiles remaining
    const bool exchange(Bag& bag, std::vector<Tile>);

    // Take the tile off the rack (presumably onto board)
    Tile& removeTile(Tile& tile);

    // Puts a tile on the rack, returns false if no room
    const bool addTile(Tile& tile);

    // Given a Player identifier, get the Rack belonging to that player
    static Rack& getPlayerRack(Player p);

    // Checks if the tiles on this rack are same tiles as passed rack
    const bool operator==(Rack&);

    // Checks if the tiles each rack are same tiles and same order
    static const bool exactMatch(Rack&, Rack&);
};



struct Board : std::vector<std::shared_ptr<Space>> {
    // Number of rows and columns in a board
    const int numRows;
    const int numCols;

    // The space in the center of the board
    std::unique_ptr<Space> centerSpace;

    // A vector of all the words that have already been played and thus points scored for
    std::vector<Word> playedWords;

    Board(int numRows, int numCols);

    // Return the space at a location on the board;
    std::shared_ptr<Space> getSpaceAt(int row, int col) const;

    // Return the tile at a location on the board;
    Tile& getTileAt(int row, int col) const;

    // Gets the tiles on the board but not yet played
    std::vector<Space&> unsavedSpaces();
};


class Model {

    friend class View;

    Board board_;

public:

    // Number of Players
    int numPlayers;

    // Stores each player's score
    std::unordered_map<Player, int> Scores;

    // Whose turn it is
    Player currentPlayer;

    Model(int numPlayers,
            const std::unordered_map<Player, int> &Scores = std::unordered_map<Player, int>(),
            Player currentPlayer = Player::P1);

// Places a tile on the board
    const bool placeTile(std::shared_ptr<Tile>, int row, int col);

    // Sets up the players racks and the game
    void initialize(int numPlayers);

    // Ends the current turn
    Player endTurn();

//private: Will make private once we can access from test
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
