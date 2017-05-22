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

/**
 * Main function. Reads and loads basic data, then executes all main
 *  functionalities of the program.
 *
 * @return int 0 represents good exit, -1 represents bad exit
 */
int main(){

    char cod[4];
    string scod;
    int hab;

    FILE *pF = fopen("cod_hab.txt", "r");

    if(pF == NULL) {
        cout << "Error on open the file." << endl;
        return -1;
    }

    while (fscanf(pF, "(%[^)]):(%d)\n", cod, &hab) != EOF)
    {
      scod = cod;
      printf("(%s):(%d)\n", cod, hab);
    }

    fclose(pF);

    return 0;
}
