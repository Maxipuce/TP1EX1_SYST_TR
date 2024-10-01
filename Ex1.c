#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_TASKS 10

//#include "hpf.h"
//#include "response_time.h"

int calc_resp_time(int tasks[MAX_TASKS][5], int n);
int calc_resp_time(int tasks[MAX_TASKS][5], int n) {
  int feasible = 1; // Assume the system is feasible initially

  //Sort tasks by priority
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (tasks[j][3] < tasks[j + 1][3]) {
        for (int k = 0; k < 5; k++) {
          int temp = tasks[j][k];
          tasks[j][k] = tasks[j + 1][k];
          tasks[j + 1][k] = temp;
        }
      }
    }
  }

  // Calculate response time for each task
  for (int i = 0; i < n; i++) {
    int r_prev = tasks[i][0]; // Initial response time r_0
    int r_next;
    r_next = tasks[i][0]; // Start with the execution time of the task itself
    while (1) {
     

      // Add the interference from higher-priority tasks
      for (int j = 0; j < i+1; j++) { 
        
        r_prev = r_next;
        double temp = (r_prev / tasks[j][2]);
        r_next = r_next + (ceil(temp) * tasks[j][0]);
        
        //printf("\nim here for task %d, with respo time = %d",i+1, r_next);
        //printf("\nr_prev = %d", r_prev);
        //printf("\ntemp = %f   ceil = %f\n",temp, ceil(temp));
        //printf("\ntask before %d is task %d, with T=%d and C=%d\n",i+1, j+1,tasks[j][2], tasks[j][0]);
      }

      // Check for convergence
      if (r_next == r_prev) {
        break;
      }

      // If r_next exceeds the task's deadline, the task cannot be scheduled in
      // time
      if (r_next > tasks[i][1]) {
        tasks[i][4] = -1; // Indicate a deadline miss
        feasible = 0;     // Mark the system as not feasible
        break;
      }

      r_prev = r_next; // Update for the next iteration
    }

    // Store the final response time if it met the deadline
    if (r_next <= tasks[i][1]) {
      printf("\n***Response time of task %d is %d***\n",i+1, r_next);
      tasks[i][4] = r_next;
    }
  }

  // Return feasibility result
  return feasible;
}

void check_feasibility(int tasks[MAX_TASKS][5], int n);
void check_feasibility(int tasks[MAX_TASKS][5], int n) {
    int current_time = 0;
    int i;

    // Trier les tâches par ordre de priorité
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
          if (tasks[j][3] > tasks[j + 1][3]) {
            for (int k = 0; k < 5; k++) {
              int temp = tasks[j][k];
              tasks[j][k] = tasks[j + 1][k];
              tasks[j + 1][k] = temp;
            }
          }
        }
      }



    printf("Ordre d'exécution des tâches selon la priorité (HPF):\n");
    for (i = 0; i < n; i++) {
        printf("Tâche %d (Durée: %d, Échéance: %d, Priorité: %d)\n",
               i+1, tasks[i][0], tasks[i][2], tasks[i][3]);
    }

    // Exécution des tâches
    for (i = 0; i < n; i++) {
        current_time += tasks[i][0];

        // Vérifier si la tâche est terminée avant son échéance
        if (current_time > tasks[i][2]) {
            printf("L'ensemble des tâches n'est pas faisable. Tâche %d dépasse l'échéance.\n", i+1);
            return;
        }
    }

    printf("L'ensemble des tâches est faisable avec HPF.\n");
}



void ex1() {
  int n;
  int t;
  
  double U = 0.0, Urm;
  printf("Choisis les paramètres de ton problème.\n\nEntre le nombre de tâches : ");
  scanf("%d", &n);

  int table[n][5];

  for (int i = 0; i < n; i++) {
    int C, D, T, P;

    printf("\nEntre la durée d'exécution C de la tâche %d : ", i + 1);
    scanf("%d", &C);
    table[i][0] = C;

    printf("Entre l'échéance D de la tâche %d : ", i + 1);
    scanf("%d", &D);
    table[i][1] = D;

    printf("Entre la période T de la tâche %d : ", i + 1);
    scanf("%d", &T);
    table[i][2] = T;

    printf("Entre la priorité P de la tâche %d : ", i + 1);
    scanf("%d", &P);
    table[i][3] = P;
  }

  for (int i = 0; i < n; i++) {
    printf("\n");
    for (int j = 0; j < 4; j++) {
      printf("%d ", table[i][j]);
    }
  }

  int ord;
  printf("\n\nChoisissez entre différents ordonnanceurs :\n");
  printf("1.Highest Priority First (HPF)\n2.Rate Monotonic (RM)\n3.Deadline "
         "Monotonic (DM)\n\n");
  printf("Votre choix (1, 2 ou 3) est : ");
  scanf("%d", &ord);
  
  // HPF
  if (ord == 1) { 
    printf("\nVous avez choisi HPF");

    check_feasibility(table, n);


  //RM
  } else if (ord == 2) {  
    printf("\nVous avez choisi RM.\n");

    // Calcul de Urm en utilisant la formule correcte
    Urm = n * (pow(2, 1.0 / n) - 1.0);

    // Calcul de U
    for (int i = 0; i < n; i++) {
      U += (double)table[i][0] / table[i][2];
    }

    if (U > 1) {
      printf("Le système est non faisable car U (%.2f) > 1.\n", U);
    
    } 
    else if (U <= Urm) {
      printf("Le système est faisable car U (%.2f) <= Urm (%.2f).\n Nous allons maintenant regarder au niveau des temps de réponse", U, Urm);

    } else {
      printf("On ne peut pas déduire selon la charge, donc on doit appliquer "
             "l'analyse des échéances : Urm < U < 1 (%.2f < %.2f < 1).\n",
             Urm, U);
             if(calc_resp_time(table,n) == 1){
                printf("Le system est faisable selon les temps de réponse.\n");
              } 
              else{
                  printf("Le system n'est aps faisable selon les temps de réponse\n");
              }
    }



  //DM
  } else if (ord == 3) {
    printf("Vous avez choisi DM\n");

    if(calc_resp_time(table,n) == 1){
      printf("The system is feasable.\n");
    } 
    else{
        printf("The system isn't feasable\n");
    }

  }
}

int main() {
    ex1();
}
