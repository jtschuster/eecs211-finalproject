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

template <class T>
bool vector_contains(std::vector<T>, T);

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
    Bonuses bonus;

    // Whether the bonus is active
    bool bonus_active;

    // Tries to put the passed tile
    const bool insert_Tile(std::shared_ptr<Tile>);

private:

    // Returns the bonus for a space
    Space::Bonuses get_bonus(std::shared_ptr<Space>) const;

    std::vector<ge211::Position> double_word =
            { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {7, 7}, {10, 10},
              {11, 11}, {12, 12}, {13, 13}, {13, 1}, {12, 2}, {11, 3},
              {10, 4}, {4, 10}, {3, 11}, {2, 12}, {1, 13}
            };
    std::vector<ge211::Position> double_letter =
            { {0, 3}, {0, 11}, {2, 6}, {2, 8}, {3, 0}, {3, 7}, {3, 14},
              {6, 2}, {6, 6}, {6, 8}, {6, 12}, {7, 3}, {7, 11}, {8, 2},
              {8, 6}, {8, 8}, {8, 12}, {11, 0}, {11, 7}, {11, 14},
              {12, 6}, {12, 8}, {14, 3}, {14, 11}
            };
    std::vector<ge211::Position> triple_word = {
            { {0, 0}, {0, 7}, {0, 14}, {7, 0}, {7, 14}, {14, 0},
              {14, 7}, {14, 14}
            }
    };
    std::vector<ge211::Position> triple_letter = {
            { {1, 5}, {1, 9}, {5, 1}, {5, 5}, {5, 9}, {5, 13}, {9, 1},
              {9, 5}, {9, 9}, {9, 13}, {13, 5}, {13, 9}
            }
    };

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

    Bag();



    // Shuffles the bag around
    void randomize();

    // swap 2 tiles
    void swap(Tile t1, Tile t2);
};


struct Rack : std::vector<std::shared_ptr<Tile>> {

    friend class View;

private:

    // Most number of tiles allowed on a Rack
     const int max_size_ = 7;

public:

    Rack(const Player player);

    // The owner of the rack
    const Player player;

    // Shuffle the tiles order on the Rack
    void shuffle();

    // Refill the Rack from the Bag
    void refill(Bag& bag);

    // Exchanges tiles with the Bag, returns false if not enough tiles remaining
    const bool exchange(Bag& bag, std::vector<Tile>);

    // Take the tile off the rack (presumably onto board)
    Tile& removeTile(std::shared_ptr<Tile> tile);

    // Puts a tile on the rack, returns false if no room
    const bool addTile(std::shared_ptr<Tile> tile);

    const bool addTile(std::shared_ptr<Tile>& tile);


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
    std::shared_ptr<Space> centerSpace;

    // A vector of all the words that have already been played and thus points scored for
    std::vector<Word> playedWords;

    Board(int numRows, int numCols);

    // Return the space at a location on the board;
    std::shared_ptr<Space> getSpaceAt(int row, int col) const;

    // Return the tile at a location on the board;
    std::shared_ptr<Tile> getTileAt(int row, int col) const;

    // Gets the tiles on the board but not yet played
    std::vector<Space&> unsavedSpaces();

};


class Model {

    friend class View;

    Board board_;

    std::unordered_map<Player, std::shared_ptr<Rack>> racks_;

public:

    // Number of Players
    int numPlayers;

    // Stores each player's score
    std::unordered_map<Player, int> Scores;

    // Whose turn it is
    Player currentPlayer;

    //Bag
    Bag bag;

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
