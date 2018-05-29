#include "TextFile.h"

TextFile::TextFile(string InFileName)
{
     if (InFileName.length() > 0)
          FileName = InFileName;
}

void TextFile::SetFile(string Source)
{
     Data.open(FileName.c_str(), ios::out);
     Data.write(Source.c_str(), Source.length());
     Data.close();
}

string TextFile::GetFile()
{
     if (DoesFileExist())
     {
          Data.open(FileName, ios::in | ios::out);
          stringstream FileStream;
          FileStream << Data.rdbuf();
          Data.close();
          return FileStream.str();
     }
     cout << "File not found." << endl;
     return nullptr;
}

bool TextFile::DoesFileExist()
{
     Data.open(FileName, ios::in | ios::binary);
     bool Status = Data.is_open();
     Data.close();
     return Status;
}
int TextFile::GetFileSize()
{
     Data.open(FileName.c_str(), ios::binary | ios::in);
     int Size = 0;
     string line;
     while (getline(Data, line))
          Size += line.length();
     Data.close();
     return Size;
}
