#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Structure Task
typedef struct {
    char task_id[10];
    int execution_time;   // Temps total d'exécution de la tâche
    int remaining_time;   // Temps restant pour terminer la tâche (pour gérer les interruptions)
    int deadline;         // Échéance absolue (initialement égale à la première période)
    int period;           // Période de répétition
    int original_deadline; // Échéance initiale pour recalculer l'échéance absolue
    int execution_count;  // Nombre de fois que la tâche a été exécutée
} Task;

// Fonction de comparaison pour qsort (ordre croissant des échéances absolues)
int compare(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskA->deadline - taskB->deadline;
}

// Affichage des informations sur une tâche
void print_task(Task task) {
    printf("Tâche %s | Temps d'exécution: %ds | Temps restant: %ds | Échéance: %ds | Période: %ds | Exécutions: %d\n", 
           task.task_id, task.execution_time, task.remaining_time, task.deadline, task.period, task.execution_count);
}

// Vérification si toutes les tâches ont été exécutées deux fois
int all_tasks_executed_twice(Task tasks[], int num_tasks) {
    for (int i = 0; i < num_tasks; i++) {
        if (tasks[i].execution_count < 2) {
            return 0; // Si une tâche n'a pas été exécutée deux fois, retourner 0
        }
    }
    return 1; // Toutes les tâches ont été exécutées deux fois
}

void run_edf_scheduler(Task tasks[], int num_tasks, int hyperperiod) {
    int current_time = 0;

    while (current_time < hyperperiod) {

        if (all_tasks_executed_twice(tasks, num_tasks)) {
            printf("Toutes les tâches ont été exécutées deux fois sans problème. Arrêt de l'ordonnanceur.\n");
            break;
        }

        // Tri des tâches selon l'échéance absolue la plus proche (algorithme EDF)
        qsort(tasks, num_tasks, sizeof(Task), compare);

        int task_executed = 0;  // Indicateur pour savoir si une tâche a été exécutée à cet instant

        // Chercher la prochaine tâche à exécuter
        for (int i = 0; i < num_tasks; i++) {
            Task *task = &tasks[i];

            // Si le temps restant est positif, la tâche est prête à être exécutée
            if (task->remaining_time > 0 && current_time + 1 <= task->deadline) {
                // Exécution de la tâche pour une unité de temps
                printf("Exécution de la tâche %s à l'instant %d (échéance à %d)\n", 
                       task->task_id, current_time, task->deadline);
                
                // Simuler une unité de temps d'exécution
                sleep(1);
                task->remaining_time -= 1;
                current_time += 1;

                printf("Tâche %s a exécuté 1 unité de temps. Temps restant : %d\n", 
                       task->task_id, task->remaining_time);
                printf("=========================================\n");
                task_executed = 1;
                break;  // Préempter après chaque unité de temps pour permettre la réévaluation
            }
        }

        if (!task_executed) {
            // Si aucune tâche n'a été exécutée, avancer dans le temps (idle state)
            printf("Aucune tâche prête à l'instant %d. CPU en attente.\n", current_time);
            current_time++;
        }

        // Mettre à jour les tâches pour la prochaine période
        for (int i = 0; i < num_tasks; i++) {
            Task *task = &tasks[i];
            if (current_time >= task->deadline) {
                // Vérifier si la tâche est incomplète avant la deadline
                if (task->remaining_time > 0) {
                    printf("Erreur : La tâche %s n'a pas pu être terminée avant son échéance (%ds).\n", 
                           task->task_id, task->deadline);
                } else {
                    // Incrémenter le compteur d'exécutions si la tâche est terminée
                    task->execution_count += 1;
                }
                
                // Réinitialiser pour la prochaine période
                task->deadline += task->period;
                task->remaining_time = task->execution_time;
                printf("Tâche %s se répète, nouvelle échéance : %d\n", task->task_id, task->deadline);
            }
        }
    }

    printf("L'ordonnanceur EDF a terminé son exécution.\n");
}

int get_positive_int(const char *prompt) {
    int value;
    int result;

    do {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result != 1) {
            printf("Erreur : veuillez entrer un nombre entier valide.\n");
            while (getchar() != '\n'); // Vider le buffer de l'entrée
        }
        // Vérifier si l'entrée est un entier positif
        else if (value < 0) {
            printf("Erreur : la valeur ne peut pas être négative.\n");
        }
    } while (result != 1 || value < 0);

    return value;
}


int calculate_hyperperiod(Task tasks[], int num_tasks) {
    int hyperperiod = tasks[0].period;
    for (int i = 1; i < num_tasks; i++) {
        int a = hyperperiod, b = tasks[i].period;
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        hyperperiod = (hyperperiod * tasks[i].period) / a;
    }
    return hyperperiod;
}

int main() {
    int n;

    // Choix de l'input pour l'utilisateur
    n = get_positive_int("Entre le nombre de tâches de ton problème : ");

    // Allouer dynamiquement le tableau tasks[] de taille n
    Task *tasks = (Task *)malloc(n * sizeof(Task));

    for (int i = 0; i < n; i++) {
        char taskName[10];

        // Génération du nom de la tâche
        sprintf(taskName, "T%d", i + 1);

        printf("Donnez les informations de la tache T%d :", i + 1);
        // Obtenir la durée d'exécution, l'échéance, et la période avec vérification
        int C = get_positive_int("\nEntre la durée d'exécution (C) : ");
        int D = get_positive_int("Entre l'échéance (D) : ");
        int T = get_positive_int("Entre la période (T) : ");

        // Copier les données dans le tableau tasks[]
        strcpy(tasks[i].task_id, taskName);
        tasks[i].execution_time = C;
        tasks[i].remaining_time = C;   // Initialiser le temps restant
        tasks[i].deadline = D;  // Initialiser l'échéance absolue à la première période
        tasks[i].period = T;
        tasks[i].original_deadline = D; // Stocker l'échéance initiale pour référence
        tasks[i].execution_count = 0;   // Initialiser le compteur d'exécutions à 0
    }

    // Calculer l'hyperpériode (plus petit commun multiple des périodes)
    int hyperperiod = calculate_hyperperiod(tasks, n);

    // Affichage de la liste des tâches
    printf("\nListe des tâches :\n");
    for (int i = 0; i < n; i++) {
        printf("Tâche %s : Durée = %d, Échéance = %d, Période = %d\n", 
               tasks[i].task_id, tasks[i].execution_time, tasks[i].deadline, tasks[i].period);
    }

    // Affichage des tâches avant exécution
    printf("Tâches avant l'exécution:\n");
    for (int i = 0; i < n; i++) {
        print_task(tasks[i]);
    }
    printf("=========================================\n");

    // Exécution de l'ordonnanceur EDF
    run_edf_scheduler(tasks, n, hyperperiod);

    // Libération de la mémoire
    free(tasks);

    return 0;
}
