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

typedef string Ingredient;
typedef vector<Ingredient> Ingredients;
typedef map<PizzaNumber, Ingredients> PizzaMap;

typedef int Toppings;
typedef pair<Toppings, PizzaNumber> PizzaToppings;
typedef set<PizzaToppings> PizzaToppingsSet;

typedef int TeamSize;
typedef vector<PizzaNumber> DeliveryPizzas;
typedef pair<TeamSize, DeliveryPizzas> Delivery;
typedef vector<Delivery> Deliveries;

int initializeValues(string filename, vector<int> & firstline, PizzaMap & pizzaMap, PizzaToppingsSet & pizzaToppingsSet) {
    ifstream file(filename);

    int numberOfPizzas, team2, team3, team4; 
    file >> numberOfPizzas >> team2 >> team3 >> team4;
    firstline = {numberOfPizzas, team2, team3, team4};

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
} // done

void printInitialValues(vector<int> & firstline, PizzaMap & pizzaMap, PizzaToppingsSet & pizzaToppingsSet) {
    cout << "print firstline \n";
    for(int i : firstline)
        cout << i << " ";
    cout << "\n\n";

    cout << "print pizzaMap \n";
    for(auto pizzaMapEl : pizzaMap) {
        cout << pizzaMapEl.first << " ";
        for(Ingredient ingredient : pizzaMapEl.second)
            cout << ingredient << " ";
        cout << "\n";
    }
    cout << "\n";

    cout << "print pizzaToppingsSet \n";
    for(PizzaToppings pizzaToppings : pizzaToppingsSet)
        cout << pizzaToppings.first << " " << pizzaToppings.second << "\n";
    cout << "\n";
} // done

void outputDeliveries(string outputFilename, Deliveries & deliveries) {
    ofstream file(outputFilename);
    file << deliveries.size() << "\n";
    for(Delivery delivery : deliveries) {
        file << delivery.first << " ";
        for(PizzaNumber pizzaNumber : delivery.second)
            file << pizzaNumber << " ";
        file << "\n";
    }
    file.close();
} // done



// TODO: initially just make it 1 function, but then branch off into seperate deliveries depending on delivery size
Delivery createDelivery(PizzaMap & pizzaMap, PizzaToppingsSet & pizzaToppingsSet, int deliverySize) {
    Delivery delivery;
    delivery.first = deliverySize;
    for(int i = 0; i < deliverySize; i++) {
        PizzaNumber pizzaNumber = pizzaToppingsSet.rbegin()->second;
        delivery.second.push_back(pizzaNumber);
        pizzaToppingsSet.erase(prev(pizzaToppingsSet.end()));
    }
    return delivery;
}


// TODO 
void calculateDeliveries(vector<int> & firstline, PizzaMap & pizzaMap, PizzaToppingsSet & pizzaToppingsSet, Deliveries & deliveries) {    
    int totalPizzas = firstline[0];
    int team2 = firstline[1];
    int team3 = firstline[2];
    int team4 = firstline[3];

    while (totalPizzas >= 4 && team4 >= 1) {
        deliveries.push_back(createDelivery(pizzaMap, pizzaToppingsSet, 4));
        totalPizzas -= 4;
        team4--;
    }

    while (totalPizzas >= 3 && team3 >= 1) {
       deliveries.push_back(createDelivery(pizzaMap, pizzaToppingsSet, 3));
        totalPizzas -= 3;
        team3--;
    }

    while (totalPizzas >= 2 && team2 >= 1) {
        deliveries.push_back(createDelivery(pizzaMap, pizzaToppingsSet, 2));
        totalPizzas -= 2;
        team2--;
    }
}

void calculateDeliveries(string inputFilename, string outputFilename) {
    vector<int> firstline;
    PizzaMap pizzaMap;
    PizzaToppingsSet pizzaToppingsSet;
    Deliveries deliveries;

    initializeValues(inputFilename, firstline, pizzaMap, pizzaToppingsSet);
    // printInitialValues(firstline, pizzaMap, pizzaToppingsSet); // for testing
    calculateDeliveries(firstline, pizzaMap, pizzaToppingsSet, deliveries);
    outputDeliveries(outputFilename, deliveries);
}

int main() {
    // calculateDeliveries("files/ain.txt", "files/a_output.txt");   // 49 | 0.01s
    // calculateDeliveries("files/bin.in", "files/b_output.txt"); // 6737 | 0.05s
    // calculateDeliveries("files/cin.in", "files/c_output.txt"); // 220,910,920 | 0.9s
    // calculateDeliveries("files/din.in", "files/d_output.txt"); // 2,140,547 | 1m43s
    calculateDeliveries("files/ein.in", "files/e_output.txt"); // 7,326,413 | 22m18s
}
