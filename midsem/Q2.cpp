#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
using namespace std;

struct process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;

    bool operator<(const process &y) const
    {
        if (priority != y.priority)
            return priority < y.priority;
        else if (arrival_time != y.arrival_time)
            return arrival_time > y.arrival_time;
        else
            return process_id > y.process_id;
    }

    bool operator>(const process &y) const
    {
        if (priority > y.priority)
            return priority < y.priority;
        else if (arrival_time < y.arrival_time)
            return arrival_time < y.arrival_time;
        else
            return process_id < y.process_id;
    }
};

bool comp1(process a, process b)
{
    if (a.arrival_time != b.arrival_time)
        return a.arrival_time < b.arrival_time;

    else
        return a.process_id < b.process_id;
}

int main()
{
    int n;
    ::cout << "Enter the number of processes: ";
    cin >> n;

    process processes[n];
    int completion_times[n];
    int start_times[n] = {};
    int turn_around_times[n];
    int waiting_times[n];
    int response_times[n];
    int remaining_burst_times[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].process_id = i;
        printf("Enter the Details for process %d: ", i + 1);
        printf("\n");
        printf("\tArrival Time: ");
        cin >> processes[i].arrival_time;
        printf("\tPriority: ");
        cin >> processes[i].priority;
        printf("\tBurst Time: ");
        cin >> processes[i].burst_time;
        remaining_burst_times[i] = processes[i].burst_time;
    }

    sort(processes, processes + n, comp1);

    priority_queue<process> ready_queue;

    int completed = 0;
    int elapsed_time = -1;
    int process_idx = 0;

    while (completed != n)
    {

        if (ready_queue.empty())
        {
            elapsed_time++;

            while (processes[process_idx].arrival_time <= elapsed_time &&
                   process_idx < n)
                ready_queue.push(processes[process_idx++]);

            continue;
        }

        process cur_process = ready_queue.top();
        int processId = cur_process.process_id;

        if (start_times[processId] == 0)
            start_times[processId] = elapsed_time;

        remaining_burst_times[processId]--;
        elapsed_time++;

        while (processes[process_idx].arrival_time <= elapsed_time &&
               process_idx < n)
            ready_queue.push(processes[process_idx++]);

        if (remaining_burst_times[processId] == 0)
        {
            completion_times[processId] = elapsed_time;
            completed++;
            ready_queue.pop();
        }
    }

    for (auto p : processes)
    {
        turn_around_times[p.process_id] =
            completion_times[p.process_id] - p.arrival_time;
    }

    for (auto p : processes)
    {
        waiting_times[p.process_id] =
            turn_around_times[p.process_id] - p.burst_time;
    }

    for (auto p : processes)
    {
        response_times[p.process_id] =
            start_times[p.process_id] - p.arrival_time;
    }

    ::cout << "\n";
    ::cout << "No.\t"
           << "AT\t"
           << "BT\t"
           << "CT\t"
           << "TAT\t"
           << "WT\t"
           << "RT\n";

    for (int i = 0; i < n; i++)
    {
        ::cout << processes[i].process_id + 1 << "\t"
               << processes[i].arrival_time << "\t" << processes[i].burst_time
               << "\t" << completion_times[processes[i].process_id] << "\t"
               << turn_around_times[processes[i].process_id] << "\t"
               << waiting_times[processes[i].process_id] << "\t"
               << response_times[processes[i].process_id] << "\n";
    }

    double avg_waiting_time = 0;
    double avg_turn_around_time = 0;
    double avg_response_time = 0;

    for (int i = 0; i < n; i++)
    {
        avg_waiting_time += waiting_times[i];
        avg_turn_around_time += turn_around_times[i];
        avg_response_time += response_times[i];
    }

    avg_waiting_time /= n;
    avg_turn_around_time /= n;
    avg_response_time /= n;
    ::cout << "\n";
    ::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
    ::cout << "Average Turn Around Time: " << avg_turn_around_time << "\n";
    ::cout << "Average Response Time: " << avg_response_time << "\n";
}