#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
using namespace std;

#include "pizza.h"
#include "pizzaria.h"
#include "teamorder.h"
#include "deliveries.h"  

// TODO: record the number of the pizza.

void printDelivery(string outputFileA, Deliveries deliveries) {
    ofstream outputFile(outputFileA);

    outputFile << deliveries.numberOfDeliveries << "\n";

    for( int i = 0; i < deliveries.numberOfDeliveries; i++ ) {
        ostringstream teamSizeandPizzaNumbers;

        teamSizeandPizzaNumbers << deliveries.teamOrders[i].teamSize << " ";

        for( int pizzaNumber : deliveries.teamOrders[i].pizzaNumbers) {
            teamSizeandPizzaNumbers << pizzaNumber << " ";
        }

        outputFile << teamSizeandPizzaNumbers.str() << "\n";
    }

    outputFile.close();
}

void addTeamOrder(int teamSize, vector<Pizza> & copyPizzaList, Deliveries & deliveries) {
    TeamOrder teamOrder;
    teamOrder.teamSize = teamSize;

    set<string> teamOrderIngredients;

    for(int teamMemberIter = 0; teamMemberIter < teamSize; teamMemberIter++) {
        
        vector<pair<int, int>> pizzaScores; // can just be a vector of ints now. 

        // find scores of top 10 pizzas.
        for(int copyPizzaListIter = 0; copyPizzaListIter < copyPizzaList.size() && copyPizzaListIter < 10; copyPizzaListIter++) {
            Pizza pizza = copyPizzaList[copyPizzaListIter]; 

            set<string> copyTeamOrderIngredients = teamOrderIngredients;
            int prePizzaTeamOrderIngredientsSize = copyTeamOrderIngredients.size();

            vector<string> pizzaIngredients = pizza.ingredients;
            for(string ingredient : pizzaIngredients) {
                copyTeamOrderIngredients.insert(ingredient);
            }

            int postPizzaTeamOrderIngredientsSize = copyTeamOrderIngredients.size();
            int pizzaScore = postPizzaTeamOrderIngredientsSize - prePizzaTeamOrderIngredientsSize;

            pizzaScores.emplace_back(pizza.pizzaNumber, pizzaScore);
        }

        // select largest score
        pair<int, int> currentBestPizza = pizzaScores[0];
        int currentBestPizzaIter = 0; // easy delete
        for(int pizzaScoresIter = 0; pizzaScoresIter < pizzaScores.size(); pizzaScoresIter++) {
            if(currentBestPizza.second < pizzaScores[pizzaScoresIter].second) {
                currentBestPizza = pizzaScores[pizzaScoresIter];
                currentBestPizzaIter = pizzaScoresIter;
            }
        }

        // add pizza to teamorder 
        teamOrder.pizzaNumbers.push_back(currentBestPizza.first);
        
        copyPizzaList.erase(copyPizzaList.begin()+currentBestPizzaIter);
    }

    deliveries.teamOrders.push_back(teamOrder);
}

void algorithm4(Pizzaria & pizzaria, Deliveries & deliveries) {

    vector<Pizza> copyPizzaList = pizzaria.pizzaList;

    int numbersOfPizzaLeft = pizzaria.numberOfPizzas;
    int numberOf2TeamsLeft = pizzaria.numOf2PersonTeams;
    int numberOf3TeamsLeft = pizzaria.numOf3PersonTeams;
    int numberOf4TeamsLeft = pizzaria.numOf4PersonTeams;
    
    while(numbersOfPizzaLeft >= 4 && numberOf4TeamsLeft >= 1) {
        addTeamOrder(4, copyPizzaList, deliveries);
        numbersOfPizzaLeft = numbersOfPizzaLeft - 4;
        numberOf4TeamsLeft = numberOf4TeamsLeft - 1;
        cout << deliveries.teamOrders.size() << endl;
    }

    while(numbersOfPizzaLeft >= 3 && numberOf3TeamsLeft >= 1) {
        addTeamOrder(3, copyPizzaList, deliveries);
        numbersOfPizzaLeft = numbersOfPizzaLeft - 3;
        numberOf4TeamsLeft = numberOf4TeamsLeft - 1;
        cout << deliveries.teamOrders.size() << endl;
    }

    while(numbersOfPizzaLeft >= 2 && numberOf2TeamsLeft >= 1) {
        addTeamOrder(2, copyPizzaList, deliveries);
        numbersOfPizzaLeft = numbersOfPizzaLeft - 2;
        numberOf4TeamsLeft = numberOf4TeamsLeft - 1;
        cout << deliveries.teamOrders.size() << endl;
    }

    deliveries.numberOfDeliveries = deliveries.teamOrders.size(); // cant this be done at the very end?

} // alg 4


int main() {
    // string inputFile = "files/ain.txt"; 
    // string outputFile = "files/a_output.txt";
    string inputFile = "files/bin.in";
    string outputFile = "files/b_output.txt";
    // string inputFile = "files/cin.in";
    // string outputFile = "files/c_output.txt";
    // string inputFile = "files/din.in";
    // string outputFile = "files/d_output.txt";
    // string inputFile = "files/ein.in";
    // string outputFile = "files/e_output.txt";

    Pizzaria pizzaria(inputFile);
    sort(pizzaria.pizzaList.begin(), pizzaria.pizzaList.end());

    Deliveries deliveries;

    algorithm4(pizzaria, deliveries);
        
    printDelivery(outputFile, deliveries);

    return 0;
}