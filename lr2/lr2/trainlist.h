#pragma once
#include "TRAIN.h"

class TrainList {
private:
    TRAIN** items;
    int count;
    int capacity;

    void grow();
    void swap(TrainList& other);

public:
    TrainList();
    explicit TrainList(int capacity);
    TrainList(const TrainList& other);
    TrainList& operator=(const TrainList& other);
    ~TrainList();

    int getCount() const;

    void insertAt(const TRAIN& train, int position);
    void removeAt(int index);
    void clear();

    void sortByTime();
    void printAll() const;
    void findByDestination(const std::string& destination) const;

    TRAIN& operator[](int index);
};