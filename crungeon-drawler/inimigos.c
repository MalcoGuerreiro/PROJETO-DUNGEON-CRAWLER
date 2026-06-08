#include "jogo.h"
#include "mapas.h"
#include "inimigos.h"

void inicializarInimigosDaFase() {
    if (faseAtual != FASE_ANDAR_2) {
        monstroXAtivo = 0;
    }

    if (faseAtual != FASE_ANDAR_3) {
        monstroYAtivo = 0;
        mattAtivo = 0;
    }
}

void moverInimigos() {
    if (faseAtual == FASE_ANDAR_2) {
        moverMonstroX();
    }

    if (jogadorMorreu == 1 || jogoRodando == 0) {
        return;
    }

    if (faseAtual == FASE_ANDAR_3) {
        moverMonstroY();

        if (jogadorMorreu == 1 || jogoRodando == 0) {
            return;
        }

        moverMatt();

        if (jogadorMorreu == 1 || jogoRodando == 0) {
            return;
        }

        if (((int)time(NULL)) - mattUltimoTiro >= COOLDOWN_TIRO_MATT) {
            ataqueDistanciaMatt();
            mattUltimoTiro = (int)time(NULL);
        }
    }
}

void moverMonstroX() {
    int direcao;
    int novaLinha;
    int novaColuna;

    if (monstroXAtivo == 0) {
        return;
    }

    direcao = rand() % 4;
    novaLinha = monstroXLinha;
    novaColuna = monstroXColuna;

    if (direcao == 0) {
        novaLinha = novaLinha - 1;
    } else if (direcao == 1) {
        novaLinha = novaLinha + 1;
    } else if (direcao == 2) {
        novaColuna = novaColuna - 1;
    } else if (direcao == 3) {
        novaColuna = novaColuna + 1;
    }

    tentarMoverInimigo(1, novaLinha, novaColuna);
}

void moverMonstroY() {
    int novaLinha;
    int novaColuna;
    int difLinha;
    int difColuna;

    if (monstroYAtivo == 0) {
        return;
    }

    novaLinha = monstroYLinha;
    novaColuna = monstroYColuna;
    difLinha = jogadorLinha - monstroYLinha;
    difColuna = jogadorColuna - monstroYColuna;

    if (difLinha < 0) {
        difLinha = difLinha * -1;
    }

    if (difColuna < 0) {
        difColuna = difColuna * -1;
    }

    if (difLinha >= difColuna) {
        if (jogadorLinha < monstroYLinha) {
            novaLinha = monstroYLinha - 1;
        } else if (jogadorLinha > monstroYLinha) {
            novaLinha = monstroYLinha + 1;
        }
    } else {
        if (jogadorColuna < monstroYColuna) {
            novaColuna = monstroYColuna - 1;
        } else if (jogadorColuna > monstroYColuna) {
            novaColuna = monstroYColuna + 1;
        }
    }

    tentarMoverInimigo(2, novaLinha, novaColuna);
}

void moverMatt() {
    int novaLinha;
    int novaColuna;
    int difLinha;
    int difColuna;

    if (mattAtivo == 0) {
        return;
    }

    novaLinha = mattLinha;
    novaColuna = mattColuna;
    difLinha = jogadorLinha - mattLinha;
    difColuna = jogadorColuna - mattColuna;

    if (difLinha < 0) {
        difLinha = difLinha * -1;
    }

    if (difColuna < 0) {
        difColuna = difColuna * -1;
    }

    if (difLinha >= difColuna) {
        if (jogadorLinha < mattLinha) {
            novaLinha = mattLinha - 1;
        } else if (jogadorLinha > mattLinha) {
            novaLinha = mattLinha + 1;
        }
    } else {
        if (jogadorColuna < mattColuna) {
            novaColuna = mattColuna - 1;
        } else if (jogadorColuna > mattColuna) {
            novaColuna = mattColuna + 1;
        }
    }

    tentarMoverInimigo(3, novaLinha, novaColuna);
}

