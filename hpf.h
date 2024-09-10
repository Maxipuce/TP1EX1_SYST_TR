// hpf.h
#ifndef HPF_H
#define HPF_H

// Définition d'une structure de tâche
typedef struct {
    int id;             // Identifiant de la tâche
    int execution_time; // Durée d'exécution de la tâche
    int deadline;       // Échéance de la tâche
    int period;         // Période de la tâche
    int priority;       // Priorité de la tâche
} Task;

// Prototypes des fonctions
void check_feasibility(Task tasks[], int n);
int compare(const void *a, const void *b);

#endif // HPF_H
