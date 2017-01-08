
#ifndef XMLHELPER_H
#define XMLHELPER_H
#include "MeterBaseComm.h"
#include <MsXml2.h>
#include <objbase.h>
#include <ObjIdl.h>
#include <ObjSafe.h>
#include <atlbase.h>
#include <atlcom.h>
class METERBASE_API XmlHelper
{
private :
	IXMLDOMDocument *xmlDoc;
	IXMLDOMElement *rootEle;
public :
	XmlHelper();
	~XmlHelper();

	static bool GetAttribute(IXMLDOMNode *Node,wchar_t *attName,VARIANT * value);
	bool LoadFile(const wchar_t *file);
	bool Close();
	IXMLDOMElement * GetDoucumentElement();
};
#endif