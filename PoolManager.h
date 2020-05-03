/*!
* \file PoolManager.h
* \date 2020/05/03 20:39
* \author pangcunqi
*/
#pragma once

#include <vector>
using namespace std;

template <typename T>
class CPoolManager
{
public:
	CPoolManager(){}
	T* GetOneInstance()
	{
		for (int i = 0; i < m_vecPoolT.size(); i++)
		{
			if (!m_vecPoolT[i]->m_bUsing)
			{
				m_vecPoolT[i]->m_bUsing = true;
				return m_vecPoolT[i];
			}
		}

		const int PER_NEW_COUNT = 32;
		for (int i = 0; i < PER_NEW_COUNT; i++)
		{
			T* pT = new T;
			m_vecPoolT.push_back(pT);
		}

		return this->GetOneInstance();
	}
private:
	vector<T*> m_vecPoolT;
};

template <typename T>
class CMemObject
{
public:
	CMemObject()					{ m_bUsing = false; }
	void			ReleaseObject()	{ m_bUsing = false; }
	static T*	CreateObject()		{ return m_sobjPoolManager.GetOneInstance(); }

	bool										m_bUsing;
	static CPoolManager<T>	m_sobjPoolManager;
};

template <typename T>
CPoolManager<T> CMemObject<T>::m_sobjPoolManager;
