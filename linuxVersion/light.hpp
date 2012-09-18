
#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "Math.hpp"
class Light{
public:
	Light();


	virtual ~Light();



	int shaRays;

	virtual Vec Sample(RNG* rng)=0;
	virtual float Pdf()=0;
};
#endif