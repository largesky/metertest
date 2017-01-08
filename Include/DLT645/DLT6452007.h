#ifndef DLT6452007_H
#define DLT6452007_H

#include "DLT645.h"

class DLT645_API DLT6452007 : public DLT645
{
public :
	DLT6452007();
	const wchar_t *GetName();
	const wchar_t *GetDes();
	int Init();
};
#endif