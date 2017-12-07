#ifndef SPATIAL_VECTOR_H
#define SPATIAL_VECTOR_H

#include <vector>
#include <cmath>
#include <ostream>

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
    
    double length() const;
    
    void normalize(double desiredLength = 1.0);
    void rescale (double coef);
    
    SpatialVector& operator+=(const SpatialVector& rhs);
    SpatialVector& operator-=(const SpatialVector& rhs);
    SpatialVector& operator*=(double coef);
    
    SpatialVector& operator=(const SpatialVector& rhs);
    
    void setCoordinate(unsigned int idx, double val);
    
    void setCoordinates(double x, double y = 0.0, double z = 0.0);
    
    void randomize();
    
    // TODO: implement [] operator
	// TODO implement ofstream<< operator

};

std::ostream& operator<<(std::ostream& os, const SpatialVector& obj);
const SpatialVector operator+(SpatialVector const& lhs, SpatialVector const& rhs);
const SpatialVector operator-(SpatialVector const& lhs, SpatialVector const& rhs);
bool operator==(SpatialVector const& lhs, SpatialVector const& rhs);
bool operator!=(SpatialVector const& lhs, SpatialVector const& rhs);
double distance(const SpatialVector& a, const SpatialVector& b);
double angle(const SpatialVector& a, const SpatialVector& b);


#endif
