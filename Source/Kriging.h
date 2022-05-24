// Kriging.h: interface for the Kriging class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KRIGING_H__2D4FB688_334E_464E_9E9F_55D489A8E5FC__INCLUDED_)
#define AFX_KRIGING_H__2D4FB688_334E_464E_9E9F_55D489A8E5FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Interpolater.h"
#include "Matrix.h"
#include "Numeric.h"
#include <string>
#include <vector>
#include <tchar.h>
#include <iostream>
using namespace std;

template<class ForwardIterator>
double GetDistance(const ForwardIterator start, int i, int j)
{
	return ::sqrt(::pow(((*(start+i)).x - (*(start+j)).x), 2) + ::pow(((*(start+i)).y - (*(start+j)).y), 2));
}

template<class ForwardIterator>
double GetDistance(double xpos, double ypos, const ForwardIterator start, int i)
{
	return ::sqrt(::pow(((*(start+i)).x - xpos), 2) + ::pow(((*(start+i)).y - ypos), 2));
}

template<class T, class ForwardIterator>
class TKriging : public TInterpolater<ForwardIterator>
{
public:
	TKriging(const ForwardIterator first, const ForwardIterator last, double dSemivariance) : m_dSemivariance(dSemivariance)
	{
		m_nSize = 0;
		ForwardIterator start = first;
		while(start != last) {
			++m_nSize;
			++start;
		}

		m_matA.SetDimension(m_nSize, m_nSize);

		for(int j=0; j<m_nSize; j++) {
			for(int i=0; i<m_nSize; i++) {
				if(i == m_nSize-1 || j == m_nSize-1) {
					m_matA(i, j) = 1;
					if(i == m_nSize-1 && j == m_nSize-1)
						m_matA(i, j) = 0;
					continue;
				}
				m_matA(i, j) = ::GetDistance(first, i, j) * dSemivariance;
			}
		}
		int nD;
		LUDecompose(m_matA, m_Permutation, nD);
	}
	double GetInterpolatedZ(double xpos, double ypos, ForwardIterator first, ForwardIterator last) throw(InterpolaterException)
	{
		std::vector<double> vecB(m_nSize);
		for(int i=0; i<m_nSize; i++) {
			double dist = ::GetDistance(xpos, ypos, first, i);
			vecB[i] = dist * m_dSemivariance;
		}
		vecB[m_nSize-1] = 1;

		LUBackSub(m_matA, m_Permutation, vecB);

		double z = 0;
		for(i=0; i<m_nSize-1; i++) {
			double inputz = (*(first+i)).z;
			z += vecB[i] * inputz;
		}
		if(z < 0)
			z = 0;
		return z;
	}
private:
	TMatrix<T> m_matA;
	vector<int> m_Permutation;
	int m_nSize;
	double m_dSemivariance;
};

typedef TKriging<double, Point3D*> Kriging;

#endif // !defined(AFX_KRIGING_H__2D4FB688_334E_464E_9E9F_55D489A8E5FC__INCLUDED_)
