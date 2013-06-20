#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

//sort these
int getArrSize(FILE* in);
void readInFile(DATA_HEAD *data);
int myStringCompare(void* pcompany1, void* pcompany2);
void cleanupData(DATA_HEAD *data);
void freeBST(void* structData);
void saveToFile(DATA_HEAD *data);
void processWrite (void * dataPtr, FILE* spData);

#endif // FILEIO_H_INCLUDED