void tentarMoverInimigo(int tipo, int novaLinha, int novaColuna) {
    int linhaAtual;
    int colunaAtual;
    char simbolo;

    if (tipo == 1) {
        linhaAtual = monstroXLinha;
        colunaAtual = monstroXColuna;
        simbolo = 'X';
    } else if (tipo == 2) {
        linhaAtual = monstroYLinha;
        colunaAtual = monstroYColuna;
        simbolo = 'Y';
    } else {
        linhaAtual = mattLinha;
        colunaAtual = mattColuna;
        simbolo = 'Z';
    }

    if (dentroDoMapa(novaLinha, novaColuna) == 0) {
        return;
    }

    if (novaLinha == jogadorLinha && novaColuna == jogadorColuna) {
        perderVida();
        return;
    }

    if (celulaEhLivreParaInimigo(novaLinha, novaColuna) == 0) {
        return;
    }

    mapaAtual[linhaAtual][colunaAtual] = ' ';
    mapaAtual[novaLinha][novaColuna] = simbolo;

    if (tipo == 1) {
        monstroXLinha = novaLinha;
        monstroXColuna = novaColuna;
    } else if (tipo == 2) {
        monstroYLinha = novaLinha;
        monstroYColuna = novaColuna;
    } else {
        mattLinha = novaLinha;
        mattColuna = novaColuna;
    }
}

void ataqueDistanciaMatt() {
    int linha;
    int coluna;
    int passo;
    int direcaoLinha;
    int direcaoColuna;
    int distancia;

    if (mattAtivo == 0) {
        return;
    }

    direcaoLinha = 0;
    direcaoColuna = 0;
    distancia = 0;

    if (jogadorLinha == mattLinha) {
        if (jogadorColuna < mattColuna) {
            direcaoColuna = -1;
            distancia = mattColuna - jogadorColuna;
        } else if (jogadorColuna > mattColuna) {
            direcaoColuna = 1;
            distancia = jogadorColuna - mattColuna;
        }
    } else if (jogadorColuna == mattColuna) {
        if (jogadorLinha < mattLinha) {
            direcaoLinha = -1;
            distancia = mattLinha - jogadorLinha;
        } else if (jogadorLinha > mattLinha) {
            direcaoLinha = 1;
            distancia = jogadorLinha - mattLinha;
        }
    }

    if (distancia == 0 || distancia > ALCANCE_TIRO_MATT) {
        return;
    }

    linha = mattLinha;
    coluna = mattColuna;

    for (passo = 1; passo <= distancia; passo++) {
        linha = linha + direcaoLinha;
        coluna = coluna + direcaoColuna;

        if (mapaAtual[linha][coluna] == '*') {
            return;
        }

        if (linha == jogadorLinha && coluna == jogadorColuna) {
            limparTela();
            printf("Matt acertou um ataque a distancia.\n");
            Sleep(600);
            perderVida();
            return;
        }
    }
}

void danoEmInimigo(int linha, int coluna) {
    if (mapaAtual[linha][coluna] == 'X') {
        monstroXAtivo = 0;
        mapaAtual[linha][coluna] = ' ';
        return;
    }

    if (mapaAtual[linha][coluna] == 'Y') {
        monstroYAtivo = 0;
        mapaAtual[linha][coluna] = ' ';
        return;
    }

    if (mapaAtual[linha][coluna] == 'Z') {
        mattVida = mattVida - 1;

        if (mattVida <= 0) {
            mattAtivo = 0;
            mapaAtual[linha][coluna] = ' ';
            mostrarVitoria();
            return;
        }
    }
}

int existeInimigoNaPosicao(int linha, int coluna) {
    if (monstroXAtivo == 1 && monstroXLinha == linha && monstroXColuna == coluna) {
        return 1;
    }

    if (monstroYAtivo == 1 && monstroYLinha == linha && monstroYColuna == coluna) {
        return 1;
    }

    return 0;
}

int existeMattNaPosicao(int linha, int coluna) {
    if (mattAtivo == 1 && mattLinha == linha && mattColuna == coluna) {
        return 1;
    }

    return 0;
}
