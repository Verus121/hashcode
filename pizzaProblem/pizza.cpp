#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
using namespace std;


int main() {
    ifstream file("files/ain.txt"); // 5
    // ifstream file("files/bin.in"); // 500
    // ifstream file("files/cin.in"); // 10,000p
    // ifstream file("files/din.in"); // 100,000p 
    // ifstream file("files/ein.in"); // 100,000p

    string line;
    getline(file, line);
    istringstream iss(line);
    vector<string> fileLine{istream_iterator<string>{iss}, istream_iterator<string>{}};
    int numOfPizzas = stoi(fileLine[0]);
    int numOfTeam2 = stoi(fileLine[1]);
    int numOfTeam3 = stoi(fileLine[2]);
    int numOfTeam4 = stoi(fileLine[3]);
    cout << numOfPizzas << " " << numOfTeam2 << " " << numOfTeam3 << " " << numOfTeam4 << endl;

    int iter = 0;
    map<int, vector<string>> pizzaMap;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> fileLine{istream_iterator<string>{iss}, istream_iterator<string>{}};
        pizzaMap[iter] = fileLine;
        iter++;
    }

    int pizzasLeft = numOfPizzas;
    int numOfdeliveries = 0;

    int team4sLeft = numOfTeam4;
    while (pizzasLeft >= 4 && team4sLeft >= 1) {
        numOfdeliveries++;
        pizzasLeft -= 4;
        team4sLeft--;
    }

    int team3sLeft = numOfTeam3;
    while (pizzasLeft >= 3 && team3sLeft >= 1) {
        numOfdeliveries++;
        pizzasLeft -= 3;
        team3sLeft--;
    }

    int team2sLeft = numOfTeam2;
    while (pizzasLeft >= 2 && team2sLeft >= 1) {
        numOfdeliveries++;
        pizzasLeft -= 2;
        team2sLeft--;
    }

    cout << numOfdeliveries << endl;

    file.close();
}