#pragma once
#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

#include <fstream>
#include <iostream>

extern "C"
{
    #include <pthread.h>
    #include "string.h"
}



class FileHandler
{
    public:
    static FileHandler* getInstance(const char* file_name);
    ~FileHandler();

    void ReadCoords(double *x, double *y);
    void WriteCoords(double x, double y);

    static void Notify();
    static bool getNotification();
    private:

    FileHandler(const char* file_name);
    static FileHandler* instance;

    static bool notify_flag;
    char* filename;

    std::ofstream out_stream;
    std::ifstream in_stream;
};

#endif