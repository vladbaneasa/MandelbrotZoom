#include "FileHandler.hpp"


bool FileHandler::notify_flag = false;

FileHandler* FileHandler::getInstance(const char* file_name)
{
    if (!instance)
    {
        instance = new FileHandler(file_name);
    }
    return instance;
}

FileHandler::FileHandler(const char* file_name)
{
    filename = new char[strlen(file_name) + 1];
    strcpy(filename, file_name);

    in_stream.open(filename, std::fstream::in);
    in_stream.close();

    out_stream.open(filename, std::fstream::out);
    out_stream.close();
}

FileHandler::~FileHandler()
{
    if (in_stream.is_open())
    {
        in_stream.close();
    }

    if (out_stream.is_open())
    {
        out_stream.close();
    }

    delete filename;
}

void FileHandler::Notify()
{

    if (notify_flag == true)
    {
        notify_flag = false;
    }
    else if(notify_flag == false)
    {
        notify_flag = true;
    } 

}

bool FileHandler::getNotification()
{
    return notify_flag;
}

void FileHandler::ReadCoords(double* x, double* y)
{

    in_stream.open(filename, std::fstream::in);
    in_stream >> *x >> *y;
    in_stream.close();

}

void FileHandler::WriteCoords(double x, double y)
{

    out_stream.open(filename, std::fstream::out);
    out_stream << x << " " << y << std::endl;
    out_stream.close();

}