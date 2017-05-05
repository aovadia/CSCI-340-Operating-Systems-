//
//  PriorityQ.cpp
//  
//
//  Created by Adam on 12/1/16.
//
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>  //swap
#include <utility>
#include <string>
#include <stdlib.h> //random number generator

using namespace std;

template <class ItemType>
void PriorityQueue<ItemType>::outputPrinterQ() {
    for (int a = 0; a < pQ.size(); a++) {
        cout << pQ[a].name <<endl;
    }
}

template <class ItemType>
void PriorityQueue<ItemType>::PrintInterrupt(string name) {
    cout <<"Currently Processing: " <<name <<endl;
    myProcess temp;
    
    cout <<"Process: " <<name <<" is printing: " <<pQ[0].fileName <<endl;
    pQ.erase(pQ.begin()); //printing process is done, remove from print queue
    cout <<"Process finished its cpu burst and is re-entering ready queue" <<endl;
}

template <class ItemType>
void PriorityQueue<ItemType>::insertPrinterQ(string Pname, string aFile) {
    if (printersInUse < mySystem.getPrinters()) {
        myPrinterQ temp;
        temp.printProcess = cpu.inCpu;
        temp.name = Pname;
        temp.fileName = aFile;
        pQ.push_back(temp);
        printersInUse++;
    }
    else {
        cout <<"The printer queue is full" <<endl;
    }
}

template <class ItemType>
void PriorityQueue<ItemType>::insertDiskQ(std::string dName, std::string aFile) {
    if (disksInUse < mySystem.getDisks()) {
        myDiskQ temp;
        temp.diskProcess = cpu.inCpu;
        temp.name = dName;
        temp.fileName = aFile;
        dQ.push_back(temp);
        disksInUse++;
        
    }
    else {
        cout <<"The disk queue is full" <<endl;
    }
}

template <class ItemType>
void PriorityQueue<ItemType>::diskInterrupt(std::string name) {
    cout <<"Currently Processing: " <<name <<endl;
    myProcess temp;
    
    cout <<"Process: " <<name <<" is tranferring to disk: " <<dQ[0].fileName <<endl;
    dQ.erase(dQ.begin()); //disk process is done, remove from disk queue
    cout <<"Process finished its cpu burst and is re-entering ready queue" <<endl;
}

template <class ItemType>
void PriorityQueue<ItemType>::outputDiskQ() {
    for (int a = 0; a < dQ.size(); a++) {
        cout << dQ[a].name <<endl;
    }
}

template <class ItemType>
bool PriorityQueue<ItemType>::enoughMemory(int mem) {
    int sysMem = mySystem.getMemory();
    if (mem + MemInUse <= sysMem) {
        return true;
    }
    return false;
}

template <class ItemType>
void PriorityQueue<ItemType>::displayReadyQ() {
    if (currentSize == 0) {
        cout <<"Ready queue is empty" <<endl;
    }
    else {
        cout <<"Ready Queue Contents: " <<endl;
        cout <<"Priority: " <<'\t' <<"memory: " << '\t' << "pid: " <<endl;
        for (int a = 0; a <currentSize; a++) {
            cout << process[a].priority << '\t' <<'\t' <<process[a].memory <<'\t' <<'\t' <<process[a].pid <<endl;
        }
    }
}

template <class ItemType>
void PriorityQueue<ItemType>::Interrupt () {
    MemInUse = MemInUse - cpu.inCpu.memory;
    insert(cpu.inCpu);
}

template <class ItemType>
void PriorityQueue<ItemType>::endInterrupt() {
    cpu.inCpu = findMax();
    deleteMax();
}

