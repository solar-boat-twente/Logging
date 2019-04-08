/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Thread.cpp
 * Author: Rboon
 * 
 * Created on 23 mei 2018, 11:06
 */

#include "headerfiles/thread.h"

Thread::Thread()
{
    // path to pipes
    /*Logger user_power_logger ("config/user_power.conf");
    structures::PowerInput *power_input_ptr, power_input;
    power_input_ptr = &power_input;
    structures::PowerOutput *power_output_ptr, power_output;
    power_output_ptr = &power_output;
    structures::UserInput *user_input_ptr, user_input;
    user_input_ptr = &user_input;
     * */
}

Thread::Thread(const Thread& orig)
{
    
}

Thread::~Thread()
{
    pthread_join(thread1, &temp);
    pthread_join(thread2, &temp);
}

const char *PathToPipeA = "/home/ronaldboon/NetBeansProjects/Logging/pipes/BoardReadPipe";
const char *PathToPipeB = "/home/ronaldboon/NetBeansProjects/Logging/pipes/BoardWritePipe";



//buffers to write data from pipe in
char InputString[1000];
char OutputString[1000];

//prototype functions
void *ThreadReadPipe(void *ptr);
void *ThreadWritePipe(void *ptr);
inline bool exist_test(const std::string& name);

int flagThread = 0;

//create mutexes  
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;



    
int Thread::CreateThread()
{
    /*! \fn int Thread::CreateThread()
     \brief Creates a thread for reading and writing via pipes to server
     \return 0 if succesfull, returns -1 if failed 
     */
    
    //gets result from fifo check
    bool ExistFiFoA = exist_test(PathToPipeA);
    bool ExistFiFoB = exist_test(PathToPipeB);

    //checks if fifo exists, if not it creates them
    if ((ExistFiFoA == 0) || (ExistFiFoB == 0))
    {  
        if (mkfifo(PathToPipeA, 0666))
        {
            std::cout << "Pipe A created succesfully" << std::endl;
        }
        else
        {
            std::cout << "Creating pipe A failed! Errno: " << errno << ": ";
            std::cout << strerror(errno) << std::endl;
        }
        
        if (mkfifo(PathToPipeB, 0666))
        {
            std::cout << "Pipe B created succesfully" << std::endl;
        }
        else
        {
            std::cout << "Creating pipe B failed! Errno: " << errno << ": ";
            std::cout << strerror(errno) << std::endl;
        }
    }
    else
    {
        std::cout << "Pipes A and B exist" << std::endl;
    }
    // creates threads for reading and writing pipe
    pthread_create(&thread1, NULL, ThreadReadPipe, NULL);
    if (errno == 0)
    {
        std::cout << "Thread 1 created succesfully" << std::endl;
    }
    else
    {
        std::cout << "Creating thread 1 failed! Errno: " << errno << ": ";
        std::cout << strerror(errno) << std::endl;
        //return -1;
    }

    pthread_create(&thread2, NULL, ThreadWritePipe, NULL);
    if (errno == 0)
    {
        std::cout << "Thread 2 created succesfully" << std::endl;
    }
    else
    {
        std::cout << "Creating thread 2 failed! Errno: " << errno << ": ";
        std::cout << strerror(errno) << std::endl;
    }
    return 0;
}

std::string Thread::getString()
{
    /*! \fn void Thread::getString(char* message)
    \brief for getting a array of chars from the thrread to the main to use there
    \param message contains a array of chars that can be transfered to the main through a pointer
     */

    std::string UntilDelim;
    
    std::istringstream InputStringStream(InputString);
    std::getline(InputStringStream, UntilDelim, '$'); // gets line until stop sign '$'
    memset(InputString, '\0', sizeof (InputString));

    return UntilDelim;
}

void Thread::writeString(std::string message, int flagWrite)
{
    /*! \fn void Thread::writeString(char* message, int flagWrite)
      \brief for writing messages, from the main through the thread to the server
      \param message that needs to be written to the pipe
      \param flagWrite sets a flag in the thread if there needs to be data written to the server. Keeps the thread from spamming the server side.
     * \param bool pipe 
     */

    message = message + '$';

    strcpy(OutputString, message.c_str());

    flagThread = flagWrite;
}

void *ThreadReadPipe(void *ptr)
{
    /*! \fn void *ThreadReadPipe(void *ptr)
     \brief This is a thread to open the pipe, read data, and closes it every 10000 microseconds
     \param *ptr for making thread
     */

    int FifoA;
    char tempString[1000]; //= {};
    while (1)
    {
        memset(tempString, '\0', sizeof (tempString));
        pthread_mutex_lock(&mutex1);
        FifoA = open(PathToPipeA, O_RDONLY);
        std::cout << "reading" << std::endl;
        read(FifoA, tempString, 1000);
        close(FifoA);
        strcpy(InputString, tempString);
        pthread_mutex_unlock(&mutex1);
        std::cout << "String: " << InputString << std::endl;
        if (errno == 0)
        {
            std::cout << "Fifo A opening/read succesfully" << std::endl;
        }
        else
        {
            std::cout << "Reading/opening Fifo A failed! Errno: " << errno << ": ";
            std::cout << strerror(errno) << std::endl;
            //return -1;
        }
        usleep(100000);
    }
}


void *ThreadWritePipe(void *ptr)
{
    /*! \fn void *ThreadWritePipe(void *ptr)
     \brief This is a thread to open the pipe, write data, and closes it every 10000 microseconds
     \param *ptr for making thread
     */
    int FifoB;
    char tempString[1000];
    while (1)
    {
        if (flagThread == 1) // only needs to write if the command is given
        {
            //strcpy(tempString, OutputString); // copies data from WriteString function
            pthread_mutex_lock(&mutex2);
         
            // opens pipe, write data, closes pipe, clears buffer
            FifoB = open(PathToPipeB, O_WRONLY);
            //std::cout << "writing: " << tempString << std::endl;
            write(FifoB, tempString, 1000);
            close(FifoB);
            memset(OutputString, '\0', sizeof (OutputString));
            flagThread = 0;
           
            pthread_mutex_unlock(&mutex2);
            if (errno == 0)
            {
                std::cout << "Fifo B opening/write succesfully" << std::endl;
            }
            else
            {
                std::cout << "Writing/opening Fifo B failed! Errno: " << errno << ": ";
                std::cout << strerror(errno) << std::endl;
            }
        }
        usleep(100000);
    }
}
inline bool exist_test(const std::string & name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}