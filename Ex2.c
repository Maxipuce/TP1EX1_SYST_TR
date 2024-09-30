#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char task_id[10];
    int execution_time;
    int deadline;
} Task;

// Fonction de comparaison pour qsort (ordre croissant des deadlines)
int compare(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskA->deadline - taskB->deadline;
}

// Affichage des informations sur une tâche
void print_task(Task task) {
    printf("Tâche %s | Temps d'exécution: %ds | Échéance: %ds\n", task.task_id, task.execution_time, task.deadline);
}

// Fonction pour exécuter les tâches selon EDF
void run_edf_scheduler(Task tasks[], int num_tasks) {
    int current_time = 0;
    
    // Tri des tâches selon l'échéance la plus proche (algorithme EDF)
    qsort(tasks, num_tasks, sizeof(Task), compare);

    // Exécution des tâches
    for (int i = 0; i < num_tasks; i++) {
        Task task = tasks[i];

        printf("Exécution de la tâche %s à l'instant %d (échéance à %d)\n", task.task_id, current_time, task.deadline);
        
        // Simuler l'exécution de la tâche (en pause avec sleep)
        sleep(task.execution_time);  // Temps d'exécution simulé
        current_time += task.execution_time;

        printf("Tâche %s terminée à l'instant %d\n", task.task_id, current_time);
        printf("-----------------------------------------\n");
    }
}

int main() {

    int n;
    // Création de quelques tâches (id, temps d'exécution, échéance)
    /*Task tasks[] = {
        {"T1", 2, 5},
        {"T2", 1, 3},
        {"T3", 4, 7}
    };*/

    Task tasks[] = {

    };

    //Choix de l'input pour l'utilisateur
    printf("Entre le nombre de tâches de ton problème : ");
    scanf("%d", &n);
    
    for (int i=0; i<n; i++){
        int C, D;
        char taskName[10];

        printf("\nEntre la durée d'exécution C de la tâche %d : ", i + 1);
        scanf("%d", &C);
        

        printf("Entre l'échéance D de la tâche %d : ", i + 1);
        scanf("%d", &D);

        strcpy(tasks[i].task_id, taskName);
        tasks[i].execution_time = C;
        tasks[i].deadline = D;
    }
    
    printf("\nListe des tâches :\n");
    for (int i = 0; i < n; i++) {
        printf("Tâche %d : Durée = %d, Échéance = %d\n", i+1 , tasks[i].execution_time, tasks[i].deadline);
    }
    
    int num_tasks = sizeof(tasks) / sizeof(tasks[0]);

    // Affichage des tâches avant exécution
    printf("Tâches avant l'exécution:\n");
    for (int i = 0; i < num_tasks; i++) {
        print_task(tasks[i]);
    }
    printf("=========================================\n");

    // Exécution de l'ordonnanceur EDF
    run_edf_scheduler(tasks, num_tasks);
    
    return 0;
}
