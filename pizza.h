#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <utility>


using namespace std;

class Pizza {
    public: 
        int numOfIngredients;
        int pizzaNumber;
        vector<string> ingredients;

        // overload the operator<
        bool operator<(const Pizza& r) const
        {
            if (numOfIngredients != r.numOfIngredients)
                return numOfIngredients > r.numOfIngredients;
            return numOfIngredients > r.numOfIngredients;
        }
};