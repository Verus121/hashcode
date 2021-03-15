#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

vector<int> alg5(map<int, vector<string>> & pizzaMap, int teamSize) {
    vector<int> teamOrder;
    teamOrder.push_back(teamSize);

    set<string> teamIngredients;

    // Need to make this fasterrr

    for(int i = 0; i < teamSize; i++) {
        vector<pair<int, int>> pizzaScores;
        int mostPizzaToppings = 0;

        for(const auto & pizza : pizzaMap) {

            // this should help make things go faster
            if(pizza.second.size() < mostPizzaToppings) {
                break;
            } else if (pizza.second.size() > mostPizzaToppings) {
                mostPizzaToppings = pizza.second.size();
            }

            set<string> copyTeamIngredients = teamIngredients;
            for (string ingredient : pizza.second) {
                copyTeamIngredients.insert(ingredient);
            }
            int pizzaScore = copyTeamIngredients.size() - teamIngredients.size();
            pizzaScores.emplace_back(pizzaScore, pizza.first);
        }

        sort(pizzaScores.rbegin(), pizzaScores.rend()); // sorts in decending order

        int bestScorePizzaNumber = pizzaScores[0].second;
        teamOrder.push_back(bestScorePizzaNumber);
        pizzaMap.erase(bestScorePizzaNumber);
    }
    
    return teamOrder;
}

vector<int> alg7(map<int, vector<string>> & pizzaMap, set<pair<int, int>> & pizzaStats, int teamSize) {
    vector<int> teamOrder;
    teamOrder.push_back(teamSize);

    // take first out, then use greedy on the rest.
    for(int i = 0; i < teamSize; i++) {
        int pizzaNumber = pizzaStats.rbegin()->second;  
        teamOrder.push_back(pizzaNumber);
        pizzaMap.erase(pizzaNumber);
        pizzaStats.erase(prev(pizzaStats.end()));
    }

    return teamOrder;
}

// How to make this smaller? 
void initValues(string input, vector<string> & firstLine, map<int, vector<string>> & pizzaMap) {
    ifstream file(input);

    string fileLine;
    getline(file, fileLine);
    istringstream iss(fileLine);
    vector<string> v{istream_iterator<string>{iss}, istream_iterator<string>{}};
    firstLine = v;

    int pizzaNumber = 0;
    while (getline(file, fileLine)) {
        istringstream iss(fileLine);
        vector<string> ingredients {istream_iterator<string>{iss}, istream_iterator<string>{}};
        ingredients.erase(ingredients.begin()); // first int is not needed
        pizzaMap[pizzaNumber] = ingredients;
        pizzaNumber++;
    }

    file.close();
}

void outputDeliveries(string output, vector<vector<int>> & deliveries) {
    ofstream outputFile(output);

    outputFile << deliveries.size() << "\n";

    for(vector<int> order : deliveries) {
        ostringstream oss;
        for(int orderInt : order) {
            oss << orderInt << " ";
        }
        outputFile << oss.str() << "\n";
    }

    outputFile.close();
}

void calculateDeliveries(string inputFile, string outputFile) {
    vector<string> firstLine;    
    map<int, vector<string>> pizzaMap;

    initValues(inputFile, firstLine, pizzaMap);

    int numOfPizzas = stoi(firstLine[0]);
    int numOfTeam2s = stoi(firstLine[1]);
    int numOfTeam3s = stoi(firstLine[2]);
    int numOfTeam4s = stoi(firstLine[3]);

    set<pair<int, int>> pizzaStats; // numOfIng, pizzaNum    ordered in reverse
    for(int pizzaNumber = 0; pizzaNumber < pizzaMap.size(); pizzaNumber++) {
        pair<int, int> pizzaStat;
        pizzaStat.first = pizzaMap[pizzaNumber].size();
        pizzaStat.second = pizzaNumber;
        pizzaStats.insert(pizzaStat);
    }

    vector<vector<int>> deliveries;

    // replace with function?
    while (numOfPizzas >= 4 && numOfTeam4s >= 1) {
        deliveries.push_back(alg7(pizzaMap, pizzaStats, 4));
        numOfPizzas -= 4;
        numOfTeam4s--;
    }

    while (numOfPizzas >= 3 && numOfTeam3s >= 1) {
        deliveries.push_back(alg7(pizzaMap, pizzaStats, 3));
        numOfPizzas -= 3;
        numOfTeam3s--;
    }

    while (numOfPizzas >= 2 && numOfTeam2s >= 1) {
        deliveries.push_back(alg7(pizzaMap, pizzaStats, 2));
        numOfPizzas -= 2;
        numOfTeam2s--;
    }

    outputDeliveries(outputFile, deliveries);
}

int main() {
    // calculateDeliveries("files/ain.txt", "files/a_output.txt"); // 49 | 0.01s
    // calculateDeliveries("files/bin.in", "files/b_output.txt"); // 6737 | 0.05s
    calculateDeliveries("files/cin.in", "files/c_output.txt"); // 220,910,920 | 0.9s
    // calculateDeliveries("files/din.in", "files/d_output.txt"); // 2,140,547 | 1m43s
    // calculateDeliveries("files/ein.in", "files/e_output.txt"); // 7,326,413 | 22m18s
}