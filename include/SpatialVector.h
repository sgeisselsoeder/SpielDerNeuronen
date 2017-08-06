#ifndef SPATIAL_VECTOR_H
#define SPATIAL_VECTOR_H

#include <vector>
#include <cmath>

class SpatialVector {
 
private:
    
    static const unsigned int m_numDimensions = 3;
    std::vector<double> m_coordinates;
    
public:
    
    SpatialVector();
    SpatialVector(double x, double y = 0.0, double z = 0.0);
    SpatialVector(const SpatialVector& vec);
  
    unsigned int getNumDimensions() const;  
    
    std::vector<double> getCoordinates() const;
    
    void turn2D (double angle); //ANA: I want to have turn; AIs shall steer the direction by turning the vector
					// SG: They should, but not by angle. Lets try to use evctor geometry whereever possible (also scale to 3D and 4D etc.)
    
    double length();
    
    void normalize(double desiredLength);
    
    void rescale (double coef);
    
    void normalize();
    
    SpatialVector& operator+=(const SpatialVector& rhs);
    SpatialVector& operator-=(const SpatialVector& rhs);
    SpatialVector& operator*=(double coef);
    
    SpatialVector& operator=(const SpatialVector& rhs);
    
    void setCoordinate(unsigned int idx, double val);
    
    void setCoordinates(double x, double y = 0.0, double z = 0.0);
    
    // TODO: implement [] operator
	// TODO implement ofstream<< operator

};

double distance(const SpatialVector& a, const SpatialVector& b);
double angle(const SpatialVector& a, const SpatialVector& b);

#endif
