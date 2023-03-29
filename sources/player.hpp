//
// Created by shani on 26/03/2023.
//
#pragma once
#include <string>
#include <iostream>
using namespace std;

class Player{
    private:
        string _name;

    public:
    Player() {
        this->_name = "";
    };

    Player(std::string name){
      this->_name = std::move(name);
    };

        string getName();
        void setName(string newName);
        int stacksize();
        int cardesTaken();
};