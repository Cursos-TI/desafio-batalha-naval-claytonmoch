#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs() (valor absoluto)

// --- Constantes Globais ---
// Define o tamanho do tabuleiro principal do jogo
#define TAMANHO_TABULEIRO 10
// Define o tamanho das matrizes de habilidade (use um número ímpar para ter um centro claro)
#define TAMANHO_HABILIDADE 7

// --- Protótipos das Funções ---

// Funções para manipulação do tabuleiro
void inicializarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]);
void exibirTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]);
void copiarTabuleiro(int origem[][TAMANHO_TABULEIRO], int destino[][TAMANHO_TABULEIRO]);

// Funções para criar as matrizes de habilidade
void criarHabilidadeCone(int habilidade[][TAMANHO_HABILIDADE]);
void criarHabilidadeCruz(int habilidade[][TAMANHO_HABILIDADE]);
void criarHabilidadeOctaedro(int habilidade[][TAMANHO_HABILIDADE]);

// Função para sobrepor a habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[][TAMANHO_TABULEIRO], int habilidade[][TAMANHO_HABILIDADE], int origemLinha, int origemColuna);


// --- Função Principal ---
int main() {
    // Declaração das matrizes
    int tabuleiro_base[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int tabuleiro_efeito[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // 1. Prepara o ambiente do jogo
    inicializarTabuleiro(tabuleiro_base);
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);

    printf("--- Tabuleiro Inicial com Navios ---\n");
    exibirTabuleiro(tabuleiro_base);
    printf("\n");

    // 2. Demonstração da Habilidade CONE
    printf("--- Aplicando Habilidade: CONE na posição (2, 4) ---\n");
    copiarTabuleiro(tabuleiro_base, tabuleiro_efeito); // Reseta o tabuleiro para a demonstração
    aplicarHabilidade(tabuleiro_efeito, habilidadeCone, 2, 4);
    exibirTabuleiro(tabuleiro_efeito);
    printf("\n");

    // 3. Demonstração da Habilidade CRUZ
    printf("--- Aplicando Habilidade: CRUZ na posição (6, 6) ---\n");
    copiarTabuleiro(tabuleiro_base, tabuleiro_efeito);
    aplicarHabilidade(tabuleiro_efeito, habilidadeCruz, 6, 6);
    exibirTabuleiro(tabuleiro_efeito);
    printf("\n");

    // 4. Demonstração da Habilidade OCTAEDRO
    printf("--- Aplicando Habilidade: OCTAEDRO na posição (5, 2) ---\n");
    copiarTabuleiro(tabuleiro_base, tabuleiro_efeito);
    aplicarHabilidade(tabuleiro_efeito, habilidadeOctaedro, 5, 2);
    exibirTabuleiro(tabuleiro_efeito);
    printf("\n");

    return 0;
}

// --- Implementação das Funções ---

/**
 * @brief Preenche o tabuleiro com água (0) e posiciona alguns navios (3).
 */
void inicializarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    for (int l = 0; l < TAMANHO_TABULEIRO; l++) {
        for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
            tabuleiro[l][c] = 0; // 0 = Água
        }
    }
    // Adiciona alguns navios (valor 3)
    tabuleiro[1][1] = 3;
    tabuleiro[2][4] = 3;
    tabuleiro[3][4] = 3;
    tabuleiro[6][5] = 3;
    tabuleiro[6][6] = 3;
    tabuleiro[6][7] = 3;
    tabuleiro[5][1] = 3;
}

/**
 * @brief Exibe o tabuleiro no console com caracteres específicos para cada valor.
 */
void exibirTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    for (int l = 0; l < TAMANHO_TABULEIRO; l++) {
        for (int c = 0; c < TAMANHO_TABULEIRO; c++) {
            char simbolo;
            switch (tabuleiro[l][c]) {
                case 0:  simbolo = '~'; break; // Água
                case 3:  simbolo = 'N'; break; // Navio
                case 5:  simbolo = '*'; break; // Área de Efeito da Habilidade
                default: simbolo = '?'; break;
            }
            printf("%c ", simbolo);
        }
        printf("\n");
    }
}

/**
 * @brief Copia o conteúdo de uma matriz para outra. Útil para resetar o tabuleiro.
 */
