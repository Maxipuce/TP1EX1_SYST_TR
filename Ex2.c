#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Structure Task
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
    int all_tasks_completed_on_time = 1; // Indicateur pour savoir si toutes les tâches sont terminées à temps
    
    // Tri des tâches selon l'échéance la plus proche (algorithme EDF)
    qsort(tasks, num_tasks, sizeof(Task), compare);

    // Exécution des tâches
    for (int i = 0; i < num_tasks; i++) {
        Task task = tasks[i];
        
        // Vérifier si la tâche peut être terminée avant son échéance
        if (current_time + task.execution_time > task.deadline) {
            printf("Erreur : la tâche %s ne peut pas être terminée avant son échéance (%ds).\n", task.task_id, task.deadline);
            all_tasks_completed_on_time = 0;
            break;
        }

        // Exécution de la tâche
        printf("Exécution de la tâche %s à l'instant %d (échéance à %d)\n", task.task_id, current_time, task.deadline);
        
        // Simuler l'exécution de la tâche (en pause avec sleep)
        sleep(task.execution_time);  // Temps d'exécution simulé
        current_time += task.execution_time;

        printf("Tâche %s terminée à l'instant %d\n", task.task_id, current_time);
        printf("-----------------------------------------\n");
    }
    
    // Si toutes les tâches ont été complétées avant leur échéance
    if (all_tasks_completed_on_time) {
        printf("Toutes les tâches ont été complétées avant leurs échéances.\n");
    } else {
        printf("Certaines tâches n'ont pas pu être complétées avant leur échéance.\n");
    }
}

// Fonction pour obtenir un entier positif valide
int get_positive_int(const char *prompt) {
    int value;
    int result;
    
    do {
        printf("%s", prompt);
        result = scanf("%d", &value);
        
        // Vérifier si l'entrée est un entier valide
        if (result != 1) {
            printf("Erreur : veuillez entrer un nombre entier valide.\n");
            while (getchar() != '\n'); // Vider le buffer de l'entrée
        }
        // Vérifier si l'entrée est un entier positif
        else if (value < 0) {
            printf("Erreur : la valeur ne peut pas être négative.\n");
        }
    } while (result != 1 || value < 0);  // Boucle tant que l'entrée est incorrecte
    
    return value;
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

        printf("Donnez les informations de la tache T%d :", i+1);
        // Obtenir la durée d'exécution et l'échéance avec vérification
        int C = get_positive_int("\nEntre la durée d'exécution (C) : ");
        int D = get_positive_int("Entre l'échéance (D) : ");

        // Copier les données dans le tableau tasks[]
        strcpy(tasks[i].task_id, taskName);
        tasks[i].execution_time = C;
        tasks[i].deadline = D;
    }
    
    // Affichage de la liste des tâches
    printf("\nListe des tâches :\n");
    for (int i = 0; i < n; i++) {
        printf("Tâche %s : Durée = %d, Échéance = %d\n", tasks[i].task_id, tasks[i].execution_time, tasks[i].deadline);
    }
    
    // Affichage des tâches avant exécution
    printf("Tâches avant l'exécution:\n");
    for (int i = 0; i < n; i++) {
        print_task(tasks[i]);
    }
    printf("=========================================\n");

    // Exécution de l'ordonnanceur EDF
    run_edf_scheduler(tasks, n);

    // Libération de la mémoire
    free(tasks);
    
    return 0;
}
