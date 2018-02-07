#include "CSingleMinTerm.h"

using namespace std ;

CSingleMinTerm :: CSingleMinTerm ()
{
	iValue = 0 ;
}

CSingleMinTerm :: ~CSingleMinTerm ()
{
	;
}

void CSingleMinTerm :: Print ()
{
	cout << "(" << iValue << ") [" ;
	vector <int> :: iterator vItr ;
	for (vItr = vBR.begin(); vItr != vBR.end(); vItr++)
	{
		cout << (*vItr) << " " ;
	}
	cout << "]\n" ;
}

void CSingleMinTerm :: SetValue (int ia)
{
	iValue = ia ;
}

void CSingleMinTerm :: BR_Push (int ia)
{
	vBR.push_back (ia) ; 
}

void CSingleMinTerm :: Combine (CSingleMinTerm & csmt)
{
	vector <int> vTmp ;
	vector <int> :: iterator vItr, vItr1 ;
	
	for (vItr1 = csmt.vBR.begin(); vItr1 != csmt.vBR.end(); vItr1++)
	{
		for ( vItr = vBR.begin(); vItr != vBR.end(); vItr++)
		{
			vTmp.push_back ( (*vItr1) | (*vItr) ) ;
		}
	}
	
	vBR = vTmp ;
}

void CSingleMinTerm :: Simplify ()
{
	int iTmp = 0 ;
	vector <int> vTmp ;
	vector <int> :: iterator vItr, vItr1, vItr2 ;
	
	for (vItr = vBR.begin(); vItr != vBR.end(); vItr++)
	{
		if ( *vItr != 0 )
		{
			vItr2 = vItr ; vItr2++ ; // vItr2 points to vItr's next.
			for (vItr1 = vItr2; vItr1 != vBR.end(); vItr1++)
			{
				iTmp = (*vItr) ^ (*vItr1) ;	
				if ( (*vItr)==(*vItr1) || IsPower2 (iTmp) )
				{
					// Remove the BR term from vBR.
					if ( (*vItr) > (*vItr1) ) *vItr = 0 ; 
					else *vItr1 = 0 ; 
					// Do u know why? Cause the smaller one's number of '1'
					// is less than the bigger one's which means keeping
					// the smaller term needs less minterms in the end.
				}
			}
		}
	}
	
	for (vItr = vBR.begin(); vItr != vBR.end(); vItr++)
	{
		if ( *vItr != 0 ) vTmp.push_back ( *vItr ) ;
	}
	
	vBR = vTmp ; // Update BR term after removal of all 0 terms.
}

