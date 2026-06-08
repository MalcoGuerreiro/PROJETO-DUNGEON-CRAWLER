# Crungeon Drawler

## Sobre o jogo

**Crungeon Drawler** e um jogo dungeon crawler feito em C puro para console, usando mapas ASCII.

O jogador explora a Vila do Mouse Mal Clicado, entra em uma masmorra com tres andares, escolhe uma arma e enfrenta Matt, o boss final.

## Historia

Na pacata Vila do Mouse Mal Clicado, tudo estava normal ate que uma masmorra apareceu do nada no meio da praca.

Ninguem sabe exatamente de onde ela veio. Alguns dizem que foi causada por um erro de compilacao. Outros dizem que alguem apertou Alt + F4 no lugar errado.

Desde o surgimento da masmorra, caixas apareceram bloqueando caminhos, portas trancaram sozinhas, espinhos brotaram do chao e monstros em formato de letras comecaram a andar sem motivo aparente.

No fundo da masmorra vive Matt, o lendario campeao de boxe dos Miis. Ele transformou a dungeon em sua academia pessoal.

O jogador precisa atravessar os tres andares, coletar chaves, abrir portas, destruir caixas, sobreviver aos monstros e derrotar Matt antes que todos os moradores virem Miis musculosos com luvas de boxe.

## Como jogar

Execute o projeto no Falcon C++ usando os arquivos `.c` e `.h`.

No menu principal:

```txt
1 - Jogar
2 - Tutorial
3 - Sair
```

Durante o jogo:

```txt
w - move para cima
a - move para esquerda
s - move para baixo
d - move para direita
i - interage com o objeto a frente
o - ataca
```

O jogo usa `getch()`, entao nao e necessario apertar Enter.

## Objetivo

Escolha uma arma na vila, entre na masmorra, passe pelos tres andares e derrote Matt no andar final.

## Armas

```txt
1 - Master Sword
2 - Desert Eagle
3 - Atiesh, Grande Cajado do Guardiao
```

A Master Sword ataca uma area 3x2 na frente do jogador.

A Desert Eagle ataca 4 celulas em linha reta.

Atiesh ataca as 8 celulas ao redor do jogador.

## Simbolos

```txt
< - jogador olhando para esquerda
^ - jogador olhando para cima
> - jogador olhando para direita
v - jogador olhando para baixo
* - parede
# - espinho
k - caixa
O - botao
D - porta fechada
@ - chave
= - porta aberta
L - escada
N - NPC da vila
X - monstro tipo 1
Y - monstro tipo 2
Z - boss final Matt
```

## Desenvolvedores

Malco Guerreiro, Salim Fraiha e Rodrigo Martins.

## Uso de IA generativa

Foi utilizada IA generativa como ferramenta de apoio para planejamento, organizacao da SPEC, desenvolvimento do codigo e criacao da documentacao de estudo.



## Boss Matt

Matt e representado por `Z`. Ele tem 5 vidas, persegue o jogador de forma simples e usa apenas um ataque a distancia como habilidade especial. O tiro tem cooldown de 4 segundos, so acerta se o jogador estiver na mesma linha ou na mesma coluna do Matt, com caminho livre e ate 6 celulas de distancia. Paredes bloqueiam o tiro. Se Matt errar, nenhuma mensagem aparece.
