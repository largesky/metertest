
#ifndef DLT6451997_H
#define DLT6451997_H
#include "DLT645.h"

class DLT645_API DLT6451997 : public DLT645
{
public :
	DLT6451997();
	
	const wchar_t* GetName();

	const wchar_t* GetDes();

	int  Init();
};

#endif