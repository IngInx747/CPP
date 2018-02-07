#include "CMinTerm.h"

using namespace std;

CMinTerm :: CMinTerm ()
{
	//iDim = iNumVar;
	//vMinTerm.push_back(0) ;
	iBinReps = new int [iDim];
	iNumOfTrue = 0; // boIsPI = false;
	for (int i=0; i<iDim; i++) iBinReps[i] = 0 ;
}

CMinTerm :: ~CMinTerm ()
{
	delete [] iBinReps;
}

bool CMinTerm :: InitMinTerm (int iMx)
{
	iNumOfTrue = 0 ; //boIsPI = false ;
	iIsPI = 0 ; // Label all minterm as PI initially.
	
	if (iMx <0 || iMx >= (2<<(iDim-1)))
	{
		cout << "CMinTerm :: InitMinTerm : Out of Bounds !" <<endl;
		return false;
	}
	
	int iTmp = iMx;
	
	vMinTerm.push_back (iMx);
	
	for (int i=0; i<iDim; i++)
	{
		iBinReps[i] = iTmp %2;
		if (iTmp %2) iNumOfTrue++;
		iTmp = iTmp >>1;
	}
	
	return true ;
}

void CMinTerm :: Print ()
{
	vector <int> :: iterator itrvTmp;
	//itrvTmp = vMinTerm.begin ();
	cout << "(" ;
	//while ( itrvTmp != vMinTerm.end () )
	for (itrvTmp = vMinTerm.begin(); itrvTmp != vMinTerm.end(); itrvTmp++)
	{
		cout << (*itrvTmp) << " " ;
		//itrvTmp++ ;
	}
	cout << ") [" ;
	for (int i=iDim-1; i>=0; i--)
	{
		if (iBinReps[i] == 2) cout << '-' ;
		else cout << iBinReps[i] ;
	}
	cout << "] " ; cout << iNumOfTrue << " " ;
	//if (iIsPI==0) cout << "*" ;
	cout << endl ;
}

CMinTerm & CMinTerm :: operator = (const CMinTerm & mt)
{
	vMinTerm = mt.vMinTerm ;
	iNumOfTrue = mt.iNumOfTrue ;
	iIsPI = mt.iIsPI ;
	for (int i=0; i<iDim; i++) iBinReps[i] = mt.iBinReps[i] ;
}

bool CMinTerm :: operator == (const CMinTerm & mt)
{
	int iCol = iDim ;
	for (int i=0; i<iDim; i++)
	{
		if (iBinReps[i] != mt.iBinReps[i]) return false;
	}
	return true;
}

bool CMinTerm :: operator != (const CMinTerm & mt)
{
	return  !( (*this) == mt ) ;
}

void CMinTerm :: Merge (CMinTerm & mt)
{
	if (iIsPI == 2) return ; // Mean current minterm has been already deleted.
	else if ( (*this) != mt ) return ; // No need of merging.
	else mt.iIsPI = 2 ; // Mean deletion of this minterm.
}

int CMinTerm :: CanCombine (const CMinTerm & mt)
{
	if ( iIsPI == 2 || mt.iIsPI == 2 ) return -1 ; // Deleted minterms should not be combined.
	else if ( iNumOfTrue +1 != mt.iNumOfTrue ) return -1 ; // Out Layer judgement.
	else
	{
		int iCol = iDim ; int iTmp1 = 0, iTmp2 = 0 ; int iDig = -1 ;
		int iDiff = 0 ; // Count of difference digits between two minterms.
		for (int i=0; i<iDim; i++)
		{
			iTmp1 = iBinReps[i] ; iTmp2 = mt.iBinReps[i] ;
			switch (iTmp1)
			{
				case 0 :
					if (iTmp2 == 2) return -1 ;
					else if (iTmp2 ==1) {iDiff++ ; iDig = i ;}
					break ;
				case 1 :
					if (iTmp2 == 2) return -1 ;
					else if (iTmp2 == 0) {iDiff++ ; iDig = i ;}
					break;
				case 2 :
					if (iTmp2 != 2) return -1 ;
					break ;
				default :
					std::cout << "CMinTerm :: CanCombine : Problems exist !" << std::endl ;
			}
		}
		if (iDiff != 1) return -1 ; // Two minterms should differ 1 and only 1 digit.
		return iDig ;
	}
}

CMinTerm CMinTerm :: Combine (CMinTerm & mt, int iIndex)
{
	CMinTerm cmt ;
	
	cmt.iNumOfTrue = iNumOfTrue;
	cmt.iIsPI = 0 ;
	
	cmt.vMinTerm = vMinTerm ; vector <int> vTmp = mt.vMinTerm ;
	vector <int> :: iterator itrvTmp = vTmp.begin () ;
	while ( itrvTmp != vTmp.end () )
	{
		cmt.vMinTerm.push_back ( *itrvTmp ) ;
		itrvTmp++ ;
	}
	
	for (int i=0; i<iDim; i++)
	{
		if (i == iIndex)
		{
			if (iBinReps[i] == 1) cmt.iNumOfTrue-- ;
			cmt.iBinReps[i] = 2 ;
		}
		else cmt.iBinReps[i] = iBinReps[i] ;
	}
	
	iIsPI = 1 ; mt.iIsPI = 1 ;
	return cmt ;
}

// ===== Assistant Functions =====

std :: ostream & operator << (std::ostream os, CMinTerm & cmt)
{
	for (int i = cmt.iDim-1; i>=0; i--)
	{
		if (cmt.iBinReps[i] == 2) os << '-' ;
		else os << cmt.iBinReps[i] ;
	}
	return os ;
}
/*
std :: ostream & operator << (std::ostream os, CMinTerm * cmt)
{
	for (int i = cmt->iDim-1; i>=0; i--)
	{
		if (cmt->iBinReps[i] == 2) os << '-' ;
		else os << cmt->iBinReps[i] ;
	}
	return os ;
}
*/
/*
queue <int> FindPI (CMinTerm MT[], int iN) // Return a queue containing indexes of PI.
{
	queue <int> qMt ;
	const int iRow = iN ; // Number of MinTerm input
	const int iCol = MT[0].iDim ; // Number of binary representation's size
	int iIndex ; // Index of first time that '1' has appeared in a single column of binary representation.
	
	for (int i=0; i<iCol; i++)
	{
		iIndex = -1 ;
		for (int j=0; j<iRow; j++) // Scan over CMinTerm on their certain digit (Binary representation).
		{
			if (MT[j].iBinReps[i] == 1)
			{
				if (iIndex != -1) // Mean '1' has appeared more than 2 times in BinReps.
				{
					iIndex = -1 ; // No chance this binary position will generate a PI.
					break ; // No influence to if()
				}
				iIndex = j ; // First time meeting '1' in BinReps.
			}
		}
		if (iIndex != -1) // Mean a PI has found.
		{
			qMt.push (iIndex) ;
			cout << iIndex << " ";
		}
	}
	
	return qMt;
}
*/

