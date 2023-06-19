#include <stdio.h>
#include <stdlib.h>

// Definindo as configurações do sistema
#define NUM_CPUS 4
#define NUM_DISKS 4
#define MEMORY_SIZE 32 * 1024  // 32GB em MB
#define MAX_MEMORY_PER_PROCESS 512

// Enum para representar o estado do processo
typedef enum {
    READY,
    RUNNING,
    FINISHED
} ProcessState;

// Struct para representar um processo
typedef struct {
    int id;
    int priority;
    int cpu_time;
    int memory;
    int disk;
    int io_start;
    int io_duration;
    ProcessState state;
} Process;

// Filas de processos de usuário com diferentes prioridades
Process user_queue_0[1000];
int user_queue_0_size = 0;

Process user_queue_1[1000];
int user_queue_1_size = 0;

// Variável para representar a memória principal
int memory[MEMORY_SIZE];

// Função para simular a execução de um processo
void execute_process(Process *process) {
    printf("Executando processo %d com prioridade %d, %d segundos de CPU e %dMB de memória.\n", process->id, process->priority, process->cpu_time, process->memory);
    
    if(process->disk == 0){
        printf("sem necessidade de recursos de E/S\n");
    } else {
        printf("necessita de %d unidades de disco\n", process->disk);
    }

    if(process->io_start == 0){
        printf("sem I/O\n");
    } else {
        printf("necessita de %d segundos de I/O a partir do segundo %d\n", process->io_duration, process->io_start);
    }
}

// Função para liberar a memória alocada por um processo
void free_memory(Process *process) {
    int i;
    for (i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == process->id) {
            memory[i] = -1; // Liberando o espaço de memória
        }
    }
}

// Função para simular o escalonador de processos
void scheduler() {
    int i;

    // Execução de processos de tempo real
    for (i = 0; i < user_queue_0_size; i++) {
        Process *process = &user_queue_0[i];
        execute_process(process);
        process->state = FINISHED;
        free_memory(process);
        printf("Processo #%d: de READY para FINISHED\n", process->id);
    }

    // Execução de processos de usuário
    for (i = 0; i < user_queue_1_size; i++) {
        Process *process = &user_queue_1[i];
        execute_process(process);
        process->state = FINISHED;
        free_memory(process);
        printf("Processo #%d: de READY para FINISHED\n", process->id);
    }
}

// Função para submeter um novo processo
void submit_process(int id, int priority, int cpu_time, int memory_required, int disk, int io_start, int io_duration) {
    Process process;
    process.id = id;
    process.priority = priority;
    process.cpu_time = cpu_time;
    process.memory = memory_required;
    process.disk = disk;
    process.io_start = io_start;
    process.io_duration = io_duration;
    process.state = READY;

    if (priority == 0) {
        user_queue_0[user_queue_0_size++] = process;
        printf("Processo #%d criado e adicionado à fila de prioridade 0 (READY)\n", process.id);
    } else if (priority == 1) {
        user_queue_1[user_queue_1_size++] = process;
        printf("Processo #%d criado e adicionado à fila de prioridade 1 (READY)\n", process.id);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Erro: Caminho do arquivo de entrada não fornecido.\n");
        return 1;
    }

    // Abrindo o arquivo de entrada
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    // Lendo os processos do arquivo de entrada
    int id, priority, cpu_time, memory, disk, io_start, io_duration;
    while (fscanf(input_file, "%d, %d, %d, %d, %d, %d, %d\n", &id, &priority, &cpu_time, &memory, &disk, &io_start, &io_duration) != EOF) {
        submit_process(id, priority, cpu_time, memory, disk, io_start, io_duration);
    }

    // Fechando o arquivo de entrada
    fclose(input_file);

    // Executando o escalonador
    scheduler();

    return 0;
}
