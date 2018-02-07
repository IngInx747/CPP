#include "fun.h"

using namespace std;

// ===== Section 1 =====

int icp (char ch)
{
	switch(ch)
	{
		case '~': return 4;
		case '&': return 3;
		case '^': return 2;
		case '|': return 1;
		default : return 0;
	}
}

int isp (char ch)
{
	switch(ch)
	{
		case '~': return 4;
		case '&': return 3;
		case '^': return 2;
		case '|': return 1;
		case '(': return 0;
		case '$': return -1;
		default : return 0;
	}
}

bool mid2pos (char mid[], char pos[])
{
	stack <char> stk;
	char ch; int i = 0, j = 0;
	
	ch = mid[0]; // Begin scan from the very first of mid-expression
	stk.push('$'); // Label of end
	
	while(ch!='\0')
	{
		if( islower(ch) || ch>=48 && ch<=57 ) pos[j++] = ch; // Arguments shall be output straight
		
		else switch(ch)
		{
			case '~': case '&': case '^': case '|':
				while( icp(ch) <= isp(stk.top()) )
				{
					// If comming char's superiority is lower than the one in the stack,
					// one should keep poping chars to pos-expression until one char's superiority
					// is even lower than the comming one's. 
					// Here chars refer to operators of logic calculation.
					pos[j++] = stk.top();
					stk.pop();
				}
				stk.push(ch);
				break;
			
			case '(': stk.push(ch); break;
				// '(' has the lowest superiority (still higher than '$'), which prohibits the
				// comparison between comming char and the char deeper than '(' in the stack.
				
			case ')':
				while( stk.top() != '(' )
				{
					pos[j++] = stk.top();
					stk.pop();
				}
				stk.pop(); // Poping out '(' without putting it into pos-expression.
				break;
			
			default : return 0;
		}
		
		ch = mid[++i]; // Step to next char in mid-expression
	}
	
	while( !stk.empty() )
	{
		// Some chars were left in the stack after scanning of the mid-expression,
		// put them into pos-expression all.
		pos[j++] = stk.top();
		stk.pop();
	}
	
	pos[j-1] = '\0';
	return 1;
}

bool evalpos (char pos[])
{
	stack <bool> stk;
	char ch; int i = 0;
	bool t0, t1 ,t2;
	
	ch = pos[0];
	
	while( ch != '\0' )
	{
		if( ch=='0' || ch=='1' )
		{
			t0 = atoi(&ch);
			stk.push(t0);
		}
		
		else switch(ch)
		{
			case '~':
				t0 = stk.top(); stk.pop();
				stk.push( !t0 ); break;
			case '&':
				t1 = stk.top(); stk.pop();
				t2 = stk.top(); stk.pop();
				stk.push( t1 && t2 ); break;
			case '^':
				t1 = stk.top(); stk.pop();
				t2 = stk.top(); stk.pop();
				stk.push( t1 ^ t2 ); break;
			case '|':
				t1 = stk.top(); stk.pop();
				t2 = stk.top(); stk.pop();
				stk.push( t1 || t2 ); break;
			default :
				cout<<"Invalid expression!"<<endl; return 0; break;
		}
		
		ch = pos[++i];
	}
	
	return stk.top();
}

int NumOfArg (char * str)
{
	char ch = str[0];
	int i = 0, num = 0;
	
	while(ch!='\0')
	{
		if(ch=='*') ++num;
		ch = str[++i];
	}
	
	return num;
}

void TransOfArg (char * str, bool * b, char * mid)
{
	int i = 0, j = 0; char ch;
	
	ch = str[0];
	
	while( ch != '\0' )
	{
		if( str[i] == '*' )  { mid[i] = b[j]?'1':'0'; j++; }
		else mid[i] = str[i];
		ch = str[++i];
	}
	
	mid[i] = '\0';
}

// ===== Section 2 =====

int Truthtable_to_MinTerm (std::string str, int * iArr)
{
	const int iN = str.length() ;
	
	queue <int> qInt ;
	
	for (int i=0; i<iN; i++)
	{
		if (str[i]=='1')
		{
			qInt.push (i) ;
		}
	}
	const int ia = qInt.size() ;
	int i = 0 ;
	while (!qInt.empty())
	{
		iArr[i++] = qInt.front() ;
		qInt.pop() ;
	}
	
	return ia ;
}

bool IsPower2 (int ia)
{
	if (ia==1) return true ;
	while (ia > 1)
	{
		if (ia%2 != 0) return false ;
		ia = ia >> 1 ;
	}
	return true ;
}

