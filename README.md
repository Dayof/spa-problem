# Student-Project Allocation Problem

Terceito projeto da matéria de Teoria e Aplicação de Grafos (TAG) do semestre de 2017/1. O sistema irá resolver o "famoso" problema de alocação de estudante-projeto, porém, aplicado para professor-escola.

## Execução

Para executar este programa basta executar os seguintes comandos no terminal:

```
  $ bash run_all.sh
```

Este comando acima compila o programa utilizando o [Makefile](https://github.com/Dayof/spa-problem/Makefile) e já o executa em seguida. Caso queira só executar o programa sem necessariamente compilar novamente, executar o seguinte comando:

```
  $ ./main
```

## Pré-requisitos do sistema

Este programa foi testado no sistema operacional ``macOS Sierra``, versão ``10.12``. A linguagem de programação utilizada para implementar todo o projeto foi ``C++11``.

## Detalhes sobre o projeto

Este programa utiliza o arquivo ``cod_hab.txt`` e ``cod-hab_schools.txt`` para criar um grafo de professores que gostariam de trabalhar em certas escolas, e o requerimento de cada escola em relação a professores que gostariam de contratar . É gerado um estrutura abstrata de grafo bidirecionado e bipartido para representar ambos os professores e as escolas. Ao total são 50 escolas que querem contratar até 2 professores e 100 professores, que tem preferencia de 5 escolas.

### Funcionalidades

O programa realiza as seguintes funcionalidades a partir do menu principal:

- Opção 1 : Mostra o emparelhamento estável entre os grupos de professores e escolas, com base na preferencia do professor.

- Opção 2 : Mostra o Grafo Completo

- Opção 3 : Mostra uma tela de ajuda, relatando informações básicas sobre o programa.

- Opção 4 : Permite sair do programa.

### Fluxo do programa

- Recebe dois arquivos de texto, ``cod-hab.txt`` que contém informações das escolas e suas preferencias, ``cod-hab_schools.txt`` contendo informações dos professores e suas preferencias de escolas;
- Cria-se um vértice, contendo os seguintes elementos:
    - Entidade (professor, ou escola),
    - Código,
    - Numero de habilitações,
    - Preferencias;
- Faz o devido tratamento dos códigos dos vértices para inserção no grafo;
- Cria-se as listas de preferencias com os códigos atualizados;
- Realiza o emparelhamento estável com preferencias dos professores;
- Mostra a interface do usuário no terminal;
- Espera receber alguma ação do usuário;
- Executa a ação requisitada e volta para o menu inicial até que o usuário não queira mais utilizar o sistema (pressionando o número 4 do teclado na tela principal para sair do programa).

## Autoria

- Dayanne Fernandes da Cunha
  - Matrícula: 13/0107191
  - E-mail: dayannefernandesc@gmail.com
  - GitHub: [Dayof](https://github.com/Dayof)

- Renato Avellar Nobre
  - Matrícula: 15/0146698
  - E-mail: rekanobre@gmail.com
  - GitHub: [Skalwalker](https://github.com/Skalwalker)
