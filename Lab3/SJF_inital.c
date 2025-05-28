/* SJF_inital.c
 * Preemptive SJF (SRTF) Scheduling
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <limits.h>
 
 typedef struct {
     int process_id;
     int arrival_time;
     int burst_time;
     int remaining_time;
     int waiting_time;
     int turnaround_time;
     int is_completed;
 } Process;
 
 int n; // Number of processes
 
 // Find the index of the ready process with the shortest remaining time
 int findNextProcess(Process proc[], int current_time) {
     int idx = -1;
     int min_rem = INT_MAX;
     for (int i = 0; i < n; i++) {
         if (!proc[i].is_completed 
             && proc[i].arrival_time <= current_time
             && proc[i].remaining_time < min_rem) {
             min_rem = proc[i].remaining_time;
             idx = i;
         }
     }
     return idx;
 }
 
 // Perform the SRTF scheduling, record execution order and compute metrics
 void srtf(Process proc[]) {
     for (int i = 0; i < n; i++) {
         proc[i].remaining_time = proc[i].burst_time;
         proc[i].is_completed   = 0;
         proc[i].waiting_time   = 0;
         proc[i].turnaround_time= 0;
     }
 
     int completed = 0, current_time = 0;
     int *exec_order = malloc(sizeof(int) * 1000);
     int eo_count = 0;
 
     while (completed < n) {
         int idx = findNextProcess(proc, current_time);
         if (idx == -1) {
             // CPU is idle
             current_time++;
             continue;
         }
         // Execute one time unit
         exec_order[eo_count++] = proc[idx].process_id;
         proc[idx].remaining_time--;
         current_time++;
 
         // If process finishes, record its metrics
         if (proc[idx].remaining_time == 0) {
             proc[idx].is_completed = 1;
             completed++;
             int finish_time = current_time;
             proc[idx].turnaround_time = finish_time - proc[idx].arrival_time;
             proc[idx].waiting_time    = proc[idx].turnaround_time - proc[idx].burst_time;
         }
     }
 
     // Print execution order
     printf("Execution Order: ");
     for (int i = 0; i < eo_count; i++) {
         if (i) printf(" -> ");
         printf("P%d", exec_order[i]);
     }
     printf("\n\n");
 
     free(exec_order);
 }
 
 // Print per-process table and averages
 void printProcesses(Process proc[]) {
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
         {1, 0, 8, 0},
         {2, 1, 4, 9},
         {3, 2, 9, 3},
         {4, 3, 5, 8}
     };
     n = sizeof(proc) / sizeof(proc[0]);
 
     srtf(proc);
     printProcesses(proc);
 
     return 0;
 }
 