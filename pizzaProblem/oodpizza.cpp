#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <set>
#include <unordered_map>
using namespace std;

typedef int PizzaNumber;
typedef int NumberOfIngredients;
typedef int TeamSize;
typedef string Ingredient;
typedef int IngredientNum;

typedef set<IngredientNum> IngredientsNums;
typedef unordered_map<PizzaNumber, IngredientsNums> PizzaMap;

typedef pair<NumberOfIngredients, PizzaNumber> Toppings;
typedef set<Toppings> ToppingsSet;
typedef set<Toppings>::reverse_iterator PizzaToppingsSetIter;

typedef vector<PizzaNumber> DeliveryPizzas;
typedef pair<TeamSize, DeliveryPizzas> Delivery;
typedef vector<Delivery> Deliveries;

typedef unordered_map<Ingredient, IngredientNum> IngredientsStringMap;
typedef unordered_map<IngredientNum, Ingredient> IngredientsNumMap;

class Pizzaria {
public:
    int numberOfPizzas;
    int team2;
    int team3;
    int team4;
    int team2Deliveries;
    int team3Deliveries;
    int team4Deliveries;

    PizzaMap pizzaMap; 
    ToppingsSet toppingsSet;
    Deliveries deliveries;

    IngredientsStringMap ingredientsStringMap; // ing to ingNum
    IngredientsNumMap ingredientsNumMap; // ingNum to ing

    Pizzaria(string inputFile, string outputFile) {
        initializeValues(inputFile);
        calculateDeliveries();
        outputDeliveries(outputFile);
    }

        int initializeTeamDeliveries(int teamSize, int team, int & numberOfPizzasCopy) {
            int teamSizeLeft = team;
            while(numberOfPizzasCopy >= teamSize && teamSizeLeft > 0) {
                numberOfPizzasCopy -= teamSize;
                teamSizeLeft--;
            }
            return team-teamSizeLeft;
        }

        void initializeDeliveryStats() {
            int numberOfPizzasCopy = numberOfPizzas;
            team4Deliveries = initializeTeamDeliveries(4, team4, numberOfPizzasCopy);
            team3Deliveries = initializeTeamDeliveries(3, team3, numberOfPizzasCopy);
            team2Deliveries = initializeTeamDeliveries(2, team2, numberOfPizzasCopy);
            deliveries.reserve(team4Deliveries+team3Deliveries+team2Deliveries);
        }

    void initializeValues(string inputFile) {
        ifstream file(inputFile);
        file >> numberOfPizzas >> team2 >> team3 >> team4;
        for(PizzaNumber pizzaNumber = 0; pizzaNumber < numberOfPizzas; pizzaNumber++) {
            NumberOfIngredients numberOfIngredients;
            file >> numberOfIngredients;

            IngredientsNums ingredientsNums;

            for(int i = 0; i < numberOfIngredients; i++) {
                Ingredient ingredient;
                file >> ingredient;

                IngredientNum ingredientNum;
                if(ingredientsStringMap.find(ingredient) == ingredientsStringMap.end()) {
                    ingredientNum = ingredientsStringMap.size();
                    ingredientsStringMap[ingredient] = ingredientNum;
                    ingredientsNumMap[ingredientNum] = ingredient;
                } else {
                    ingredientNum = ingredientsStringMap[ingredient];
                }
                ingredientsNums.insert(ingredientNum);
            }
            pizzaMap[pizzaNumber] = ingredientsNums;

            toppingsSet.insert(make_pair(numberOfIngredients, pizzaNumber));
        }  
        file.close();

        initializeDeliveryStats();
    }

        Delivery createDelivery(int teamSize) {
            Delivery delivery; // teamsize, pizza#, pizza#, pizza#
            delivery.first = teamSize;

            PizzaNumber mostToppingsPizzaNumber = toppingsSet.rbegin()->second;
            delivery.second.emplace_back(mostToppingsPizzaNumber);
            set<IngredientNum> teamIngredientsNumsSet;
            for(IngredientNum ingredientNum : pizzaMap[mostToppingsPizzaNumber]) {
                teamIngredientsNumsSet.insert(ingredientNum);
            }
            toppingsSet.erase(*toppingsSet.rbegin());
            pizzaMap.erase(mostToppingsPizzaNumber);

            for(int teamMember = 1; teamMember < teamSize; teamMember++) {
                auto pizzaToppingsPointer = toppingsSet.rbegin();
                Toppings mostToppingsAdded(0, 0);

                // need to improve this - is n*n rn.
                for (PizzaToppingsSetIter toppingsIter = toppingsSet.rbegin(); toppingsIter != toppingsSet.rend(); toppingsIter++) {
                    if(mostToppingsAdded.first > toppingsIter->first) { break; }

                    PizzaNumber pizzaNumber = toppingsIter->second;

                    vector<int> result;
                    set_difference(pizzaMap[pizzaNumber].begin(), pizzaMap[pizzaNumber].end(),
                                    teamIngredientsNumsSet.begin(), teamIngredientsNumsSet.end(),
                                    back_inserter(result));
                    int newToppings = result.size();
                    
                    if(newToppings >= mostToppingsAdded.first) {
                        mostToppingsAdded.first = newToppings;
                        mostToppingsAdded.second = pizzaNumber;
                        pizzaToppingsPointer = toppingsIter;
                    }
                }

                PizzaNumber mostToppingsAddedPizzaNumber = mostToppingsAdded.second;
                delivery.second.emplace_back(mostToppingsAddedPizzaNumber);

                for(IngredientNum ingredientNum : pizzaMap[mostToppingsAddedPizzaNumber]) {
                    teamIngredientsNumsSet.insert(ingredientNum);
                }

                toppingsSet.erase(*pizzaToppingsPointer);
                pizzaMap.erase(mostToppingsAddedPizzaNumber);
            } // teamsize-1

            return delivery;
        }

        void calculateDeliveriesOfTeam(int teamSize, int teamDeliveries) {
            for(int i = 0; i < teamDeliveries; i++)
                deliveries.emplace_back(createDelivery(teamSize));
        }

    void calculateDeliveries() {
        calculateDeliveriesOfTeam(4, team4Deliveries);
        calculateDeliveriesOfTeam(3, team3Deliveries);
        calculateDeliveriesOfTeam(2, team2Deliveries);
    }

    void outputDeliveries(string outputFile) {
        ofstream file(outputFile);
        file << deliveries.size() << "\n";
        for(Delivery delivery : deliveries) {
            file << delivery.first << " ";
            for(PizzaNumber pizzaNumber : delivery.second)
                file << pizzaNumber << " ";
            file << "\n";
        }
        file.close();
    }
};

int main() { // 0.23s // 0.095
    // Pizzaria pizzaria("files/ain.txt", "files/a_output.txt");
    // Pizzaria pizzaria("files/bin.in", "files/b_output.txt"); // 0.1
    Pizzaria pizzaria("files/cin.in", "files/c_output.txt"); // 10s
    // Pizzaria pizzaria("files/din.in", "files/d_output.txt"); // 1m53s
    // Pizzaria pizzaria("files/ein.in", "files/e_output.txt"); // 13m30s
}
