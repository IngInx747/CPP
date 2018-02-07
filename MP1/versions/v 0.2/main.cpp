#include <iostream>

#include "fun.h"
#include "CMinTerm.h"
#include "CSingleMinTerm.h"

using namespace std;

int main(int argc, char** argv)
{
	// Section 1 : expr_to_truthtable ()
	/* ================================================================================ */
	
	std :: string strExpressionRaw = "~*^*&*|(*|*)" ;
	std :: string strTruthTable ;
	std :: string strMinTerm ;
	std :: string strExpression ;
	
	ofstream fstName0 ("TruthTable.txt", ios::out) ;
	ofstream fstName1 ("MinTerm.txt", ios::out) ;
	
	strTruthTable	= expr_to_truthtable (strExpressionRaw) ;
	strMinTerm		= expr_to_minterm    (strExpressionRaw) ;
	//fstName0 << expr_to_truthtable(str) ;
	//fstName1 << expr_to_minterm(str) ;
	std::cout << strTruthTable << "\n" ;
	std::cout << strMinTerm << "\n" ;
	
	//Section 2 : truthtable_to_expr ()
	/* ================================================================================ */
	
	strExpression	= truthtable_to_expr (strTruthTable);
	
	std::cout << strExpression << "\n" ;
	
	return 0;
}
