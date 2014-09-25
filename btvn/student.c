#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
typedef struct{
	int StudentID;
	char Name[30];
	char Class[10];
	char Department[10];
}student;

typedef struct node_t{
	student val;
	int r;
	struct node_t*next;
}node;
int top=-1;
node*nodeArray[100];
node*newNode(int stdID, char*stdName, char*stdClass, char*stdDepartment,int stdR);
node*readFile(char*fileName);
void printNode(node*Node);
void menu();
int main(){
	node*root;
	int select=0;
	char fileName[MAX];
	do{
		menu();
		scanf("%d",&select);
		switch(select){
			case 1:
				printf("Enter file name:");
				//scanf("%s",fileName);
				strcpy(fileName,"input.txt");
				root=readFile(fileName);
				printNode(root);
			break;
			case 2:
			break;
			case 3:
			break;
			case 4:
			break;
			case 5:
			break;
			printf("Goodbye.\n");
			default:
			printf("Input Wrong!\n");
			printf("Press enter to continues.");
			break;
		}
	}while(select!=5);
}

void printNode(node*Node){
	while(Node->next!=NULL){
		Node=Node->next;
		printf("%d:%s:%s:%s\n",Node->val.StudentID,Node->val.Name,Node->val.Class,Node->val.Department);
	}
}
void menu(){
	printf("---MENU-----------------------------\n");
	printf("\t1. Read From File.\n");
	printf("\t2. Delete Record.\n");
	printf("\t3. Append Record.\n");
	printf("\t4. Modifier Record.\n");
	printf("\t5. Exit.\n");
	printf("Select: ");
}
node*newFreshNode(){
	node*Node=(node*)malloc(sizeof(node));
	return Node;
}
node*newNode(int stdID, char*stdName, char*stdClass, char*stdDepartment,int stdR){
	node*Node=(node*)malloc(sizeof(node));
	Node->val.StudentID=stdID;
	strcpy(Node->val.Name,stdName);
	strcpy(Node->val.Class,stdClass);
	strcpy(Node->val.Department,stdDepartment);
	Node->r =stdR;
	Node->next=NULL;
	return Node;
}
node*readFile(char*fileName){
	FILE*f;
	node*root=newFreshNode();
	node*tmpNode;
	char tmp[MAX];
	char*str=(char*)malloc(sizeof(char)*MAX);
	int r=0;
	root->r=r;
	f = fopen(fileName, "r+");
	if (f == NULL) {
  		fprintf(stderr, "Can't open output file %s.\n",fileName);
  		exit(1);
	}
	tmpNode=root;
	while(fgets (str, 80, f)!=NULL){
		//create a fresh node
		tmpNode->next=newFreshNode();
		tmpNode=tmpNode->next;
		tmpNode->r=(r+1)%20;
		if(tmpNode->r==0)
			nodeArray[++top]=tmpNode;
		int i=0;
		int j=0;
		//student id reader
		while(str[i]!=':'){
			tmp[j++]=str[i++];
		}
		tmp[j]='\0';
		i++;
		tmpNode->val.StudentID=atoi(tmp);
		//Name reader
		j=0;
		while(str[i]!=':'){
			tmp[j++]=str[i++];
		}
		tmp[j]='\0';
		strcpy(tmpNode->val.Name,tmp);
		i++;
		//class reader
		j=0;
		while(str[i]!=':'){
			tmp[j++]=str[i++];
		}
		tmp[j]='\0';
		strcpy(tmpNode->val.Class,tmp);
		i++;
		//Department reader
		j=0;
		while(str[i]!='\n' && str[i]!='\0'){
			tmp[j++]=str[i++];
		}
		tmp[j]='\0';
		strcpy(tmpNode->val.Department,tmp);
		i++;
	}
	return root;
}