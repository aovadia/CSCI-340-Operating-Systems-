Adam Ovadia 
CSCI 340 Home Project

Compilation command: g++ -std=c++11 -o program  Driver.cpp
Execution command: ./program

Project description: 

Write a program that handles the basic data structures (i.e. the devices and their queues) in an operating system.

The program should have two stages of operation, the "sys gen" section, and the "running" section. During sys gen, the system installer (me) species how many devices of each type (printers and disks) are in the system. Also, your program ask user how much memory our system has. You may assume that there is only one CPU.
During the running section you will have to handle system calls issued by the process currently controlling the CPU as well as interrupts that signal various system events. These calls and interrupts will actually be indicated by keyboard input. Capital letters will be interrupts, lower case will indicate system calls. All I/O queues will be FIFO. CPU should be scheduled using preemptive priority scheduling (with no priority elevation). All interrupts will be handled "atomically" (one can not interrupt an interrupt handling routine).

An "A" entered on the keyboard indicates the arrival of a process. The system asks how much memory this process needs and what is its priority. Priority is a non-negative integer number and the HIGHER is the number, the higher is the priority. Allocate memory using "best-fit" approach. The handling routine should create a PCB for this process, generate a PID, and enqueue the PCB into the Ready Queue or allow it to use the CPU. The CPU should never be idle if the ready-queue is not empty. The process in the CPU can issue system calls. One of these is "t", which indicate that the process is terminating. The OS should recycle the PCB (but NOT the PID), in other words reclaim the now unused memory.
Each non-CPU device has a "name" consisting of a letter and an integer. The process currently in the CPU will request "printer 1" by issuing a "p1" on the keyboard, and Printer 1 will signal an interrupt indicating completion of the task at the head of its queue with a "P1" being entered at the keyboard. Similarly, "d3" to request disk 3 and "D3" to signal D3's completion. On such a "task completed" interrupt the PCB for that process should be moved to the back of the Ready Queue. After a system call (e.g. "p3") is made, you should prompt the process (that's me) for a name of the file that should be printed. The PCB for this process and the associated information should be enqueued to the appropriate device queue.

Finally, an "S" on the keyboard indicates a "Snapshot" interrupt (simulating a Big Button on the Sys-op's console). If "Sr" was entered then your program shows the content of the ready-queue and the pid of the process that is currently using the CPU. If "Si" was entered then your program shows the content of the I/O-queues and the pid of the process that is currently using the I/O device for all printers and disks.  If "Sm" was entered then your program shows the state of memory. Make sure I can clearly see where exactly each process is located in memory and what memory is free.