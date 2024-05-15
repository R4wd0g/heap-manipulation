#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX 16

typedef struct {
    int elemento;
    int prioridade;
} heapnode;

// Valores iniciais arbitrários para o array
heapnode A[MAX] = {
    {0, 0}, {2, 2}, {7, 7}, {3, 3}, {1, 1}, {14, 14},
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1},
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}
};

int num;
int e,p,indiceCorrige;

void clearnoflicker(){
    printf("[J[H");
    //J Limpa do cursor até o final
    // [H move o cursor para o início da tela (1,1)
}

int pai(int i){
    return i/2;
}
int esq(int i){
    return 2*i;
}
int dir(int i){
    return 2*i + 1;
}


void constroi_grafo(heapnode A[], int num, char* filePath) {
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(file, "<html>\n<head>\n");
    fprintf(file, "<script src=\"https://cdn.jsdelivr.net/npm/mermaid/dist/mermaid.min.js\"></script>\n");
    fprintf(file, "<script>mermaid.initialize({ startOnLoad: true, theme: 'forest' });</script>\n");
    fprintf(file, "<style>\n");
    fprintf(file, "circle {\n");
    fprintf(file, "  r: 20px !important;\n");
    fprintf(file, "  fill: green !important;\n");
    fprintf(file, "  stroke: black !important;\n");
    fprintf(file, "  stroke-width: 3px !important;\n");
    fprintf(file, "}\n");
    fprintf(file, "span.nodeLabel {\n");
    fprintf(file, "  color: white !important;\n");
    fprintf(file, "  font-weight: bold;\n");
    fprintf(file, "  font-size: 20px;\n");
    fprintf(file, "  white-space: nowrap;\n");
    fprintf(file, "}\n");
    fprintf(file, ".mermaid .node foreignObject {\n");
    fprintf(file, "  width: 40px;\n");
    fprintf(file, "  height: 40px;\n");
    fprintf(file, "  transform: translate(-12px, -4px);\n");
    fprintf(file, "}\n");
    fprintf(file, "</style>\n");
    fprintf(file, "</head>\n<body>\n");
    fprintf(file, "<div class=\"mermaid\">\n");
    fprintf(file, "graph TD;\n");

    for (int i = 1; i <= num; i++) {
        if (esq(i) <= num && A[esq(i)].elemento != -1)
            fprintf(file, "    id%d((%d)) --- id%d((%d));\n", i, A[i].elemento, esq(i), A[esq(i)].elemento);
        if (dir(i) <= num && A[dir(i)].elemento != -1)
            fprintf(file, "    id%d((%d)) --- id%d((%d));\n", i, A[i].elemento, dir(i), A[dir(i)].elemento);
    }

    fprintf(file, "</div>\n</body>\n</html>");

    fclose(file);
}

void mostra_grafo(char* filePath) {
    char command[256];
    sprintf(command, "cmd.exe /c start %s", filePath);
    system(command);
}

void imprime_array(heapnode A[]){
    printf("[95m{[0m");
    for (int i = 1; i < MAX; i++){
        if (A[i].elemento == -1){
            printf("[97m ,[0m ");
        } else if ((e != -1) && (e == A[i].elemento)){
            printf("[103m[30m%d[0m[97m,[0m ", A[i].elemento);
        }
         else {
            printf("[94m%d[0m[97m,[0m ", A[i].elemento);
        }
    }
    printf("\b\b[95m}[0m");
}

int itens_ocupando(heapnode A[]){
    num = 0;
    for (int i = 1; i < MAX; i++){
        if (A[i].elemento != -1){
            num++;
        }
    }
    return num;
}

void cabecalho(){
    clearnoflicker();
    system("chcp 65001 > nul 2>&1");
    printf("\t\t\t[93m[4m░▒▓█   Árvore Heap   █▓▒░[0m\n\n");
    printf("[1m[32mEstado do array ─→ [0m");
    imprime_array(A);
    printf(" [46m[97m %d/%d [0m",itens_ocupando(A),MAX-1);
    printf("\n\n");
}


void insere() {
    cabecalho();
    if (num == MAX - 1) {
        printf("[93mHeap Cheio![0m\n");
        system("timeout -t 2 > NUL 2>&1");
        return;
    }
    printf("[96mDigite o valor a ser inserido:[0m ");
    scanf("%d",&e);
    printf("[96mDigite a prioridade:[0m ");
    scanf("%d",&p);


    // Insere o novo elemento na próxima posição livre
    num++;
    int i = num;
    A[i].elemento = e;
    A[i].prioridade = p;

    cabecalho();
    system("timeout -t 2 > NUL 2>&1");

    // Sobe o novo elemento enquanto a prioridade do pai for menor
    while (i > 1 && A[pai(i)].prioridade < A[i].prioridade) {
        // Troca com o pai
        heapnode temp = A[i];
        A[i] = A[pai(i)];
        A[pai(i)] = temp;
        i = pai(i);
        printf("\r");
        cabecalho();
        system("timeout -t 2 > NUL 2>&1");
    }
    e = -1; // reseta a variável "e" para um valor fora de uso para ser preenchida novamente.
}

