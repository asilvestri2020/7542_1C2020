#ifndef ENEMIESTYPECONFIG_HEADER
#define ENEMIESTYPECONFIG_HEADER

#include <string>

class EnemiesTypeConfig{
    public:
        
        EnemiesTypeConfig(std::string type, std::string filePath);

        std::string getEnemyType();
        std::string getFilePath();
    private:
        std::string enemyType;
        std::string filePath;


};

#endif