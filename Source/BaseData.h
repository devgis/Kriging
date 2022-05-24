// BaseData.h: interface for the BaseData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEDATA_H__671236C3_A7E7_4782_AE8A_B81C4676A97C__INCLUDED_)
#define AFX_BASEDATA_H__671236C3_A7E7_4782_AE8A_B81C4676A97C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template<typename T>
struct TPoint2D
{
	TPoint2D() : x(0), y(0) {}
	TPoint2D(T xx, T yy) : x(xx), y(yy) {}
	T x;
	T y;
};

typedef TPoint2D<double> Point2D;

template<typename T>
struct TPoint3D
{
	TPoint3D() : x(0), y(0), z(0) {}
	TPoint3D(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
	T x;
	T y;
	T z;
};

typedef TPoint3D<double> Point3D;

inline bool Point3DCompare(const Point3D& pt1, const Point3D& pt2)
{
	return pt1.z < pt2.z;
}

#endif // !defined(AFX_BASEDATA_H__671236C3_A7E7_4782_AE8A_B81C4676A97C__INCLUDED_)
