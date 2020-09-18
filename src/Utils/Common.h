#ifndef Common_H_
#define Common_H_

#include <iostream>
#include <string>

using namespace std;

class Common
{
public:
    string currentDateTime();
    void createFile();
    void backupFile();
    void stringToUpper(string &s);
    void getDesktopResolution(int& width, int& height);
    bool fileExists (const std::string& name);
};

#endif /* Common_H_ */
