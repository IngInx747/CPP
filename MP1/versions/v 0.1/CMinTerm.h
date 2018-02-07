#ifndef CMINTERM_HXX
#define CMINTERM_HXX

#include <iostream>
#include <string>
#include <vector>
#include "fun.h"

class CMinTerm
{
public:
	static int iDim ; // Potential number of variables.
	std :: vector <int> vMinTerm ; // Restore min-term(s).
	int * iBinReps ; // Restore binary representation (2 stands for '-', i.e. covered variable(s).).
	int iNumOfTrue ; // Count of *this's 1's number in its binary representation.
	//bool boIsPI ; // Label *this is PI or not.
	int iIsPI ; // Label *this is PI (0), successfully combined (1), or deleted (merged) (2).
	
	//static void SetDim (int) ;
	CMinTerm () ;
	//CMinTerm (int) ;
	~CMinTerm () ;
	
	void Print () ;
		
	CMinTerm & operator = (const CMinTerm &) ;
	bool operator == (const CMinTerm &) ;
	bool operator != (const CMinTerm &) ;
	
	bool InitMinTerm (int) ; // Initialize MinTerms from given source.
	
	void Merge (CMinTerm &) ;
	
	int CanCombine (const CMinTerm &) ;
	// If two minterms can combine, this function will return the
	// position of difference in digit, or return -1 if they cannot combine.
	
	CMinTerm Combine (CMinTerm &, int) ;
	// This function combine two minterms, given the correct digit.
	// The second parameter requires the result from CanCombine (..).
	
	friend std::ostream & operator << (std::ostream os, CMinTerm & cmt) ;
	//friend std::ostream & operator << (std::ostream os, CMinTerm * cmt) ;
} ;

//std::queue <int> FindPI ( CMinTerm MT[], int) ;

//std :: queue <CMinTerm> PI_Generator ( CMinTerm *, int) ;

#endif
