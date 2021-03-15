#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
using namespace std;

void getPizzaMap(map<int, vector<string>> & pizzaMap, string inputFile) {
    ifstream file(inputFile);

    string fileLine;
    getline(file, fileLine); // first line not needed

    int pizzaNumber = 0;
    while (getline(file, fileLine)) {
        istringstream iss(fileLine);
        vector<string> ingredients {istream_iterator<string> {iss}, istream_iterator<string> {}};
        ingredients.erase(ingredients.begin()); // first int is not needed
        pizzaMap[pizzaNumber] = ingredients;
        pizzaNumber++;
    }

    file.close();
}

void getOutputFile(vector<vector<int>> & teamOrders, string outputFile) {
    ifstream file(outputFile);

    string fileLine;
    getline(file, fileLine); // first line not needed

    while (getline(file, fileLine)) {
        istringstream iss(fileLine);
        vector<int> pizzaNumbers{istream_iterator<int>{iss}, istream_iterator<int>{}};
        pizzaNumbers.erase(pizzaNumbers.begin()); // first int is not needed
        teamOrders.push_back(pizzaNumbers);
    }

    file.close();
}

int calculateScore(map<int, vector<string>> & pizzaMap, vector<vector<int>> & teamOrders) {
    int score = 0;

    for (vector<int> pizzaNumbers : teamOrders) {
        set<string> teamIngredients;
        for(int pizzaNumber : pizzaNumbers) {
            for(string ingredient : pizzaMap[pizzaNumber]) {
                teamIngredients.insert(ingredient);
            }
        }
        score += teamIngredients.size()*teamIngredients.size();
    }

    return score;
}

int getScore(string inputFile, string outputFile) {
    map<int, vector<string>> pizzaMap;
    getPizzaMap(pizzaMap, inputFile);

    vector<vector<int>> teamOrders;
    getOutputFile(teamOrders, outputFile);

    return calculateScore(pizzaMap, teamOrders);
}

int main() {
    cout << "A Score: " << getScore("files/ain.txt", "files/a_output.txt") << endl; // 49
    cout << "B Score: " << getScore("files/bin.in", "files/b_output.txt") << endl; // 6,737
    cout << "C Score: " << getScore("files/cin.in", "files/c_output.txt") << endl; // 686,519,933
    cout << "D Score: " << getScore("files/din.in", "files/d_output.txt") << endl; // 5,848,016
    cout << "E Score: " << getScore("files/ein.in", "files/e_output.txt") << endl; // 8,313,931

    // cout << "B Score: " << getScore("files/bin.in", "files/hunterb.txt") << endl; // 7,244
    // cout << "C Score: " << getScore("files/cin.in", "files/hunterc.txt") << endl; // 705,442,517
    // cout << "D Score: " << getScore("files/din.in", "files/hunterd.txt") << endl; // 7,747,922
    // cout << "E Score: " << getScore("files/ein.in", "files/huntere.txt") << endl; // 10,674,218
}