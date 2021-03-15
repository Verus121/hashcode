#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <set>
using namespace std;

typedef int PizzaNumber;
typedef int Toppings;
typedef int TeamSize;
typedef string Ingredient;

typedef vector<Ingredient> Ingredients;
typedef map<PizzaNumber, Ingredients> PizzaMap;

typedef pair<Toppings, PizzaNumber> PizzaToppings;
typedef set<PizzaToppings> PizzaToppingsSet;
typedef set<PizzaToppings>::reverse_iterator PizzaToppingsSetIter;

typedef vector<PizzaNumber> DeliveryPizzas;
typedef pair<TeamSize, DeliveryPizzas> Delivery;
typedef vector<Delivery> Deliveries;

class Pizzaria {
public:
    int numberOfPizzas;
    int team2;
    int team3;
    int team4;
    int pizzasToDeliver;
    int team2Deliveries;
    int team3Deliveries;
    int team4Deliveries;
    int totalDeliveries;

    PizzaMap pizzaMap;
    PizzaToppingsSet pizzaToppingsSet;
    Deliveries deliveries;

    Pizzaria(string inputFile, string outputFile) {
        initializeValues(inputFile);
        calculateDeliveries();
        outputDeliveries(outputFile);
    }

    void initializeValues(string inputFile) {
        ifstream file(inputFile);
        file >> numberOfPizzas >> team2 >> team3 >> team4;
        for(PizzaNumber pizzaNumber = 0; pizzaNumber < numberOfPizzas; pizzaNumber++) {
            Toppings toppings;
            file >> toppings;
            Ingredients ingredients;
            for(int i = 0; i < toppings; i++) {
                Ingredient ingredient;
                file >> ingredient;
                ingredients.push_back(ingredient);
            }
            pizzaMap[pizzaNumber] = ingredients;
            PizzaToppings pizzaToppings; 
            pizzaToppings.first = toppings;
            pizzaToppings.second = pizzaNumber;
            pizzaToppingsSet.insert(pizzaToppings);
        }  
        file.close();

        int numberOfPizzasCopy = numberOfPizzas;
        int team2Copy = team2;
        int team3Copy = team3;
        int team4Copy = team4;
        while(numberOfPizzasCopy >= 4 && team4Copy > 0) {
            numberOfPizzasCopy -= 4;
            team4Copy--;
        }
        while(numberOfPizzasCopy >= 3 && team3Copy > 0) {
            numberOfPizzasCopy -= 3;
            team3Copy--;
        }
        while(numberOfPizzasCopy >= 2 && team2Copy > 0) {
            numberOfPizzasCopy -= 2;
            team2Copy--;
        }
        pizzasToDeliver = numberOfPizzas - numberOfPizzasCopy;
        team2Deliveries = team2 - team2Copy;
        team3Deliveries = team3 - team3Copy;
        team4Deliveries = team4 - team4Copy;
        totalDeliveries = team2Deliveries + team3Deliveries + team4Deliveries;
    }

    Delivery createDelivery(int teamSize) {
        Delivery delivery;
        delivery.first = teamSize;

        PizzaNumber mostToppingsPizzaNumber = pizzaToppingsSet.rbegin()->second;
        delivery.second.push_back(mostToppingsPizzaNumber);

        set<string> teamToppings;
        for(Ingredient ingredient : pizzaMap[mostToppingsPizzaNumber]) {
            teamToppings.insert(ingredient);
        }

        pizzaToppingsSet.erase(*pizzaToppingsSet.rbegin());
        pizzaMap.erase(mostToppingsPizzaNumber);

        for(int teamMember = 1; teamMember < teamSize; teamMember++) {
            auto pizzaToppingsPointer = pizzaToppingsSet.rbegin(); // new
            pair<Toppings, PizzaNumber> mostToppingsAdded(0, 0);

            // need to improve this - is n*n rn.
            for (PizzaToppingsSetIter toppingsIter = pizzaToppingsSet.rbegin(); toppingsIter != pizzaToppingsSet.rend(); toppingsIter++) {
                if(mostToppingsAdded.first > toppingsIter->first) { break; }

                PizzaNumber pizzaNumber = toppingsIter->second;

                set<string> copyTeamToppings = teamToppings;
                copy(pizzaMap[pizzaNumber].begin(), pizzaMap[pizzaNumber].end(), inserter(copyTeamToppings, copyTeamToppings.end()));
                
                int newToppings = copyTeamToppings.size() - teamToppings.size();
                if(newToppings >= mostToppingsAdded.first) {
                    mostToppingsAdded.first = newToppings;
                    mostToppingsAdded.second = pizzaNumber;
                    pizzaToppingsPointer = toppingsIter; // new
                }
            }

            PizzaNumber mostToppingsAddedPizzaNumber = mostToppingsAdded.second;
            delivery.second.push_back(mostToppingsAddedPizzaNumber);

            for(Ingredient ingredient : pizzaMap[mostToppingsAddedPizzaNumber]) {
                teamToppings.insert(ingredient);
            }

            pizzaToppingsSet.erase(*pizzaToppingsPointer);
            pizzaMap.erase(mostToppingsAddedPizzaNumber);
        } // teamsize-1

        return delivery;
    }

    void calculateDeliveriesOfTeam(int teamSize, int & teamsLeft) {
        while (numberOfPizzas >= teamSize && teamsLeft >= 1) {
            deliveries.push_back(createDelivery(teamSize));
            numberOfPizzas -= teamSize;
            teamsLeft--;
        }
    }

    void calculateDeliveries() {
        calculateDeliveriesOfTeam(4, team4);
        calculateDeliveriesOfTeam(3, team3);
        calculateDeliveriesOfTeam(2, team2);
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

int main() {
    // Pizzaria pizzaria("files/ain.txt", "files/a_output.txt");   // 49 | 0.01s
    Pizzaria pizzaria("files/bin.in", "files/b_output.txt"); // 6737 | 0.288s
    // Pizzaria pizzaria("files/cin.in", "files/c_output.txt"); // 220,910,920 | 0.9s
    // Pizzaria pizzaria("files/din.in", "files/d_output.txt"); // 2,140,547 | 1m43s
    // Pizzaria pizzaria("files/ein.in", "files/e_output.txt"); // 7,326,413 | 22m18s
}
