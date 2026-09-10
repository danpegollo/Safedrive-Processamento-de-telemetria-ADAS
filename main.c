//importa bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// protótipo das funções
void carregar_dados_iniciais(float velocidade[][2], float sensores_frotais[][3], float sensores_laterais[][2], int total_amostras);
void inserir_amostras(float velocidade[][2], float sensores_frotais[][3], float sensores_laterais[][2], int total_amostras);
void processar_relatorio(float velocidade[][2], float sensores_frontais[][3], float sensores_laterais[][2], float processamento[][2], int status[][3], int total_amostras, float atrito, int sensibilidade);

int main(){
    //matrizes exigidas
    float velocidade[MAX_AMOSTRAS][2];
    float sensores_frotais[MAX_AMOSTRAS][3];
    float sensores_laterais[MAX_AMOSTRAS][2];
    float processamento[MAX_AMOSTRAS][2];
    int status[MAX_AMOSTRAS][3];

    
    float atrito;
    int sensibilidade;
    int opcao;
    int total_amostras = 0;

    //leitura obrigatória do atrito e sensibilidade
    pritnf("Digite o coeficiente de atrito: \n");
    scanf("%f", &atrito);

    printf("Escolha a sensibilidade do ADAS: \n1 - Esportivo\n 2 - Normal\n 3 - Seguro\n");

    do {
        printf("---Menu Adas ---\n");
        printf("1 - Carregar dados iniciais\n");
    }
    while()
}



