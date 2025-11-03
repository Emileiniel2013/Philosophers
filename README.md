# Philosophers

Philosophers is a concurrency simulation written in **C**, inspired by the classic *Dining Philosophers Problem*.  
The goal is to manage resource sharing between multiple threads (philosophers) without causing deadlocks or data races.

This project explores **multithreading**, **mutex synchronization**, and **timing control**, offering a practical view into how concurrent programs manage shared state safely.
---
## ⚙️ Features
- Multiple philosophers running as independent threads
- Shared resource management using **mutexes**
- Deadlock and starvation prevention
- Millisecond-accurate timing system
- Safe and graceful termination handling
---
## 🧩 How to Run

### 1. Clone and build
```bash
git clone https://github.com/yourusername/philosophers.git
cd philosophers
make
```
2. Run the program
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```
3. Example
```bash
./philo 5 800 200 200
```
Each philosopher alternates between eating, sleeping, and thinking.
They must avoid starving by acquiring forks (mutexes) in a coordinated way.
---
🧠 Technical Details

-Written in C (C99)

-Uses POSIX threads (pthreads) for concurrency

-Thread-safe output handling to avoid mixed prints

-Implemented mutex-based synchronization to avoid deadlocks

-Optional parameter allows setting a max number of meals per philosopher
