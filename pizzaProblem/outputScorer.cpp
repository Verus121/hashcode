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
    int fileAScore = getScore("files/ain.txt", "files/a_output.txt");
    int fileBScore = getScore("files/bin.in", "files/b_output.txt");
    int fileCScore = getScore("files/cin.in", "files/c_output.txt");
    int fileDScore = getScore("files/din.in", "files/d_output.txt");
    int fileEScore = getScore("files/ein.in", "files/e_output.txt");
    int finalScore = fileAScore + fileBScore + fileCScore + fileDScore + fileEScore;

    cout << "A Score: " << fileAScore << "\n"; // 49
    cout << "B Score: " << fileBScore << "\n"; // 11,555
    cout << "C Score: " << fileCScore << "\n"; // 706,947,263
    cout << "D Score: " << fileDScore << "\n"; // 7,865,154
    cout << "E Score: " << fileEScore << "\n"; // 10,791,650

    cout << "Final Score: " << finalScore << "\n";
}