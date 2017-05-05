//
//  systemGen.cpp
//  
//
//  Created by Adam on 11/30/16.
//
//

#include <stdio.h>
#include <iostream>


void sysGen::createSystem(unsigned int numPrinters, unsigned int numDisks, unsigned int numMemory) {
    printers = numPrinters;
    disks = numDisks;
    memory = numMemory;
}

void sysGen::displaySystem() {
    std::cout <<"System info: " <<std::endl;
    std::cout <<"Number of printers: " <<printers <<std::endl;
    std::cout <<"Number of disks: " <<disks <<std::endl;
    std::cout <<"Amount of memory: " <<memory <<std::endl;
    
}

int sysGen::getMemory() {
    return memory;
}

void sysGen::inputSystem() {
    std::cout <<"Enter number of Printers: ";
    std::cin >> printers;
    std::cout <<std::endl <<"Enter number of Disks: ";
    std::cin >>disks;
    std::cout << std::endl <<"Enter amount of memory in bytes: ";
    std::cin >> memory;
    std::cout <<std::endl;
}

int sysGen::getPrinters() {
    return printers;
}

int sysGen::getDisks() {
    return disks;
}
