#pragma once

#include <vector>
using namespace std;


#include "teamorder.h"

class Deliveries {
    public:
        int numberOfDeliveries;
        vector<TeamOrder> teamOrders;
};