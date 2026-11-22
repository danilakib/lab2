#pragma once
#include <string>
#include <iostream>

class TRAIN {
private:
    std::string destination;
    int number;
    std::string departure;

public:
    TRAIN();
    TRAIN(const std::string& destination, int number,
        const std::string& departure);
    TRAIN(const TRAIN& other);
    TRAIN& operator=(const TRAIN& other) = default;
    ~TRAIN();

    std::string getDestination() const;
    int getNumber() const;
    std::string getDeparture() const;

    void setDestination(const std::string& value);
    void setNumber(int value);
    void setDeparture(const std::string& value);

    friend std::istream& operator>>(std::istream& in, TRAIN& train);
    friend std::ostream& operator<<(std::ostream& out, const TRAIN& train);
}; 
