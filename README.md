
# Escalonador de processos


Escalonador de Processos escrito em C




## Stack utilizada

**Linguagem de programacao:** C

**Compilador:** GCC 11.3.0

**SO:** PopOs 6.0.12

## Compilacao

Para compilar o escalonador rode o comando:

```bash
  gcc src/main/escalonador.c -o escalonador
```



Para compilar o escalonador rode o comando:

```bash
  ./escalonador ARQUIVO_DE_INPUT
```

substitua o ARQUIVO_DE_INPUT pelo caminho do arquivo contendo os processos. Na pasta src/inputs contem alguns arquivos txt que foram usados para teste, estes sao:

src/inputs/default.txt - Este contem os processos de entrada que foram propostos como exemplo no trabalho

src/inputs/empty.txt - Este contem um arquivo vazio, onde a resposta esperada para o escalonador é que ele nao crie nenhum processo

src/inputs/realTimeProcess.txt - Este contem um processo de prioridade 0(tempo real)

src/inputs/ioProcess.txt - Este contem que irao necessitar de unidades de tempo de I/O

src/inputs/large.txt - Este contem cerca de 30 processos aleatorios