#include "Dijkstra.h"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dist(0.0, 1.0);
std::mutex outputD; // Mutex for synchronized outputD to console
std::mutex crtD; // Mutex to protect critical sections

// Function simulating philosopher getting hungry randomly
void gotHungyD(int id, StateD state[]){
    outputD.lock();
    std::cout << "Philosopher " << id << " is thinking\n";
    double number = dist(gen);

    if(number > 0.6){
        state[id] = StateD::Hungry;

        std::cout << "Philosopher " << id << " got hungry\n";
    }
    outputD.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// Check if a fork is available
bool isAvailableD(int id, std::unique_ptr<std::mutex> forks[]){
    if(forks[id]->try_lock()){
        forks[id]->unlock();
        return true;
    }
    return false;
}

// Philosopher attempts to pick up both forks
void pickUpForksD(int id, int howMany, std::unique_ptr<std::mutex> forks[], StateD state[], int forkies[]){
    crtD.lock();

    int left = id;
    int right = (id + 1) % howMany;

    if(isAvailableD(left, forks) && isAvailableD(right, forks)){
        forks[left]->lock();
        forkies[left] = id;
        outputD.lock();
        std::cout<<"Fork "<<left<<" is locked by "<<id<<"\n";
        outputD.unlock();
        forks[right]->lock();
        forkies[right] = id;
        outputD.lock();
        std::cout<<"Fork "<<right<<" is locked by "<<id<<"\n";
        outputD.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds (500));
    }

    // Checks if philosopher successfully obtained both forks
    if(forkies[left] == id && forkies[right] == id)
    {
        state[id] = StateD::Eating;
    }

    crtD.unlock();


}

// Simulate philosopher eating
void eatingD(int id, int forkies[], int howMany){
    outputD.lock();
    std::cout << "Philosopher " << id << " is currently eating\n";
    for(int i = 0; i < howMany; i++)
    {
        std::cout<<"Fork "<<i<<" is being held by: "<<forkies[i]<<std::endl;
    }
    outputD.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds (500));
}

// Philosopher puts down both forks after eating
void putDownForksD(int id, int howMany, std::unique_ptr<std::mutex> forks[], StateD state[]){
    crtD.lock();
    int left = id;
    int right = (id + 1) % howMany;

    forks[left]->unlock();
    outputD.lock();
    std::cout<<"Fork "<<left<<" is unlocked by "<<id<<std::endl;
    forks[right]->unlock();
    std::cout<<"Fork "<<right<<" is unlocked by "<<id<<std::endl;
    outputD.unlock();
    state[id] = StateD::Thinking;

    crtD.unlock();

}

// Philosopher lifecycle simulation
void philosophersD(int id, int howMany, std::unique_ptr<std::mutex> forks[], int forkies[], StateD state[]) {

    int check = 0;

    while (true) {
        if (state[id] == StateD::Thinking)
            gotHungyD(id, state);
        else if (state[id] == StateD::Hungry)
            pickUpForksD(id, howMany, forks, state, forkies);
        else if (state[id] == StateD::Eating) {
            eatingD(id, forkies, howMany);
            check = 1;
        }
        if (check == 1) {
            check = 0;
            putDownForksD(id, howMany, forks, state);
        }
    }
}

