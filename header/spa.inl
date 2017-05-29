/** @file spa.inl
 *  @brief File of libraries.
 *
 *  This file includes all general libraries
 *  of C++ as well as the signature of each funcion of the program.
 *  Also, all global variables are kept here.
 *
 *  @author Dayanne Fernandes da Cunha 13/0107191
 *  @author Renato Avellar Nobre 15/0146698
 *  @bug No bug known.
 */

#ifndef HEADERS_INL_INCLUDED
#define HEADERS_INL_INCLUDED

/* -- Basic libraries for the better functioning of the program -- */

#include <iostream>
#include <sstream>
#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

/* ----------- Definition of all functions of the program ----------- */

/* -- Functions to show data on command terminal -- */
void clear();
void pressToContinue();
void displayPrefTeach();
void printAllGraph();
void displayHelpUI();
void displayUI();
void displayWrongChoiceUI();


/* -- Functions to create and populate the base graph -- */

int convStringToInt(string);
void insertAdjOnVertex(vector<int>, int);
vector<int> calcAdj(vector<int>, int);
vector<vector<int>> findSchoolsPerHab();
void insertVertexOnGraph(int, int, int, int);

/* -- Global variables definitions -- */

#define GRAPHSIZE 150
#define TEACHERSIZE 100
#define SCHOOLSIZE 50
#define T 1
#define S 0

#define ii pair<int, int>
#define iii pair<ii, int>
#define iiiv pair <iii, vector<int> >

vector<iiiv> GRAPH(GRAPHSIZE);



/* -- Functions of the main problem -- */
void processUIChoice();
vector<ii> spa_teacher(vector<iiiv>);
int worstTeacher(vector<ii> final_match, int school, vector<int> school_pref_list);
vector<int> wtSuccessorsList(int fs, int wt);

#endif // HEADERS_INL_INCLUDED
