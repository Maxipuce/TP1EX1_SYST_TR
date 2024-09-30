// Définition d'une structure de tâche
typedef struct {
  int id;             // Identifiant de la tâche
  int execution_time; // Durée d'exécution de la tâche
  int deadline;       // Échéance de la tâche
  int period;         // Période de la tâche
  int priority;       // Priorité de la tâche
} Task;

#define MAX_TASKS 10
#define C 0 // Index for execution time
#define D 1 // Index for deadline
#define T 2 // Index for period
#define P 3 // Index for priority
#define R 4 // Index for response time

int calc_resp_time(int tasks[MAX_TASKS][5], int n);