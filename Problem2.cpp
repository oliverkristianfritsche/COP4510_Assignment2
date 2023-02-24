#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <semaphore.h>

using namespace std;

// Initialize semaphores
sem_t roomAvailable;
sem_t queueMutex;

// Global variables
int numGuestsVisited = 0;
int numGuests;
int roomCapacity = 1;
vector<int> guestsInQueue;

// Guest thread function
void visitVase(int guestId)
{
    while (numGuestsVisited < numGuests)
    {
        // Guest decides whether to visit the vase or not
        bool visit = (rand() % 2 == 0);
        if (visit)
        {
            bool firstvisit = true;
            cout << "Guest " << guestId << " is queueing to visit the vase" << endl;
            // Guest waits for the room to be available
            sem_wait(&queueMutex);
            guestsInQueue.push_back(guestId);
            sem_post(&queueMutex);
            sem_wait(&roomAvailable);
            // Guest enters the room
            cout << "Guest " << guestId << " enters the room" << endl;
            // Guest exits the room
            cout << "Guest " << guestId << " exits the room" << endl;
            sem_post(&roomAvailable);
            // Notify the next guest in the queue
            sem_wait(&queueMutex);
            guestsInQueue.erase(guestsInQueue.begin());
            if (!guestsInQueue.empty())
            {
                sem_post(&roomAvailable);
            }
            sem_post(&queueMutex);
            if(firstvisit){
                numGuestsVisited++;
            }
            firstvisit = false;
        }
    }
}

int main()
{
    // Get number of guests from user
    cout << "Enter the number of guests: ";
    cin >> numGuests;
    // Seed random number generator
    srand(time(nullptr));

    // Initialize semaphores
    sem_init(&roomAvailable, 0, roomCapacity);
    sem_init(&queueMutex, 0, 1);

    // Create guest threads
    vector<thread> guestThreads(numGuests);
    for (int i = 0; i < numGuests; i++)
    {
        guestThreads[i] = thread(visitVase, i);
    }

    // Wait for all guest threads to finish
    for (auto &t : guestThreads)
    {
        t.join();
    }
    
    // Destroy semaphores
    sem_destroy(&roomAvailable);
    sem_destroy(&queueMutex);

    return 0;
}