void copiarTabuleiro(int origem[][TAMANHO_TABULEIRO], int destino[][TAMANHO_TABULEIRO]) {
    for(int l = 0; l < TAMANHO_TABULEIRO; l++) {
        for(int c = 0; c < TAMANHO_TABULEIRO; c++) {
            destino[l][c] = origem[l][c];
        }
    }
}


/**
 * @brief Gera dinamicamente a matriz de efeito da habilidade Cone.
 * A lógica cria um triângulo que se expande para baixo a partir do centro da linha superior.
 */
void criarHabilidadeCone(int habilidade[][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int l = 0; l < TAMANHO_HABILIDADE; l++) {
        for (int c = 0; c < TAMANHO_HABILIDADE; c++) {
            // CONDIÇÃO: A posição da coluna 'c' deve estar dentro da "abertura" do cone
            // na linha 'l'. A abertura aumenta conforme 'l' aumenta.
            // Ex: na linha 0, a abertura é 1. Na linha 1, é 3. Na linha 2, é 5.
            if (c >= centro - l && c <= centro + l) {
                habilidade[l][c] = 1; // 1 = Área afetada
            } else {
                habilidade[l][c] = 0; // 0 = Área não afetada
            }
        }
    }
}

/**
 * @brief Gera dinamicamente a matriz de efeito da habilidade Cruz.
 * A lógica marca como afetada qualquer célula que esteja na linha central OU na coluna central.
 */
void criarHabilidadeCruz(int habilidade[][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int l = 0; l < TAMANHO_HABILIDADE; l++) {
        for (int c = 0; c < TAMANHO_HABILIDADE; c++) {
            // CONDIÇÃO: A posição está na linha central (l == centro) OU na coluna central (c == centro).
            if (l == centro || c == centro) {
                habilidade[l][c] = 1;
            } else {
                habilidade[l][c] = 0;
            }
        }
    }
}

/**
 * @brief Gera dinamicamente a matriz de efeito da habilidade Octaedro (losango).
 * A lógica usa a "Distância de Manhattan" do centro.
 */
void criarHabilidadeOctaedro(int habilidade[][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int l = 0; l < TAMANHO_HABILIDADE; l++) {
        for (int c = 0; c < TAMANHO_HABILIDADE; c++) {
            // CONDIÇÃO: A soma das distâncias vertical e horizontal do centro
            // (Distância de Manhattan) deve ser menor ou igual ao "raio" do losango (o centro).
            if (abs(l - centro) + abs(c - centro) <= centro) {
                habilidade[l][c] = 1;
            } else {
                habilidade[l][c] = 0;
            }
        }
    }
}

/**
 * @brief Sobrepõe a matriz de habilidade no tabuleiro principal.
 * @param tabuleiro A matriz do jogo a ser modificada.
 * @param habilidade A matriz de efeito (0s e 1s) a ser aplicada.
 * @param origemLinha A linha do tabuleiro onde o centro da habilidade será posicionado.
 * @param origemColuna A coluna do tabuleiro onde o centro da habilidade será posicionado.
 */
void aplicarHabilidade(int tabuleiro[][TAMANHO_TABULEIRO], int habilidade[][TAMANHO_HABILIDADE], int origemLinha, int origemColuna) {
    int centroHabilidade = TAMANHO_HABILIDADE / 2;

    // Itera sobre cada célula da matriz de HABILIDADE
    for (int l_hab = 0; l_hab < TAMANHO_HABILIDADE; l_hab++) {
        for (int c_hab = 0; c_hab < TAMANHO_HABILIDADE; c_hab++) {
            
            // Verifica se a célula atual da habilidade é uma área de efeito (valor 1)
            if (habilidade[l_hab][c_hab] == 1) {
                
                // Calcula a coordenada correspondente no TABULEIRO principal.
                // O cálculo parte do ponto de origem e aplica o deslocamento
                // da célula atual em relação ao centro da habilidade.
                int linhaAlvo = origemLinha + (l_hab - centroHabilidade);
                int colunaAlvo = origemColuna + (c_hab - centroHabilidade);

                // VALIDAÇÃO DE LIMITES: Garante que a área de efeito não "vaze" para fora do tabuleiro.
                if (linhaAlvo >= 0 && linhaAlvo < TAMANHO_TABULEIRO &&
                    colunaAlvo >= 0 && colunaAlvo < TAMANHO_TABULEIRO) {
                    
                    // Marca a posição no tabuleiro com o valor de efeito (5).
                    tabuleiro[linhaAlvo][colunaAlvo] = 5;
                }
            }
        }
    }
}