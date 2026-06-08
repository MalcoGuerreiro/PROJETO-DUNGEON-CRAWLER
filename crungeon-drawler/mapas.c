#include "jogo.h"
#include "mapas.h"
#include "inimigos.h"

char mapaVila[VILA_LINHAS][VILA_COLUNAS + 1] = {
    "**********",
    "*        *",
    "*  N     *",
    "*        *",
    "*        *",
    "*    L   *",
    "*        *",
    "*        *",
    "*  ^     *",
    "**********"
};

char mapaAndar1[ANDAR1_LINHAS][ANDAR1_COLUNAS + 1] = {
    "**********",
    "*^ @*   L*",
    "*   *    *",
    "* k *    *",
    "*   *    *",
    "*   D    *",
    "*   *    *",
    "*   *    *",
    "*   *    *",
    "**********"
};

char mapaAndar2[ANDAR2_LINHAS][ANDAR2_COLUNAS + 1] = {
    "***************",
    "*^ @    *    L*",
    "*  ***  * *****",
    "*  k    D     *",
    "*       *  #  *",
    "***** *****   *",
    "*   *     *   *",
    "* O *  X  *   *",
    "*   ***** *   *",
    "*       * *   *",
    "*  @    D *   *",
    "*       *     *",
    "***** ****** **",
    "*             *",
    "***************"
};

char mapaAndar3[ANDAR3_LINHAS][ANDAR3_COLUNAS + 1] = {
    "*************************",
    "*^  @      *     Y      *",
    "*  *****   *   *****    *",
    "*      *   D       *    *",
    "*** ** ***** ***** * ****",
    "*    *       *   *      *",
    "* k  ***** *** * ****** *",
    "*        *     *        *",
    "***** ** ************ ***",
    "*@     *       *        *",
    "* **** * ***** * ****** *",
    "*    * *     * D      * *",
    "***  * ***** * ****** * *",
    "*    *       *        * *",
    "* ****** ********** **  *",
    "*      *    @       *   *",
    "* **** ***** ******** ***",
    "*    *     *           **",
    "**** D *** **********  **",
    "*      *        #      **",
    "* #### * ************* **",
    "*      *               **",
    "*   k      *******   Z **",
    "*          *           **",
    "*************************"
};
void carregarFase(int fase) {
    faseAtual = fase;
    chaves = 0;
    jogadorMorreu = 0;
    faseMudou = 1;

    if (fase == FASE_VILA) {
        copiarMapaVila();
        linhasMapaAtual = VILA_LINHAS;
        colunasMapaAtual = VILA_COLUNAS;
    } else if (fase == FASE_ANDAR_1) {
        copiarMapaAndar1();
        linhasMapaAtual = ANDAR1_LINHAS;
        colunasMapaAtual = ANDAR1_COLUNAS;
    } else if (fase == FASE_ANDAR_2) {
        copiarMapaAndar2();
        linhasMapaAtual = ANDAR2_LINHAS;
        colunasMapaAtual = ANDAR2_COLUNAS;
    } else if (fase == FASE_ANDAR_3) {
        copiarMapaAndar3();
        linhasMapaAtual = ANDAR3_LINHAS;
        colunasMapaAtual = ANDAR3_COLUNAS;
    }

    encontrarElementos();
    inicializarInimigosDaFase();
}

void copiarMapaVila() {
    int i;
    int j;

    for (i = 0; i < VILA_LINHAS; i++) {
        for (j = 0; j < VILA_COLUNAS + 1; j++) {
            mapaAtual[i][j] = mapaVila[i][j];
        }
    }
}

void copiarMapaAndar1() {
    int i;
    int j;

    for (i = 0; i < ANDAR1_LINHAS; i++) {
        for (j = 0; j < ANDAR1_COLUNAS + 1; j++) {
            mapaAtual[i][j] = mapaAndar1[i][j];
        }
    }
}

void copiarMapaAndar2() {
    int i;
    int j;

    for (i = 0; i < ANDAR2_LINHAS; i++) {
        for (j = 0; j < ANDAR2_COLUNAS + 1; j++) {
            mapaAtual[i][j] = mapaAndar2[i][j];
        }
    }
}

void copiarMapaAndar3() {
    int i;
    int j;

    for (i = 0; i < ANDAR3_LINHAS; i++) {
        for (j = 0; j < ANDAR3_COLUNAS + 1; j++) {
            mapaAtual[i][j] = mapaAndar3[i][j];
        }
    }
}

