## Bipartite_graph

Movie and actor associations to count Kevin Bacon distance number and Universe

_Collaborators: Lucas Martins (Minerio) and Sen Chai (Sun Shine) - 2020_

### Utilizacao do programa:
Digite make go para compilar e executar o codigo principal. O comando aciona o compilador gcc.
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
