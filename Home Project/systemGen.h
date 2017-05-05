//
//  systemGen.h
//  
//
//  Created by Adam on 11/30/16.
//
//

#ifndef systemGen_h
#define systemGen_h

// Class used to generate the simulated system
class sysGen {
    private:
        unsigned int printers;
        unsigned disks;
        unsigned int memory;
    public:
        void createSystem(unsigned int numPrinters, unsigned int numDisks, unsigned int numMemory);
        void displaySystem();
        int getMemory();
        void inputSystem();
        int getPrinters();
        int getDisks();
};



#endif /* systemGen_h */
#include "systemGen.cpp"
