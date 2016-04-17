#include "Boid.h"

/*

Add functions needed to create a working flock.


*/
Boid::Boid(int x, int y, int xbound, int ybound,
        int     mboundaryPadding    ,
        float   mmaxSpeed           ,
        float   mmaxForce           ,
        float   mflockSepWeight     ,
        float   mflockAliWeight     ,
        float   mflockCohWeight     ,
        float   mflockSepRadius     ,
        float   mflockAliRadius     ,
        float   mflockCohRadius     )
{

    loc.setval(x,y);
	vel.setval(0,0);
	acc.setval(0,0);
    r = 3.0;
    orient = 0;
    endCorner.setval(xbound,ybound);
    reachedDestination = false;
    hitObstacle = false;

    boundaryPadding =   mboundaryPadding;
    maxSpeed        =   mmaxSpeed      ;  
    maxForce        =   mmaxForce      ;  
    flockSepWeight  =   mflockSepWeight;
    flockAliWeight  =   mflockAliWeight;
    flockCohWeight  =   mflockCohWeight;
    flockSepRadius  =   mflockSepRadius;
    flockAliRadius  =   mflockAliRadius;
    flockCohRadius  =   mflockCohRadius;

}

// Method to update location
void Boid::update(vector<Boid> &boids, Vec2f destination) {

	flock(boids, destination);

    vel += acc;   // Update velocity
    vel *= maxSpeed;
    loc += vel;
    acc.setval(0,0);  // Resetval accelertion to 0 each cycle
    orient = (float)atan2(vel.y,vel.x) * 180/PI;

    boundCheck(boundaryPadding); 


}


void Boid::boundCheck(int padding) {

    if(loc.x>endCorner.x-padding)
    {
        loc.x=endCorner.x-padding;
        vel.x=-vel.x;

    }

    else if(loc.x<0+padding)
     {
         loc.x=0+padding;
         vel.x=-vel.x;
     }

    if(loc.y>endCorner.y-padding)
    {
        loc.y=endCorner.y-padding;
        vel.y=-vel.y;
    }

    else if(loc.y<0+padding)
    {
        loc.y=0+padding;
        vel.y=-vel.y;
    }


}

//Flock your boids here
void Boid::flock(vector<Boid> &boids, Vec2f destination) {

	float m;
	
	m = (destination.y - loc.y) / (destination.x - loc.x);
	
	loc.x = loc.x+0.3;
	loc.y = m*(loc.x - destination.x) + destination.y;
	
	loc.setval( loc.x, loc.y );
}



bool Boid::isHit(int x, int y, int radius) {
    
    int range = 1;//calculation error range
    int dist =radius + range;
    if(pow((x-loc.x),2)+pow((y-loc.y),2) < (dist * dist) ){
        return true;
    }
    return false;
}


float Boid::dist(Vec2f v1,Vec2f v2)
{
    return v1.distance(v2);
}

float Boid::clamp(float val, float minval, float maxval)
{
    if(val<minval)
        return minval;
    else if (val>maxval)
        return maxval;
    else
        return val;
}
