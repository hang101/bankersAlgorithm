#include <iostream>
using namespace std;
#define N 5 // no of processes
#define M 3 // no of resources

void input_resource(int res[])
{
    int temp;
    for (int i = 0; i < M; i++)
    {
        cout << "Enter no of resource " << i << ":";
        cin >> temp;
        res[i] = temp;
    }
}

void enter_allocated(int allocated[][M])
{
    int temp;
    for (int i = 0; i < N; i++) // row
    {
        for (int j = 0; j < M; j++) // column
        {
            cout << "Enter the allocated resource for: R[" << i << "]"
                 << "[" << j << "]: ";
            cin >> temp;
            allocated[i][j] = temp;
        }
        cout << "\n";
    }
}

void max_resource(int max[][M])
{
    int temp;
    for (int i = 0; i < N; i++) // row
    {
        for (int j = 0; j < M; j++) // column
        {
            cout << "Enter the max resource for: R[" << i << "]"
                 << "[" << j << "]: ";
            cin >> temp;
            max[i][j] = temp;
        }
        cout << "\n";
    }
}

void required_marrix(int required[][M], int max[][M], int available[][M])
{
    for (int i = 0; i < N; i++) // row
    {
        for (int j = 0; j < M; j++) // column
        {
            required[i][j] = max[i][j] - available[i][j];
        }
    }
}

void printMatrix(int matrix[][M])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

template <typename T>
void copy_matrix(T a[M], T b[M])
{
    for (int j = 0; j < M; j++)
    {
        b[j] = a[j];
    }
}

template <typename T>
void assign_value(T matrix[M], T value)
{
    for (int i = 0; i < M; i++)
    {
        matrix[i] = value;
    }
}

bool all_finish(bool finish[N])
{
    for (int i = 0; i < N; i++)
    {
        if (finish[i] == false)
            return false;
    }
    return true;
}

int main()
{
    int available[M], max[N][M], allocated[N][M], needed[N][M], work[M];
    bool finish[M];

    input_resource(available);
    enter_allocated(allocated);
    max_resource(max);
    required_marrix(needed, max, allocated);
    printMatrix(needed);
    assign_value(finish, false);

    copy_matrix(available, work);
    int loop = 0;
    int i = 0;
    while (i >= 0)
    {
        for (int j = 0; j < M; j++) // selecting resource
        {
            if (finish[i] == false && needed[i][j] <= work[j])
            {
                work[j] = work[j] + allocated[i][j];
                finish[i] = true;
            }
        }
        i++;
        if (i > N)
        {
            i = 0;
            loop++;
        }
        if (all_finish(finish))
        {
            cout << "safe confition is achieved!" << endl;
            break;
        }
        if (loop > M)
        {
            break;
        }
    }
}

/*
To summarize how the code works
say we have N no of processes
M no of resources but each resource have its own no of instances
say resource is tape reader there can be many tape recorder
here tape recorder is an resource and many recorder are instances



now we have
1.Resource[M]
2.Allocated[N][M]
3.Max[N][M]
4.Needed[N][M]

1.Resource[M] stores the available resource (free resource)
2.Allocated[i][j] stores the resource "j" occupied by process "i"
3.max[i][j] stores the max "j" resource required by the "i"th process
4.Needed[i][j] stores the amount of "j"th resources required by the "i"th process

read all of this code on your own

        input_resource(available);
        enter_allocated(allocated);
        max_resource(max);
        required_marrix(needed, max, allocated);
        printMatrix(needed);
        assign_value(finish, false);



finsh[m] is used to store which process is finished
work[n] stores the resource available


if we have free resources more than needed then we use the resource
so :
    here "j" is the resource no:

            work[j] = work[j] + allocated[i][j];
            finish[i] = true;


ALL MAGIC IS DONE BY THIS PORTION

int loop = 0;
    int i = 0;
    while (i >= 0)//because we have to start loop from the beginning of the process
    {
        for (int j = 0; j < M; j++) // selecting resource
        {
            if (finish[i] == false && needed[i][j] <= work[j])
            {
                work[j] = work[j] + allocated[i][j];
                finish[i] = true;
            }
        }
        i++;
        if (i > N)//If all process is looped then start from the beginning
        {
            i = 0;
            loop++;//check how many times have we looped
        }
        if (all_finish(finish))
        {
            cout << "safe confition is achieved!" << endl;
            break;
        }
        if (loop > M)//if we looped more than the no of process then it is unsafe because
        //if say at worst case only one loop can allow
        //one process to then at max it will take M no of loops
        {
            break;
        }
    }


*/