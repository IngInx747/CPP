#include <iostream>

#include "fun.h"
#include "CMinTerm.h"
#include "CSingleMinTerm.h"

using namespace std;

int SetDim()
{
	int a;
	cout << "Static int iDim (Number of Variables) : " << endl;
	cin >> a;
	return a;
}

int CMinTerm::iDim = SetDim();

int main(int argc, char** argv)
{
	// Section 1 : expr_to_truthtable ()
	/* ========================================
	char * ch = "~*|*&*(*|*~*)";
	
	ofstream fstName0 ("TruthTable.txt",ios::out);
	ofstream fstName1 ("MinTerm.txt",ios::out);
	
	fstName0 << expr_to_truthtable(ch);
	fstName1 << expr_to_minterm(ch);
	======================================== */
	
	//Section 2 : truthtable_to_expr ()
	//int CMinTerm::iDim = 4;
	
	//int iMinTerm[6] = {0, 1, 4, 11, 5, 7}; // Sample of MinTerms
	
	string str = "0010101011101101" ;
	string str_Result = truthtable_to_expr(str);
	std::cout << str_Result << "\n" ;
	/*
	int * iMinTerm = new int [ str.length() ];
	const int iNumOfMT = Truthtable_to_MinTerm (str, iMinTerm) ;
	/*
	for (int i=0; i<iNumOfMT; i++)
	{
		std::cout << iMinTerm[i] << " " ;
	}
	
	
	int iMinTerm[9] = {2,4,6,8,9,10,12,13,15};
	int iNumOfMT = 9;
	
	
	CMinTerm * mt = new CMinTerm [__NUM__];
	for (int i=0; i <iNumOfMT; i++)
	{
		if (mt[i].InitMinTerm (iMinTerm[i]) == 0) std::exit (0) ; 
	}
	
	CMinTerm * cmtTmp ; // = new CMinTerm () ;
	//cmtTmp->Print () ;
	
	queue <int> qInt ;
	queue <CMinTerm *> qCmt, qCmt2 ;
	
	qCmt = QM_PI_Generator ( mt, iNumOfMT ) ;
	
	// qCmt2 = qCmt ;
	
	qCmt2 = QM_Petrick (qCmt, mt, iNumOfMT ) ;
	
	//std::cout << qCmt.size() << "\n" ;
	
	//std::cout << qCmt2.size() << "\n" ;
	
	while (!qCmt2.empty())
	{
		//std::cout << qCmt.front() << "\n" ;
		cmtTmp = qCmt2.front() ;
		cmtTmp->Print() ;
		qCmt2.pop() ;
	}
	*/
	/*
	int i = 0 ;
	while (!qCmt.empty())
	{
		if ( i == qInt.front() )
		{
			//std::cout << "err\n" ;
			cmtTmp = qCmt.front() ;
			cmtTmp->Print() ;
			qInt.pop() ;
		}
		qCmt.pop() ;
		i++ ;
	}
	*/
	//std::cout << "\n" ;
	/*
	CSingleMinTerm csmt[5] ;
	csmt[0].SetValue (0) ; csmt[1].SetValue (2) ;
	//csmt[0].BR_Push(1);csmt[0].BR_Push(6);
	//csmt[1].BR_Push(4);csmt[1].BR_Push(16);
	//csmt[0].BR_Push(5);csmt[0].BR_Push(6);csmt[0].BR_Push(17);
	//csmt[1].BR_Push(2);csmt[1].BR_Push(8);
	csmt[0].BR_Push(13); csmt[0].BR_Push(51); csmt[0].BR_Push(25); csmt[0].BR_Push(14); csmt[0].BR_Push(38);
	csmt[1].BR_Push(16); csmt[1].BR_Push(32);
	csmt[0].Print(); csmt[1].Print();
	csmt[0].Combine(csmt[1]);
	csmt[0].Print();
	csmt[0].Simplify();
	csmt[0].Print();
	*/
	
	return 0;
}
