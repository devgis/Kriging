// InverseDist.h: interface for the InverseDist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INVERSEDIST_H__BB8C4FFF_A66C_4669_8B04_7D3080F5066A__INCLUDED_)
#define AFX_INVERSEDIST_H__BB8C4FFF_A66C_4669_8B04_7D3080F5066A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Interpolater.h"
#include <cassert>
#include <cmath>

struct WeightAndZ
{
	WeightAndZ(double w, double zz) : weight(w), z(zz) {}
	double weight;
	double z;
};

template<class ForwardIterator>
class TInverseDist : public TInterpolater<ForwardIterator>
{
public:
	TInverseDist(double dRadius=200, double dExponent=8) throw() : m_dRadius(dRadius), m_dExponent(dExponent) {}
	double GetInterpolatedZ(double xpos, double ypos, ForwardIterator first, ForwardIterator last) 
	throw(InterpolaterException)
	{
		// Check if Data is valid
		assert(first != last);

		double distance = 0;
		double weight = 0;
		double totalWeight = 0;

		vector<WeightAndZ> vecWeight;
		ForwardIterator start = first;
		while(start != last) {
			distance = ::sqrt((::pow((xpos - (*start).x), 2) + ::pow((ypos - (*start).y), 2)));
			if(distance == 0) // exact match
				return (*start).z;

			if(distance > m_dRadius) {
				++start;
				continue;
			}

			weight = 1 / ::pow(distance, m_dExponent);
			vecWeight.push_back(WeightAndZ(weight, (*start).z));

			totalWeight += weight;
			++start;
		}
		for(int i=0; i<vecWeight.size(); i++)
			vecWeight[i].weight /= totalWeight;

		double nodeValue = 0;
		for(i=0; i<vecWeight.size(); i++) {
			nodeValue += vecWeight[i].weight * vecWeight[i].z;
			++first;
		}
		return nodeValue;
	}
private:
	double m_dRadius;
	double m_dExponent;
};

typedef TInverseDist<Point3D*> InverseDist;

#endif // !defined(AFX_INVERSEDIST_H__BB8C4FFF_A66C_4669_8B04_7D3080F5066A__INCLUDED_)
