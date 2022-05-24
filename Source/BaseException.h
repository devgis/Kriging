// BaseException.h: interface for the CBaseException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEEXCEPTION_H__0902F453_576E_48BB_90ED_7FC4CA666A82__INCLUDED_)
#define AFX_BASEEXCEPTION_H__0902F453_576E_48BB_90ED_7FC4CA666A82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdexcept>
#include <string>
#include <iostream>

#pragma warning( disable : 4290 ) // disable Exception Specification warning

#define LOCATION Location(__FILE__, __LINE__)

/** This function returns string object of Error filename and line number */
inline std::string Location(std::string file, int lineNo) {
	char buf[64];
	sprintf(buf, " line no. %d", lineNo);

	return file + buf;
}

class BaseException : public std::runtime_error
{
public:
	BaseException() throw() : runtime_error("error") {}
	BaseException(std::string message) throw() : runtime_error(message) {}
	BaseException(std::string message, std::string location) throw() : std::runtime_error(message+location) {}
	void Log(std::ostream& os) throw() { os << what() << std::endl; }
};

#endif // !defined(AFX_BASEEXCEPTION_H__0902F453_576E_48BB_90ED_7FC4CA666A82__INCLUDED_)
