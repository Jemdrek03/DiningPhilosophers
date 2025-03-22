#include "Philosopher.h"
#include "Dijkstra.h"
#include <vector>

int main() {
    int numPhil;
    int option;
    std::cout << "How many Philosophers are there? \n";
    std::cin >> numPhil;


    std::cout<<"Which solution \n1 for Hierarchy Solution\n2 for Dijkstra's Solution'\n";
    do{
        std::cin>>option;
    }
    while (option != 1 && option != 2);


    if(option == 1)
    {
        // Shared array representing ownership of forks (-1 indicates no owner)
        std::vector<int> forkies(numPhil, 100);

        // Shared array representing philosophers' states (Thinking, Hungry, Eating)
        std::vector<State> state(numPhil, State::Thinking);

        // Initialize mutexes for forks
        std::vector<std::unique_ptr<std::mutex>> forks;
        for (int i = 0; i < numPhil; i++)
            forks.push_back(std::make_unique<std::mutex>());

        // Launch philosopher threads
        std::vector<std::thread> phil;
        for (int i = 0; i < numPhil; i++)
            phil.emplace_back(philosophers, i, numPhil, forks.data(), forkies.data(), state.data());

        // Wait for all philosopher threads to complete
        for (auto &t : phil)
            t.join();
    }
    else
    {
        // Shared array representing ownership of forks (-1 indicates no owner)
        std::vector<int> forkies(numPhil, 100);

        // Shared array representing philosophers' states (Thinking, Hungry, Eating)
        std::vector<StateD> state(numPhil, StateD::Thinking);

        // Initialize mutexes for forks
        std::vector<std::unique_ptr<std::mutex>> forks;
        for (int i = 0; i < numPhil; i++)
            forks.push_back(std::make_unique<std::mutex>());

        // Launch philosopher threads
        std::vector<std::thread> phil;
        for (int i = 0; i < numPhil; i++)
            phil.emplace_back(philosophersD, i, numPhil, forks.data(), forkies.data(), state.data());

        // Wait for all philosopher threads to complete
        for (auto &t : phil)
            t.join();
    }


    return 0;
}
