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
  // printf("%d : %d : %d\n", GRAPH[posix].first.second, GRAPH[posix].first.first.first, GRAPH[posix].first.first.second);
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

  pF = fopen("cod_hab.txt", "r");

  if(pF == NULL)
  {
    printf("Error on open the file.\n");
    return -1;
  }

  i = 0;
  while (fscanf(pF, "(%[^)]):(%d)\n", cod, &hab) != EOF)
  {
    scod = cod;
    scod.erase(0,1);
    icod = stoi(scod);
    insertVertexOnGraph(S, icod, hab, i);
    ++i;
  }

  fclose(pF);

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
    insertVertexOnGraph(T, icod, hab, i);
    ++i;
  }

  fclose(pF);

  return 0;
}