int NumOfOne (int ia)
{
	int iCount = 0 ;
	
	while (ia>1)
	{
		if (ia&1) iCount++ ;
		ia /= 2 ;
	}
	
	return iCount +1 ;
}

std :: queue < CMinTerm * > QM_PI_Generator (CMinTerm * mt, int iNumFirstLoop)
{
	int iN = iNumFirstLoop ; int iPos = -1 ; int iMove = 0 ;
	std :: queue < CMinTerm * > qMinTerm ;
	
	while (iN != 0)
	{
		// Merge : Delete repeated minterm(s).
		for (int i=0; i<iN-1; i++)
		{
			if (mt[i].iIsPI == 2) continue ;
			for (int j = i+1; j<iN; j++) mt[i].Merge (mt[j]) ;
		}
		//cout << "New terms : \n" ;
		// Combine : Two minterms will generate a new minterm with less arguments regarding logic term.
		for (int i=0; i<iN-1; i++)
		{
			if (mt[i].iIsPI == 2) continue ;
			for (int j=i+1; j<iN; j++)
			{
				iPos = mt[i].CanCombine (mt[j]);
				if (iPos != -1)
				{
					if ( iN+iMove >= __NUM__)
					{
						cout << "PI_Generator : Array out of bound !" << endl ;
						exit (1) ;
					}
					mt[iN+iMove] = mt[i].Combine (mt[j], iPos); // !! DANGEROUS !!
					//mt[iN+iMove].Print () ;
					iMove++ ; // Now iMove stands for count of new-attended minterms.
				}
			}
		}
		//cout << "PI : \n" ;		
		// Queue in PI
		for (int i=0; i<iN; i++)
		{
			if (mt[i].iIsPI == 0)
			{
				qMinTerm.push (mt+i) ;
				//mt[i].Print () ;
				//qMinTerm.back()->Print() ;
			}
		}
		
		mt += iN ; // Move the head of array to original one's end.
		iN = iMove ; // Update size of array. If iN==0 the loop stops.
		iMove = 0 ;
	}
	
	return qMinTerm ;
}

std :: queue <CMinTerm *> QM_Petrick (queue <CMinTerm *> qCmt, CMinTerm * mt, int iN)
{
	int iTmp, iTmp2 ;
	
	CMinTerm * cmtTmp = new CMinTerm () ;
	
	CSingleMinTerm * csmtTmp, * csmtTmp2 ;
	csmtTmp = new CSingleMinTerm () ;
	csmtTmp2 = new CSingleMinTerm () ;
	CSingleMinTerm * csmt = new CSingleMinTerm [iN] ;
	
	vector <CMinTerm *> vCmt ;
	vector <int> :: iterator vItrInt, vItrInt2 ;
	vector <CMinTerm *> :: iterator vItr, vItrBR ;
	
	std :: queue <CMinTerm *> qCmt_Result ;
	//std :: queue < int > qInt_Result ;
	
	map <int, CSingleMinTerm *> mapICmt ;
	
	while ( !qCmt.empty() )
	{
		vCmt.push_back ( qCmt.front () ) ;
		qCmt.pop () ;
	}
	
	// Initialize single minterms of their values.
	// Create a map to connect their criticial values and BR tables.
	for (int i=0; i<iN; i++)
	{
		iTmp = mt[i].vMinTerm.front () ;
		csmt[i].SetValue ( iTmp ) ;
		mapICmt[iTmp] = csmt + i ; // Assume the raw minterms differ with each other.
	}
	
	// Scan over PI to initialize single minterms -- CSingleMinTerm
	iTmp2 = 1 ;
	
	for (vItr = vCmt.begin(); vItr != vCmt.end(); vItr++)
	{
		cmtTmp = *vItr ;
		for ( vItrInt = cmtTmp->vMinTerm.begin(); vItrInt != cmtTmp->vMinTerm.end(); vItrInt++)
		{
			csmtTmp2 = mapICmt[(*vItrInt)] ; // Here mapICmt[(*vItrInt)]->BR_Push (iTmp2) is wrong.
			csmtTmp2->BR_Push (iTmp2) ;
		}
		iTmp2 *= 2 ;
	}
	
	// Petrick algorithm's process
	csmtTmp->SetValue ( 0 ) ; // iValue is not important in the following process.
	csmtTmp->vBR = csmt->vBR ; // Get the BR table of the first single minterm.

	for (int i=1; i<iN; i++)
	{
		csmtTmp->Combine ( csmt[i] ) ;
		csmtTmp->Simplify () ;
		//csmtTmp->Print () ;
	}
	
	// Find the Merge containing the least PI.
	iTmp = 999 ;
	// Here iTmp stands for the number of '1' of an integer in BR in the result.
	vItrInt = csmtTmp->vBR.begin () ; // Point to the integer with the least '1's.
	for (vItrInt2 = csmtTmp->vBR.begin(); vItrInt2 != csmtTmp->vBR.end(); vItrInt2++)
	{
		iTmp2 = NumOfOne (*vItrInt2) ;
		if (iTmp > iTmp2)
		{
			vItrInt = vItrInt2 ;
			iTmp = iTmp2 ;
		}
	}
	
	//iTmp2 = -1 ; // Position of selected PI(s).
	iTmp = *vItrInt ; // Here iTmp stands for the integer with the least '1's.
	for (vItr = vCmt.begin(); vItr != vCmt.end(); vItr++)
	{
		if (iTmp&1)
		{
			cmtTmp = *vItr ;
			qCmt_Result.push ( cmtTmp );
			//cmtTmp->Print() ;
		}
		iTmp /= 2 ;
	}
	return qCmt_Result ;
	
	/*
	iTmp = *vItrInt ; // Here iTmp stands for the integer with the least '1's.
	for (int i=0; i<iN; i++)
	{
		if (iTmp&1)
		{
			qInt_Result.push (i) ;
		}
		iTmp /= 2 ;
	}
	cout << "err\n" ;
	return qInt_Result ;*/
}


