#ifndef DLT645DI_H
#define DLT645DI_H

#include "DLT645Comm.h"
class DLT645_API DLT645DI
{
private :
	wchar_t *di;
	wchar_t *des;

public :
	DLT645DI();
	~DLT645DI();

	const wchar_t *GetDI();
	void SetDI(const wchar_t *di);

	const wchar_t *GetDes();
	void SetDes(const wchar_t *des);
};
#endif