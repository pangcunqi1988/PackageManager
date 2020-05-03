/*!
 * \file PackageMgr.h
 * \date 2020/05/03 13:52
 * \author pangcunqi
*/

#pragma once

#include <string>
#include <vector>
using namespace std;

class PackageMgr
{
public:
	static	PackageMgr& GetInstance();
	bool	InitPackage(const char* pszDirectory);
	FILE*	Myfopen(const char* pszFileName, const char* pszOperator);
	char*	Myfgets(char* pszBuffer, int nSize, FILE * fp);

private:
	bool LoadPackage();
	void SavePackage();
	void SearchIniFile();
	void GeneratorPackage();
	struct FileInfo
	{
		string	strFileName;
		int	nOffset;
		int	nSize;
		int	nReadPos;
	};
	vector<FileInfo> m_vecFileInfo;
	char*					m_pBuffer;
	int					m_pWritePos;
	string					m_strDirectory;
};

#define g_objPackageMgr PackageMgr::GetInstance()
