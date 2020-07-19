## Bipartite_graph

Movie and actor associations to count Kevin Bacon distance number and Universe

_Collaborators: Lucas Martins (Minerio) and Sen Chai (Sun Shine) - 2020_

### Utilizacao do programa:
Dado o arquivo de entrada “input-top-grossing.txt”. 
Digite make go para compilar e executar o código principal. O comando aciona o compilador gcc.
Após um novo menu abrirá, a opção 1 permite pesquisa de nome de ator seguindo o formato: “Bacon, Kevin”. A opção 2 mostra media e desvio padrão de todos os atores até Kevin Bacon.

### Estrutura de Dados
Escolhemos a lista de adjacencias, pois é sabido que o modelo trabalhado é de grafo bipartite, atores ligam-se exclusivamente com filmes e filmes com atores.
A maioria dos atores trabalhou em poucos filmes, comparado a numero total de filmes existentes, deixando um numero pequeno de adjacentes para os atores. O modelo tende a um grafo pouco denso, justificando a rejeicao do modelo de matriz de adjacencias.
As arestas sao bidirecionadas.

### Complexidade de Busca
A busca a partir do nome do filme ou ator é linear, mas de acesso direto. Entao se ja conhecida o indice do vetor, a complexidade temporal do acesso é O(1).
Os indices dos vertices nao mudam ao longo da insercao, pois nao ha opcao de excluir elementos e nem conexoes.

### Insercao de Vertice
Vertices ao serem inseridos, antes passam por busca para ver se existiam anteriormente, entao a complexidade é linear.

### Insercao de Aresta
A lista de adjacencias guarda o valor de indice do vertice o qual se liga, esta lista de adjacencia é uma estrutura de vetor dinamico, onde o espcao alocado muda conforme seu crescimento, sua complexidade é constante.

### Caminho mais curto
Algoritimo usado requer fila e lista de cores para respectivamente guardar os vertices seguintes que devem ser percorridos, e as cores para marcar os vertices ja percorridos. O ponto incial sempre é Kevin Bacon, nesta proposta é verificar os caminhos dos demais atores ate Kevin Bacon.


### Calculo do número de Kevin Bacon e caminho mais curto
Método  usado é baseado no Algoritmo de busca em largura. Requer uma fila e uma lista de cores para respectivamente guardar os vértices seguintes que devem ser percorridos, e as cores para marcar os vértices já percorridos. O ponto inciais sempre é Kevin Bacon, nesta proposta é verificar os caminhos dos demais atores ate Kevin Bacon.
Esse processo resulta em um vetor de antecedentes, que é percorrido do índice do ator consultado até Kevin Bacon (ou mostra uma mensagem de erro caso esse ator não se ligue a origem) e reproduz o caminho até Kevin Bacon.

### O mundo de Kevin
Tambem baseado no algoritmo de busca em largura, essa função utiliza o vetor de antecedentes para calcular o número de KB e armazenar em um vetor de distância, que será utilizado para as operações do calculo da media e do desvio padrão
