/** @file spa.cpp
 *  @brief Main file.
 *
 *  This file contains all the functions and variables
 *  to fully execute the third project of TAG 2017/1.
 *
 *  @author Dayanne Fernandes da Cunha 13/0107191
 *  @author Renato Avellar Nobre 15/0146698
 *  @bug No bug known.
 */

#include "spa.inl"


// void spaT()
// {
//   freeTeachers();
//   freeUniversities();
//   while()
// }

void insertVertexOnGraph(int entity, int cod, int hab, int posix)
{
  ii inner_node = make_pair(cod, hab);
  iii node = make_pair(inner_node, entity);
  iiiv node_struc = make_pair(node, vector<int>());
  GRAPH[posix] = (node_struc);
}

vector<int> findSchoolsAdj(int hab)
{
  vector<int> t_adj;

  for(int i=0; i < 100; ++i)
    if(GRAPH[i].first.first.second == hab)
      t_adj.push_back(i);

  return t_adj;
}

vector<int> calcAdj(vector<int> raw_adj, int entity)
{
  vector<int> final_adj(raw_adj.size());

  for(int i=0; i<raw_adj.size(); ++i)
  {
    // 99 = 100 - 1
    if(entity) final_adj[i] = raw_adj[i] + 99;
    else final_adj[i] = raw_adj[i] - 1;
  }

  return final_adj;
}

void insertAdjOnVertex(vector<int> adj, int v_origin)
{
  GRAPH[v_origin].second = adj;
}

void printAllGraph()
{
  for(int i=0; i < GRAPHSIZE; ++i)
  {
    printf("Entity : %d | Cod : %d | Hab : %d | Adj : \n", GRAPH[i].first.second, GRAPH[i].first.first.first, GRAPH[i].first.first.second);
    for(int j=0; j<GRAPH[i].second.size(); ++j)
      printf("%d -> ", GRAPH[i].second[j]);
    printf("\n");
  }
}

/**
 * Main function. Reads and loads basic data, then executes all main
 *  functionalities of the program.
 *
 * @return int 0 represents good exit, -1 represents bad exit
 */
int main(){

  char cod[4], p1[4], p2[4], p3[4], p4[4], p5[4];
  string scod, sp1, sp2, sp3, sp4, sp5;
  int hab, i, icod;

  FILE *pF;

  pF = fopen("cod-hab_schools.txt", "r");

  if(pF == NULL)
  {
    printf("Error on open the file.\n");
    return -1;
  }

  i = 0;
  while (fscanf(pF, "(%[^,], %d): (%[^,], %[^,], %[^,], %[^,], %[^)])\n", cod, &hab, p1, p2, p3, p4, p5) != EOF)
  {
    scod = cod;
    scod.erase(0,1);
    icod = stoi(scod);
    insertVertexOnGraph(T, icod-1, hab, i);
    ++i;
  }

  fclose(pF);

  pF = fopen("cod_hab.txt", "r");

  if(pF == NULL)
  {
    printf("Error on open the file.\n");
    return -1;
  }

  while (fscanf(pF, "(%[^)]):(%d)\n", cod, &hab) != EOF)
  {
    scod = cod;
    scod.erase(0,1);
    icod = stoi(scod);
    insertVertexOnGraph(S, icod-1, hab, i);
    insertAdjOnVertex(calcAdj(findSchoolsAdj(hab), S), i);
    ++i;
  }

  fclose(pF);

  printAllGraph();

  return 0;
}
