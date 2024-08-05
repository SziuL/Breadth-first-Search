#include <stdio.h>
#include <stdlib.h>

typedef struct coordenates
{
    int i;
    int j;
    struct coordenates *prox;
} C;

void insertRow(C **fila, C *coordenate)
{
    C *newElement = (C *)malloc(sizeof(C));
    newElement->i = coordenate->i;
    newElement->j = coordenate->j;
    newElement->prox = NULL;

    if (*fila == NULL)
    {
        *fila = newElement;
    }
    else
    {
        C *aux = *fila;
        while (aux->prox)
            aux = aux->prox;
        aux->prox = newElement;
    }
}

void findGoal_BreadthFirstSearch(char **labirinto, char goal, int x, int y)
{
    int MAX_INTERACTIONS = x * y;
    C *fila = NULL;

    char **map = (char **)malloc(x * sizeof(char *));
    for (int i = 0; i < x; i++)
    {
        map[i] = (char *)malloc(y * sizeof(char));
        for (int j = 0; j < y; j++)
        {
            map[i][j] = labirinto[i][j];
        }
    }

    int counter = 0;
    C coordenate;
    coordenate.i = 0;
    coordenate.j = 0;

    insertRow(&fila, &coordenate);

    while (fila != NULL)
    {
        coordenate = *fila;
        C *temp = fila;
        fila = fila->prox;
        free(temp);

        char atual = labirinto[coordenate.i][coordenate.j];

        if (atual == goal)
        {
            printf("Encontrou o objetivo em (%d, %d)\n", coordenate.i, coordenate.j);
            return;
        }

        if (counter >= MAX_INTERACTIONS)
        {
            printf("Máximo de interações atingido.\n");
            return;
        }

        if (coordenate.i + 1 < x && map[coordenate.i + 1][coordenate.j] != '-' && labirinto[coordenate.i + 1][coordenate.j] != '#')
        {
            C newCoordenate = {coordenate.i + 1, coordenate.j, NULL};
            insertRow(&fila, &newCoordenate);
            map[coordenate.i + 1][coordenate.j] = '-';
        }
        if (coordenate.i - 1 >= 0 && map[coordenate.i - 1][coordenate.j] != '-' && labirinto[coordenate.i - 1][coordenate.j] != '#')
        {
            C newCoordenate = {coordenate.i - 1, coordenate.j, NULL};
            insertRow(&fila, &newCoordenate);
            map[coordenate.i - 1][coordenate.j] = '-';
        }
        if (coordenate.j + 1 < y && map[coordenate.i][coordenate.j + 1] != '-' && labirinto[coordenate.i][coordenate.j + 1] != '#')
        {
            C newCoordenate = {coordenate.i, coordenate.j + 1, NULL};
            insertRow(&fila, &newCoordenate);
            map[coordenate.i][coordenate.j + 1] = '-';
        }
        if (coordenate.j - 1 >= 0 && map[coordenate.i][coordenate.j - 1] != '-' && labirinto[coordenate.i][coordenate.j - 1] != '#')
        {
            C newCoordenate = {coordenate.i, coordenate.j - 1, NULL};
            insertRow(&fila, &newCoordenate);
            map[coordenate.i][coordenate.j - 1] = '-';
        }

        counter++;
    }

    printf("Labirinto completamente explorado sem sucesso de saída.\n");
}

int main()
{
    int x, y;

    printf("Qual o tamanho do labirinto? ");
    scanf("%d %d", &x, &y);

    char **labirinto = (char **)malloc(x * sizeof(char *));
    for (int i = 0; i < x; i++)
    {
        labirinto[i] = (char *)malloc(y * sizeof(char));
    }

    printf("Digite o labirinto:\n");
    for (int i = 0; i < x; i++)
    {
        scanf("%s", labirinto[i]);
    }

    findGoal(labirinto, '*', x, y);

    for (int i = 0; i < x; i++)
    {
        free(labirinto[i]);
    }
    free(labirinto);

    return 0;
}
