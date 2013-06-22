#include<stdio.h>
#include<stdlib.h>
#include"bst.h"
#include"stack.h"
#include"team.h"
#include"userIO.h"
#include"hash.h"
#include"fileIO.h"
#include"main.h"
int main(){DATA_HEAD*node;node=malloc(sizeof(DATA_HEAD));if(!node)exit(1);readInFile(node);menuOptions(node);saveToFile(node);cleanupData(node);return 0;}void menuOptions(DATA_HEAD*node){char userChoice;do{printMenu();userChoice=getChoice();switch(userChoice){case'a':insertCompany(node);break;case'd':deleteCompany(node);break;case's':search(node);break;case'h':printHashed(node);break;case'k':printKeySequence(node);break;case't':printTree(node);break;case'w':saveToFile(node);break;case'e':printEfficiency(node);break;case'u':undoDelete(node);break;default:return;}}while(userChoice !='q');}void insertManager(DATA_HEAD*data,COMPANY*newCompany){insertBST(data->pTree,newCompany);insertHash(data,newCompany);}COMPANY*deleteManager(DATA_HEAD*data,COMPANY*companyPtr){COMPANY*deletedPtr;if(deleteBST(data->pTree,companyPtr,(void**)&deletedPtr),deleteHash(data,companyPtr->companyName))return deletedPtr;else return NULL;}
