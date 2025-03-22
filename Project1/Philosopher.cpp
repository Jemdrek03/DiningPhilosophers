#include "Philosopher.h"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dist(0.0, 1.0);
std::mutex output; // Mutex for synchronized output to console
std::mutex crt; // Mutex to protect critical sections

// Function simulating philosopher getting hungry randomly
void gotHungy(int id, State state[]){
    output.lock();
    std::cout << "Philosopher " << id << " is thinking\n";
    double number = dist(gen);

    if(number > 0.6){
        state[id] = State::Hungry;

        std::cout << "Philosopher " << id << " got hungry\n";
    }
    output.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// Check if a fork is available
bool isAvailable(int id, std::unique_ptr<std::mutex> forks[]){
    if(forks[id]->try_lock()){
        forks[id]->unlock();
        return true;
    }
    return false;
}

// Philosopher tries to pick up left and right forks
void pickUpForks(int id, int howMany, std::unique_ptr<std::mutex> forks[], State state[], int forkies[]){
    crt.lock();

    int left = id;
    int right = (id + 1) % howMany;

    if(left < right){
        if(isAvailable(left, forks))
        {
            forks[left]->lock();
            forkies[left] = id;
            output.lock();
            std::cout<<"Fork "<<left<<" is locked by "<<id<<"\n";
            output.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds (500));
        }
        if(forkies[left] == id && isAvailable(right, forks))
        {
            forks[right]->lock();
            forkies[right] = id;
            output.lock();
            std::cout<<"Fork "<<right<<" is locked by "<<id<<"\n";
            output.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds (500));
        }
    }
    else{
        if(isAvailable(right, forks))
        {
            forks[right]->lock();
            forkies[right] = id;
            output.lock();
            std::cout<<"Fork "<<right<<" is locked by "<<id<<"\n";
            output.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds (500));

        }
        if(forkies[right] == id && isAvailable(left, forks))
        {
            forks[left]->lock();
            forkies[left] = id;
            output.lock();
            std::cout<<"Fork "<<left<<" is locked by "<<id<<"\n";
            output.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds (500));
        }

    }

    // Check if philosopher successfully got both forks
    if(forkies[left] == id && forkies[right] == id)
    {
        state[id] = State::Eating;
    }

    crt.unlock();


}

// Simulate philosopher eating
void eating(int id, int forkies[], int howMany){
    output.lock();
    std::cout << "Philosopher " << id << " is currently eating\n";
    for(int i = 0; i < howMany; i++)
    {
        std::cout<<"Widelec "<<i<<" trzymany przez: "<<forkies[i]<<std::endl;
    }
    output.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds (500));
}

// Philosopher puts down both forks after eating
void putDownForks(int id, int howMany, std::unique_ptr<std::mutex> forks[], State state[]){
    crt.lock();
    int left = id;
    int right = (id + 1) % howMany;

    forks[left]->unlock();
    output.lock();
    std::cout<<"Fork "<<left<<" is unlocked by "<<id<<std::endl;
    forks[right]->unlock();
    std::cout<<"Fork "<<right<<" is unlocked by "<<id<<std::endl;
    output.unlock();
    state[id] = State::Thinking;

    crt.unlock();

}

// Philosopher lifecycle simulation
void philosophers(int id, int howMany, std::unique_ptr<std::mutex> forks[], int forkies[], State state[]) {

    int check = 0;

    while (true) {
        if (state[id] == State::Thinking)
            gotHungy(id, state);
        else if (state[id] == State::Hungry)
            pickUpForks(id, howMany, forks, state, forkies);
        else if (state[id] == State::Eating) {
            eating(id, forkies, howMany);
            check = 1;
        }
        if (check == 1) {
            check = 0;
            putDownForks(id, howMany, forks, state);
        }
    }
}