void encontrarElementos() {
    int i;
    int j;

    for (i = 0; i < linhasMapaAtual; i++) {
        for (j = 0; j < colunasMapaAtual; j++) {
            if (mapaAtual[i][j] == '^' || mapaAtual[i][j] == 'v' || mapaAtual[i][j] == '<' || mapaAtual[i][j] == '>') {
                jogadorLinha = i;
                jogadorColuna = j;
                direcaoJogador = mapaAtual[i][j];
            }

            if (mapaAtual[i][j] == 'X') {
                monstroXLinha = i;
                monstroXColuna = j;
                monstroXAtivo = 1;
            }

            if (mapaAtual[i][j] == 'Y') {
                monstroYLinha = i;
                monstroYColuna = j;
                monstroYAtivo = 1;
            }

            if (mapaAtual[i][j] == 'Z') {
                mattLinha = i;
                mattColuna = j;
                mattAtivo = 1;
                mattVida = VIDA_MATT;
                mattUltimoTiro = (int)time(NULL);
            }
        }
    }
}

void mostrarMapa() {
    int i;
    int j;

    limparTela();

    printf("Crungeon Drawler\n");
    printf("Vidas: %d | Chaves: %d | ", vidas, chaves);

    if (armaEscolhida == ARMA_NENHUMA) {
        printf("Arma: Nenhuma\n");
    } else if (armaEscolhida == ARMA_MASTER_SWORD) {
        printf("Arma: Master Sword\n");
    } else if (armaEscolhida == ARMA_DESERT_EAGLE) {
        printf("Arma: Desert Eagle\n");
    } else if (armaEscolhida == ARMA_ATIESH) {
        printf("Arma: Atiesh\n");
    }

    if (faseAtual == FASE_VILA) {
        printf("Local: Vila do Mouse Mal Clicado\n\n");
    } else if (faseAtual == FASE_ANDAR_1) {
        printf("Local: Andar 1\n\n");
    } else if (faseAtual == FASE_ANDAR_2) {
        printf("Local: Andar 2\n\n");
    } else if (faseAtual == FASE_ANDAR_3) {
        int tempoAtual;
        int falta;

        tempoAtual = (int)time(NULL);
        falta = COOLDOWN_TIRO_MATT - (tempoAtual - mattUltimoTiro);

        if (falta <= 0) {
            printf("Local: Andar 3 | Vida Matt: %d | Tiro Matt: pronto\n", mattVida);
        } else {
            printf("Local: Andar 3 | Vida Matt: %d | Tiro Matt: %ds\n", mattVida, falta);
        }

        printf("Dica: nao fique na mesma linha ou coluna do Matt quando o tiro estiver pronto.\n\n");
    }

    for (i = 0; i < linhasMapaAtual; i++) {
        for (j = 0; j < colunasMapaAtual; j++) {
            printf("%c", mapaAtual[i][j]);
        }
        printf("\n");
    }

    printf("\nComandos: w a s d | i interagir | o atacar\n");
}

void removerBarreiraDoBotao() {
    int i;

    if (faseAtual == FASE_ANDAR_2) {
        for (i = 8; i <= 12; i++) {
            if (mapaAtual[i][10] == '*') {
                mapaAtual[i][10] = ' ';
            }
        }
    }
}

int dentroDoMapa(int linha, int coluna) {
    if (linha < 0) {
        return 0;
    }

    if (coluna < 0) {
        return 0;
    }

    if (linha >= linhasMapaAtual) {
        return 0;
    }

    if (coluna >= colunasMapaAtual) {
        return 0;
    }

    return 1;
}

int celulaBloqueiaMovimento(char celula) {
    if (celula == '*') {
        return 1;
    }

    if (celula == 'k') {
        return 1;
    }

    if (celula == 'D') {
        return 1;
    }

    if (celula == 'N') {
        return 1;
    }

    if (celula == '@') {
        return 1;
    }

    if (celula == 'O') {
        return 1;
    }

    if (celula == 'L') {
        return 1;
    }

    return 0;
}

int celulaEhLivreParaInimigo(int linha, int coluna) {
    char celula;

    if (dentroDoMapa(linha, coluna) == 0) {
        return 0;
    }

    celula = mapaAtual[linha][coluna];

    if (celula == ' ') {
        return 1;
    }

    if (celula == '^' || celula == 'v' || celula == '<' || celula == '>') {
        return 1;
    }

    return 0;
}
