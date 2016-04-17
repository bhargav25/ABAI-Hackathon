#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <unistd.h>     // Header File for sleeping.
#include <string.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "constants.h"
#include "Simulation.h"
#include "dynamic.h"

#include <iostream>

/* ASCII code for the escape key. */
#define ESCAPE 27
char* getMapForLevel(int level);

char map0[100] = "maps/scene0.vdb";
char map1[100]= "maps/scene1.vdb";
char map2[100] = "maps/scene2.vdb";
char map3[100] = "maps/scene3.vdb";


Flocking* flockDisplay; 
Scene* sceneDisplay;

char* getMapForLevel(int level){
  if(level == 0)
    return map0;
  else if (level == 1)
    return map1;
  else if (level == 2)
    return map2;
  else if (level == 3)
    return map3;
  return map0;

}

int simMain(int argc, char* argv[])
{

    if(argc<4)
    {
        printf("Ideally these are the parameters you should be passing to run the solver\n");
        printf("%s <sleep_time (ms)> <fish_count>            \
          <boundary_padding> <random_seed> <level>                                    \
          \
          \n", argv[0]);
        exit(0);
        return 1;
    }

    // The command line parameters for this would look like this:
    
    char* mapFile;  //path to the vdb file
    char* sleep_time = argv[1];  //eventually you'll make this 0 to see how fast your solver really is.
    char* fish_count = argv[2];
    char* boundary_padding = argv[3];
    char* rand_seed = argv[4];
    char* clevel = argv[5];

    cout <<"PRinting args" << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    cout << argv[3] << endl;    
    cout << argv[4] << endl;
    cout << argv[5] << endl;


    level                       = stoi(clevel);
    long sleepTime              = stoi(sleep_time);
    int fishCount               = stoi(fish_count);
    int boundaryPadding         = stoi(boundary_padding);
    int randSeed                = stoi(rand_seed);
    
    mapFile = getMapForLevel(level);   
    cout << "Sim Main " << level<<endl;

    //Provide appropriate values for these.
    float maxSpeed = 0;
    float maxForce = 0;
    float flockSepWeight = 0;
    float flockAliWeight = 0;
    float flockCohWeight = 0;
    float collisionWeight = 0;
    float flockSepRadius = 0;
    float flockAliRadius = 0;
    float flockCohRadius = 0;
    float destWeight = 0;
    

    Simulation simulation;
    simulation.loadScene(mapFile);
    simulation.init(sleepTime,
                    fishCount,boundaryPadding,
                    maxSpeed,maxForce,
                    flockSepWeight,
                    flockAliWeight,
                    flockCohWeight,
                    collisionWeight,
                    flockSepRadius,
                    flockAliRadius,
                    flockCohRadius,
                    destWeight,
                    randSeed
                    );  
    cout <<"Before run\n"<<endl;

    flockDisplay = simulation.getFlockHandle();
    
    cout << "Finished flockHandle\n";
    
    sceneDisplay = simulation.getSceneHandle();
    
    cout << "Starting run\n";

    simulation.run();

    std::cout << "Total Simulation Time : " << simulation.totalTime() << std::endl;

    exit(0);
    return 0;
}


int main(int argc, char **argv){

    flockDisplay=NULL;
    sceneDisplay=NULL;

       
    std::thread simThread(simMain,argc,argv); 
    usleep(1000);
    levelHandler(level); 
    cout << "You are running Level: " << level << endl;
    while(true){

    }
    
    return 0;
}




