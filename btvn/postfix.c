#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 255

int top =-1;
int topDb=-1;
char stack[max];
double stackDb[max];

typedef struct node_t{
	char val;
	struct node_t*left;
	struct node_t*right;
}node;

node*stackNd[max];
int topNd=-1;

//create node
node*newNode(char a);
node* createTree(char postfix[max]);



void infixToPostfix(char infix[max], char postfix[max]);
void reverse(char array[max]);
//function with char stack
char pop();
void push(char sym);
void emptyStack();
//function with double stack
double popDb();
void pushDb(double num);
void emptyStackDb();

node*popNd();
void pushNd(node*nd);
void emptyStackNd();

int isOperator(char sym);
int isNumber(char sym);
int prcd(char sym);
double calculator(char postfix[max],double x);
double countTree(node*root,double x);
void printTree(node*root);

int main(){
	double f;
	node*root;
	double a;
	char infix[max], postfix[max],temp;
	printf("Enter f(x) operator: ");
	scanf("%s",infix);
	printf("Enter x value: ");
	scanf("%lf",&f);
	infixToPostfix(infix,postfix);
	printf("in Reverse Polish notation: ");
	puts(postfix);
	printf("The result: %0.1lf\n",calculator(postfix,f));
	root=createTree(postfix);
	printf("print Tree: ");
	printTree(root);
	printf("\n");
	printf("The result is using Binary Expression: ");
	printf("%0.1lf\n",countTree(root,f));
}




void infixToPostfix(char infix[max], char postfix[max]){
	emptyStack();
	int i=0,j=0;
	while(infix[i]!='\0'){
		if(isOperator(infix[i])!=1){ // if is operand
			postfix[j++]=infix[i];
		}else if(infix[i]== '(')
			push(infix[i]);
		else if(infix[i]==')'){
			while(stack[top]!='(')
				postfix[j++]=pop();
			top--;
		}else{
			while(top!=-1 && prcd(infix[i])<=prcd(stack[top]))
				postfix[j++]=pop();
			push(infix[i]);
		}
		i++;
	}
	while(top!=-1)
		if(stack[top]!=')' || stack[top]!='(')
			postfix[j++]=pop();
		else top--;
	postfix[j]='\0';
}

void reverse(char array[max]){
	int i,j;
	char temp[100];
	for(i=strlen(array)-1,j==0;i+1!=0;--i,++j)
		temp[j] = array[i];
	temp[j]='\0';
	strcpy(array,temp);
}

char pop(){
	char a;
	a=stack[top];
	top--;
	return a;
}

void push(char sym){
	top++;
	stack[top]=sym;
}
void emptyStack(){
	top=-1;
}
int prcd(char sym){
	switch(sym){
		case '+':
		case '-':
			return 2;
			break;
		case '*':
		case '/':
			return 4;
			break;
		case '$':
		case '^':
			return 6;
			break;
		case '#':
		case '(':
		case ')':
			return 1;
			break;
		default:
			return 0;
			break;
	}
}
int isNumber(char sym){
	if(sym>=48 && sym<=57)
		return 1;
	else return 0;
}

int isOperator(char sym){
	switch(sym) {
			case '+':
	        case '-':
	        case '*':
	        case '/':
	        case '^':
	        case '$':
	        case '&':
	        case '(':
	        case ')':
	        return 1;
			break;
		default:
	        return 0;
	    }
}
double calculator(char postfix[max],double x){
	int i=0;
	double val1,val2,sum=0.0;
	double tmp;
	emptyStackNd();
	while(postfix[i]!='\0'){
		if(isOperator(postfix[i])!=1){
			if(postfix[i]!='x')
				pushDb(postfix[i]-48);
			else
				pushDb(x);
		}
		else{
			val1=popDb();
			val2=popDb();
			switch(postfix[i]){
				case '+':
					sum=val1+val2;
					break;
				case '-':
					sum = val2 - val1;
					break;
				case '*':
					sum = val2*val1;
					break;
				case '/':
					sum = val2/val1;
					break;
			}
			pushDb(sum);
		}
		i++;	
	}
	return popDb();
}

double popDb(){
	topDb--;
	return stackDb[topDb+1];
}
void pushDb(double num){
	stackDb[++topDb]=num;
}
void emptyStackDb(){
	topDb=-1;
}

node*newNode(char a){
	node*tmp=(node*)malloc(sizeof(node));
	tmp->left=NULL;
	tmp->right=NULL;
	tmp->val=a;
	return tmp;
}
node*popNd(){
	topNd--;
	return stackNd[topNd+1];
}
void pushNd(node*nd){
	topNd++;
	stackNd[topNd]=nd;
}

node* createTree(char postfix[max]){
	node*root;
	node*tmp;
	int i=0;
	node* val1,*val2;
	while(postfix[i]!='\0'){
		if(isOperator(postfix[i])!=1){
			if(postfix[i]!='x'){
				tmp=newNode(postfix[i]);
				pushNd(tmp);
			}else{
				tmp=newNode('x');
				pushNd(tmp);
			}
		}
		else{
			val1=popNd();
			val2=popNd();
			switch(postfix[i]){
				case '+':
					root=newNode('+');
					root->left=val2;
					root->right=val1;
					break;
				case '-':
					root=newNode('-');
					root->left=val2;
					root->right=val1;
					break;
				case '*':
					root=newNode('*');
					root->left=val2;
					root->right=val1;
					break;
				case '/':
					root=newNode('/');
					root->left=val2;
					root->right=val1;
					break;
			}
			pushNd(root);
		}
		i++;	
	}
	return root;
}

double countTree(node*root, double x){
	if(root->left!=NULL && root->right!=NULL)
		switch(root->val){
			case '+': return countTree(root->left,x) + countTree(root->right,x);
			case '-': return countTree(root->left,x) - countTree(root->right,x);
			case '*': return countTree(root->left,x) * countTree(root->right,x);
			case '/': return countTree(root->left,x) / countTree(root->right,x);
		}
	else if(root->left!=NULL && root->right==NULL)
		return countTree(root->left,x);
	else if(root->left==NULL && root->right!=NULL)
		return countTree(root->right,x);
	else if(root->left==NULL && root->right==NULL){
		if(root->val=='x')
			return x;
		else return root->val-48;
	}
}
void printTree(node*root){
	if(root!=NULL){
		printTree(root->left);
		printTree(root->right);
		printf("%c",root->val);
	}
}
void emptyStackNd(){
	topNd=-1;
}