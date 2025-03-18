#include "Philosopher.h"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dist(0.0, 1.0);

void gotHungy(int id, State state[]){
    std::cout << "Philosopher " << id << " is thinking\n";
    double number = dist(gen);

    if(number > 0.6){
        state[id] = State::Hungry;
        std::cout << "Philosopher " << id << " got hungry\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

bool isAvailable(int id, std::unique_ptr<std::mutex> forks[]){
    if(forks[id]->try_lock()){
        forks[id]->unlock();
        return true;
    }
    return false;
}

void pickUpForks(int id, int howMany, std::unique_ptr<std::mutex> forks[], State state[], int forkies[]){

    int left = id;
    int right = (id + 1) % howMany;

    if(left < right){
        if(isAvailable(left, forks))
        {
            forks[left]->lock();
            forkies[left] = id;
            std::cout<<"Fork "<<left<<" is locked by"<<id<<"\n";
        }
        if(isAvailable(right, forks))
        {
            forks[right]->lock();
            forkies[right] = id;
            std::cout<<"Fork "<<right<<" is locked by"<<id<<"\n";
        }
    }
    else{
        if(isAvailable(right, forks))
        {
            forks[right]->lock();
            forkies[right] = id;
            std::cout<<"Fork "<<right<<" is locked by"<<id<<"\n";
        }
        if(isAvailable(left, forks))
        {
            forks[left]->lock();
            forkies[left] = id;
            std::cout<<"Fork "<<left<<" is locked by"<<id<<"\n";
        }

    }
    if(forkies[left] == id && forkies[right] == id)
    {
        state[id] = State::Eating;
    }

}

void eating(int id){
    std::cout << "Philosopher " << id << " is currently eating\n";
    std::this_thread::sleep_for(std::chrono::milliseconds (500));
}

void putDownForks(int id, int howMany, std::unique_ptr<std::mutex> forks[], State state[]){
    int left = id;
    int right = (id + 1) % howMany;

    forks[left]->unlock();
    std::cout<<"Fork "<<left<<" is unlocked\n";
    forks[right]->unlock();
    std::cout<<"Fork "<<right<<" is unlocked\n";
    state[id] = State::Thinking;
}

void philosophers(int id, int howMany, std::unique_ptr<std::mutex> forks[]){
    // Przygotowanie
    State state[howMany];
    for(int i = 0; i < howMany; i++)
        state[i] = State::Thinking;

    int check = 0;

    int forkies[howMany];
    while(true){
        if(state[id] == State::Thinking)
            gotHungy(id, state);
        else if(state[id] == State::Hungry)
            pickUpForks(id, howMany, forks, state, forkies);
        else if(state[id] == State::Eating){
            eating(id);
            check = 1;
        }
        if(check == 1){
            check = 0;
            putDownForks(id, howMany, forks, state);
        }
    }
}
