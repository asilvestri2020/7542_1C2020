#ifndef EnemySpawn_HEADER
#define EnemySpawn_HEADER

#include <string>

class EnemySpawn{
    public:
        EnemySpawn();
        EnemySpawn(std::string type, int time, int spawnPosX, int spawnPosY, int velX, int velY);
        ~EnemySpawn();
        int getSpawnPosX();
        int getSpawnPosY();
        int getVelX();
        int getVelY();
        int getSpawnTime();
        void setSpawnTime(int time);
        std::string getEnemyType();
    private:
        std::string enemyType;
        int spawnPosX;
        int spawnPosY;
        int velX;
        int velY;
        int spawnTime;


};

#endif