//
//  PriorityQ.h
//  
//
//  Created by Adam on 12/1/16.
//
//

#ifndef PriorityQ_h
#define PriorityQ_h
#include <vector>
#include <string>
#include "systemGen.h"
#include "myProcessdef.h"


template <class ItemType>
class PriorityQueue {
    private:
        // initialize system details
        int currentSize;
        int pid_counter;
        int printersInUse;
        int disksInUse;
        std::vector<myProcess> process;
        unsigned int MemInUse; /* keeps track of system memory in use */
        sysGen mySystem;
    
    
        // Cpu operations
        struct myCpu {
            myProcess inCpu;
            bool empty;
        };
        myCpu cpu; // myProcess currently in use by cpu
    
        // Printer Operations
        struct myPrinterQ {
            myProcess printProcess;
            std::string name;
            std::string fileName;
        };
        std::vector<myPrinterQ> pQ;
        void outputPrinterQ();
        void PrintInterrupt(std::string name);
        void insertPrinterQ(std::string Pname, std::string aFile);
    
    
        // Disk Operations
        struct myDiskQ {
            myProcess diskProcess;
            std::string name;
            std::string fileName;
        };
        std::vector<myDiskQ> dQ;
        void insertDiskQ(std::string dName, std::string aFile);
        void diskInterrupt(std::string name);
        void outputDiskQ();
    
    

        bool enoughMemory(int mem);
        void displayReadyQ();
 
        //void processReadyQ();
        void Interrupt();
        void endInterrupt();
        void moveToCpu(bool force);
  
    
        void displayIOQ();
    

        // Standard Queue functions
        ItemType getItem(int pos);
        bool isEmpty() const;
        const myProcess findMax() const;
        void insert(myProcess aProcess);
        void deleteMax();
        void deleteMax(ItemType & maxItem);
        void clear();
        int getSize();
        int getPosition(const ItemType value);
        ItemType getValue(int pos);
    
    public:
    
        explicit PriorityQueue(int capacity = 1000);
    
    
        // initialize system
        void setSysParam();
    
        // Handler user input
        void enterKey(std::string input);

};



#endif /* PriorityQ_h */
#include "PriorityQ.cpp"
