#ifndef IPSTRUCT_H
#define IPSTRUCT_H
//当我们想在.h声明中定义成员变量，有时会报类型重定义错误，如果不是工程中真的重复定义了多个同名类，那么多半是没有给该类的头文件加条件指示符#ifndef，条件指示符#ifndef 最主要的目的就是防止头文件的重复包含和编译，这样才能保证头文件被多个其他文件引用时，内部的数据不会被多次定义而造成错误。解决方法有两种：


#include <windows.h>
typedef struct  
{
	DWORD m_dwLocalIP;
	DWORD m_dwTransIP;
	unsigned int m_nPort;
	DWORD m_dwLocalLogicIP;
	DWORD m_dwReceiverLogicIP;

} Address;
#endif