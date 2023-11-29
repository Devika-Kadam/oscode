#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void findNeedValue(int** needArray, int** maxArray, int** allocationArray, int totalProcess, int totalResources);

bool checkSafeSystem(int* processes, int* availableArray, int** maxArray, int** allocationArray, int totalProcess, int totalResources);

int totalResources;

int main() {
    int numberOfProcesses;
    printf("Enter total number of processes: ");
    scanf("%d", &numberOfProcesses);

    printf("Enter total number of resources: ");
    scanf("%d", &totalResources);

    int* processes = (int*)malloc(numberOfProcesses * sizeof(int));
    for (int i = 0; i < numberOfProcesses; i++) {
        processes[i] = i;
    }

    int* availableArray = (int*)malloc(totalResources * sizeof(int));
    for (int i = 0; i < totalResources; i++) {
        printf("Enter the availability of resource %d: ", i);
        scanf("%d", &availableArray[i]);
    }

    int** maxArray = (int**)malloc(numberOfProcesses * sizeof(int*));
    for (int i = 0; i < numberOfProcesses; i++) {
        maxArray[i] = (int*)malloc(totalResources * sizeof(int));
        for (int j = 0; j < totalResources; j++) {
            printf("Enter the maximum resource %d that can be allocated to process %d: ", j, i);
            scanf("%d", &maxArray[i][j]);
        }
    }

    int** allocationArray = (int**)malloc(numberOfProcesses * sizeof(int*));
    for (int i = 0; i < numberOfProcesses; i++) {
        allocationArray[i] = (int*)malloc(totalResources * sizeof(int));
        for (int j = 0; j < totalResources; j++) {
            printf("How many instances of resource %d are allocated to process %d? ", j, i);
            scanf("%d", &allocationArray[i][j]);
        }
    }


    if (checkSafeSystem(processes, availableArray, maxArray, allocationArray, numberOfProcesses, totalResources)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state due to a lack of resources.\n");
    }

    free(processes);
    free(availableArray);
    for (int i = 0; i < numberOfProcesses; i++) {
        free(maxArray[i]);
        free(allocationArray[i]);
    }
    free(maxArray);
    free(allocationArray);

    return 0;
}

void findNeedValue(int** needArray, int** maxArray, int** allocationArray, int totalProcess, int totalResources) {
    for (int i = 0; i < totalProcess; i++) {
        for (int j = 0; j < totalResources; j++) {
            needArray[i][j] = maxArray[i][j] - allocationArray[i][j];
        }
    }
}

bool checkSafeSystem(int* processes, int* availableArray, int** maxArray, int** allocationArray, int totalProcess, int totalResources) {
    int** needArray = (int**)malloc(totalProcess * sizeof(int*));
    for (int i = 0; i < totalProcess; i++) {
        needArray[i] = (int*)malloc(totalResources * sizeof(int));
    }

    findNeedValue(needArray, maxArray, allocationArray, totalProcess, totalResources);

    bool* finishProcesses = (bool*)malloc(totalProcess * sizeof(bool));
    int* safeSequenceArray = (int*)malloc(totalProcess * sizeof(int));
    int* workArray = (int*)malloc(totalResources * sizeof(int));

    for (int i = 0; i < totalProcess; i++) {
        finishProcesses[i] = false;
    }

    for (int i = 0; i < totalProcess; i++) {
        safeSequenceArray[i] = 0;
    }

    for (int i = 0; i < totalResources; i++) {
        workArray[i] = availableArray[i];
    }

    int counter = 0;

    while (counter < totalProcess) {
        bool foundSafeSystem = false;

        for (int m = 0; m < totalProcess; m++) {
            if (!finishProcesses[m]) {
                int j;

                for (j = 0; j < totalResources; j++) {
                    if (needArray[m][j] > workArray[j]) {
                        break;
                    }
                }

                if (j == totalResources) {
                    for (int k = 0; k < totalResources; k++) {
                        workArray[k] += allocationArray[m][k];
                    }

                    safeSequenceArray[counter++] = m;
                    finishProcesses[m] = true;
                    foundSafeSystem = true;
                }
            }
        }

        if (!foundSafeSystem) {
            printf("The system is not in the safe state due to a lack of resources.\n");
            return false;
        }
    }

    printf("The system is in a safe sequence and the sequence is as follows: ");
    for (int i = 0; i < totalProcess; i++) {
        printf("P%d ", processes[safeSequenceArray[i]]);
    }

    printf("\n");


    free(needArray);
    free(finishProcesses);
    free(safeSequenceArray);
    free(workArray);

    return true;
}
