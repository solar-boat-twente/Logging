/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Thread.h
 * Author: Rboon
 *
 */

#ifndef THREAD_H
#define THREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "structures.h"


class Thread {
public:
    void* temp;
    pthread_t thread1, thread2;

    Thread();
    Thread(const Thread& orig);
    
    virtual ~Thread();
    
    int CreateThread();
    std::string getString();
    void writeString(std::string message, int flagWrite);
private:

};
#endif /* THREAD_H */

