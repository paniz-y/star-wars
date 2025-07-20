#ifndef SPACESHIP.HPP
#define SPACESHIP.HPP
#include <string> 
class Spaceship
{
    public:
    void destroy();



    private:
        int distance;
        int radarResistency;
        int distruction;
        int controllessDictance;
        std :: string type;

};
#endif