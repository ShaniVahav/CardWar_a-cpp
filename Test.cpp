//
// Created by shani on 26/03/2023.
//

#include <iostream>
#include <sstream>
#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include <stdexcept>
using namespace std;

stringstream buff;  // use for keep the output

void changeStandardOutput(){
    // change the standard output
    // when use 'cout' it will be saved in 'buff' instead of print it to the console
    std::cout.rdbuf(buff.rdbuf());
}



TEST_CASE("Validation") {

    // saving the standard output pointer
    streambuf *standard = std::cout.rdbuf();

    changeStandardOutput();

    Player p1;
    Player p2;

    string players[20];  // 20 names represents our players

    for (int i = 0; i < players->size(); i++) {
        players[i] = rand();  // a random meaningless string that represents the name of player i
    }


    SUBCASE("Valid Winner") {
        for (int i = 0; i < 100; ++i) {
            buff.str("");

            p1.setName(players[rand() % 20]); // give to p1 a random name
            p2.setName(players[rand() % 20]);  // give to p2 a random name

            Game game(p1, p2);
            game.playAll();

            game.printWiner();  // the result saved in 'buff'
            string winner = buff.str();

            // the winner must be one of the two players that played
            REQUIRE((winner == p1.getName() || winner == p2.getName()));
        }

        buff.str("");
    }


    SUBCASE("Valid Turn") {
        int p1_stack, p2_stack;  // the amount of cards left
        int p1_last_stack = 100, p2_last_stack = 100;

        for (int i = 0; i < 100; ++i) {
            p1.setName(players[rand() % 20]);
            p2.setName(players[rand() % 20]);
            Game game(p1, p2);

            for (int j = 0; j < 27; ++j) {
                game.playTurn();
                p1_stack = p1.stacksize();
                p2_stack = p2.stacksize();

                if (p1_stack >= p1_last_stack || p2_stack >= p2_last_stack) {
                    // back to the standard output (console)
                    cout.rdbuf(standard);
                    throw runtime_error("stacksize should be reduced from turn to turn");
                }

                if (p1_stack == 0 || p2_stack == 0) {
                    CHECK_THROWS(game.playTurn());  // for a turn need to be cards for both of the players
                }

                if ((p1_stack < 0) || (p2_stack < 0)) {
                    // back to the standard output (console)
                    cout.rdbuf(standard);
                    throw runtime_error("stacksize can't be less than 0");
                }

                p1_last_stack = p1_stack;
                p2_last_stack = p2_stack;
            }

            // check the score of the winner
            game.printWiner();
            string winner = buff.str();

            if(p1.getName() == winner){
                REQUIRE(p1.cardesTaken() > p2.cardesTaken());
            }
            else{
                REQUIRE(p1.cardesTaken() > p2.cardesTaken());
            }
            buff.str("");
        }
    }
    // back to the standard output (console)
    cout.rdbuf(standard);
}

