#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <iostream>
#include <mutex>
#include <thread>
#include <random>
#include <memory>

enum class State{
    Thinking = 0,
    Hungry = 1,
    Eating = 2,
};

void philosophers(int id, int howMany, std::unique_ptr<std::mutex> forks[], int forkies[], State state[]);
void pickUpForks(int id, int howMany, std::unique_ptr<std::mutex> forks[], State state[], int forkies[]);
void putDownForks(int id, int howMany, std::unique_ptr<std::mutex> forks[], State state[]);
void gotHungy(int id, State state[]);
void eating(int id, int forkies[], int howMany);


#endif
