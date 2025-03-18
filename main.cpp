#include "Philosopher.h"

int main() {
    int numPhil;
    std::cout << "How many Philosophers are there? ";
    std::cin >> numPhil;

    std::vector<std::unique_ptr<std::mutex>> forks;
    for (int i = 0; i < numPhil; i++)
        forks.push_back(std::make_unique<std::mutex>());

    std::vector<std::thread> phil;
    for (int i = 0; i < numPhil; i++)
        phil.emplace_back(philosophers, i, numPhil, forks.data());

    for(auto &t : phil)
        t.join();

    return 0;
}