// force is used when process is terminating --> don't check priority, just move next highest priority process to cpu
template <class ItemType>
void PriorityQueue<ItemType>::moveToCpu(bool force) {
    // if force is true, replace current cpu execution with the next item in the ready queue
    if (force){
        if (currentSize > 0 ) { /* make sure there is another process in the ready queue */
            MemInUse = MemInUse - cpu.inCpu.memory; // Free up process's memory
            cpu.inCpu = findMax();
            cpu.empty = false;
            deleteMax();
            return;
        }
        else {
            cpu.empty = true;
            MemInUse = MemInUse - cpu.inCpu.memory; // Free up process's memory
            return;
        }
    }
    // otherwise, use preemptive priority scheduling
    if (cpu.empty) {
        cpu.inCpu = findMax();
        cpu.empty = false;
        deleteMax();
    }
    
    // if the 2 priority's are equal, prefer the process currently in cpu
    else if (cpu.inCpu.priority < findMax().priority) {
        MemInUse = MemInUse - cpu.inCpu.memory; // remove mem because insert function will add it again
        insert(cpu.inCpu);
        
        cpu.inCpu = findMax();
        cpu.empty = false;
        deleteMax();
        
    }
    else if (cpu.empty && currentSize == 0) { /* if no process is in cpu and ready queue is empty, set cpu to empty */
        cpu.empty = true;
    }
    
}

template <class ItemType>
void PriorityQueue<ItemType>::displayIOQ() {
    if (pQ.empty()) {
        cout <<"Printer Queue is empty" <<endl;
    }
    else {
        cout <<"Printer Queue Contents: " <<endl;
        cout <<"Priority: " <<'\t' <<"memory: " << '\t' << "pid: " << '\t' <<"Item Name: " <<endl;
        for (int a = 0; a < pQ.size(); a++) {
            cout << pQ[a].printProcess.priority <<'\t' <<'\t' << pQ[a].printProcess.memory <<'\t' <<'\t' <<pQ[a].printProcess.pid <<'\t' <<'\t' <<pQ[a].name <<endl;
        }
    }
    if (dQ.empty()) {
        cout <<"Disk Queue is empty" <<endl;
    }
    else {
        cout <<"Disk Queue Contents: " <<endl;
        cout <<"Priority: " <<'\t' <<"memory: " << '\t' << "pid: " << '\t' <<"Item Name: " <<endl;
        for (int a = 0; a < dQ.size(); a++) {
            cout << dQ[a].diskProcess.priority <<'\t' <<'\t' << dQ[a].diskProcess.memory <<'\t' <<'\t' <<dQ[a].diskProcess.pid <<'\t' <<'\t' <<dQ[a].name <<endl;
        }
        
    }
}

template <class ItemType>
ItemType PriorityQueue<ItemType>::getItem(int pos) {
    return process[pos].priority;
}

template <class ItemType>
bool PriorityQueue<ItemType>::isEmpty() const {
    return currentSize == 0;
}

template <class ItemType>
const myProcess PriorityQueue<ItemType>::findMax() const {
    return process[0];
}

template <class ItemType>
void PriorityQueue<ItemType>::insert(myProcess aProcess) {
    
    // insert process if ready queue is empty
    if (currentSize == 0) {
        process[0] = aProcess;
        currentSize++;
        return;
    }
    
    // calculate what position in ready queue process belongs
    int curPos = 0;
    for (int a = 0; a < currentSize; a++) {
        if (aProcess.priority < process[a].priority) {
            curPos++;
        }
    }
    
    // insert process if process has the least priority
    if (currentSize == curPos) {
        process[curPos] = aProcess;
    }
    
    // insert process if a swapping routine is require
    else {
        //    process[currentSize+1] = process[currentSize];
        for (int b = currentSize + 1; b >= curPos; b--) {
            process[b+1] = process[b];
        }
    }
    
    process[curPos] = aProcess;
    
    // increment currenSize which keeps track of the size of the ready queue
    currentSize++;
    
    // Update memory usage with new process
    MemInUse = MemInUse + aProcess.memory;
}

template <class ItemType>
void PriorityQueue<ItemType>::deleteMax() {
    for (int a = 0; a < currentSize; a++) {
        process[a] = process[a+1];
    }
    currentSize--;
    
}

template <class ItemType>
void PriorityQueue<ItemType>::deleteMax(ItemType & maxItem) {
    int curPos;
    for (int a = 0; a < currentSize; a++) {
        if (process[a].priority == maxItem) {
            curPos = a;
            break;
        }
    }
    for (int b = curPos; b < currentSize; b++) {
        process[b] = process[b+1];
    }
}

template <class ItemType>
void PriorityQueue<ItemType>::clear() {
    currentSize = 0;
}

template <class ItemType>
int PriorityQueue<ItemType>::getSize() {
    return currentSize;
}

