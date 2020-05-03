#pragma once

struct MemInfo 
{
	void*			ptr;
	const char*	file;
	unsigned int line;
	MemInfo*	link;
};
//---------------------------------------------------------------
// 内存记录栈 
//---------------------------------------------------------------
class MemStack 
{
private:
	MemInfo* head;
public:
	MemStack();
	~MemStack();
	void Insert(void* ptr, const char* file, unsigned int line);
	void Delete(void* ptr);
	void LogMemLeak();
};
extern MemStack g_objMemStack;
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
#ifndef MEM_STACK_CPP
#define new new(__FILE__,__LINE__)
#endif
//---------------------------------------------------------------