#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fstream>
#include <set>
using namespace std;

class Pizza {
    public:
        int numOfIngredients;
        int pizzaNumber;
        vector<string> ingredients;

        bool operator<(const Pizza &r) {
            if (numOfIngredients != r.numOfIngredients) {
                return numOfIngredients < r.numOfIngredients;
            }
            return numOfIngredients > r.numOfIngredients;
        }
};

class Pizzaria {
    public:
        int numberOfPizzas;
        int numOf2PersonTeams;
        int numOf3PersonTeams;
        int numOf4PersonTeams;
        vector<Pizza> pizzaList;

        Pizzaria(string inputFile) {
            ifstream file(inputFile);

            string line;
            vector<vector<string>> fileLines;
            while (getline(file, line)) {
                istringstream iss(line);
                vector<string> fileLine{istream_iterator<string>{iss}, istream_iterator<string>{}};
                fileLines.push_back(fileLine);
            }

            numberOfPizzas = stoi(fileLines[0][0]);
            numOf2PersonTeams = stoi(fileLines[0][1]);
            numOf3PersonTeams = stoi(fileLines[0][2]);
            numOf4PersonTeams = stoi(fileLines[0][3]);

            for (int i = 1; i < fileLines.size(); i++) {
                Pizza pizza;
                pizza.numOfIngredients = stoi(fileLines[i][0]);
                for (int j = 1; j < fileLines[i].size(); j++) {
                    pizza.ingredients.push_back(fileLines[i][j]);
                }
                pizza.pizzaNumber = pizzaList.size();
                pizzaList.push_back(pizza);
            }

            file.close();
        };
};

class TeamOrder {
    public:
        int teamSize;             // 2 3 or 4
        vector<int> pizzaNumbers; 
};

class Deliveries {
    public:
        int numberOfDeliveries;
        vector<TeamOrder> teamOrders;
};

// TODO: need to test now, and find error with smart order

void smartestAddTeamOrder(int teamSize, vector<Pizza> &copyPizzaList, Deliveries &deliveries) {
    TeamOrder teamOrder;
    teamOrder.teamSize = teamSize;

    set<string> teamOrderIngredients;

    // lets auto add the first one. 
    Pizza pizza = copyPizzaList[0];
    for (string ingredient : pizza.ingredients) {
        teamOrderIngredients.insert(ingredient);
    }
    teamOrder.pizzaNumbers.push_back(pizza.pizzaNumber);
    copyPizzaList.erase(copyPizzaList.begin());

    for (int teamMemberIter = 1; teamMemberIter < teamSize; teamMemberIter++) {

        vector<pair<int, int>> pizzaScores; // can just be a vector of ints now.

        // find scores of top 10 pizzas.
        for (int copyPizzaListIter = 0; copyPizzaListIter < copyPizzaList.size() && copyPizzaListIter < 10; copyPizzaListIter++) {
            Pizza pizza = copyPizzaList[copyPizzaListIter];
            set<string> copyTeamOrderIngredients = teamOrderIngredients; // use a hash?

            for (string ingredient : pizza.ingredients) {
                copyTeamOrderIngredients.insert(ingredient);
            }

            int pizzaScore = copyTeamOrderIngredients.size() - teamOrderIngredients.size(); // remove to opt
            pizzaScores.emplace_back(pizzaScore, pizza.pizzaNumber); // swapping
        }

        // pizzaScore, pizza.pizzaNumber
        sort(pizzaScores.begin(), pizzaScores.end());
        pair<int, int> currentBestPizza = pizzaScores.back();

        int currentBestPizzaIter = 0; // easy delete
        for(; currentBestPizzaIter < pizzaScores.size(); currentBestPizzaIter++) {
            if(currentBestPizza.second == copyPizzaList[currentBestPizzaIter].pizzaNumber) {
                break;
            }
        }

        teamOrder.pizzaNumbers.push_back(currentBestPizza.second);
        copyPizzaList.erase(copyPizzaList.begin() + currentBestPizzaIter); // and this is why we needed that iter.
    }

    deliveries.teamOrders.push_back(teamOrder);
}

