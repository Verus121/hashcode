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


void exitIfFileFail(bool fileFail) {
    if(fileFail) {
        cout << "File opening failed.\n";
        exit(1); // exits program immediately 
    }
}

vector<string> getFileLine(ifstream& file) {
    string line;
    getline(file, line);
    istringstream iss(line);
    vector<string> fileLine {
        istream_iterator<string>{iss}, 
        istream_iterator<string>{}
    };
    return fileLine;
}

vector<Pizza> getPizzaList(ifstream& file) {
    vector<Pizza> pizzas;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> fileLine {
            istream_iterator<string>{iss}, 
            istream_iterator<string>{}
        };

        Pizza newPizza;
        newPizza.numOfIngredients = stoi(fileLine[0]);
        for(int i = 0; i < newPizza.numOfIngredients; i++) {
            newPizza.ingredients.push_back(fileLine[i+1]);
        }
        newPizza.pizzaNumber = pizzas.size();
        pizzas.push_back(newPizza);
    }

    return pizzas;
}

class Pizzaria {
    public: 
        int numberOfPizzas;
        int numOf2PersonTeams;
        int numOf3PersonTeams;
        int numOf4PersonTeams;
        vector<Pizza> pizzaList; // DO NOT CHANGE THIS LIST ORDER - index corresponds with pizza id. 

        Pizzaria(string inputFile) {
            ifstream file(inputFile);
            exitIfFileFail(file.fail());

            vector<string> fileFirstLine = getFileLine(file);

            numberOfPizzas = stoi(fileFirstLine[0]);
            numOf2PersonTeams = stoi(fileFirstLine[1]);
            numOf3PersonTeams = stoi(fileFirstLine[2]);
            numOf4PersonTeams = stoi(fileFirstLine[3]);
            pizzaList = getPizzaList(file);

            file.close();
        };
};