#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct node** arr;
	int size;
};

struct node {
struct RecordType iPtr;
struct node* next;
} node;

// Compute the hash function
int hash(int x)
{
	//simple formula to get nums 0-22
	return (x%23);
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if(pHashArray[i].arr == NULL) {
			continue;
		}

		struct node *temp = pHashArray->arr[i]; 
		while(temp->next != NULL){
			printf("Hash table index %d has the value %d %c %d\n",hashSz,temp->iPtr.id,temp->iPtr.name,temp->iPtr.order);
			temp = temp->next;
		}

		printf("Hash table index %d has the value %d %c %d\n",hashSz, temp->iPtr.id, temp->iPtr.name, temp->iPtr.order);

	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	printf("\n\nHash results\n\n");

	int setindex;
	struct HashType *table;
	table = (struct HashType*)malloc(sizeof(struct HashType));
    table->arr = (struct node**)malloc(sizeof(struct  node)*23);
    struct node *temp2;

	struct node *temp;
	//Set to NULL
	for (int i=0;i<23;++i)
	{
		
		table->arr[i] = NULL;

	}

    int i;
	for (i=0;i<recordSz;++i)
	{
		//Get the index
		setindex = hash(pRecords[i].id);
        temp = table->arr[setindex];
        temp2 = (struct node*)malloc(sizeof(node));
        temp2->iPtr = pRecords[i];

		if(&table->arr[setindex] == NULL) {
			//Add direclty the node
			table->arr[setindex] = temp2;
		}

		else {
           
            while (temp->next != NULL){
				temp = temp->next;
			}
            temp->next = temp2;
		}

	}

	/*
	//Pass the array values into the hash table
	for (int i=0;i<recordSz;++i)
	{
		//Get the index
		setindex = hash(pRecords[i].id);

		//Check if NULL
		if(table[setindex].arr == NULL) {
			//Add direclty the node
			temp->iPtr.id = (int)pRecords[i].id;
			temp->iPtr.name = (char)pRecords[i].name;
			temp->iPtr.order = (int)pRecords[i].order;
			temp->next = NULL;
			table[setindex].arr = temp;
		}

		//Traverse list and append at the end;
		else {
			temp = table[setindex].arr;
			while (temp->next != NULL){
				temp = temp->next;
			}
			
			struct node temp2;
			temp2.iPtr = pRecords[i];
			temp2.next = NULL;
			temp->next = &temp2;
		}

	}
	*/

	displayRecordsInHash(table,23);

	//Free the mem
    for(i=0;i<recordSz;i++) {
        temp = table->arr[i];
        temp = temp;
        //free(table->arr[i]);
        while(temp->next != NULL) {
            temp2 = temp->next;
            free(temp);
            temp = temp2; 
        }
        free(temp);
    }
	free(table);
	free(pRecords);

}