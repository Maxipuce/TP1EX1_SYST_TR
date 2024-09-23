#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void ex1() {
  int n;
  printf("Entre le nombre de tâches : ");
  scanf("%d", &n);

  int table[n][4];

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
  printf("\nChoisissez entre différents ordonnanceurs :\n");
  printf("1.Highest Priority First (HPF) or 2.Rate Monotonic (RM) or "
         "3.Deadline Monotonic (DM)");
  printf("Votre choix (1,2 ou 3) est : ");
  scanf("%d", &ord);

  if (ord = 1) {
    printf("Vous avez choisis HPF");
  } else if (ord = 2) {
    printf("Vous avez choisis RM");
  } else if (ord = 3) {
    printf("Vous avez choisis DM");
  }
}

int main() {
  int c1;
  printf("Choisis l'exercice (1 ou 2 ou 3) :");
  scanf("%d", &c1);
  if (c1 == 1) {
    ex1();
  } else if (c1 == 2) {
    printf("Exercise 2\n");
  } else if (c1 == 3) {
    printf("Exercise 3\n");
  }
}
