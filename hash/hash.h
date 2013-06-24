#ifndef __HASHMULTIMAPSTART__
#define __HASHMULTIMAPSTART__

#include <iostream>
using namespace std;
const unsigned int MAX_SIZE_HASH= 10000;

template< class KeyType, class ValueType, int(*Hasher)(KeyType) > 
class HashMultiMap
{
protected:
	struct m_case
	{
		KeyType key;
		ValueType data;
		m_case *next;
		~m_case()
		{
			delete next;
		};
		void Print_all()
		{
			cout.width(6);
			cout << "Key: " << key << endl;
			cout << "Data: "<< data << endl;
			if (next != NULL) (*next).Print_all();
		}
		void Print_all(ofstream &out)
		{
			out << key << "  " << data << endl;
			if (next != NULL) (*next).Print_all(out);
		}
	};
	m_case **a;
public:
	HashMultiMap()
	{
		a = new m_case* [MAX_SIZE_HASH];
		for (int i = 0; i<MAX_SIZE_HASH; ++i)
			a[i]=NULL;
	};

	~HashMultiMap()
	{
		for (int i = 0; i<MAX_SIZE_HASH; ++i)
			if (a[i]!=NULL) delete a[i];
		delete [] a;
	};

	void HMM_push(KeyType key, ValueType data)
	{
		int index = Hasher(key)%MAX_SIZE_HASH;
		if (a[index] == NULL)
	
		{
			a[index]=new m_case;
			(*(a[index])).key = key;
			(*(a[index])).data = data;
			(*(a[index])).next = NULL;

		}
		else
		{
			m_case *tmp = a[index];
			while ((*tmp).next != NULL)
				tmp=(*tmp).next;
			(*tmp).next=new m_case;
			tmp = (*tmp).next;
			(*(tmp)).key = key;
			(*(tmp)).data = data;
			(*(tmp)).next = NULL;
		}
	};

	ValueType HMM_search(KeyType key)
	{
		m_case *tmp = a[Hasher(key)%MAX_SIZE_HASH];
		while (tmp!=NULL)
		{
			if ((*tmp).key == key) return (*tmp).data;
			tmp = (*tmp).next;
		}
		return NULL;
	};

	void HMM_delete(KeyType key)
	{
		int index = Hasher(key)%MAX_SIZE_HASH;
		if (a[index] == NULL) { /*cout << "\nNot faund\n";*/return;}
		m_case *tmp;
		if ((*(a[index])).key == key)
		{
			tmp = a[index];
			a[index]=(*(a[index])).next;
			(*tmp).next = NULL;
			delete tmp;
		}
		else
		{
			tmp = a[index];
			while((*tmp).next != NULL)
			{
				if ((*((*tmp).next)).key == key)
				{
					m_case *d = (*tmp).next;
					(*tmp).next = (*((*tmp).next)).next;
					(*d).next = NULL;
					delete d;
				}
				tmp=(*tmp).next;
			}
			
		}
	}
	void HMM_Print_all()
	{
		for (int i = 0;i<MAX_SIZE_HASH;++i)
			if (a[i]!=NULL) (*(a[i])).Print_all();
	}
	void HMM_Print_all(ofstream &out)
	{
		for (int i = 0;i<MAX_SIZE_HASH;++i)
			if (a[i]!=NULL) (*(a[i])).Print_all(out);
	}
};

#endif