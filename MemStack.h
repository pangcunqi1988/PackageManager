#pragma once

struct MemInfo 
{
	void*			ptr;
	const char*	file;
	unsigned int line;
	MemInfo*	link;
};
//---------------------------------------------------------------
// �ڴ��¼ջ 
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
// ����new,new[],delete,delete[] 
//---------------------------------------------------------------
void* operator new(size_t size, const char* file, unsigned int line);
void* operator new[](size_t size, const char* file, unsigned int line);
void operator delete(void* ptr);
void operator delete[](void* ptr);

//---------------------------------------------------------------
// ʹ�ú꽫�����Դ����е�new��delte�滻Ϊ���ص�new��delete 
//---------------------------------------------------------------
#ifndef MEM_STACK_CPP
#define new new(__FILE__,__LINE__)
#endif
//---------------------------------------------------------------