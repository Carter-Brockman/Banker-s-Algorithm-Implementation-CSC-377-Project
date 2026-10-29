#include <iostream>
#include <vector>

int main()
{
	//Variable declaration and assignment -- Banker's Algorithm
	int processes; int resources;

	std::cout << "Input number of processes : "; std::cin >> processes; std::cout << std::endl;
	std::cout << "Input number of resources : "; std::cin >> resources; std::cout << std::endl;

	//Variable declaration and assignment -- Safety Algorithm
	int count = 0; bool safeFound = false;

	//The following are matricies that are allocated at runtime to allow variable testing:
	//For Banker's Algorithm
	std::vector<int> available(resources); //Number of resources available for processes to use, size is unique resources that exist
	std::vector<std::vector<int>> max(processes, std::vector<int>(resources, 0)); //Maximum number of resources a process needs max[i,j] = k, where k is the resource number, j, process i needs at most
	std::vector<std::vector<int>> allocation(processes, std::vector<int>(resources, 0)); //Number of resources allocated to a process, allocation[i,j] = k, where k is the number of resources assigned to a process
	std::vector<std::vector<int>> need(processes, std::vector<int>(resources, 0)); //Number of resources needed for a process to complete execution, need[i,j] = k, where k is the number of resources needed to complete execution

	//For Safety Algorithm
	std::vector<bool> finish(processes);
	std::vector<int> safeSequence(processes);

	//First we will find the number of resources a process will need using the max matrix
	std::cout << "Enter the max matrix : " << std::endl;
	
	for (int i = 0; i < processes; i++)
	{
		for (int j = 0; j < resources; j++)
		{
			std::cin >> max[i][j];
		}
	}

	//Next decide how many resources are already allocated using the allocation matrix
	std::cout << "Enter the allocation matrix : " << std::endl;;

	for (int i = 0; i < processes; i++)
	{
		for (int j = 0; j < resources; j++)
		{
			std::cin >> allocation[i][j];
		}
	}

	//Finally decide how many resources are available using the available matrix

	std::cout << "Enter the available vector: " << std::endl;
	for (int i = 0; i < resources; i++)
	{
		std::cin >> available[i];
	}

	//Now the need[i][j] logic, we will do max[i,j] - allocation[i,j]
	for (int i = 0; i < processes; i++)
	{
		for (int j = 0; j < resources; j++)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}

	//Here will be the safety algorithm checks to ensure the system is still in a safe state
	for (int i = 0; i < processes; i++) //all values in finish should start as false
	{
		finish[i] = false;
	}

	while (count < processes)
	{
		safeFound = false; //resets every time we check the processes in a loop
		for (int i = 0; i < processes; i++)
		{
			if (finish[i] == false)
			{
				bool safe = true;
				for (int j = 0; j < resources; j++)
				{
					if (need[i][j] > available[j])
					{
						safe = false; break;
					}
				}
				if (safe)
				{
					for (int k = 0; k < resources; k++) 
					{
						available[k] += allocation[i][k];
					}
					safeSequence[count++] = i;
					finish[i] = true;
					safeFound = true;
				}
			}
		}
		if (!safeFound)
		{
			std::cout << "Unsafe state detected! Chance of deadlock!" << std::endl;
			return 0;
		}
	}

	//Output the processes in the order they are ran to avoid a deadlock
	std::cout << "System is in safe state, no deadlock detected.\nThe safe sequence is: ";
	for (int i = 0; i < processes - 1; i++)
	{
		std::cout << "Process " << safeSequence[i] << ", ";
	}


	std::cout << "Process " << safeSequence.back() << std::endl;

	return 0;
}
