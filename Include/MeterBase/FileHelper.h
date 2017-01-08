#ifndef FILEHELPER_H
#define FILEHELPER_H

#include "MeterBaseComm.h"
class METERBASE_API FileHelper
{
public :

	static bool FileExist(const wchar_t * filePath);
};
#endif