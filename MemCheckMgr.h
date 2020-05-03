/*!
 * \file MemCheckMgr.h
 * \date 2020/05/03 20:13
 * \author pangcunqi
*/
#pragma once

//---------------------------------------------------------------
// 内存记录栈 
//---------------------------------------------------------------
class MemCheckMgr 
{
private:
	struct MemInfo 
	{
		void*			ptr;
		const char*	file;
		unsigned int line;
		MemInfo*	link;
	};
	MemInfo* head;
public:
	MemCheckMgr();
	~MemCheckMgr();
	void Insert(void* ptr, const char* file, unsigned int line);
	void Delete(void* ptr);
	void LogMemLeak();
};
extern MemCheckMgr g_objMemCheckMgr;
//---------------------------------------------------------------
// 重载new,new[],delete,delete[] 
//---------------------------------------------------------------
void* operator new(size_t size, const char* file, unsigned int line);
void* operator new[](size_t size, const char* file, unsigned int line);
void operator delete(void* ptr);
void operator delete[](void* ptr);

//---------------------------------------------------------------
// 使用宏将带测试代码中的new和delte替换为重载的new和delete 
//---------------------------------------------------------------
#ifndef MEM_CHECK_MGR_CPP
#define new new(__FILE__,__LINE__)
#endif
//---------------------------------------------------------------