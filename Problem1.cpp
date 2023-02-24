#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
using namespace std;
mutex mtx;

bool mazeEmptyFlag = true;

bool problem1(){
    int nguests;

    cout << "Enter number of guests: ";
    cin >> nguests;

    // Create an array of threads
    std::thread *guests = new std::thread[nguests];
    // Create an array of bools to keep track of who has gone
    bool *hasGone = new bool[nguests+1];//extra index for global kill flag
    bool *isNext = new bool[nguests];

    // Initialize the array of bools to false
    for(int i = 0; i < nguests; i++){
        hasGone[i] = false;
        isNext[i] = false;
    }

    // randomly select guest till all guests have gone
    for(int i = 0; i < nguests; i++){
        
        guests[i] = std::thread([=](){
            while(!hasGone[nguests]){
                //mark themselves off on communal list
                
                if(isNext[i]){
                    
                    mtx.lock();
                    hasGone[i] = true;
                    mtx.unlock();
                    bool tempFlag = true;
                    //have guest check list to see if everyone is done
                    for(int j = 0; j < nguests; j++){
                        if(!hasGone[j]){
                            tempFlag = false;
                            break;
                        }
                    }
                    
                    
                    //lock to avoid multiple threads entering maze at once
                    
                    
                    cout<< "Guest " << i+1 << " has gone into the maze" << endl;
                    
                    mtx.lock();
                    hasGone[nguests] = tempFlag;
                    isNext[i] = false;
                    mazeEmptyFlag = true;
                    mtx.unlock();
                }
            }
        });
        
            
        
        
        
    }
    while(!hasGone[nguests]){
        //randomly select a guest
        if(mazeEmptyFlag){
            mtx.lock();
            mazeEmptyFlag = false;
            int guest = rand() % nguests;
            isNext[guest] = true;
            mtx.unlock();
            
            
        }
    }

    for(int i = 0; i < nguests; i++){
        guests[i].join();
    }
    return true;
}

int main(){
        bool result = problem1();
        cout << result << endl;
        return 0;
}