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

            // put all inputs into vector of strings 
            string line;
            vector<string> fileLines; 
            while(getline(file, line)) {
                fileLines.push_back(line);
            } 

            string firstLine = fileLines[0];
            istringstream iss(firstLine);
            vector<string> fileFirstLine { istream_iterator<string>{iss}, istream_iterator<string>{} };

            numberOfPizzas = stoi(fileFirstLine[0]);
            numOf2PersonTeams = stoi(fileFirstLine[1]);
            numOf3PersonTeams = stoi(fileFirstLine[2]);
            numOf4PersonTeams = stoi(fileFirstLine[3]);

            fileLines.erase(fileLines.begin()); // delete since we are done with it. 

            for(string fileLine : fileLines) {
                istringstream iss(fileLine);
                vector<string> lineStrings { istream_iterator<string>{iss}, istream_iterator<string>{} };

                Pizza pizza;
                pizza.numOfIngredients = stoi(lineStrings[0]);
                lineStrings.erase(lineStrings.begin());

                for(string ingredient : lineStrings) {
                    pizza.ingredients.push_back(ingredient);
                }

                pizza.pizzaNumber = pizzaList.size();
                pizzaList.push_back(pizza);
            }

            file.close();
        };
};