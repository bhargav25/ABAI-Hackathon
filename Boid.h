#pragma once

#include "Vector.h"
#include <vector>
#include "Scene.h"

using namespace math;
using namespace std;

/* PLEASE READ!!!
This class can be used to define the unit of Flocking - Boid.



*/

class Boid {
public:

	/* This is the world space co-ordinates of the Boids. 
	 Poulate this to view in Blender*/

	//Set these variables appropriately. These are required.
	Vec2f loc;
	bool reachedDestination;
	float orient;
	//--------------------------------------------------


	Vec2f vel,acc;
	Vec2i endCorner;

    float r;
	

	bool hitObstacle;

	int 	boundaryPadding;
	float 	maxSpeed;	
	float 	maxForce;	
	float 	flockSepWeight;
	float 	flockAliWeight;
	float 	flockCohWeight;
	float 	flockSepRadius;
	float 	flockAliRadius;
	float 	flockCohRadius;


	Boid(int x, int y, int xbound, int ybound,
		int 	mboundaryPadding	,
		float 	mmaxSpeed 			,
		float 	mmaxForce 			,
		float 	mflockSepWeight 	,
		float 	mflockAliWeight 	,
		float 	mflockCohWeight 	,
		float 	mflockSepRadius 	,
		float 	mflockAliRadius 	,
		float 	mflockCohRadius 	);


    float dist(Vec2f v1,Vec2f v2);
    float clamp(float val, float minval, float maxval);
	
	void update(vector<Boid> &boids, Vec2f agh,Scene * sceneMap);
    void boundCheck(int padding);
    void flock(vector<Boid> &boids,Vec2f nbvs,Scene * sceneMap);
    bool isHit(int x,int y, int radius);

};

