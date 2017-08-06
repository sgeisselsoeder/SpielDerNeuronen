#ifndef THING_H
#define THING_H

#include <vector>
#include <list>
#include "SpatialVector.h"
#include <string>
#include "World.h"

class World;

class Thing
{	
protected:

	unsigned int m_identifier;	// should one day identify every thing to be able to trace it everywhere

	std::string	classID;
	// SG: I don't think a thing need to know about its world like that
	//~ World*		m_world;	

	SpatialVector m_position;
	SpatialVector m_velocity;	// has to be reduced in every timestep by friction
	double m_mass;
	double m_friction;
	
	//std::vector<double> acceleration;
	//std::vector<double> orientation;
	
	double m_health; // should be reduced in every timestep by a small amount
	double m_maxHealth; // maybe Things should split into children beyond a certain energy
	
	double m_maxSpeed;
	// double strength; // could also be a function s(health), with different objects having different maxHealth
	std::list<Thing> m_baggage;
	bool m_isFree;

	virtual void move(double dt);

	//~ virtual void look();
	//~ std::list<Thing> sense(const World* map);

	//~ virtual std::vector<double> plan(const std::list<Thing>& environment);
	//~ virtual void act(std::vector<double> plan);
	// amount of drained energy should maybe be scale down by amount *= (own.energy - target.energy)/target.energy
	// , but not more than factor 1.0
	//~ virtual void transferHealth(Thing& target, double amount);	// = eat(), heal()
	//~ virtual void transferEnergy(Thing& target, double amount);	// = throw()
	//~ virtual void pickUp(Thing& target);
	//~ virtual void drop(Thing& target);
        
public:
	Thing(SpatialVector position, SpatialVector velocity, double mass, double health, double maxHealth, double maxSpeed);
	Thing();
	//~ Thing(const SpatialVector& pos, const SpatialVector& vel, World* world);
	Thing(const SpatialVector& pos, const SpatialVector& vel);
	~Thing();
	
    double getMass() const;
	//~ double getEnergy();
    SpatialVector getPosition() const;
    //~ const SpatialVector& getPosition() const; 
    
    double getHealth() const;
    
    virtual void progress(double dt, World* world);
    
    virtual void print();
    
    std::string getClassID() const;
    
    virtual double transferHealth(const Thing* reciever);	// ANA: another thing can try to drain energy over this interface
															// ANA: it depends on implementation how much energy can be transferred in each case
															// ANA: e.g. stones do not let drain any energy and return zero
    
};


#endif
