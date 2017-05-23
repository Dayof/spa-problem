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

using namespace std;

/* ----------- Definition of all functions of the program ----------- */

/* -- Functions to show data on command terminal -- */

/* -- Functions to create and populate the base graph -- */

void insertAdjOnVertex(vector<int>, int);
vector<int> calcAdj(vector<int>, int);
vector<vector<int>> findSchoolsPerHab(int);
void insertVertexOnGraph(int, int, int, int);

/* -- Global variables definitions -- */

#define GRAPHSIZE 150
#define T 1
#define S 0

#ifdef WINDOWS
  #define CLEARSCR() system("cls")
#else
  #define CLEARSCR() system("clear")
#endif

#define ii pair<int, int>
#define iii pair<ii, int>
#define iiiv pair <iii, vector<int> >

vector<iiiv> GRAPH(GRAPHSIZE);

#endif // HEADERS_INL_INCLUDED
