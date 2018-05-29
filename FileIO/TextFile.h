#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class TextFile
{
     fstream Data;
     string FileName;

public:
     /* Sets default values. */
     TextFile(string InFileName);

     /* Receives a std::string and writes that into the file. */
     void SetFile(string Source);

     /* Returns whole file as a std::string. */
     string GetFile();

private:
     /* Returns false if file is not found. */
     bool DoesFileExist();

     /* Returns number of characters in the file (not bytes). */
     int GetFileSize();

     /* Returns true if file is empty. */
     __forceinline bool IsEmpty() { return GetFileSize() <= 0; }
};
