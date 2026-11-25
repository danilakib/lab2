#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

#include "trainlist.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

TrainList::TrainList()
    : items(nullptr), count(0), capacity(0) {
    std::cout << "TrainList: конструктор без параметров.\n";
}

TrainList::TrainList(int n)
    : items(nullptr), count(0), capacity(0) {
    std::cout << "TrainList: конструктор с параметрами.\n";

    if (n < 0)
        throw std::invalid_argument(
            "Вместимость не может быть отрицательной.");

    if (n > 0) {
        items = new TRAIN * [n];
        capacity = n;
    }
}

TrainList::TrainList(const TrainList& other)
    : items(nullptr), count(0), capacity(0) {
    std::cout << "TrainList: конструктор копирования.\n";

    try {
        if (other.count > 0) {
            items = new TRAIN * [other.count];
            capacity = other.count;

            for (int i = 0; i < other.count; ++i) {
                items[count] = new TRAIN(*other.items[i]);
                ++count;
            }
        }
    }
    catch (...) {
        clear();
        delete[] items;
        throw;
    }
}

void TrainList::swap(TrainList& other) {
    std::swap(items, other.items);
    std::swap(count, other.count);
    std::swap(capacity, other.capacity);
}

TrainList& TrainList::operator=(const TrainList& other) {
    if (this != &other) {
        TrainList copy(other);
        swap(copy);
    }

    return *this;
}

TrainList::~TrainList() {
    std::cout << "TrainList: деструктор.\n";
    clear();
    delete[] items;
}

int TrainList::getCount() const {
    return count;
}

void TrainList::grow() {
    if (capacity == std::numeric_limits<int>::max())
        throw std::length_error("Слишком много поездов.");

    int nextCapacity = capacity == 0 ? 4 :
        (capacity > std::numeric_limits<int>::max() / 2 ?
            std::numeric_limits<int>::max() : capacity * 2);

    TRAIN** next = new TRAIN * [nextCapacity];

    for (int i = 0; i < count; ++i)
        next[i] = items[i];

    delete[] items;
    items = next;
    capacity = nextCapacity;
}

void TrainList::insertAt(const TRAIN& train, int position) {
    if (position < 0 || position > count)
        throw std::out_of_range(
            "Неверная позиция вставки.");

    if (count == capacity)
        grow();

    TRAIN* copy = new TRAIN(train);

    for (int i = count; i > position; --i)
        items[i] = items[i - 1];

    items[position] = copy;
    ++count;
}

void TrainList::removeAt(int index) {
    if (index < 0 || index >= count)
        throw std::out_of_range(
            "Поезда с таким номером нет.");

    delete items[index];

    for (int i = index; i + 1 < count; ++i)
        items[i] = items[i + 1];

    --count;
}

void TrainList::clear() {
    for (int i = 0; i < count; ++i)
        delete items[i];

    count = 0;
}

void TrainList::sortByTime() {
    for (int i = 1; i < count; ++i) {
        TRAIN* current = items[i];
        int j = i - 1;

        while (j >= 0 &&
            items[j]->getDeparture() >
            current->getDeparture()) {
            items[j + 1] = items[j];
            --j;
        }

        items[j + 1] = current;
    }
}

void TrainList::printAll() const {
    if (count == 0) {
        std::cout << "Список поездов пуст.\n";
        return;
    }

    for (int i = 0; i < count; ++i)
        std::cout << i + 1 << ". " << *items[i] << '\n';
}

void TrainList::findByDestination(
    const std::string& name
) const {
    bool found = false;

    for (int i = 0; i < count; ++i) {
        if (items[i]->getDestination() == name) {
            std::cout << *items[i] << '\n';
            found = true;
        }
    }

    if (!found)
        std::cout << "Поезда не найдены.\n";
}

TRAIN& TrainList::operator[](int index) {
    if (index < 0 || index >= count)
        throw std::out_of_range(
            "Поезда с таким номером нет.");

    return *items[index];
}