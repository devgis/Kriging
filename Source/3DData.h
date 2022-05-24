// 3DData.h: interface for the TC3DData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DDATA_H__CFB5BADB_20A1_4513_8CE7_2CAAAF4325BF__INCLUDED_)
#define AFX_3DDATA_H__CFB5BADB_20A1_4513_8CE7_2CAAAF4325BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseData.h"
#include <vector>
#include <string>

template<class T>
class TC3DData
{
public:
	static TC3DData<T>* GetInstance(std::string legend = "Untitled") throw() { return new TC3DData<T>(legend); }
	void Clear() throw() { m_strLegend = _T(""); m_vecData.clear(); }
	void AddData(double xdata, double ydata, double zdata) throw() { m_vecData.push_back(Point3D(xdata, ydata, zdata)); }
	void SetAt(int index, double xdata, double ydata, double zdata) throw() {
		m_vecData[index].x = xdata; m_vecData[index].y = ydata; m_vecData[index].z = zdata; 
	}
	void SetSize(int size) throw() { m_vecData.resize(size); }
	int GetSize() const throw() { return m_vecData.size(); }
	double GetXdata(int index) const throw() { return m_vecData[index].x; }
	double GetYdata(int index) const throw() { return m_vecData[index].y; }
	double GetZdata(int index) const throw() { return m_vecData[index].z; }
private:
	TC3DData(std::string legend) : m_strLegend(legend) {}
	TC3DData(const TC3DData<T>& rhs) {}
	TC3DData<T>& operator=(const TC3DData<T>& rhs) {}
	std::string	m_strLegend;
	std::vector<Point3D> m_vecData;
};

typedef TC3DData<double> C3DData;

#endif // !defined(AFX_3DDATA_H__CFB5BADB_20A1_4513_8CE7_2CAAAF4325BF__INCLUDED_)
