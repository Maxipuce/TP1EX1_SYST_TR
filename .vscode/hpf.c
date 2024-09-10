    // hpf.c
#include <stdio.h>
#include <stdlib.h>
#include "hpf.h"

// Fonction de comparaison pour trier les tâches en fonction de leur priorité
int compare(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return (taskA->priority - taskB->priority); // Priorité la plus basse en premier
}

// Fonction pour vérifier la faisabilité de l'ensemble des tâches
void check_feasibility(Task tasks[], int n) {
    int current_time = 0;
    int i;

    // Trier les tâches par ordre de priorité
    qsort(tasks, n, sizeof(Task), compare);

    printf("Ordre d'exécution des tâches selon la priorité (HPF):\n");
    for (i = 0; i < n; i++) {
        printf("Tâche %d (Durée: %d, Échéance: %d, Priorité: %d)\n",
               tasks[i].id, tasks[i].execution_time, tasks[i].deadline, tasks[i].priority);
    }

    // Exécution des tâches
    for (i = 0; i < n; i++) {
        current_time += tasks[i].execution_time;

        // Vérifier si la tâche est terminée avant son échéance
        if (current_time > tasks[i].deadline) {
            printf("L'ensemble des tâches n'est pas faisable. Tâche %d dépasse l'échéance.\n", tasks[i].id);
            return;
        }
    }

    printf("L'ensemble des tâches est faisable avec HPF.\n");
}
