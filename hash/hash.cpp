// hash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hash.h"
#include <cmath>
#include <string>

int HF (int x)
{
	x *= x;
	x >>= 11;
	return x % 1024; 
};

int _tmain(int argc, _TCHAR* argv[])
{
	HashMultiMap<int,string,HF> F;
	int x = 0;
	//char s[50];
	string s, tmp;
	cout << "key > "; cin >>x;
	while (x>=0)
	{
		cout << "data >  "; cin.get(); cin >> s; while (cin.peek()!='\n') {cin >> tmp; s = s+" "+tmp;}
		F.HMM_push(x,s);
		cout << "key > "; cin >>x;
	}
	cout << endl;
	F.HMM_Print_all();
	cout << endl;
	cout << "Input > "; cin >> x;
	cout << F.HMM_search(x) << endl;
	cout <<  "Input > "; cin >> x;
	while (x>=0)
	{
		F.HMM_delete(x);
		cout <<  "Input > "; cin >> x;
	}
	cout << endl;
	F.HMM_Print_all();
	cout << endl;
	system("pause");
	return 0;
}

