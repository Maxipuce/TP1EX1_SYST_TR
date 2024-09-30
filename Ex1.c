#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "response_time.h"

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
         "Monotonic (DM)\n");
  printf("Votre choix (1, 2 ou 3) est : ");
  scanf("%d", &ord);

  if (ord == 1) {
    printf("Vous avez choisi HPF");

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
    } else if (U <= Urm) {
      printf("Le système est faisable car U (%.2f) <= Urm (%.2f).\n", U, Urm);
    } else {
      printf("On ne peut pas déduire selon la charge, donc on doit appliquer "
             "l'analyse des échéances : Urm < U < 1 (%.2f < %.2f < 1).\n",
             Urm, U);
    }

  } else if (ord == 3) {
    printf("Vous avez choisi DM");

    calc_resp_time(table, n);

  }
}

int main() {
    ex1();
}
