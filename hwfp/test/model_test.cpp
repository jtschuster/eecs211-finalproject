#include "model.h"
#include <catch.h>
#include "view.h"

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

    Model model(2);
    Board board(15, 15);
    Tile h('H');
    Tile i('I');
    Tile k('K');
    Tile m('M');
    Tile n('N');

    model.placeTile(std::make_shared<Tile>(i),7,7);
    model.placeTile(std::make_shared<Tile>(n),8,7);
    model.placeTile(std::make_shared<Tile>(k),6,7);

    CHECK(model.isMoveValid());
    Word multi = model.findWord(7, 7, model.Vertical);
    multi.sumScore();
    CHECK(multi.Score == 14);
    model.endTurn();

    model.placeTile(std::make_shared<Tile>(h),7,6);
    model.placeTile(std::make_shared<Tile>(i),8,6);
    model.placeTile(std::make_shared<Tile>(m),9,6);
    CHECK(model.isMoveValid());

    Word multi3 = model.findWord(7, 6, model.Vertical);
    multi3.sumScore();
    CHECK(multi3.Score == 9);

    Word multi4 = model.findWord(7, 6, model.Horizontal);
    multi4.sumScore();
    CHECK(multi4.Score == 5);

    Word multi5 = model.findWord(9, 6, model.Vertical);
    multi5.sumScore();
    CHECK(multi5.Score == 9);

    CHECK(multi5 == multi3);

    model.endTurn();
}

TEST_CASE("Shuffle tiles")
{
    // the tiles on the rack can be shuffled within themselves

    Rack rack1(P1);
    Bag bag;
    Tile h('H');
    rack1.refill(bag);
    Rack rack2 = rack1;
    rack1.shuffle();
    CHECK_FALSE(Rack::exactMatch(rack1, rack2));
    CHECK_FALSE(rack1.addTile(std::make_shared<Tile>(h))); // Make sure rack won't allow overfilling

}



TEST_CASE("Checking Validity of Move")
{
    Bag bag;
    Model model(2);
    Tile h('H');
    Tile e('E');
    Tile y('Y');

    model.placeTile(std::make_shared<Tile>(h),7,7);
    model.placeTile(std::make_shared<Tile>(e),8,7);
    model.placeTile(std::make_shared<Tile>(y),9,7);


    CHECK(model.isMoveValid());
}

TEST_CASE("Check bad word")
{
    Bag bag;
    Model model(2);
    Tile p('P');
    Tile l('L');
    Tile o('O');
    Tile w('W');

    model.placeTile(std::make_shared<Tile>(p),5,7);
    model.placeTile(std::make_shared<Tile>(o),6,7);
    model.placeTile(std::make_shared<Tile>(l),7,7);
    model.placeTile(std::make_shared<Tile>(w),8,7);

    CHECK_FALSE(model.isMoveValid());

}

TEST_CASE("Check bad move")
{
    Bag bag;
    Model model(2);
    Tile p('P');
    Tile l('L');
    Tile o('O');
    Tile w('W');

    model.placeTile(std::make_shared<Tile>(p),5,7);
    model.placeTile(std::make_shared<Tile>(o),6,7);
    model.placeTile(std::make_shared<Tile>(l),7,7);
    model.placeTile(std::make_shared<Tile>(0),7,8);

    CHECK_FALSE(model.isMoveValid());

}


// testing to make sure that a tile can be placed on the edges of the board
TEST_CASE("Checking actual edges")
{
    Bag bag;
    Model model(2);

    model.placeTile(std::make_shared<Tile>('C'),7,0);
    model.placeTile(std::make_shared<Tile>('O'),7,1);
    model.placeTile(std::make_shared<Tile>('M'),7,2);
    model.placeTile(std::make_shared<Tile>('P'),7,3);
    model.placeTile(std::make_shared<Tile>('U'),7,4);
    model.placeTile(std::make_shared<Tile>('T'),7,5);
    model.placeTile(std::make_shared<Tile>('E'),7,6);
    model.placeTile(std::make_shared<Tile>('R'),7,7);

    CHECK(model.isMoveValid());

    model.endTurn();

    CHECK(model.Scores[Player::P1] == 102);
}

//TEST_CASE("Exchange tiles")
//{
//    // the tiles on the rack can be shuffled within themselves
//
//    Rack rack1(P1);
//    Bag bag;
//    bag.empty();
//    rack1.refill(bag);
//    Tile h('H');
//    Tile r('R');
//    bag.push_back(std::make_shared<Tile>(h));
//    bag.push_back(std::make_shared<Tile>(r));
//
//    CHECK_FALSE(rack1.exchange(bag, tnew std::vector<Tile> {rack1[0], rack1[1], rack1[2]}));  // Fails since not enough tiles left in bag to exchange
//    CHECK(rack1.exchange(bag, new std::vector<Tile> {rack1[0]})); // Works since 1 < 2
//
//}
