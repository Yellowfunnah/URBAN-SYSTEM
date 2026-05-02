#pragma once
#include <string>
using namespace std;

class Resident {
public:
    string residentID;
    int age;
    string transportMode;
    double dailyDistance;
    double emissionFactor;
    int averageDays;

    Resident() {
        residentID = "";
        age = 0;
        transportMode = "";
        dailyDistance = 0;
        emissionFactor = 0;
        averageDays = 0;
    }

    double calculateMonthlyEmission() const {
        return dailyDistance * emissionFactor * averageDays;
    }

    string getAgeGroup() {
        if (age >= 6 && age <= 17)
            return "Children & Teenagers";
        else if (age >= 18 && age <= 25)
            return "University Students / Young Adults";
        else if (age >= 26 && age <= 45)
            return "Working Adults (Early Career)";
        else if (age >= 46 && age <= 60)
            return "Working Adults (Late Career)";
        else
            return "Senior Citizens / Retirees";
    }
};