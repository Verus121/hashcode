#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
using namespace std;

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

    string line;

    ifstream file(inputFile);
    getline(file, line); // first line not needed

    int iter = 0;
    map<int, vector<string>> pizzaMap;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> fileLine{istream_iterator<string>{iss}, istream_iterator<string>{}};
        pizzaMap[iter] = fileLine;
        iter++;
    }

    file.close(); // input file is loaded

    ifstream ofile(outputFile);
    getline(ofile, line); // first line not needed

    int score = 0;
    while (getline(ofile, line)) {
        istringstream iss(line);
        vector<int> fileLine{istream_iterator<int>{iss}, istream_iterator<int>{}};

        set<string> teamIngredients;
        for(int pizzaNumber = 1; pizzaNumber <= fileLine[0]; pizzaNumber++) {
            vector<string> pizza = pizzaMap[fileLine[pizzaNumber]];
            for(int i = 1; i < pizza.size(); i++) {
                teamIngredients.insert(pizza[i]);
            }
        }
        score += teamIngredients.size()*teamIngredients.size();
    }
    cout << "Score: " << score << endl;

    ofile.close();
}