void dumbAddTeamOrder(int teamSize, vector<Pizza> &copyPizzaList, Deliveries &deliveries) {
    TeamOrder order;
    order.teamSize = teamSize;

    for(int i = 0; i < teamSize; i++) {
        order.pizzaNumbers.push_back(copyPizzaList[0].pizzaNumber);
        copyPizzaList.erase(copyPizzaList.begin());
    } // this is fastest i think


    deliveries.teamOrders.push_back(order);
}

void addTeamOrder(int teamSize, vector<Pizza> &copyPizzaList, Deliveries &deliveries) {
    dumbAddTeamOrder(teamSize, copyPizzaList, deliveries);
    // smartestAddTeamOrder(teamSize, copyPizzaList, deliveries);
}

void algorithm4(Pizzaria &pizzaria, Deliveries &deliveries) {
    vector<Pizza> copyPizzaList = pizzaria.pizzaList;

    int numbersOfPizzaLeft = pizzaria.numberOfPizzas;

    int numberOf4TeamsLeft = pizzaria.numOf4PersonTeams;
    while (numbersOfPizzaLeft >= 4 && numberOf4TeamsLeft >= 1) {
        addTeamOrder(4, copyPizzaList, deliveries);
        numbersOfPizzaLeft = numbersOfPizzaLeft - 4;
        numberOf4TeamsLeft = numberOf4TeamsLeft - 1;
    }

    int numberOf3TeamsLeft = pizzaria.numOf3PersonTeams;
    while (numbersOfPizzaLeft >= 3 && numberOf3TeamsLeft >= 1) {
        addTeamOrder(3, copyPizzaList, deliveries);
        numbersOfPizzaLeft = numbersOfPizzaLeft - 3;
        numberOf3TeamsLeft = numberOf3TeamsLeft - 1;
    }

    int numberOf2TeamsLeft = pizzaria.numOf2PersonTeams;
    while (numbersOfPizzaLeft >= 2 && numberOf2TeamsLeft >= 1) {
        addTeamOrder(2, copyPizzaList, deliveries);
        numbersOfPizzaLeft = numbersOfPizzaLeft - 2;
        numberOf2TeamsLeft = numberOf2TeamsLeft - 1;
    }

    deliveries.numberOfDeliveries = deliveries.teamOrders.size();
}


void printDelivery(string outputFileA, Deliveries deliveries) {
    ofstream outputFile(outputFileA);

    outputFile << deliveries.numberOfDeliveries << "\n";

    for(TeamOrder order : deliveries.teamOrders) {
        ostringstream oss;
        oss << order.teamSize << " ";
        for(int pizzaNumber : order.pizzaNumbers) {
            oss << pizzaNumber << " ";
        }
        outputFile << oss.str() << "\n";
    }

    outputFile.close();
}

void printScore(Pizzaria & pizzaria, Deliveries & deliveries) {
    int score = 0;

    for (TeamOrder order : deliveries.teamOrders) {
        set<string> teamIngredients;
        for(int pizzaNumber : order.pizzaNumbers) {
            for(string ingredient : pizzaria.pizzaList[pizzaNumber].ingredients) {
                teamIngredients.insert(ingredient);
            }
        }
        score += teamIngredients.size()*teamIngredients.size();
    }

    cout << "Score: " << score << endl;
}

int main() {
    // dumb C_output real 6.7
    // smart C_output real 6.8

    // string inputFile = "files/ain.txt";
    // string outputFile = "files/a_output.txt";
    string inputFile = "files/bin.in";
    string outputFile = "files/b_output.txt";
    // string inputFile = "files/cin.in";
    // string outputFile = "files/c_output.txt"; 
    // string inputFile = "files/din.in";
    // string outputFile = "files/d_output.txt"; // 6m
    // string inputFile = "files/ein.in";
    // string outputFile = "files/e_output.txt"; // 14m

    Pizzaria pizzaria(inputFile);
    sort(pizzaria.pizzaList.begin(), pizzaria.pizzaList.end());
    Deliveries deliveries;

    algorithm4(pizzaria, deliveries);

    printDelivery(outputFile, deliveries);
    printScore(pizzaria, deliveries);
    return 0;
}