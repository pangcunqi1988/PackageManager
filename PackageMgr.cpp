#include "PackageMgr.h"
#include "MemStack.h"

#include <stdio.h>
#include <io.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

PackageMgr& PackageMgr::GetInstance()
{
	static PackageMgr obj;
	return obj;
}

bool PackageMgr::InitPackage(const char* pszDirectory)
{
	m_pWritePos = 0;
	m_pBuffer = NULL;
	m_vecFileInfo.clear();
	m_strDirectory = pszDirectory;

	if (LoadPackage())
	{
		return true;
	}

	SearchIniFile();
	GeneratorPackage();
	SavePackage();
	return true;
}

void PackageMgr::DestoryPackage()
{
	if (m_pBuffer)
	{
		delete[] m_pBuffer;
	}
	m_vecFileInfo.clear();
}

void PackageMgr::SearchIniFile()
{
	string strPath = m_strDirectory;
	strPath += "/*.*";

	_finddata_t fileinfo;
	long handle = _findfirst(strPath.c_str(), &fileinfo);
	if (handle == -1)
		return;
	do
	{
		FileInfo obj;
		obj.strFileName = m_strDirectory;
		obj.strFileName += "/";
		obj.strFileName += fileinfo.name;
		m_vecFileInfo.push_back(obj);
	} while (!_findnext(handle, &fileinfo));
	_findclose(handle);
}

void PackageMgr::GeneratorPackage()
{
	m_pBuffer = new char[200*1024*1024];
	for (int i = 0; i < m_vecFileInfo.size(); i++)
	{
		FILE* fp = fopen(m_vecFileInfo[i].strFileName.c_str(),"rb");
		if (fp)
		{
			fseek(fp,0,SEEK_END);
			int nSize = ftell(fp);
			fseek(fp,0,SEEK_SET);

			fread(m_pBuffer+m_pWritePos,1,nSize,fp);
			fclose(fp);

			m_vecFileInfo[i].nOffset = m_pWritePos;
			m_vecFileInfo[i].nSize = nSize;
			m_vecFileInfo[i].nReadPos = 0;

			m_pWritePos += nSize;
		}
	}
}

void PackageMgr::SavePackage()
{
	if (m_vecFileInfo.size() > 0 && m_pWritePos > 0)
	{
		FILE* fp = fopen("MyIniFile.package", "wb");
		if (fp)
		{
			fwrite(m_pBuffer, 1, m_pWritePos, fp);
			fclose(fp);
		}
		fp = fopen("MyIniFile.index", "wb");
		if (fp)
		{
			for (int i = 0; i < m_vecFileInfo.size(); i++)
			{
				fprintf(fp, "%-32s %8d %8d\n", m_vecFileInfo[i].strFileName.c_str(), m_vecFileInfo[i].nOffset, m_vecFileInfo[i].nSize);
			}
			fclose(fp);
		}
	}
}

bool PackageMgr::LoadPackage()
{
	if (PathFileExists("MyIniFile.package"))
	{
		FILE* fp = fopen("MyIniFile.package", "rb");
		if (fp)
		{
			fseek(fp,0,SEEK_END);
			int nSize = ftell(fp);
			fseek(fp,0,SEEK_SET);

			m_pBuffer = new char[nSize];
			fread(m_pBuffer, 1, nSize, fp);
			fclose(fp);
		}

		fp = fopen("MyIniFile.index", "r");
		if (fp)
		{
			while (true)
			{
				FileInfo objFile;
				char szFileName[64] = {0};
				if (EOF == fscanf(fp, "%s %d %d\n", szFileName, &objFile.nOffset, &objFile.nSize))
				{
					break;
				}
				objFile.strFileName = szFileName;
				m_vecFileInfo.push_back(objFile);
			}
			fclose(fp);
		}
		return true;
	}
	return false;
}

FILE* PackageMgr::Myfopen(const char* pszFileName, const char* pszOperator)
{
	for (int i = 0; i < m_vecFileInfo.size(); i++)
	{
		if (m_vecFileInfo[i].strFileName == pszFileName)
		{
			m_vecFileInfo[i].nReadPos = 0;
			return (FILE*)(i+1);
		}
	}
	return NULL;
}

char* PackageMgr::Myfgets(char* pszBuffer, int nSize, FILE * fp)
{
	int nIndex = (int)fp - 1;
	if (nIndex < 0 || nIndex >= m_vecFileInfo.size())
	{
		return NULL;
	}

	FileInfo& objFile = m_vecFileInfo[nIndex];
	if (objFile.nReadPos >= objFile.nSize)
	{
		return NULL;
	}

	char* pCurrentPos = m_pBuffer+objFile.nOffset+objFile.nReadPos;
	for (int i  = 0; i < nSize; i++)
	{
		pszBuffer[i] = *(pCurrentPos+i);
		objFile.nReadPos++;
		if (pszBuffer[i] == 0xa || objFile.nReadPos >= objFile.nSize)
		{
			break;
		}
	}

	return pszBuffer;
}