void corrige_heap(int i){
    int esq_i = esq(i);
    int dir_i = dir(i);

    int maior = i;
    if (esq_i <= num && A[esq_i].prioridade > A[i].prioridade)
        maior = esq_i;
    if (dir_i <= num && A[dir_i].prioridade > A[maior].prioridade)
        maior = dir_i;

    if (maior != i) {
        heapnode temp = A[i];
        A[i] = A[maior];
        A[maior] = temp;
        system("cls");
        cabecalho();
        printf("Corrigindo heap: trocado %d com %d\n", A[i].elemento, A[maior].elemento);
        system("timeout -t 4 > NUL 2>&1");
        corrige_heap(maior);
    }
    e = -1;
}

void extrai_maximo() {
    cabecalho();
    if (num == 0) {
        printf("[93mHeap Vazio![0m\n");
        system("timeout -t 2 > NUL 2>&1");
        return;
    }
    int maximo = A[1].elemento;  // Guarda o valor máximo para uso ou exibição posterior
    printf("Extraindo máximo: %d com prioridade %d\n", maximo, A[1].prioridade);
    system("timeout -t 4 > NUL 2>&1");
    A[1] = A[num--];  // Move o último elemento para a raiz e decrementa o tamanho
    A[num+1].elemento = -1; // Coloca -1 no índice que ficou vazio
    cabecalho();
    printf("Elemento %d movido para a raiz. Iniciando correção do heap...\n", A[1].elemento);
    system("timeout -t 4 > NUL 2>&1");
    printf("[A[2K");
    corrige_heap(1);  // Ajusta o heap a partir da raiz
    cabecalho();
    printf("[A[2K");
    printf("Heap após correção ↑\n");
    system("timeout -t 3 > NUL 2>&1");
    cabecalho();  // Assumindo que essa função imprime o heap de forma formatada
    system("timeout -t 3 > NUL 2>&1");
}



void heapsort(){
    int n = num;
    heapnode temp;

    // Limpar a tela e preparar para o Heapsort
    system("cls");
    cabecalho();
    printf("[96mExecutando Heapsort...[0m\n");
    system("timeout -t 2 > NUL 2>&1");

    // Construir o heap máximo
    for (int i = n / 2; i >= 1; i--) {
        corrige_heap(i);
        // Atualizar a visualização do heap após cada correção
        system("cls");
        cabecalho();
        printf("[96mConstruindo heap:[0m\n");
        imprime_array(A);
        system("timeout -t 2 > NUL 2>&1");
    }

    // Extrair os elementos um por um do heap
    for (int i = n; i >= 2; i--) {
        // Trocar o elemento máximo com o último elemento não ordenado
        temp = A[1];
        A[1] = A[i];
        A[i] = temp;

        // Reduzir o tamanho do heap para a correção
        num--;
        corrige_heap(1);

        // Mostrar progresso após cada extração
        system("cls");
        cabecalho();
        printf("[96mElemento máximo extraído e inserido na posição correta:[0m\n");
        system("timeout -t 3 > NUL 2>&1");
        system("cls");
        cabecalho();
        printf(" [46m[97m %d/%d [0m",itens_ocupando(A),MAX-1);
        printf("\n\n");
        system("timeout -t 2 > NUL 2>&1");
        system("cls");
        cabecalho();
    }

    // Finalizar e mostrar o array ordenado
    system("cls");
    cabecalho();
    printf("[96mHeapsort concluído![0m\n");
    imprime_array(A);
    system("timeout -t 2 > NUL 2>&1");
    system("cls");
}





void menu(){
    printf("[46m[96m[4m«« ESCOLHA UMA OPÇÃO »»[0m\n");
    printf("[96m1:[0m Inserir\n");
    printf("[96m2:[0m Extrair Máximo\n");
    printf("[96m3:[0m Corrige Heap\n");
    printf("[96m4:[0m Heapsort\n");
    printf("[93m5:[0m Atribuir valores ao array\n");
    printf("--------------\n");
    printf("[96m6:[0m Mostrar Grafo\n");
    printf("[96m0:[0m Sair\n\n");

}

void atribuivalores(){
    printf("[96mDigite os valores a serem inseridos no array, separados por vírgula:[0m\n");
    char valores[100];
    scanf("%s", valores);

    char* token = strtok(valores, ",");
    int i = 1;
    while (token != NULL) {
        A[i].elemento = atoi(token);
        A[i].prioridade = i;
        token = strtok(NULL, ",");
        i++;
    }
    num = i - 1;

    // Preencher os índices restantes com -1
    for (int j = i; j < MAX; j++) {
        A[j].elemento = -1;
        A[j].prioridade = -1;
    }
}



int main() {
    
    int opcao;
    char arquivoGrafo[] = "00.graph_mermaid.html";
    num = itens_ocupando(A); 
    while(1){
        cabecalho();
        menu();


        while (1) {
            char digit = getch();
            if (digit >= '0' && digit <= '9') {
                opcao = digit - '0';
                break;
            }
        }

        system("cls");


        switch (opcao) {
        case 1:
            cabecalho();
            insere();
            break;
        case 2:
            cabecalho();
            extrai_maximo();
            break;
        case 3:
            cabecalho();
            printf("Digite o índice do elemento a ser corrigido: ");
            scanf("%d", &indiceCorrige);
            corrige_heap(indiceCorrige);
            system("pause");
            system("cls");
            break;
        case 4:
            cabecalho();
            heapsort();
            break;
        case 5:
            atribuivalores();
            system("cls");
            break;
        case 6:
            constroi_grafo(A, num, arquivoGrafo);
            mostra_grafo(arquivoGrafo);
            break;
        case 0:
            exit(0);

        default:
            break;
        
        }
    }

}

