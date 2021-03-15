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

typedef string Ingredient;
typedef int IngredientNum;
typedef unordered_map<Ingredient, IngredientNum> IngredientsStringMap;
typedef unordered_map<IngredientNum, Ingredient> IngredientsNumMap;

int main() {
    vector<string> input;
    input.push_back("a");
    input.push_back("b");
    input.push_back("c");
    input.push_back("d");
    input.push_back("a");
    input.push_back("c");
    input.push_back("b");

    IngredientsStringMap ingredientsStringMap;
    IngredientsNumMap ingredientsNumMap;

    for(string s : input) {
        IngredientsStringMap::const_iterator ingredientsMapIter = ingredientsStringMap.find(s);
        bool ingredientNotInMap = ingredientsMapIter == ingredientsStringMap.end();
        if(ingredientNotInMap) {
            int i = ingredientsStringMap.size();
            ingredientsStringMap[s] = i;
            ingredientsNumMap[i] = s;
        } else {
            cout << ingredientsStringMap[s] << " here ya go \n";
        }
    }

    cout << "strToNummap cout \n";
    for(auto a : ingredientsStringMap)
        cout << a.first << " " << a.second << "\n";

    cout << "numToStrmap cout \n";
    for(auto a : ingredientsNumMap)
        cout << a.first << " " << a.second << "\n";

}