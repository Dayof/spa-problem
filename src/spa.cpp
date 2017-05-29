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

void clear(){
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
/**
 * Information message to guide the user to press any key to continue using the
 *  system.
 *
 * @return void
 */
void pressToContinue(){
    cout << endl << "\t    Aperte <QUALQUER TECLA> para voltar ao menu.    ";
    getchar();
    getchar();
}


void displayPrefTeach(){
    spa_teacher(GRAPH);

    pressToContinue();
}


/**
 * Print the hole Graph.
 *
 * @return void
 */
void printAllGraph()
{
  bool flag = 1, flag2 = 1;

  for(int i=0; i < GRAPHSIZE; ++i)
  {
    if(GRAPH[i].first.second  == 0 ){
        if(flag){
            cout << endl << endl << "GRAFO BIDIRECIONADO MOSTANDO AS ESCOLAS E SEUS REQUERIDOS PROFESSORES" << endl << endl;
            flag = 0;
        }

        cout << "E" << GRAPH[i].first.first.first-99 << " : ";

        for(int j=0;j<GRAPH[i].second.size();j++){
            cout << "P" << GRAPH[i].second[j] << "-> ";
        }

        cout << " \\ " << endl << endl;

    } else {
        if(flag2){
            cout << endl << endl << "GRAFO BIDIRECIONADO MOSTANDO OS PROFESSORES E SUAS REQUERIDAS ESCOLAS" << endl << endl;
            flag2 = 0;
        }

        cout << "P" << GRAPH[i].first.first.first << " : ";
        for(int j=0;j<GRAPH[i].second.size();j++){
            cout << "E" << GRAPH[i].second[j] << " -> ";
        }

        cout << " \\ " << endl;
    }
  }

  pressToContinue();
}


/**
 * Displays the help screen.
 *
 * @return void
 */
void displayHelpUI(){
    cout << "\t--------------Teacher School Allocation Problem-------------" << endl;
    cout << "\t- Terceiro projeto da materia de Teoria e Aplicacao        -" << endl;
    cout << "\t- de Grafos (TAG) do semestre de 2017/1.                   -" << endl;
    cout << "\t- Feito por Dayanne Fernandes e Renato Nobre               -" << endl;
    cout << "\t-                                                          -" << endl;
    cout << "\t- O trabalho implementa um grafo bidirecionado de          -" << endl;
    cout << "\t- professores e faculdades. E procura o emparelhamento     -" << endl;
    cout << "\t- perfeito para o grafo. A opcão 1 mostra o                -" << endl;
    cout << "\t- emparelhamento com base nas escolas, a opcao 2           -" << endl;
    cout << "\t- mostra o grafo completo.                                 -" << endl;
    cout << "\t------------------------------------------------------------" << endl;

    pressToContinue();
}


/**
 * Displays the main user interface of the project.
 *
 * @return void
 */
void displayUI(){
    clear();

    cout << "\t--------------Teacher School Allocation Problem-------------" << endl;
    cout << "\t-                                                          -" << endl;
    cout << "\t- 1. Alocacao com preferencia do professor                 -" << endl;
    cout << "\t- 2. Grafo                                                 -" << endl;
    cout << "\t- 3. Ajuda                                                 -" << endl;
    cout << "\t- 4. Sair                                                  -" << endl;
    cout << "\t-                                                          -" << endl;
    cout << "\t------------------------------------------------------------" << endl;
    cout << endl << "\t>>> ";
}

/**
 * Displays a message when the user inputs a not valid choice for the
 *  processUIChoice.
 *
 * @return void
 */
void displayWrongChoiceUI(){
    displayUI();
    cout << "\tEscolha invalida, informe um valor de 1 a 4" << endl;
    cout << "\t>>> ";
}

/**
 * Process what is the user's choice of the main user interface
 *  and call the respective method.
 *
 * @return void
 */
void processUIChoice(){
    int choice = 0;

    cin >> choice;

    while(choice != 4){
        clear();

        if(choice == 1){
            displayPrefTeach();
            displayUI();
        } else if(choice == 2){
            printAllGraph();
            displayUI();
        } else if(choice == 3){
            displayHelpUI();
            displayUI();
        } else {
            displayWrongChoiceUI();
        }

        cin >> choice;
    }

}

// worst teacher means that is the last teacher temporary assignment on the
// preference list of the school
int worstTeacher(vector<pair<int, int>> final_match, int school, vector<int> school_pref_list){
    int ind, big_index = -1;
    vector<int> index_to_look;

    for(auto elem : final_match)
        if(elem.second == school)
            index_to_look.push_back(elem.first);

    for(int i = 0; i < index_to_look.size(); i++)
        for(int j = 0; j < school_pref_list.size(); j++)
            if(school_pref_list[j] == i){
                ind = j;
                if(ind > big_index)
                    big_index = ind;
            }

    return (big_index > -1) ? school_pref_list[big_index] : -1;
}

vector<int> wtSuccessorsList(int fs, int index_wt){
    vector<int> v;

    for(int i=0; i < GRAPH[fs].second.size(); ++i)
      if(i >= index_wt) v.push_back(GRAPH[fs].second[i]);

    return v;
}

void spa_teacher(vector<iiiv> G){

    int ft, fs, actual_place_fs, wt, index_wt;
    // Tf: teachers free list
    vector<int> Tf, edge, wt_successors;
    // Vs: dict of vacancies of each school
    map<int, int> Vs;
    // list of tuples of the stable marriage
    vector<pair<int, int>> final_match;
    pair<int, int> last_match;
    bool run = true;

    for(int i = 0 ; i < TEACHERSIZE ;i++)
        Tf.push_back(i);

    for(int i = TEACHERSIZE-1 ; i < GRAPHSIZE ;i++)
        Vs[i] = 2;

    // first free teacher to test
    ft = Tf[0];
    Tf.erase(remove(Tf.begin(), Tf.end(), ft), Tf.end());

    // while there is a free teacher
    while(run){
      if(!G[ft].second.empty() && !Tf.empty())
      {
        ft = Tf[0];
        Tf.erase(remove(Tf.begin(), Tf.end(), ft), Tf.end());
        continue;
      }

      run = !Tf.empty() ? true : false;

      // get first school preference of the teacher we're trying to match
      fs = G[ft].second[0];
      // assign this teacher temporary on a school
      last_match = make_pair(ft, fs);
      final_match.push_back(last_match);
      // delete this school preference on the teacher preference list
      G[ft].second.erase(remove(G[ft].second.begin(),
                        G[ft].second.end(), fs),
                        G[ft].second.end());
      // decrease one vacancy of that school
      Vs[fs]--;

      // check if school vacancy is over subscribed
      if(Vs[fs] < 0){
          // get worst teacher
          wt = worstTeacher(final_match, fs, G[fs].second);
          if(wt > -1){
              // delete the worst teacher temporary assigned
              final_match.erase(remove(final_match.begin(),
                                  final_match.end(), make_pair(wt, fs)),
                                  final_match.end());
              // put this teacher back on the free list of teachers
              Tf.push_back(wt);
              // remove this teacher from the preference of that school
              G[fs].second.erase(
                            remove(G[fs].second.begin(),
                                G[fs].second.end(), wt),
                                G[fs].second.end());
              // increase one vancacy of that school
              Vs[fs]++;
          } else {
              // if on the final match there is no teacher of the preference
              // of that school, delete the last one
              final_match.erase(remove(final_match.begin(),
                                  final_match.end(), last_match),
                                  final_match.end());
              // put this last back on the free list of teachers
              Tf.push_back(last_match.first);
              // increase one vancacy of that school
              Vs[fs]++;
          }
      }

      // check if school vacancy is full
      if(Vs[fs] == 0){
          // get worst teacher
          wt = worstTeacher(final_match, fs, G[fs].second);
          if(wt > -1){
              index_wt = *(find(G[fs].second.begin(),
                            G[fs].second.end(), wt)) + 1;
              wt_successors = wtSuccessorsList(fs, index_wt);

              if(!wt_successors.empty()){
                  for(int i = 0; i < wt_successors.size();i++){
                      // remove teachers sucessors after the index of the
                      // worst teacher on the school preference list
                      if(find(G[fs].second.begin(),
                          G[fs].second.end(),
                          wt_successors[i]) != G[fs].second.end())
                          G[fs].second.erase(
                            remove(G[fs].second.begin(), G[fs].second.end(), wt_successors[i]),
                            G[fs].second.end());

                      // also, remove this school preferenre on the teachers
                      // removed preference list
                      if(find(G[wt_successors[i]].second.begin(),
                          G[wt_successors[i]].second.end(),
                          fs) != G[wt_successors[i]].second.end())
                          G[wt_successors[i]].second.erase(
                            remove(G[wt_successors[i]].second.begin(), G[wt_successors[i]].second.end(), fs),
                            G[wt_successors[i]].second.end());
                  }
              }
          }
      }

      // get next free teacher on ft
      if(!Tf.empty()){
          ft = Tf[0];
          Tf.erase(remove(Tf.begin(), Tf.end(), ft), Tf.end());
      }
  }

  // temporary print 
  for(auto elem : final_match)
      cout << elem.first << "->" << elem.second << endl;

}


/**
 * Incert a vertex with entyty, code, habilities ans position on the GRAPH.
 *
 * @param entity int value that determine if the vertex is a professor or school
 *
 * @param cod professor or school code
 *
 * @param hab amount of habilities a professor have or a school requires
 *
 * @param posix position index of the vertex to be inserted
 *
 * @return void
 */
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

/**
 * Insert Edges on the graph.
 *
 * @param adj  vector of adjecents to represent the edges
 *
 * @param v_origin index of the origin vertex
 *
 * @return void
 */
void insertAdjOnVertex(vector<int> adj, int v_origin)
{
  GRAPH[v_origin].second = adj;
}


/**
 * Convert string to int. Used to remove E and T from the text file.
 *
 * @param word  the string to be converted
 *
 * @return iword integer made from the string
 */
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

  // printAllGraph();

  displayUI();
  processUIChoice();

  return 0;
}
