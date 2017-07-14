#include "heap.h"

Heap *createHeap(size_t initialSize, HEAP_TYPE htype, void (*destroyDataFP)(void *data),void (*printNodeFP)(void *toBePrinted),int (*compareFP)(const void *first, const void *second))
{

    Heap * temp = malloc(sizeof(Heap) * initialSize);
    if(temp == NULL)
    {
        return NULL;
    }

    temp->heapTable = malloc(sizeof(*temp->heapTable) * initialSize);

    for(int i = 0; i < initialSize; i++)
    {
        temp->heapTable[i] = NULL;
    }

    temp->type = htype;
    temp->initialSize = 0;
    temp->maxSize = initialSize;
    temp->destroyDataFP = destroyDataFP;
    temp->printNodeFP = printNodeFP;
    temp->compareFP = compareFP;

    return temp;

}

Node *createHeapNode(int priority, void *clientID, void *symptomCode)
{

    Node * temp = malloc(sizeof(Node));
    temp->clientID = malloc(sizeof(clientID));
    temp->symptomCode = malloc(sizeof(symptomCode));
    // printf("3\n");
    if(temp == NULL)
    {
        return NULL;
    }

    // strcpy(temp->data, data);
    temp->priority = priority;
    strcpy(temp->clientID, clientID);
    strcpy(temp->symptomCode, symptomCode);
    // temp->data = data;
    // temp->clientID = clientID;
    // temp->symptomCode = symptomCode;

    return temp;

}

void insertHeapNode(Heap *heap, int priority, void *clientID, void *symptomCode)
{



    if(heap == NULL)
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
        //     return NULL;  
    }
    else
    {
        Node * temp = createHeapNode(priority, clientID, symptomCode);

        int tempSize = heap->initialSize;

        heap->initialSize++;

        while(tempSize && temp->priority > heap->heapTable[getParent(tempSize)]->priority)
        {
            heap->heapTable[tempSize] = heap->heapTable[getParent(tempSize)];
            tempSize = getParent(tempSize);
        }

        heap->heapTable[tempSize] = temp;

        reheapifyMin(heap, 0);


    }

}

void deleteMinOrMax(Heap *heap)
{

    if(heap != NULL)
    {

        Node * minVal = getMinOrMax(heap);
        free(minVal);
        heap->maxSize--;
        reheapifyMin(heap, 0);
        // printf("Max Value successfully deleted\n");
    }
    else
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
    }

}

void *getMinOrMax(Heap *heap)
{
    if(heap != NULL)
    {
        return heap->heapTable[heap->maxSize - 1];
    }
    else
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
        return NULL;
    }
}


void deleteHeap(Heap *heap)
{
    if(heap != NULL)
    {


        while(heap->maxSize != 1)
        {

            deleteMinOrMax(heap);

        }

        heap->maxSize--;
        free(heap->heapTable);
        // printf("Heap has been successfully deleted\n");
    }
    else
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
    }
    // }
}

void reheapifyMin(Heap * heap, int tempSize)
{

    if(heap != NULL)
    {

        int tempInt = 0;
        // printf("tempSize1: %d\n", tempSize);
        // printf("3\n");
        if(getLeftChild(tempSize) < heap->initialSize && heap->heapTable[getLeftChild(tempSize)]->priority < heap->heapTable[tempSize]->priority)
        {
            // printf("4\n");
            tempInt = getLeftChild(tempSize);
            // printf("tempSize2: %d\n", tempSize);
            // printf("5\n");
        }
        else
        {
            // printf("6\n");
            tempInt = tempSize;
            // printf("tempSize3: %d\n", tempSize);
            // printf("7\n");
        }
        // printf("8\n");
        if(getRightChild(tempSize) < heap->initialSize && heap->heapTable[getRightChild(tempSize)]->priority < heap->heapTable[tempInt]->priority)
        {
            // printf("9\n");
            tempInt = getRightChild(tempSize);
            // printf("tempSize: %d\n", tempSize);
            // printf("10\n");
        }
        // printf("11\n");
        if(tempInt != tempSize)
        {

            Node * swapNode = heap->heapTable[tempSize];
            // printf("13\n");

            heap->heapTable[tempSize] = heap->heapTable[tempInt];
            // printf("14\n");

            heap->heapTable[tempInt] = swapNode;
            // printf("15\n");
            reheapifyMin(heap, tempInt);
        }
    }
    else
    {
        printf("Heap either does not exist or has been created incorrectly.\n");
    }
}

int getParent(int tempInt)
{

    return ((tempInt - 1)/2);

}

int getLeftChild(int tempInt)
{

    return ((tempInt * 2) + 1);

}

int getRightChild(int tempInt)
{

    return ((tempInt * 2) + 2);

}

void printHeap(Heap * heap, FILE * outputFile, int option)
{
    if(heap != NULL)
    {
        if(option == 1)
        {
            for(int i = 0; i < heap->initialSize; i++)
            {
                if(strcmp(heap->heapTable[i]->symptomCode, "CV") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Cardiovascular\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "HN") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Ears, mouth, throat, nose\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "EV") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Environmental\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "GI") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Gastrointestinal\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "MH") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Mental Health\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "NC") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Neurological\n",heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "EC") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Opthalmology\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "RC") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Respiratory\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "SK") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Skin\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "SA") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Substance Abuse\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "TR") == 0)
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Trauma\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else
                {
                    fprintf(outputFile, "ClientID: %s, Priority: %d, Symptom Code: Unknown\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
            }
        }
        else
        {

            for(int i = 0; i < heap->initialSize; i++)
            {
                if(strcmp(heap->heapTable[i]->symptomCode, "CV") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Cardiovascular\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "HN") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Ears, mouth, throat, nose\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "EV") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Environmental\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "GI") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Gastrointestinal\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "MH") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Mental Health\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "NC") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Neurological\n",heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "EC") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Opthalmology\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "RC") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Respiratory\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "SK") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Skin\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "SA") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Substance Abuse\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else if(strcmp(heap->heapTable[i]->symptomCode, "TR") == 0)
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Trauma\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
                else
                {
                    printf("ClientID: %s, Priority: %d, Symptom Code: Unknown\n", heap->heapTable[i]->clientID, heap->heapTable[i]->priority);
                }
            }

        }

    }
    else
    {

        printf("Heap either does not exist or has been created incorrectly.\n");
    }
}

void deleteHeapNode(Heap *heap, void *clientID)
{

    for(int i = 0; i < heap->initialSize; i++)
    {
        if(strcmp(heap->heapTable[i]->clientID, clientID) == 0)
        {
            printf("clientID: %s\n", heap->heapTable[i]->clientID);
            free(heap->heapTable[i]);
            heap->initialSize--;
            reheapifyMin(heap, i);
        }
    }

}

