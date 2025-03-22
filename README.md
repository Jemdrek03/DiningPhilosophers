
# HI

## 🇵🇱 Wersja Polska

### Projekt: Problem Ucztujących Filozofów (Rozwiązania: Hierarchiczne i Dijkstry)

### Opis problemu

Problem Ucztujących Filozofów to klasyczny problem synchronizacji w programowaniu współbieżnym. Filozofowie na przemian myślą i jedzą, a do jedzenia potrzebują dwóch widelców, które są współdzielone z sąsiadami. Celem jest uniknięcie zakleszczenia (deadlock) oraz zagłodzenia (starvation).

Projekt zawiera dwa podejścia do rozwiązania problemu:
1. **Rozwiązanie hierarchiczne** – filozofowie podnoszą widelce w określonej kolejności.
2. **Rozwiązanie Dijkstry** – filozofowie podnoszą oba widelce jednocześnie. Nie występuje tutaj sytuacja gdy jeden filozof podnosi tylko jeden widelec.

---

### Instrukcja uruchomienia

1. Wymagania: CMake 3.28+, kompilator C++17.
2. Budowanie projektu:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ./DiningPhilosophers
   ```
3. Po uruchomieniu:
   - Podaj liczbę filozofów.
   - Wybierz rozwiązanie (1 – Hierarchiczne, 2 – Dijkstry).

---

### Wątki i ich funkcje

- Dla każdego filozofa tworzony jest **oddzielny wątek** (`std::thread`), który wykonuje cykl życia filozofa:
  - **Thinking → Hungry → Eating → Thinking**.

---

### Sekcje krytyczne i ich rozwiązanie

- **Sekcje krytyczne**:
  - Dostęp do widelców (mutexy dla każdego widelca).
  - Wyjście na konsolę (mutex `output` / `outputD`).
  - Operacje zmieniające stan filozofa (`crt` / `crtD`).

- **Zabezpieczenia**:
  - Użyto mutexów (`std::mutex`) do synchronizacji dostępu do współdzielonych zasobów.
  - Hierarchiczne podejście zapewnia kolejność podnoszenia widelców, elimując występowanie zakleszczenia.
  - W rozwiązaniu Dijkstry zastosowano mechanizm podnoszenia obu widelców.

---

## 🇬🇧 English Version

### Project: Dining Philosophers Problem (Solutions: Hierarchical and Dijkstra)

### Problem Description

The dining philosophers problem is a classic synchronization issue in concurrent programming. Philosophers alternate between thinking and eating, requiring two forks to eat, shared with neighbors. The goal is to avoid deadlock and starvation.

This project includes two approaches to solving the problem:
1. **Hierarchical Solution** – philosophers pick up forks in a specific order.
2. **Dijkstra's Solution** – only picks up forks if both are available.

---

### How to Run

1. Requirements: CMake 3.28+, C++17 compiler.
2. Build instructions:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ./DiningPhilosophers
   ```
3. On startup:
   - Enter number of philosophers.
   - Choose solution (1 – Hierarchical, 2 – Dijkstra).

---

### Threads and Their Role

- Each philosopher runs in a **separate thread** (`std::thread`) executing the philosopher's life cycle:
  - **Thinking → Hungry → Eating → Thinking**.

---

### Critical Sections and Handling

- **Critical sections**:
  - Fork access (mutexes for each fork).
  - Console output (mutex `output` / `outputD`).
  - State transitions (mutex `crt` / `crtD`).

- **Handling**:
  - Mutexes (`std::mutex`) ensure synchronized access to shared resources.
  - Hierarchical solution enforces fork pickup order, eliminating deadlocks.
  - Dijkstra's solution checks if both forks are available.

---
