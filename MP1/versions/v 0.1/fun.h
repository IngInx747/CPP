#ifndef FUN_HXX
#define FUN_HXX

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <cstdlib>

#include "CMinTerm.h"
#include "CSingleMinTerm.h"

#define __NUM__ 100

class CMinTerm ;

class CSingleMinTerm ;

// ===== Section 1 =====

bool isInt (char) ;

int icp (char) ;

int isp (char) ;

bool mid2pos (char *, char *) ;

bool evalpos (char *) ;

int NumOfArg (char *) ;

void TransOfArg (char *, bool *, char *) ;

// ===== Section 2 =====

int Truthtable_to_MinTerm (std::string, int *) ;

bool IsPower2 (int) ;

//void QM (CMinTerm *, int) ;

std :: queue <CMinTerm *> QM_PI_Generator (CMinTerm *, int) ;

std :: queue <CMinTerm *> QM_Petrick (std::queue <CMinTerm *>, CMinTerm *, int) ;

// ===== Outside =====

std::string expr_to_truthtable (char *) ;

std::string expr_to_minterm (char *) ;

std::string truthtable_to_expr (std::string) ;

#endif
