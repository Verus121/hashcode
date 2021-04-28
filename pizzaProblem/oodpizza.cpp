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
#include <unordered_set>
using namespace std;

typedef int PizzaNumber;
typedef int NumberOfIngredients;
typedef int TeamSize;
typedef int IngredientNum;
typedef string Ingredient;

typedef unordered_set<IngredientNum> IngredientsNums;
typedef unordered_map<PizzaNumber, IngredientsNums> PizzaMap;

typedef unordered_map<Ingredient, IngredientNum> IngredientsToNumMap;

typedef pair<NumberOfIngredients, PizzaNumber> ToppingsOfPizza;
typedef set<ToppingsOfPizza> ToppingsSet;
typedef set<ToppingsOfPizza>::reverse_iterator ToppingsSetIter;    

typedef vector<PizzaNumber> DeliveryPizzas;
typedef pair<TeamSize, DeliveryPizzas> Delivery;
typedef vector<Delivery> Deliveries;


class Pizzaria {
public:
    int team2Deliveries;
    int team3Deliveries;
    int team4Deliveries;

    PizzaMap pizzaMap; 
    ToppingsSet toppingsSet;
    Deliveries deliveries;

    Pizzaria(const string inputFile, const string outputFile) {
        initializeValues(inputFile);
        calculateDeliveries();
        outputDeliveries(outputFile);
    }

    int initializeTeamDeliveries(const int teamSize, const int team, int & numberOfPizzas) {
        int teamDeliveries;
        for(teamDeliveries = 0; teamDeliveries < team; teamDeliveries++) {
            if(numberOfPizzas < teamSize) break;
            numberOfPizzas -= teamSize;
        }
        return teamDeliveries;
    }

    void initializeValues(const string inputFile) {
        ifstream file(inputFile);
        int numberOfPizzas, team2, team3, team4;
        file >> numberOfPizzas >> team2 >> team3 >> team4;

        IngredientsToNumMap ingredientsToNumMap;
        
        for(PizzaNumber pizzaNumber = 0; pizzaNumber < numberOfPizzas; pizzaNumber++) {
            NumberOfIngredients numberOfIngredients;
            file >> numberOfIngredients;

            IngredientsNums ingredientsNums;
            for(int i = 0; i < numberOfIngredients; i++) {
                Ingredient ingredient;
                file >> ingredient;
                ingredientsToNumMap.emplace(ingredient, ingredientsToNumMap.size()); // Important
                ingredientsNums.emplace(ingredientsToNumMap[ingredient]);
            }
            pizzaMap[pizzaNumber] = ingredientsNums;

            toppingsSet.emplace(numberOfIngredients, pizzaNumber);
        }

        team4Deliveries = initializeTeamDeliveries(4, team4, numberOfPizzas);
        team3Deliveries = initializeTeamDeliveries(3, team3, numberOfPizzas);
        team2Deliveries = initializeTeamDeliveries(2, team2, numberOfPizzas);
        deliveries.reserve(team4Deliveries+team3Deliveries+team2Deliveries);

        file.close();
    }

    Delivery createDelivery(const int teamSize) {
        Delivery delivery; // teamsize, pizza#, pizza#, pizza#
        delivery.first = teamSize;

        PizzaNumber mostToppingsPizzaNumber = toppingsSet.rbegin()->second;
        set<int> teamIngredientsNumsSet = pizzaMap[mostToppingsPizzaNumber];
        delivery.second.emplace_back(mostToppingsPizzaNumber);
        toppingsSet.erase(*toppingsSet.rbegin());

        for(int teamMember = 1; teamMember < teamSize; teamMember++) {
            ToppingsSetIter toppingsSetPointer = toppingsSet.rbegin();
            pair<int, int> toppingsAddedOfPizza(0, toppingsSet.rend()->second);

            for (ToppingsSetIter toppingsIter = toppingsSet.rbegin(); toppingsIter != toppingsSet.rend(); toppingsIter++) {
                if(toppingsAddedOfPizza.first > toppingsIter->first) break;

                PizzaNumber pizzaNumber = toppingsIter->second;
                vector<int> newToppings(pizzaMap[pizzaNumber].size()+teamIngredientsNumsSet.size());
                set_difference(pizzaMap[pizzaNumber].begin(), pizzaMap[pizzaNumber].end(), teamIngredientsNumsSet.begin(), teamIngredientsNumsSet.end(), back_inserter(newToppings));
                if(newToppings.size() > toppingsAddedOfPizza.first) {
                    toppingsAddedOfPizza = make_pair(newToppings.size(), pizzaNumber);
                    toppingsSetPointer = toppingsIter;
                }
            }

            PizzaNumber pizzaNumber = toppingsAddedOfPizza.second;
            teamIngredientsNumsSet.insert(pizzaMap[pizzaNumber].begin(), pizzaMap[pizzaNumber].end());
            delivery.second.emplace_back(pizzaNumber);
            toppingsSet.erase(*toppingsSetPointer);
        }

        return delivery;
    }

    void calculateDeliveries() {
        int i;
        for(i = 0; i < team4Deliveries; i++)
            deliveries.push_back(createDelivery(4));
        for(i = 0; i < team3Deliveries; i++)
            deliveries.push_back(createDelivery(3));
        for(i = 0; i < team2Deliveries; i++)
            deliveries.push_back(createDelivery(2));
    }

    void outputDeliveries(const string outputFile) {
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

int main() { // 4 seconds
    Pizzaria pizzariaA("files/ain.txt", "files/a_output.txt");
    Pizzaria pizzariaB("files/bin.in", "files/b_output.txt"); // 0.1/
    Pizzaria pizzariaC("files/cin.in", "files/c_output.txt"); // 9.8s
    Pizzaria pizzariaD("files/din.in", "files/d_output.txt"); // 1m53s
    Pizzaria pizzariaE("files/ein.in", "files/e_output.txt"); // 13m30s
}
