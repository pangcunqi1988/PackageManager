#include <stdio.h>
#include <stdlib.h>

#define MEM_CHECK_MGR_CPP
#include "MemCheckMgr.h"

MemCheckMgr::MemCheckMgr() :head(NULL)
{

}

MemCheckMgr::~MemCheckMgr()
{
	MemInfo* tmp;
	while(head) 
	{
		free(head->ptr); // 释放泄漏的内存 
		tmp = head->link;
		free(head);
		head = tmp;
	}
}

void MemCheckMgr::Insert(void* ptr, const char* file, unsigned int line)
{
	MemInfo* node = (MemInfo*)malloc(sizeof(MemInfo));
	node->ptr = ptr; node->file = file; node->line=line;
	node->link = head; head = node;
}

void MemCheckMgr::Delete(void* ptr)
{
	MemInfo* node = head;
	MemInfo* preNode = NULL;
	while(node && node->ptr!=ptr) 
	{
		preNode = node;
		node = node->link;
	}

	if(node)
	{
		if(preNode == NULL) // 删除的是head 
			head = node->link;
		else 
			preNode->link = node->link;
		free(node);
	}
}

void MemCheckMgr::LogMemLeak()
{
	FILE* fp = fopen("MemLeakInfo.txt", "w");
	if (fp)
	{
		if(head == NULL) 
		{
			fprintf(fp, "No Memory Leak.\n");
		}
		else
		{
			fprintf(fp, "Find Memory Leak:\n");
			MemInfo* node = head;    
			while(node != NULL) 
			{
				fprintf(fp, "FileName: %s 行数: %d\n", node->file, node->line);
				node = node->link;
			}
		}
		fclose(fp);
	}
}

MemCheckMgr g_objMemCheckMgr;
void* operator new(size_t size, const char* file, unsigned int line)
{
	void* ptr = malloc(size);
	g_objMemCheckMgr.Insert(ptr, file, line);
	return ptr;
}

void* operator new[](size_t size, const char* file, unsigned int line)
{
	return operator new(size, file, line);
}

void operator delete(void* ptr)
{
	free(ptr);
	g_objMemCheckMgr.Delete(ptr);
}

void operator delete[](void* ptr)
{
	operator delete(ptr);
}
