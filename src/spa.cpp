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

vector<vector<int>> findSchoolsPerHab()
{
  vector<vector<int>> all_t_adj(3);

  for(int i=0; i < 100; ++i)
  {
    if(GRAPH[i].first.first.second == 1)
      all_t_adj[0].push_back(i);
    else if(GRAPH[i].first.first.second == 2)
      all_t_adj[1].push_back(i);
    else if(GRAPH[i].first.first.second == 3)
      all_t_adj[2].push_back(i);
  }

  return all_t_adj;
}

vector<int> calcAdj(vector<int> raw_adj, int entity)
{
  vector<int> final_adj(raw_adj.size());

  for(int i=0; i<raw_adj.size(); ++i)
  {
    // 99 = 100 - 1
    if(entity) final_adj[i] = raw_adj[i] + 99;
    else final_adj[i] = raw_adj[i];
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

int convStringToInt(string word)
{
  int iword;

  word.erase(0,1);
  iword = stoi(word);

  return iword;
}

/**
 * Main function. Reads and loads basic data, then executes all main
 *  functionalities of the program.
 *
 * @return int 0 represents good exit, -1 represents bad exit
 */
int main(){

  char cod[4], p1[4], p2[4], p3[4], p4[4], p5[4];
  vector<vector<int>> all_t_adj(3);
  vector<int> t_adj, s_adj(5);
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
    sp1 = p1; sp2 = p2; sp3 = p3; sp4 = p4; sp5 = p5;
    s_adj[0] = convStringToInt(sp1); s_adj[1] = convStringToInt(sp2); s_adj[2] = convStringToInt(sp3); s_adj[3] = convStringToInt(sp4); s_adj[4] = convStringToInt(sp5);
    insertAdjOnVertex(calcAdj(s_adj, T), i);
    ++i;
  }

  fclose(pF);

  pF = fopen("cod_hab.txt", "r");

  if(pF == NULL)
  {
    printf("Error on open the file.\n");
    return -1;
  }

  all_t_adj = findSchoolsPerHab();

  while (fscanf(pF, "(%[^)]):(%d)\n", cod, &hab) != EOF)
  {
    insertVertexOnGraph(S, i, hab, i);

    if(hab==1)
      t_adj = all_t_adj[0];
    else if(hab==2)
      t_adj = all_t_adj[1];
    else if(hab==3)
      t_adj = all_t_adj[2];

    insertAdjOnVertex(calcAdj(t_adj, S), i);
    ++i;
  }

  fclose(pF);

  printAllGraph();

  return 0;
}
