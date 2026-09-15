//importa bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_AMOSTRAS 100

// protótipo das funções
int carregar_dados_iniciais(float velocidade[][2], float sensores_frotais[][3], float sensores_laterais[][2], int total_amostras);
int inserir_amostras(float velocidade[][2], float sensores_frotais[][3], float sensores_laterais[][2], int total_amostras);
void processar_relatorio(float velocidade[][2], float sensores_frontais[][3], float sensores_laterais[][2], 
    float processamento[][2], int status[][3], int total_amostras, float atrito, int sensibilidade);

void analise_risco_frontal(float velocidades[][2], float processamento[][2], int status[][3], int n) {
    int i;
    for (i = 0; i < n; i++) {
            float velocidade_relativa = velocidades[i][0] - velocidades[i][1];
            
            if (velocidade_relativa <= 0) {
                status[i][0] = 0;
            }
            else {
                float distancia_segura = processamento[i][1];
                float distancia_validada = processamento[i][0];

                if (distancia_validada >= distancia_segura) {
                    status[i][0] = 0;
                }
                else if (distancia_validada >= (distancia_segura / 2.0)) {
                    status[i][0] = 1;
                }
                else {
                    status [i][0] = 2;
                }
            }
    }
}

void assistente_faixa_dinamica(float velocidades[][2], float sensores_laterais[][2], int status[][3], int n) {
    int i;
    for (i = 0; i < n; i++) {
        float margem_dinamica = 0.50;
        float velocidade_atual = velocidades[i][0];
        
        if (velocidade_atual > 80.0) {
            margem_dinamica += 0.01 * (velocidade_atual - 80.0);
        }

        int k;
        for (k = 0; k < 2; k++) {
            float leitura = sensores_laterais[i][k];

            if (leitura < margem_dinamica) {
                status[i][k + 1] = 2;
            }
            else if (leitura < (margem_dinamica + 0.20)) {
                status[i][k + 1] = 1;
            }
            else {
                status[i][k + 1] = 0;
            }
        }
    }
}


int main(){
    //matrizes exigidas
    float velocidade[MAX_AMOSTRAS][2];
    float sensores_frontais[MAX_AMOSTRAS][3];
    float sensores_laterais[MAX_AMOSTRAS][2];
    float processamento[MAX_AMOSTRAS][2];
    int status[MAX_AMOSTRAS][3];

    //variáveis necessárias
    float atrito;
    int sensibilidade;
    int opcao;
    int total_amostras = 0;

    //leitura obrigatória do atrito e sensibilidade
    printf("Digite o coeficiente de atrito: \n");
    scanf("%f", &atrito);
    printf("Escolha a sensibilidade do ADAS: \n1 - Esportivo\n 2 - Normal\n 3 - Seguro\n");
    scanf("%d", &sensibilidade);
    //laço do menu interativo
    do {
        printf("---Menu Adas ---\n");
        printf("1 - Carregar dados iniciais\n");
        printf("2 - Inserir nova amostra\n");
        printf("3 - Processar e exibir relatório de riscos\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: \n");
        scanf("%d", &opcao);
    //opções do menu
        switch (opcao) {
        case 1:
            carregar_dados_iniciais(velocidade, sensores_frontais, sensores_laterais, total_amostras);
            break;
        case 2:
            inserir_amostras(velocidade, sensores_frontais, sensores_laterais, total_amostras);
            break;
        case 3:
            processar_relatorio(velocidade, sensores_frontais, sensores_laterais, processamento, status, total_amostras, atrito, sensibilidade);
            break;
        default:
        printf("Opção inválida\n");
            break;
        }
    } while (opcao != 4);
return 0;
}

int carregar_dados_iniciais(float velocidade[][2], float sensores_frontais[][3], float sensores_laterais[][2], int total_amostras){
    //preenche 50 registros semialeatórios
    for(int i = 0; i < 50 && i < MAX_AMOSTRAS; i++){
        //velocidade atual[0] e velocidade da frente[1], 0 a 140km/h
        velocidade[i][0] = 20 + (rand() % 121);
        velocidade[i][1] = 20 + (rand() % 121);
        //sensores frontais, radar, camera, distância em metros, 5 a 100m
        sensores_frontais[i][0] = 5 + (rand() % 96);
        sensores_frontais[i][1] = 5 + (rand() % 96);
        sensores_frontais[i][2] = 5 + (rand() % 96);
        //sensores laterais, esquerda e direita, 0.1 a 1.5m
        sensores_laterais[i][0] = 0.1 + ((rand() % 140)/100);
        sensores_laterais[i][1] = 0.1 + ((rand() %140)/100);
    }
    printf("Os dados foram iniciados, 50 registros adicionados\n");
    return 50; //total de amostras preenchidas
}
int inserir_amostras(float velocidade[][2], float sensores_frotais[][3], float sensores_laterais[][2], int total_amostras){
    if(total_amostras >= MAX_AMOSTRAS){
        printf("Erro, atingiu o limite máximo de amostras %d\n", MAX_AMOSTRAS);
        return total_amostras;
    }
    printf("\n Inserir nova amostra (indice %d)\n", total_amostras);

    printf("Digite a velocidade atual (km/h): ");
    scanf("%f", &velocidade[total_amostras][0]);

    printf("Digite a velocidade do veículo a frente (km/h): ");
    scanf("%f", &velocidade[total_amostras][1]);

    printf("Digite a leitura do Radar Frontal (m): ");
    scanf("%f", &sensores_frotais[total_amostras][0]);

    printf("Digite a leitura do  lidar frontal (m): ");
    scanf("%f", &sensores_frotais[total_amostras][1]);

    printf("Digite a leitura da camera frontal (m): ");
    scanf("%f", &sensores_frotais[total_amostras][2]);

    printf("Digite a distância da faixa esquerda (m): ");
    scanf("%f", &sensores_laterais[total_amostras][0]);

    printf("Digite a distância da faixa direita (m): ");
    scanf("%f", &sensores_laterais[total_amostras][1]);

    printf("Amostra inserida\n");
    // retorna nova amostra
    return total_amostras + 1;
}