// ===== Outside =====

std::string expr_to_truthtable (char * str)
{
	unsigned int a;
	int i; int Ns = NumOfArg(str);
	char tmpMid[100]; char tmpPos[100];
	bool boolTmp; bool * b = new bool[Ns];
	string strFl;
	
	for (i=0;i<Ns;i++) cout<<"arg"<<(i+1)<<"\t";
	cout<<str<<endl;
	
	for (a=0; a<(1<<Ns); a++)
	{
		for (i=Ns-1; i>=0; i--)
		{
			b[Ns-1-i] = (a>>i)&1;
			cout<<b[Ns-1-i]<<"\t";
		}
		
		TransOfArg (str, b, tmpMid);
		mid2pos (tmpMid,tmpPos);
		boolTmp = evalpos (tmpPos);
		cout << boolTmp << endl;
		
		switch (boolTmp)
		{
			case 0:
				strFl += "0\n"; break;
			case 1:
				strFl += "1\n"; break;
			default:
				break;
		}
		
	}
	return strFl;
}

std::string expr_to_minterm (char * str)
{
	unsigned int a;
	int i; int Ns = NumOfArg(str);
	char tmpMid[100]; char tmpPos[100];
	bool boolTmp; bool * b = new bool[Ns];
	stringstream ss;
	
	for (a=0; a<(1<<Ns); a++)
	{
		for (i=Ns-1; i>=0; i--)
		{
			b[Ns-1-i] = (a>>i)&1;
		}
		
		TransOfArg (str, b, tmpMid);
		mid2pos (tmpMid,tmpPos);
		boolTmp = evalpos (tmpPos);
		
		if (boolTmp)
		{
			cout << a << " ";
			ss << a << "\n";
		}
		
	}
	return ss.str ();
}

std::string truthtable_to_expr (string str)
{
	int * iMinTerm = new int [ str.length() ];
	const int iNumOfMT = Truthtable_to_MinTerm (str, iMinTerm) ;
	
	stringstream ss ;
	
	CMinTerm * cmtTmp ; // = new CMinTerm () ;
	CMinTerm * mt = new CMinTerm [__NUM__];
	
	queue <int> qInt ;
	queue <CMinTerm *> qCmt, qCmt2 ;

	for (int i=0; i <iNumOfMT; i++)
	{
		if (mt[i].InitMinTerm (iMinTerm[i]) == 0) std::exit (0) ; 
	}
	
	qCmt = QM_PI_Generator ( mt, iNumOfMT ) ;
	
	qCmt2 = QM_Petrick (qCmt, mt, iNumOfMT ) ;
	
	while (!qCmt2.empty())
	{
		cmtTmp = qCmt2.front() ;
		for (int i=0; i<cmtTmp->iDim; i++)
		{
			if (cmtTmp->iBinReps[i] == 2) ss << "-" ;
			else ss << (cmtTmp->iBinReps[i]) ;
		}
		ss << " " ;
		qCmt2.pop() ;
	}
	
	return ss.str() ;
}

