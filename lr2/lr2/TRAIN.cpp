#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "TRAIN.h"
#include <sstream>
#include <stdexcept>

namespace {
    std::string trim(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");

        if (a == std::string::npos)
            return "";

        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }
}

TRAIN::TRAIN()
    : destination(""), number(0), departure("00:00") {
    std::cout << "TRAIN: конструктор без параметров.\n";
}

TRAIN::TRAIN(const std::string& d, int n, const std::string& t)
    : destination(""), number(0), departure("00:00") {
    std::cout << "TRAIN: конструктор с параметрами.\n";

    setDestination(d);
    setNumber(n);
    setDeparture(t);
}

TRAIN::TRAIN(const TRAIN& other)
    : destination(other.destination),
    number(other.number),
    departure(other.departure) {
    std::cout << "TRAIN: конструктор копирования.\n";
}

TRAIN::~TRAIN() {
    std::cout << "TRAIN: деструктор.\n";
}

std::string TRAIN::getDestination() const {
    return destination;
}

int TRAIN::getNumber() const {
    return number;
}

std::string TRAIN::getDeparture() const {
    return departure;
}

void TRAIN::setDestination(const std::string& value) {
    std::string s = trim(value);

    if (s.empty())
        throw std::invalid_argument(
            "Пункт назначения не может быть пустым.");

    destination = s;
}

void TRAIN::setNumber(int value) {
    if (value <= 0)
        throw std::invalid_argument(
            "Номер поезда должен быть положительным.");

    number = value;
}

void TRAIN::setDeparture(const std::string& value) {
    std::string s = trim(value);

    if (s.size() != 5 || s[2] != ':' ||
        s[0] < '0' || s[0] > '9' ||
        s[1] < '0' || s[1] > '9' ||
        s[3] < '0' || s[3] > '9' ||
        s[4] < '0' || s[4] > '9') {
        throw std::invalid_argument(
            "Введите время в формате ЧЧ:ММ.");
    }

    int h = (s[0] - '0') * 10 + s[1] - '0';
    int m = (s[3] - '0') * 10 + s[4] - '0';

    if (h > 23 || m > 59)
        throw std::invalid_argument(
            "Неверное время отправления.");

    departure = s;
}

std::istream& operator>>(std::istream& in, TRAIN& train) {
    std::string d, n, t;

    if (&in == &std::cin)
        std::cout << "Пункт назначения: ";

    if (!std::getline(in, d))
        throw std::runtime_error(
            "Ошибка ввода пункта назначения.");

    if (&in == &std::cin)
        std::cout << "Номер поезда: ";

    if (!std::getline(in, n))
        throw std::runtime_error(
            "Ошибка ввода номера поезда.");

    if (&in == &std::cin)
        std::cout << "Время отправления (ЧЧ:ММ): ";

    if (!std::getline(in, t))
        throw std::runtime_error(
            "Ошибка ввода времени.");

    std::istringstream parser(n);
    int number;
    std::string extra;

    if (!(parser >> number) || (parser >> extra))
        throw std::invalid_argument(
            "Номер поезда должен быть целым числом.");

    TRAIN checked(d, number, t);
    train = checked;

    return in;
}

std::ostream& operator<<(std::ostream& out, const TRAIN& train) {
    return out << "Поезд № " << train.number
        << ", пункт: " << train.destination
        << ", отправление: " << train.departure;
}