João Henrique Batista da Costa 202500560669

# 🎯 Bocha Geométrica T1ED

> **Trabalho I de Estrutura de Dados I - UEL**

#### Um simulador de "Bocha Geométrica" desenvolvido em C99, modularizado com Tipos Abstratos de Dados (TADs). O programa lê arquivos de definição de mundo (`.geo`) e arquivos de comandos de jogo (`.qry`), processa interações físicas como disparos e colisões, e gera visualizações em SVG.

---

## 🚀 Como Executar

### 1. Compilar o Projeto
Abra o terminal no diretório `src` e execute:
```bash
make ted
```
para executar o programa, e em seguida execute este comando:
```bash
./ted [-e <dir_entrada>] -f <arquivo.geo> [-q <arquivo.qry>] -o <dir_saida> [sufixo]
```

| Parâmetro | Tipo | Descrição |
| :--- | :--- | :--- |
| `-e <dir>` | Opcional | Diretório-base para os arquivos de entrada (BED). |
| `-f <arq.geo>` | **Obrigatório** | Arquivo de descrição geométrica inicial. |
| `-q <arq.qry>` | Opcional | Arquivo com os comandos do jogo. |
| `-o <dir>` | **Obrigatório** | Diretório-base para os arquivos de saída (BSD). |
| `[sufixo]` | Opcional | Nome extra adicionado ao primeiro arquivo SVG gerado. |

## 📁 Exemplos de Uso

### Exemplo Básico (Apenas .geo)

Gera o SVG inicial do chão.
```bash
./ted -e testes -f mundo.geo -o saida
```

### 1. Exemplo Completo (Jogo com .qry)

Executa uma partida completa, processa colisões e gera relatórios.
```bash
./ted -e testes -f mundo.geo -q partida1.qry -o saida
```

### 2. Exemplo com Sufixo Personalizado

Adiciona "versao_v1" ao nome do arquivo SVG do mundo.
```bash
./ted -e testes -f mundo.geo -q partida1.qry -o saida versao_v1
```


## ⚔️ Regras do Jogo (calc)

As formas na arena interagem par-a-par (I vs J) com as seguintes regras:

  * Sem Colisão: Ambas as formas voltam para o jogo.

  * Colisão e Área(I) < Área(J): 💥 Esmagamento! A forma I é destruída e sua área conta como pontos.

  * Colisão e Área(I) ≥ Área(J): 🧬 Clonagem! A forma I muda a cor de J, cria um clone com cores invertidas, e todas voltam para o jogo.


## 🗂️ Estrutura do Projeto

```text
Trabalho-1/
└── src/
    ├── Makefile
    ├── main.c
    ├── argumentos.c/.h        # Processamento de linha de comando
    ├── leitor.c/.h            # Leitura genérica de arquivos
    ├── leitor_geo.c/.h        # Processamento do mundo (.geo)
    ├── leitor_qry.c/.h        # Processamento do jogo (.qry)
    ├── cor_complementar.c/.h  # Utilitários de cor
    ├── disparador.c/.h        # TAD Disparador
    ├── carregador.c/.h        # TAD Carregador
    ├── (Formas).c/.h          # circulo, retangulo, linha, texto
    └── (Estruturas).c/.h      # pilha, fila, lista
```
## 🧹 Limpeza
execute o seguinte comando para limpar os arquivos gerados pela compilação:
```bash
  make clean
```


## 📋 Requisitos

  * Compilador GCC com suporte a C99 (-std=c99).

  * GNU Make para build.

  * Ambiente Linux/Unix.

  * Bibliotecas padrão C (math.h, string.h, etc.).
