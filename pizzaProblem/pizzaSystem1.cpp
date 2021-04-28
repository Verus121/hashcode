#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

typedef int PizzaNumber;
typedef int Toppings;
typedef vector<int> Ingredients;

vector<int> greedyIngredientsPizzaSelector(int teamSize, vector<pair<Toppings, PizzaNumber>>& toppingsOfPizzaVector, unordered_map<PizzaNumber, Ingredients>& pizzaNumberIngredientsMap) {
    vector<int> delivery;
    
    int pizzaWithMostToppings = toppingsOfPizzaVector[0].second;
    unordered_map<int, bool> deliveryIngredients;

    for(int ingredient : pizzaNumberIngredientsMap[pizzaWithMostToppings]) {
        deliveryIngredients.emplace(ingredient, true);
    }

    delivery.push_back(pizzaWithMostToppings);
    toppingsOfPizzaVector.erase(toppingsOfPizzaVector.begin());

    for(int i = 1; i < teamSize; i++) {
        int mostToppingsAdded = -1;
        int mostToppingsAddedPizza = -1;
        int mostToppingsVectorLocation = -1;

        for(int j = 0; j < toppingsOfPizzaVector.size(); j++) {
            if(toppingsOfPizzaVector[j].first < mostToppingsAdded) break;

            int pizzaNumber = toppingsOfPizzaVector[j].second;
            int toppingsAdded = 0;
            for(int ingredient : pizzaNumberIngredientsMap[pizzaNumber]) {
                if(deliveryIngredients.find(ingredient) == deliveryIngredients.end()) {
                    toppingsAdded++;
                }
            }

            if(toppingsAdded >= mostToppingsAdded) {
                mostToppingsAdded = toppingsAdded;
                mostToppingsAddedPizza = pizzaNumber;
                mostToppingsVectorLocation = j;
            }
        }

        for(int ingredient : pizzaNumberIngredientsMap[mostToppingsAddedPizza]) {
            deliveryIngredients.emplace(ingredient, true);
        }

        delivery.push_back(mostToppingsAddedPizza);
        toppingsOfPizzaVector.erase(toppingsOfPizzaVector.begin()+mostToppingsVectorLocation);
    }
    return delivery;
}

void runProgram(string inputFile, string outputFile) {
    ifstream fileIn(inputFile);
    int numberOfPizzasAvailable, numberOf2PersonTeams, numberOf3PersonTeams, numberOf4PersonTeams;
    fileIn >> numberOfPizzasAvailable >> numberOf2PersonTeams >> numberOf3PersonTeams >> numberOf4PersonTeams;

    unordered_map<PizzaNumber, Ingredients> pizzaNumberIngredientsMap;

    unordered_map<string, int> ingredientsNameToNumberMap; 
    for(int pizzaNumber = 0; pizzaNumber < numberOfPizzasAvailable; pizzaNumber++) {
        int numberOfIngredients;
        fileIn >> numberOfIngredients;

        vector<int> ingredientNumberVector;
        for(int i = 0; i < numberOfIngredients; i++) {
            string ingredientName;
            fileIn >> ingredientName;
            ingredientsNameToNumberMap.emplace(ingredientName, ingredientsNameToNumberMap.size());
            ingredientNumberVector.push_back(ingredientsNameToNumberMap[ingredientName]);
        }

        pizzaNumberIngredientsMap[pizzaNumber] = ingredientNumberVector;
    }

    fileIn.close();

    vector<pair<Toppings, PizzaNumber>> toppingsOfPizzaVector;
    for(auto pizza : pizzaNumberIngredientsMap) {
        toppingsOfPizzaVector.push_back(make_pair(pizza.second.size(), pizza.first));
    }
    sort(toppingsOfPizzaVector.rbegin(), toppingsOfPizzaVector.rend());

    vector<vector<int>> deliveries;

    if(toppingsOfPizzaVector.size() == 5) {
        deliveries.push_back(greedyIngredientsPizzaSelector(3, toppingsOfPizzaVector, pizzaNumberIngredientsMap));
        deliveries.push_back(greedyIngredientsPizzaSelector(2, toppingsOfPizzaVector, pizzaNumberIngredientsMap));
        numberOf3PersonTeams--;
        numberOf2PersonTeams--;
    }

    while(numberOf4PersonTeams != 0 && toppingsOfPizzaVector.size() >= 4) {
        deliveries.push_back(greedyIngredientsPizzaSelector(4, toppingsOfPizzaVector, pizzaNumberIngredientsMap));
        numberOf4PersonTeams--;
    }
    while(numberOf3PersonTeams != 0 && toppingsOfPizzaVector.size() >= 3) {
        deliveries.push_back(greedyIngredientsPizzaSelector(3, toppingsOfPizzaVector, pizzaNumberIngredientsMap));
        numberOf3PersonTeams--;
    }
    while(numberOf2PersonTeams != 0 && toppingsOfPizzaVector.size() >= 2) {
        deliveries.push_back(greedyIngredientsPizzaSelector(2, toppingsOfPizzaVector, pizzaNumberIngredientsMap));
        numberOf2PersonTeams--;
    }

    ofstream fileOut(outputFile);
    fileOut << deliveries.size() << "\n";
    for(vector<int> delivery : deliveries) {
        fileOut << delivery.size() << " ";
        for(int pizzaNumber : delivery) {
            fileOut << pizzaNumber << " ";
        }
        fileOut << "\n";
    }
    fileOut.close();
}

int main() {
    string inputFile = "files/ain.txt";
    string outputFile = "files/a_output.txt";
    // string inputFile = "files/bin.in";
    // string outputFile = "files/b_output.txt";
    // string inputFile = "files/cin.in";
    // string outputFile = "files/c_output.txt";
    // string inputFile = "files/din.in";
    // string outputFile = "files/d_output.txt";
    // string inputFile = "files/ein.in";
    // string outputFile = "files/e_output.txt";

    runProgram(inputFile, outputFile);    
}
