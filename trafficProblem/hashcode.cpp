#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fstream>
#include <set>
using namespace std;

class Street {
    public: 
        int beginIntersection;
        int endIntersection;
        string streetName;
        int streetTime;
};

class Car {
    public:
        int streetsToTravel;
        vector<Street> streets;
};

class Traffic {
    public:
        int simTime;
        int numOfIntersections;
        int numOfStreets;
        int numOfCars;
        int bonusPoints;
        vector<Street> streets;
        vector<Car> cars;

        Traffic(string inputFile) {
            ifstream file(inputFile);

            // put input into 2d vector of strings
            string line;
            vector<vector<string>> fileLines;
            while (getline(file, line)) {
                istringstream iss(line);
                vector<string> fileLine{istream_iterator<string>{iss}, istream_iterator<string>{}};
                fileLines.push_back(fileLine);
            }

            simTime = stoi(fileLines[0][0]);
            numOfIntersections = stoi(fileLines[0][1]);
            numOfStreets = stoi(fileLines[0][2]);
            numOfCars = stoi(fileLines[0][3]);
            bonusPoints = stoi(fileLines[0][4]);

            for(int i = 1; i <= numOfStreets; i++) {
                Street street;
                street.beginIntersection = stoi(fileLines[i][0]);
                street.endIntersection = stoi(fileLines[i][1]);
                street.streetName = fileLines[i][2];
                street.streetTime = stoi(fileLines[i][3]);
                streets.push_back(street);
            }

            for(int i = numOfStreets+1; i <= (numOfStreets+numOfCars); i++) {
                Car car;
                car.streetsToTravel = stoi(fileLines[i][0]);
                for(int si = 1; si <= car.streetsToTravel; si++) {
                    string carStreetName = fileLines[i][si];
                    for(Street street : streets) {
                        if(street.streetName == carStreetName) {
                            car.streets.push_back(street);
                            break;
                        }
                    }
                }
                cars.push_back(car);
            }

            file.close();
        }
};

class Intersection {
    public:
        int interId;
        int incomingStreets = 0;
        vector<pair<string, int>> streetLights;
};

class Schedule {
    public:
        int numOfintersections;
        vector<Intersection> intersections; // id is the vector iter? no
};

void printDelivery(string outputFileA, Schedule schedule) {
    ofstream outputFile(outputFileA);

    outputFile << schedule.numOfintersections << "\n";

    int numberOfStreetsCrossed = 0;
    int streetLightsCrossed = 0;

    for(Intersection intersection : schedule.intersections) {
        for(pair<string, int> streetLight : intersection.streetLights) {
            numberOfStreetsCrossed++;
            streetLightsCrossed += streetLight.second;
        }
    }

    int avg = streetLightsCrossed / numberOfStreetsCrossed;
    cout << avg << " more than this is abnormal \n";

    for(Intersection intersection : schedule.intersections) {
        outputFile << intersection.interId << "\n";
        outputFile << intersection.incomingStreets << "\n";
        for(pair<string, int> streetLight : intersection.streetLights) {
            if(streetLight.second > avg*10) {
                outputFile << streetLight.first << " " << 3 << "\n";
            } else {
                outputFile << streetLight.first << " " << 1 << "\n";
            }
        }
    }

    outputFile.close();
}

void alg(Traffic & traffic, Schedule & schedule) {

    for(Car car : traffic.cars) {
        for(int i = 0; i < car.streets.size()-1; i++) {

            bool intersectExists = false;
            for(Intersection &intersect : schedule.intersections) {
                if(intersect.interId == car.streets[i].endIntersection) {
                    intersectExists = true;

                    bool is_street_counted = false;
                    for(pair<string, int> & streetLight : intersect.streetLights) {
                        if (streetLight.first == car.streets[i].streetName) {
                            is_street_counted = true;

                            // TODO:
                            streetLight.second++;
                            break;
                        }
                    }
                    if(!is_street_counted) {
                        intersect.incomingStreets++;
                        pair<string, int> streetLight;
                        streetLight.first = car.streets[i].streetName;
                        streetLight.second = 1;
                        intersect.streetLights.push_back(streetLight);
                    }
                    break;
                }
            }

            if(!intersectExists) {
                Intersection intersect;
                intersect.interId = car.streets[i].endIntersection;
                intersect.incomingStreets++;
                pair<string, int> streetLight;
                streetLight.first = car.streets[i].streetName;
                streetLight.second = 1;
                intersect.streetLights.push_back(streetLight);

                schedule.intersections.push_back(intersect);
            }

        } // for every street
    } // for all cars

    // now make busy lights longer. 


    schedule.numOfintersections = schedule.intersections.size();
}

int main() {
    // string inputFile = "files/a.txt";
    // string outputFile = "files/a_output.txt"; // .01
    string inputFile = "files/b.txt";
    string outputFile = "files/b_output.txt"; // 5.3
    // string inputFile = "files/c.txt";
    // string outputFile = "files/c_output.txt"; // 55
    // string inputFile = "files/d.txt";
    // string outputFile = "files/d_output.txt"; // 5m5
    // string inputFile = "files/e.txt";
    // string outputFile = "files/e_output.txt"; // .1s
    // string inputFile = "files/f.txt";
    // string outputFile = "files/f_output.txt"; // 39s

    Traffic traffic(inputFile);
    Schedule schedule;
    alg(traffic, schedule);

    printDelivery(outputFile, schedule);
}