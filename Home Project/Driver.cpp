//  Adam Ovadia
//  Driver.cpp
//  
//
//
//
//

#include <stdio.h>
#include <vector>
#include <iostream>
#include "PriorityQ.h"
using namespace std;





int main() {
    
    // output to terminal instructions
    cout <<"List of all valid inputs: " <<endl;
    cout <<"A:   Adds a new process" <<endl;
    cout <<"t:   Terminates current process in cpu" <<endl;
    cout <<"px:   x = a process number. Signals an interrupt for use of the printer" <<endl;
    cout <<"Px:   x = a process number. Signals the completion of the interrupt process of printer" <<endl;
    cout <<"dx:   x = a process number. Signals an interrupt for the use of the disk" <<endl;
    cout <<"Dx:   x = a process number. Signals the completion of the interrupt process of disk" <<endl;
    cout <<"Sr:   Displays the contents of the Ready Queue and the CPU" <<endl;
    cout <<"Si:   Displays the contents of the IO Queues and the process currently using the IO device" <<endl;
    cout <<"Sm:   Displays the state of the Memory" <<endl;
    cout <<"exit:   Quits the program" <<endl <<endl;
    
    // Initialize system
    PriorityQueue<int>* myQueue = new PriorityQueue<int>();
    vector<int> myVec = {23,6,111,7,21,6,8};
    myQueue->setSysParam();
    
    bool cont = true;
    while (cont) {
        string userInput;
        cout <<"Enter Input: ";
        cin >> userInput;
        cout <<endl;
        if (userInput == "exit") { /* user types exit to quit program */
            cont = false;
            cout <<"Program completed!" <<endl;
            break;
        }
        else {
            myQueue->enterKey(userInput);
        }
    }
       
    return 0;
}
