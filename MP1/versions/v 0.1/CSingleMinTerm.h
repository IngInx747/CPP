#ifndef SINGLE_MIN_TERM_HXX
#define SINGLE_MIN_TERM_HXX

#include <iostream>
#include <string>
#include <vector>
#include "fun.h"

class CSingleMinTerm
{
public:
	int iValue ;
	std :: vector <int> vBR ;
	
	CSingleMinTerm () ;
	~CSingleMinTerm () ;
	
	void Print () ;
	
	void SetValue (int) ;
	void BR_Push (int) ;
	
	void Combine (CSingleMinTerm &) ;
	void Simplify () ;
} ;

#endif
