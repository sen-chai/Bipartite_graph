#include <stdlib.h>
#include <stdio.h>
#include <graph.c>
#include <graph.h>
#include <document_reader.c>
// #include <data_structures.h>

int main(void)
{
    GRAPH *graph = init_graph();

    // Input de dados
    // FILE *file = fopen("test.txt", "r");
    FILE *file = fopen("input-top-grossing.txt", "r");
    assert(file);
    // role pode ser MOVIE, ACTOR ou EOF
    int role = MOVIE, movie, actor;
    char *name = (char *)malloc(999 * sizeof(char));

    while (role != EOF)
    {
        if (role == MOVIE)
        {
            role = read_name(file, &name);
            if (role == EOF)
            {
                break;
            }
            // printf("\nMOVIE %s\n",name);

            // retornar filme do momento e adiciona-lo
            movie = ins_get_vertex(graph, name, MOVIE);
        }
        if (role == ACTOR)
        {
            role = read_name(file, &name);

            // printf("\nACTOR %s\n",name);

            // retornar posicao do ator e inserir-lo
            actor = ins_get_vertex(graph, name, ACTOR);
            // ligar ator ao filme que participou
            ins_edge(graph, movie, actor);
        }
    }

    //menu
    int origin = ins_get_vertex(graph, "Bacon, Kevin", ACTOR);
    int option = -1;
    while (option != 0)
    {
        printf("\nDigite 1 para buscar o numero de Kevin bacon de um ator, 2 para saber as informaçoes gerais e 0 para sair:\n");
        scanf(" %d", &option);
        switch (option)
        {
        //buscar um ator
        case 1:
            printf("\nDigite o nome e sobrenome:");
            scanf(" %[^\n]s",name);
           actor = ins_get_vertex(graph, name, ACTOR);
            search_actor(graph,origin,actor);
            break;
        //mundo de kevin
        case 2:
        kevin_world(graph,origin);
            break;
        default:
            break;
        }
    }
    fclose(file);
    free(name);
    return 0;
}