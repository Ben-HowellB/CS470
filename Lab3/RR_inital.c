/* RR_inital.c
 * Round Robin Scheduling
 */

 #include <stdio.h>
 #include <stdlib.h>
 
 typedef struct {
     int process_id;
     int arrival_time;
     int burst_time;
     int remaining_time;
     int waiting_time;
     int turnaround_time;
 } Process;
 
 // Simulate RR, record execution order and compute waiting times
 void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
     int *rt = malloc(n * sizeof(int));
     for (int i = 0; i < n; i++) {
         rt[i] = proc[i].burst_time;
         proc[i].waiting_time = 0;
     }
 
     int completed = 0, current_time = 0;
     int *exec_order = malloc(sizeof(int) * 1000);
     int eo_count = 0;
 
     while (completed < n) {
         int did_run = 0;
         for (int i = 0; i < n; i++) {
             if (proc[i].arrival_time <= current_time && rt[i] > 0) {
                 did_run = 1;
                 int slice = (rt[i] > quantum ? quantum : rt[i]);
                 // Run for 'slice' time units
                 for (int t = 0; t < slice; t++) {
                     exec_order[eo_count++] = proc[i].process_id;
                     current_time++;
                     // increment waiting of all other ready processes
                     for (int j = 0; j < n; j++) {
                         if (j != i && proc[j].arrival_time <= current_time && rt[j] > 0) {
                             proc[j].waiting_time++;
                         }
                     }
                 }
                 rt[i] -= slice;
                 if (rt[i] == 0) {
                     completed++;
                 }
             }
         }
         if (!did_run) {
             // No process ready; idle
             current_time++;
         }
     }
 
     // Print execution order
     printf("Execution Order: ");
     for (int i = 0; i < eo_count; i++) {
         if (i) printf(" -> ");
         printf("P%d", exec_order[i]);
     }
     printf("\n\n");
 
     free(rt);
     free(exec_order);
 }
 
 // Compute turnaround times from burst + waiting
 void calculateTurnaroundTime(Process proc[], int n) {
     for (int i = 0; i < n; i++) {
         proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
     }
 }
 
 void roundRobin(Process proc[], int n, int quantum) {
     calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
     calculateTurnaroundTime(proc, n);
 }
 
 // Print per-process table and averages
 void printProcesses(Process proc[], int n) {
     double total_wt = 0, total_tat = 0;
     printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");
     for (int i = 0; i < n; i++) {
         printf("P%d\t%d\t%d\t%d\t%d\n",
                proc[i].process_id,
                proc[i].arrival_time,
                proc[i].burst_time,
                proc[i].waiting_time,
                proc[i].turnaround_time);
         total_wt += proc[i].waiting_time;
         total_tat+= proc[i].turnaround_time;
     }
     printf("\nAverage Waiting Time   = %.2f\n", total_wt / n);
     printf("Average Turnaround Time= %.2f\n", total_tat / n);
 }
 
 int main() {
    // Example data; you can modify or read from input 
     Process proc[] = {
         {1, 0, 24, 42},
         {2, 0, 3, 9},
         {3, 0, 3, 39}
     };
     int n = sizeof(proc) / sizeof(proc[0]);
     int quantum = 4;
 
     roundRobin(proc, n, quantum);
     printProcesses(proc, n);
 
     return 0;
 }
 