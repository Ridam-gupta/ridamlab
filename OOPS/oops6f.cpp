#include <stdio.h>
// Function to find the waiting time for all
// processes
void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[])
{
    // waiting time for first process is 0
    wt[0] = 0;
    // calculating waiting time
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1] - (at[i] - at[i - 1]);
}
// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[], int at[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
// Function to calculate average time
void findavgTime(int processes[], int n, int bt[], int at[])
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt, at);
    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat, at);
    // Display processes along with all details
    printf("Processes Burst_time Waiting_time Turn_around_time\n");
    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" %d ", (i + 1));
        printf("\t\t%d ", bt[i]);
        printf("\t\t%d", wt[i]);
        printf("\t\t%d\n", tat[i]);
    }
    float s = (float)total_wt / (float)n;
    float t = (float)total_tat / (float)n;
    printf("Average waiting time = %f", s);
    printf("\n");
    printf("Average turn around time = %f ", t);
}
// Driver code
int main()
{
    // process id's
    int processes[] = {1, 2, 3, 4, 5};
    int n = sizeof processes / sizeof processes[0];
    int arr_time[] = {0, 1, 2, 3, 4};
    // Burst time of all processes
    int burst_time[] = {8, 1, 3, 2, 6};
    findavgTime(processes, n, burst_time, arr_time);
    return 0;
}