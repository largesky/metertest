#include "..\Include\DLT645\DLT645Frame.h"

wchar_t DLT645Frame::FE=0xFE;

int DLT645Frame::ReverseAndAdd(const wchar_t *data, size_t len,char *buf,char addChar)
{
	if( data==0 ||( wcslen(data)%2 !=0) || wcslen(data) <2 )
	{
		return 0;
	}
	for(int j=(int)(len-1),i=0;j>0;j-=2,i++)
	{
		buf[i]=(DLT645Frame::WCharToDigit(data[j-1]) <<4 )+ DLT645Frame::WCharToDigit(data[j]);
		buf[i]+=addChar;
	}
	int dafd=(int) len/2;
	assert(dafd>0);
	
	return (int)(len/2);
}

char DLT645Frame::GetXOR(const char* buf,int offset,int len)
{
	char xor=0;
	for(int i=0;i<len;i++)
	{
		xor+=buf[i+offset];
	}
	return xor;
}

char DLT645Frame::WCharToDigit(wchar_t chr)
{
	if(chr >=0 && chr <=15)
	{
		return (char)chr;
	}
	char a=wctob(towupper(chr));
	if(isdigit(a) !=0)
	{
		return a-'0';
	}
	return a-'A'+10;
}

wchar_t DLT645Frame::DigitToWChar(char chr)
{
	if(chr>=0 && chr <=9)
	{
		chr+='0';
	}
	else
	{
		chr=chr-10 +'A';
	}
	return btowc(chr);
}

char DLT645Frame::MakeBCDChar(wchar_t ch1,wchar_t ch2)
{
	char c=(WCharToDigit(ch1) << 4) + WCharToDigit(ch2);
	return c;
}

int DLT645Frame::MakeBCDString(wchar_t *source,char *buf)
{
	int len=0;
	int i=0;
	if(wcslen(source) %2 !=0)
		return 0;
	for(; source[i] && source[i+1];i+=2)
	{
		buf[len++]=MakeBCDChar(source[i],source[i+1]);
	}
	return len;
}

void DLT645Frame::ExpandBCDChar(char value,wchar_t *ch1,wchar_t *ch2)
{
	*ch1=DigitToWChar((0xF0 & value) >> 4);
	*ch2=DigitToWChar(0x0F & value);
}

void DLT645Frame::ExpandBCDString(char *source,int len,wchar_t *buf)
{
	int i=0,j=0;
	for(;i<len;i++)
	{
		ExpandBCDChar(source[i],buf+j,buf+j+1);
		j+=2;
	}
	buf[j]=0;
}
bool DLT645Frame::MakeAddressOK(wchar_t ** address)
{
	size_t addLen=wcslen(*address);
	//地址转换成大写
	if(addLen && (_wcsupr_s(*address,addLen+1) !=0))
		return false;
	wchar_t * tmp=new wchar_t[13];
	tmp[12]=0;
	if(_wcsset_s(tmp,13,L'0') !=0)
	{
		delete tmp;
		return false;
	}
	//查找第个为 A 或者数字的下标
	int index=0;
	for(;*(*address +index);index++)
	{
		if((*(*address +index) ==L'A') || (*(*address +index)>=L'0' && *(*address +index) <=L'9'))
		{
			break;
		}
	}
	//没有找到符合的数字，则返回 所为0
	if(index ==addLen)
	{
		delete *address;
		*address=tmp;
		return true;
	}

	//查找最后一个为A或者数字的下标
	size_t lastIndex=index+1;
	for(;lastIndex <addLen ;lastIndex++)
	{
		if(((*(*address +lastIndex) ==L'A') || (*(*address +lastIndex)>=L'0' && *(*address +lastIndex) <=L'9')) ==false)
		{
			break;
		}
	}
	if(lastIndex <addLen)
	{
		*(*address + lastIndex)=0;
	}
	//复制数据
	if(wcscpy_s(tmp+(12-(lastIndex-index)),lastIndex-index+1,*address+index)!=0)
	{
		delete tmp;
		return false;
	}
	delete *address;
	*address=tmp;
	assert(_CrtCheckMemory());
	return true;
}

bool DLT645Frame::DupString(wchar_t ** dst,const wchar_t * source,bool deleteDst)
{
	assert(_CrtCheckMemory());
	assert(source);
	if(*dst ==0 || (wcslen(*dst) <wcslen(source)))
	{
		if(*dst !=0 && deleteDst==true)
		{
			//__try
			//{
				delete *dst;
			//}
			//__except(EXCEPTION_CONTINUE_EXECUTION)
			//{
			//}
		}
		*dst=new wchar_t[wcslen(source)+1];
	}
	wcscpy_s(*dst,wcslen(source)+1,source);
	assert(_CrtCheckMemory());
	return true;
}

DLT645Frame::DLT645Frame()
{
	this->address=0;
	this->cmd=0;
	this->di=0;
	this->userCode=0;
	this->password=0;
	this->xor=0;
	this->data=0;
	this->feCount=3;
}

DLT645Frame::~DLT645Frame()
{
	delete this->address;
	delete this->di;
	delete this->userCode;
	delete this->password;
	delete this->data;
}

const wchar_t *DLT645Frame::GetAddress()
{
	return this->address;
}

void DLT645Frame::SetAddress(const wchar_t* address)
{
	DLT645Frame::DupString(&this->address,address,true);
}

wchar_t DLT645Frame::GetCmd()
{
	return this->cmd;
}

void DLT645Frame::SetCmd(wchar_t cmd)
{
	this->cmd=cmd;
}

const wchar_t *DLT645Frame::GetDI()
{
	return this->di;
}

void DLT645Frame::SetDI(const wchar_t *di)
{
	DLT645Frame::DupString(&this->di,di,true);
}

const wchar_t *DLT645Frame::GetUserCode()
{
	return this->userCode;
}

void DLT645Frame::SetUserCode(const wchar_t *userCode)
{
	DLT645Frame::DupString(&this->userCode,userCode,true);
}

const wchar_t *DLT645Frame::GetPassword()
{
	return this->password;
}

void DLT645Frame::SetPassword(const wchar_t * password)
{
	DLT645Frame::DupString(&this->password,password,true);
}

const wchar_t *DLT645Frame::GetData()
{
	return this->data;
}

void DLT645Frame::SetData(const wchar_t *data)
{
	DLT645Frame::DupString(&this->data,data,true);
}

int DLT645Frame::GetFECount()
{
	return this->feCount;
}

void DLT645Frame::SetFECount(int feCount)
{
	this->feCount=feCount;
}

int DLT645Frame::GetDataLen()
{
	if(this->GetData() ==0)
		return 0;

	return (int)(wcslen(this->GetData())+1)/2;
}