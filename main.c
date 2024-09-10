#include <stdio.h>
#include <stdlib.h>
#include "hpf.h"

int main() {
    int n, i;
    printf("Entrez le nombre de tâches : ");
    scanf("%d", &n);

    Task *tasks = malloc(n * sizeof(Task));

    for (i = 0; i < n; i++) {
        printf("Entrez les détails de la tâche %d (Durée d'exécution, Échéance, Période, Priorité) :\n", i + 1);
        tasks[i].id = i + 1;
        scanf("%d %d %d %d", &tasks[i].execution_time, &tasks[i].deadline, &tasks[i].period, &tasks[i].priority);
    }

    // Vérifier la faisabilité
    check_feasibility(tasks, n);

    free(tasks); // Libérer la mémoire allouée
    return 0;
}
