
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

### Projekt: Prosty Czat TCP (Server-Client)

### Opis projektu

Ten projekt implementuje prosty system czatu TCP oparty na architekturze klient-serwer z obsługą wielu klientów.

- **Serwer** nasłuchuje na porcie TCP (12345) i obsługuje wiele połączeń za pomocą wątków.
- **Klient** łączy się z serwerem, umożliwia wysyłanie wiadomości oraz odbiór transmisji od innych klientów (broadcast).

---

### Instrukcja uruchomienia

1. Wymagania: CMake 3.28+, kompilator C++17.
2. Budowanie projektu:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Uruchamianie:
    - Serwer:
      ```bash
      ./ChatApp
      ```
    - Klient:
      ```bash
      ./ChatApp client
      ```

---

### Funkcje i implementacja

- **Serwer** (`Server`):
    - Akceptuje połączenia klientów.
    - Dla każdego klienta tworzy nowy wątek (`std::thread`).
    - Przesyła wiadomości do wszystkich połączonych klientów (z wyłączeniem nadawcy).

- **Klient** (`runClient`):
    - Łączy się z serwerem.
    - Odbiera wiadomości w osobnym wątku.
    - Pozwala użytkownikowi wysyłać wiadomości lub zakończyć sesję komendą `/exit`.


### Wątki i ich funkcje

- **Serwer**: uruchamia wątek do akceptowania klientów (`acceptClients`) oraz indywidualny wątek dla każdego klienta (`handleClient`), który odbiera wiadomości i przekazuje je dalej.
- **Klient**: uruchamia jeden wątek odbierający wiadomości z serwera, a w głównym wątku obsługuje wysyłanie wiadomości użytkownika.


### Sekcje krytyczne i ich rozwiązanie

- **Serwer**:
    - Dostęp do listy klientów (`clients`) chroniony przez mutex `clientMutex`.
    - Każde wysyłanie wiadomości do klientów odbywa się w sekcji chronionej.
- **Klient**:
    - Odbiór i wyświetlanie wiadomości odbywa się w osobnym wątku, niezależnie od wysyłania.

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


### Project: Simple TCP Chat (Server-Client)

### Project Description

This project implements a basic TCP chat system based on a server-client architecture supporting multiple clients.

- **Server** listens on TCP port (12345) and handles multiple connections using threads.
- **Client** connects to the server and allows for sending and receiving (broadcasted) messages.
---

### How to Run

1. Requirements: CMake 3.28+, C++17 compiler.
2. Build instructions:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Running:
    - Server:
      ```bash
      ./ChatApp
      ```
    - Client:
      ```bash
      ./ChatApp client
      ```

---

### Features and Implementation

- **Server** (`Server`):
    - Accepts incoming client connections.
    - Spawns a new thread (`std::thread`) per client.
    - Broadcasts messages to all clients except the sender.

- **Client** (`runClient`):
    - Connects to the server.
    - Receives messages in a separate thread.
    - Allows user to send messages or exit with `/exit` command.

---

### Threads and Their Role

- **Server**: spawns a thread (`acceptClients`) for accepting new clients and individual threads (`handleClient`) for each connected client to receive and forward messages.
- **Client**: starts a receiving thread that listens to server broadcasts while the main thread manages user input and sending messages.

### Critical Sections and Handling

- **Server**:
    - The list of connected clients is protected using a `clientMutex` to prevent race conditions.
    - Broadcasting messages is performed in a thread-safe way using the same mutex.
- **Client**:
    - Receiving and displaying messages is done concurrently in a dedicated thread.