template <class ItemType>
int PriorityQueue<ItemType>::getPosition(const ItemType value) {
    int position;
    for (int a = 0; a < currentSize; a++) {
        if (process[a].priority == value) {
            position = a;
            cout <<"Pocess " <<a <<endl;
        }
        
    }
    return position;
}

template <class ItemType>
ItemType PriorityQueue<ItemType>::getValue(int pos) {
    return process[pos].priority;
}

// Constuctor
template <class ItemType>
PriorityQueue<ItemType>::PriorityQueue(int capacity)
: process(capacity + 1), currentSize(0), pQ(0)
{
    cpu.empty = true;
    pid_counter = 1;
    printersInUse = 0;
    disksInUse = 0;
}

template <class ItemType>
void PriorityQueue<ItemType>::setSysParam() {
    mySystem.inputSystem();
}

// handle input
template <class ItemType>
void PriorityQueue<ItemType>::enterKey(string input) {
    if (input == "A") { /* add a new process */
        myProcess newProcess;
        int priv;
        long mem;
        cout <<"Enter the amount of memory for new process: ";
        cin >> mem;
        cout <<endl <<"Enter the priority for the new process: ";
        cin >> priv;
        newProcess.priority = priv;
        newProcess.memory = mem;
        newProcess.pid = pid_counter;
        bool freeSoace = enoughMemory(mem);
        if (freeSoace) {
            insert(newProcess);
            MemInUse = MemInUse + mem;
            moveToCpu(false);
            pid_counter++;
  
        }
        else {
            cout <<"Not enough Memory" <<endl;
            }
    }
    
    else if (input[0] == 'p') {
        myPrinterQ print;
        print.name = input;
        print.printProcess = cpu.inCpu;
        Interrupt();
        
        string file;
        cout <<"Enter filename to print: ";
        cin >> file;
        cout <<endl;
        
        insertPrinterQ(input, file);
        endInterrupt();
    }
    else if (input[0] == 'P') { /* Only try to process Printer is printer use was requested */
        if (printersInUse > 0) {
            PrintInterrupt(input);
            printersInUse--;
        }
    }
    
    else if (input[0] == 'd') {
        myDiskQ disk;
        disk.diskProcess = cpu.inCpu;
        Interrupt();
        string file;
        cout <<"Enter filename to tranfer to disk: ";
        cin >> file;
        cout <<endl;

        insertDiskQ(input, file);
        endInterrupt();
    }
    
    else if (input[0] == 'D') {
        if (disksInUse > 0) { /* Only try to process Disk if disk use was requested */
            diskInterrupt(input);
            disksInUse--;
        }
    }
    
    // display ready queue
    else if (input == "Sr") {
        displayReadyQ();
        if (!cpu.empty) {
            cout <<"The CPU is currently processing: " <<endl;
            cout <<"Priority: " <<'\t' <<"memory: " << '\t' << "pid: " <<endl;
            cout <<cpu.inCpu.priority <<'\t' <<'\t' <<cpu.inCpu.memory <<'\t' <<'\t' <<cpu.inCpu.pid <<endl;
        }
        else {
            cout <<"The CPU is not executing any processes -> the ReadyQueue is empty " <<endl;
        }

    }
    
    else if (input == "Si") { /* Display IO Queues */
        displayIOQ();
    }
    
    else if (input == "Sm") { /* Display Memory usage */
        cout <<"The contents of the memory is: " <<endl;
        for (int a = 0; a < currentSize; a++) {
            cout <<"Pid: " <<process[a].pid <<  '\t' <<"Memory usage: " << process[a].memory <<endl;
        }
        cout <<"Pid: " <<cpu.inCpu.pid <<  '\t' <<"Memory usage: " << cpu.inCpu.memory <<endl;
        cout <<"Total memory in use: " <<MemInUse <<" bytes" <<endl;
        
        
        unsigned int tests = mySystem.getMemory();
        cout <<"mem in use: " <<MemInUse <<'\t' <<"total mem: " <<mySystem.getMemory() <<'\t' <<endl;
    }
    
    else if (input == "t") { /* Process is terminating */
        if (!cpu.empty) {
            moveToCpu(true);
        }
        else {
            cout <<"Cannot terminate a process when there are no processes in cpu" <<endl;
        }
    }
    
    
    else { /* user entered an incorrect key */
        cout <<"You entered an invalid key. Please enter a value key." <<endl;
    }
    
}
