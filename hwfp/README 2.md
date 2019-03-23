# Words without Friends

## Instructions

1. For the path of the file that binarySearch() function in model.cpp takes in
must be in the resources folder. In case GSC moves the word.txt file into a different folder
the path must be changed in this function to "../directory/words.txt"

2. The game can be played by running and building the words.cpp file and the game
is played using the same guidelines as mentioned in the PROPOSAL.md

## Changes from proposal

1. We removed the function involving Success, failure, and victory noise as it was unnecessary
and we already had 13 other functional elements to implement.

## Evaluation guide

  1. Scores a word (with bonuses) - Implemented in test cases 1 and 2. the function 
  Word::sumScore() calculates the score of a move including bonuses such as doubleletter
  or triple word and Word::score() returns the int.
  
  2. Checks if a word is valid - Implemented in test case 1 when Dictionary::binarySearch(std::string)
  is called, this returns a boolean if the word is valid or not. This can also be checked by
  actually playing the game as the controller will not let you hit enter if the word is not valid
  
  3. Checks if a word is valid - Used in test cases 2, 4, and 5. This function returns 
       a boolean if the move played by the player is valid or not. This can also be checked by
       actually playing the game as the controller will not let you hit enter if the move is not valid

  4. Refill the rack tiles - test case 3 uses this by calling Rack::refill() which puts new tiles in
  the rack if it has less than 7 tiles. This can also be observed by playing the game. refill is called
  every time a player uses its tiles and the rack is refilled for the next turn.
  
  5. Shuffle rack - Test case 3 implements this by calling Rack::shuffle this reorients the tiles in the
  rack. This can also be confirmed by playing the game and hitting the letter s.
  
  6. Start game - This can be evaluated by running the game from the beginning. There are
  no tiles on the board, it is player 1's turn and the first move must be played on the center 
  star space.
  
  7. Check for end of game - This can be evaluated by actually playing the game and it is 
  implemented by the function Model::checkGameOver. If the rack is not full and it cannot be refilled
  and the bag is empty then the game is over and the winner is displayed. Alternatively you
  can press q and that will end the game at any point.
  
  8. Score end of game - The is evaluated in the actual gameplay. The score of each player is 
  displayed on the bottom right and when the game ends then the winning player is displayed.
  
  9. Place tile on board - This is implemented in the test cases 1, 2, 4, and 5 by calling the function
  Model::placeTile . This actually places the tile on the board. It can be verified by also playing the game
  and clicking the tile you want to place and then clicking the space you want to place it in.
  
  10. Configure blank tiles - This can be evaluated by actually playing the game. When a blank tile is placed
  on the board the user can then type the letter that they would like to switch it to, and the blank
  tile inherits the letter and its value. This is implemented using the functions View::designate_blank
  and View::choose_blank
  
  11. Draw board - This can be evaluated by playing the game. A new board is drawn each time the game is run.
  This board has no tiles placed on it and only has the bonuses belonging to the space and the star center
  space from which the player 1 must start.
  
  12. Draw all tiles - This can be evaluated by playing the game. The tiles are first drawn in the rack of the
  player and then can be placed onto the board by clicking the tile and then a space on the board. The tile
  is then drawn on the board on the allocated space or swapped with a preexisting tile placed on the same turn.
  
  13. End turn & change player - This can also be evaluated by playing the game. The players turn ends when
  he presses enter on the keyboard. The turn is automatically switched to the next player and the rack is 
  replaced by the second players rack.
  
  
## Model Test Cases

  1. TEST_CASE("Word Check") line number - 1403
  This test case calls Dictionary::binarySearch to binary search through a dictionary and return a boolean if
  a word is true or not.
  
  2. TEST_CASE("Point Calculator") line number - 1410
  This test's preliminary purpose is to check for a valid move and then calculate the total score for the word.
  
  3. TEST_CASE("Multi word score") line number - 1435
  This test deals with a preexisting word 'kin' and then another word 'him' is added in the next turn so as to
  form multiple words including him, hi, and in. The score includes the total score from all the words.
  
  4. TEST_CASE("Checking Validity of Move") line number - 1500
  This test case checks if the initial move is valid or not by returning a boolean if the first move involves
  placing a word on the center space.
  
  5. TEST_CASE("Checking actual edges") line number - 1553
  This test case makes sure that we can place tiles on the edges as that was an aspect that was causing errors 
  in our project initially.
  



