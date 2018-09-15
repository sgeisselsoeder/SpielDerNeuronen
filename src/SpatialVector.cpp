#include <vector>
#include <cmath>
#include "SpatialVector.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>



SpatialVector::SpatialVector() : m_coordinates(m_numDimensions, 0.0) {}

SpatialVector::SpatialVector(const SpatialVector& vec) : m_coordinates(m_numDimensions, 0.0) {
    //~ m_coordinates.resize(m_numDimensions);
    for(unsigned int i = 0; i < m_numDimensions; i++) {
        m_coordinates[i] = vec.m_coordinates[i];
    }
}
SpatialVector::SpatialVector(double x, double y, double z) : m_coordinates(m_numDimensions, 0.0)  {
    setCoordinates(x, y, z);
}

void SpatialVector::setCoordinate(unsigned int idx, double val) {
    if (idx < m_numDimensions) {
        m_coordinates[idx] = val;
    }
}

void SpatialVector::setCoordinates(double x, double y, double z) {
	m_coordinates[0] = x;
	m_coordinates[1] = y;
	m_coordinates[2] = z;
}

void SpatialVector::turn2D(double angle) {
	
	double x = m_coordinates[0] * cos(angle) - m_coordinates[1] * sin(angle);
	double y = m_coordinates[0] * sin(angle) + m_coordinates[1] * cos(angle);
	
	m_coordinates[0] = x;
	m_coordinates[1] = y;
	
}

SpatialVector& SpatialVector::operator+=(const SpatialVector& rhs) {
	
	for (unsigned i = 0; i < m_numDimensions; i++) {
		m_coordinates[i] += rhs.m_coordinates[i];
	}
	
	return *this;
}


SpatialVector& SpatialVector::operator*=(double coef) {
	
	rescale(coef);
	return *this;
	
}


SpatialVector& SpatialVector::operator-=(const SpatialVector& rhs) {
	
	for (unsigned i = 0; i < m_numDimensions; i++) {
		m_coordinates[i] -= rhs.m_coordinates[i];
	}
	
	return *this;
}

SpatialVector& SpatialVector::operator=(const SpatialVector& rhs) {
	
	for (unsigned i = 0; i < m_numDimensions; i++) {
		m_coordinates[i] = rhs.m_coordinates[i];
	}
	
	return *this;
}

std::vector<double> SpatialVector::getCoordinates() const{
		return m_coordinates;
}


unsigned int SpatialVector::getNumDimensions() const{
		return m_numDimensions;
}


double SpatialVector::length() const {
	
    double sum = 0.0;
    
    for(unsigned int i = 0; i < m_numDimensions; i++) {
        sum += m_coordinates[i] * m_coordinates[i];
    }
    
    return sqrt(sum);
    
}

void SpatialVector::normalize(double desiredLength) {
	rescale(desiredLength / length());
	
}

void SpatialVector::rescale (double coef) {
	
	for(unsigned i = 0; i < m_numDimensions; i++) {
		m_coordinates[i] *= coef;
	}
	
}

void SpatialVector::randomize () {
	for(unsigned i = 0; i < m_numDimensions; i++) {
		m_coordinates[i] = rand()-0.5*RAND_MAX;
	}
}


double distance(const SpatialVector& a, const SpatialVector& b) {
    double sum = 0.0;
    
    for(unsigned int i = 0; i < a.getNumDimensions(); i++) {
        sum += (a.getCoordinates()[i] - b.getCoordinates()[i]) * (a.getCoordinates()[i] - b.getCoordinates()[i]);
    }
    
    return sqrt(sum);
    
}

double angle(const SpatialVector& a, const SpatialVector& b) {
    
    double length = 0.0;
    double vec_length = 0.0;
    double scalar_prod = 0.0;
    
    for(unsigned int i = 0; i < a.getNumDimensions(); i++) {
        vec_length		+= (b.getCoordinates()[i]) * (b.getCoordinates()[i]);
        length			+= (a.getCoordinates()[i]) * (a.getCoordinates()[i]);
        scalar_prod		+= (a.getCoordinates()[i]) * (b.getCoordinates()[i]);
    }
    double cos_angle = scalar_prod / sqrt (length) / sqrt(vec_length);
    // The min function is there to prevent numerical errors that can occur when the angle is close to zero, hence the cos_angle is approx. 1.
    // acos is not defined for 1.0+eps
    return acos(std::min(cos_angle, 1.0));
}

const SpatialVector operator+(SpatialVector const& lhs, SpatialVector const& rhs)
{
  SpatialVector tmp(lhs); //Kopie des linken Operanden
  tmp += rhs; //Implementierung mittels des +=-Operators
  return tmp;
}

const SpatialVector operator-(SpatialVector const& lhs, SpatialVector const& rhs)
{
  SpatialVector tmp(lhs); //Kopie des linken Operanden
  tmp -= rhs; //Implementierung mittels des -=-Operators
  return tmp;
}

bool operator==(SpatialVector const& a, SpatialVector const& b){
	for(unsigned int i = 0; i < a.getNumDimensions(); i++) {
		if (a.getCoordinates()[i] != b.getCoordinates()[i]) {
			return false;
		}
    }
    return true;
}

bool operator!=(SpatialVector const& a, SpatialVector const& b) {
	return !(a==b) ;
}

std::ostream& operator<<(std::ostream& os, const SpatialVector& obj)
{
	// write obj to stream
	for (unsigned i = 0; i < obj.getNumDimensions(); i++) {
		os << obj.getCoordinates()[i] << " ";
	}
	return os;
}
