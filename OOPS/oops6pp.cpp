// #include <stdio.h>

// struct Process {
//     int id;
//     int arrivalTime;
//     int burstTime;
//     int priority;
// };

// void swap(struct Process* a, struct Process* b) {
//     struct Process temp = *a;
//     *a = *b;
//     *b = temp;
// }

// void sortByPriority(struct Process processes[], int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (processes[j].priority > processes[j + 1].priority) {
//                 swap(&processes[j], &processes[j + 1]);
//             }
//         }
//     }
// }

// void priorityScheduling(struct Process processes[], int n) {
//     sortByPriority(processes, n);

//     int waitingTime[n];
//     waitingTime[0] = 0;
//     int turnaroundTime[n];

//     for (int i = 1; i < n; i++) {
//         waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
//     }

//     for (int i = 0; i < n; i++) {
//         turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
//     }

//     double totalWaitingTime = 0;
//     double totalTurnaroundTime = 0;

//     printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
//     for (int i = 0; i < n; i++) {
//         printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority, waitingTime[i], turnaroundTime[i]);
//         totalWaitingTime += waitingTime[i];
//         totalTurnaroundTime += turnaroundTime[i];
//     }

//     printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
//     printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
// }

// int main() {
//     int n;
//     printf("Enter the number of processes: ");
//     scanf("%d", &n);
//     struct Process processes[n];

//     for (int i = 0; i < n; i++) {
//         processes[i].id = i + 1;
//         printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
//         scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
//     }

//     priorityScheduling(processes, n);

//     return 0;
// }

#include <stdio.h>

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
};

void swap(struct Process *a, struct Process *b)
{
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    // Sort the processes by arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    int current_time = 0;
    int completed = 0;

    while (completed < n)
    {
        int highest_priority = -1;
        int selected_process = -1;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0)
            {
                if (highest_priority == -1 || processes[i].priority < highest_priority)
                {
                    highest_priority = processes[i].priority;
                    selected_process = i;
                }
            }
        }

        if (selected_process == -1)
        {
            current_time++;
        }
        else
        {
            processes[selected_process].remaining_time--;
            current_time++;

            if (processes[selected_process].remaining_time == 0)
            {
                completed++;
                processes[selected_process].turnaround_time = current_time - processes[selected_process].arrival_time;
                processes[selected_process].waiting_time = processes[selected_process].turnaround_time - processes[selected_process].burst_time;
            }
        }
    }

    // Calculate and display the turnaround time and waiting time for each process
    printf("\nProcess\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\n", processes[i].id, processes[i].turnaround_time, processes[i].waiting_time);
    }

    // Calculate and display average turnaround time and average waiting time
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }
    float avg_turnaround_time = (float)total_turnaround_time / n;
    float avg_waiting_time = (float)total_waiting_time / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);

    return 0;
}