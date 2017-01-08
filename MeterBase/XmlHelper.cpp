#include "..\Include\MeterBase\XmlHelper.h"

XmlHelper::XmlHelper()
{
	this->xmlDoc=0;
	this->rootEle=0;
}


XmlHelper::~XmlHelper()
{
}

bool XmlHelper::LoadFile(const wchar_t *file)
{
	if(CoCreateInstance(CLSID_DOMDocument2,NULL, CLSCTX_INPROC_SERVER,IID_IXMLDOMDocument,(PVOID *)&xmlDoc) !=S_OK)
	{
		return false;
	}
	VARIANT_BOOL isLoadOK=false;
	HRESULT hr;
	hr=xmlDoc->load(CComVariant(file),&isLoadOK);
	if(hr != S_OK || isLoadOK==false)
	{
		return false;
	}
	if(this->xmlDoc->get_documentElement(&this->rootEle) != S_OK)
		return false;
	return true;
}

IXMLDOMElement *XmlHelper::GetDoucumentElement()
{
	return this->rootEle;
}

bool XmlHelper::Close()
{
	if(this->xmlDoc ==0)
	{
		return false;
	}

	this->xmlDoc->Release();
	return true;
}

bool XmlHelper::GetAttribute(IXMLDOMNode *node,wchar_t *attName,VARIANT * value)
{
	IXMLDOMNamedNodeMap * attMap=0;
	if(node->get_attributes(&attMap) != S_OK)
	{
		return false;
	}
	IXMLDOMNode *attNode=0;
	if(attMap->getNamedItem(attName,&attNode) !=S_OK)
	{
		return false;
	}

	if(attNode->get_nodeValue(value) != S_OK)
	{
		return false;
	}
	return true;
}