#include "response_time.h"
#include <stdio.h>
#include <stdlib.h>

int calc_resp_time(int tasks[MAX_TASKS][5], int n) {
  int feasible = 1; // Assume the system is feasible initially

  // Sort tasks by priority
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (tasks[j][P] > tasks[j + 1][P]) {
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
    int r_prev = tasks[i][C]; // Initial response time r_0
    int r_next;

    while (1) {
      r_next = tasks[i][C]; // Start with the execution time of the task itself

      // Add the interference from higher-priority tasks
      for (int j = 0; j < i; j++) { 
        r_next += ceil(r_prev / tasks[j][T]) * tasks[j][C];
      }

      // Check for convergence
      if (r_next == r_prev) {
        break;
      }

      // If r_next exceeds the task's deadline, the task cannot be scheduled in
      // time
      if (r_next > tasks[i][D]) {
        tasks[i][R] = -1; // Indicate a deadline miss
        feasible = 0;     // Mark the system as not feasible
        break;
      }

      r_prev = r_next; // Update for the next iteration
    }

    // Store the final response time if it met the deadline
    if (r_next <= tasks[i][D]) {
      tasks[i][R] = r_next;
    }
  }

  // Return feasibility result
  return feasible;
}