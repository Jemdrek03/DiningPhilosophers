#ifndef DININGPHILOSOPHERS_DIJKSTRA_H
#define DININGPHILOSOPHERS_DIJKSTRA_H

#include <iostream>
#include <mutex>
#include <thread>
#include <random>
#include <memory>

enum class StateD{
    Thinking = 0,
    Hungry = 1,
    Eating = 2,
};

void philosophersD(int id, int howMany, std::unique_ptr<std::mutex> forks[], int forkies[], StateD state[]);
void pickUpForksD(int id, int howMany, std::unique_ptr<std::mutex> forks[], StateD state[], int forkies[]);
void putDownForksD(int id, int howMany, std::unique_ptr<std::mutex> forks[], StateD state[]);
void gotHungyD(int id, StateD state[]);
void eatingD(int id, int forkies[], int howMany);


#endif //DININGPHILOSOPHERS_DIJKSTRA_H
