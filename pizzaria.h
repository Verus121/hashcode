#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include "pizza.h"

class Pizzaria {
    public: 
        int numberOfPizzas;
        int numOf2PersonTeams;
        int numOf3PersonTeams;
        int numOf4PersonTeams;
        vector<Pizza> pizzaList; // DO NOT CHANGE THIS LIST ORDER - index corresponds with pizza id. 

        Pizzaria(string inputFile) {
            ifstream file(inputFile);

            string line;
            vector< vector<string> > fileLines;
            while(getline(file, line)) {
                istringstream iss(line);
                vector<string> fileLine { istream_iterator<string>{iss}, istream_iterator<string>{} };
                fileLines.push_back(fileLine);
            } 

            numberOfPizzas = stoi(fileLines[0][0]);
            numOf2PersonTeams = stoi(fileLines[0][1]);
            numOf3PersonTeams = stoi(fileLines[0][2]);
            numOf4PersonTeams = stoi(fileLines[0][3]);

            for(int i = 1; i < fileLines.size(); i++) {
                Pizza pizza;
                pizza.numOfIngredients = stoi(fileLines[i][0]);
                for(int j = 1; j < fileLines[i].size(); j++) {
                    pizza.ingredients.push_back(fileLines[i][j]);
                }
                pizza.pizzaNumber = pizzaList.size();
                pizzaList.push_back(pizza);
            }

            file.close();
        };
};