/*!
 * \file MemCheckMgr.h
 * \date 2020/05/03 20:13
 * \author pangcunqi
*/
#pragma once

//---------------------------------------------------------------
// �ڴ��¼ջ 
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
// ����new,new[],delete,delete[] 
//---------------------------------------------------------------
void* operator new(size_t size, const char* file, unsigned int line);
void* operator new[](size_t size, const char* file, unsigned int line);
void operator delete(void* ptr);
void operator delete[](void* ptr);

//---------------------------------------------------------------
// ʹ�ú꽫�����Դ����е�new��delte�滻Ϊ���ص�new��delete 
//---------------------------------------------------------------
#ifndef MEM_CHECK_MGR_CPP
#define new new(__FILE__,__LINE__)
#endif
//---------------------------------------------------------------