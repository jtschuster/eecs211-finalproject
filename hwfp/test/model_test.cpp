#include "model.h"
#include <catch.h>

TEST_CASE("example test")
{
    CHECK( 1 + 1 == 2 );
}

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate at least six of the functional
// requirements.
//
TEST_CASE("Word Check")
{
    Dictionary dictionary;
    CHECK_FALSE(dictionary.binarySearch("uhtf"));
    CHECK(dictionary.binarySearch("ZZZ"));
}

TEST_CASE("Point Calculator") {

    Model model(1);
    Board board(15, 15);
    Rack rack(Player::P1);

    Tile A('A');
    Tile d1('D');
    Tile d2('D');

    rack.empty();
    rack.addTile(std::make_shared<Tile>(d1));


    model.placeTile(std::make_shared<Tile>(A),8,8);
    model.placeTile(std::make_shared<Tile>(d1),8,9);
    model.placeTile(std::make_shared<Tile>(d2),8,10);
    Word add = model.findWord(8, 8, model.Horizontal);
    add.sumScore();

    CHECK(add.Score == 6);
}



TEST_CASE("Multi word score")
{
    // the score must contain all words like   K
    //                                       H I
    //                                       I N
    //                                       M
    // if the word him is added to the pre-existing word kin then the score must contain the words hi and in

    Model model(1);
    Board board(15, 15);
    Tile h('H');
    Tile i('I');
    Tile k('K');
    Tile m('M');
    Tile n('N');

    model.placeTile(std::make_shared<Tile>(h),2,2);
    model.placeTile(std::make_shared<Tile>(n),3,2);
    model.placeTile(std::make_shared<Tile>(i),3,1);
    model.placeTile(std::make_shared<Tile>(m),4,1);
    model.placeTile(std::make_shared<Tile>(h),2,1);
    model.placeTile(std::make_shared<Tile>(k),1,2);

    CHECK(model.isMoveValid());
    Word multi = model.findWord(2, 2, model.Vertical);
    multi.sumScore();
    CHECK(multi.Score == 10);
    board.erase();

}

TEST_CASE("Shuffle tiles")
{
    // the tiles on the rack can be shuffled within themselves

    Rack rack1;
    Bag bag;
    Tile tile;
    rack1.refill(bag);
    Rack rack2 = rack1;
    rack1.shuffle();
    CHECK_FALSE(Rack::exactMatch(rack1, rack2));
    CHECK_FALSE(rack1.addTile(tile)); // Make sure rack won't allow overfilling

}

TEST_CASE("Exchange tiles")
{
    // the tiles on the rack can be shuffled within themselves

    Rack rack1;
    Bag bag;
    bag.empty();
    rack1.refill(bag);

    bag.push_back(new Tile('e'));
    bag.push_back(new Tile('r'));

    CHECK_FALSE(rack1.exchange(bag, new std::vector<Tile> {rack1[0], rack1[1], rack1[2]}));  // Fails since not enough tiles left in bag to exchange
    CHECK(rack1.exchange(bag, new std::vector<Tile> {rack1[0]})); // Works since 1 < 2

}

TEST_CASE("")
{

}
 */