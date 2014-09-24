#include <stdio.h>
#include <string.h>
#define max 255

int top =-1;
int topDb=-1;
char stack[max];
double stackDb[max];


double popDb();
void pushDb(double num);
void emptyStackDb();

void infixToPrefix(char infix[max], char prefix[max]);
void reverse(char array[max]);
char pop();
void push(char sym);
void emptyStack();
int isOperator(char sym);
int isNumber(char sym);
int prcd(char sym);
double calculator(char prefix[max],double x);





int main(){
	double f;
	char infix[max], prefix[max],temp;
	printf("Enter f(x) operator: ");
	scanf("%s",infix);
	printf("Enter x value: ");
	scanf("%lf",&f);
	infixToPrefix(infix,prefix);
	printf("in Reverse Polish notation: ");
	puts(prefix);
	f=calculator(prefix,f);
	printf("The result: %0.1lf\n",f);
}




void infixToPrefix(char infix[max], char prefix[max]){
	emptyStack();
	int i=0,j=0;
	while(infix[i]!='\0'){
		if(isOperator(infix[i])!=1){ // if is operand
			prefix[j++]=infix[i];
		}else if(infix[i]== '(')
			push(infix[i]);
		else if(infix[i]==')'){
			while(stack[top]!='(')
				prefix[j++]=pop();
			top--;
		}else{
			while(top!=-1 && prcd(infix[i])<=prcd(stack[top]))
				prefix[j++]=pop();
			push(infix[i]);
		}
		i++;
	}
	while(top!=-1)
		if(stack[top]!=')' || stack[top]!='(')
			prefix[j++]=pop();
		else top--;
	prefix[j]='\0';
}

// void infixToPrefix(char infix[max], char prefix[max]){
// 	emptyStack();
// 	int i=0,j=0;
// 	while(infix[i]!='\0'){
// 		if(isOperator(infix[i])==1){
// 			if(top!=-1 && infix[i]==')')
// 				while(stack[top]!='(' )
// 					prefix[j++]=pop();
// 			else
// 			while(top!=-1 && prcd(infix[i])<=prcd(stack[top]))
// 				prefix[j++]=pop();
// 			push(infix[i]);
// 		}else if(isOperator(infix[i])!=1) 
// 			prefix[j++] = infix[i];
// 		else if(infix[i]=='(')
// 			push(infix[i]);
// 		else if(infix[i]==')'){
// 			do{
// 				prefix[j]=pop();
// 			}while(prefix[j]!='(');
// 		}
// 		i++;
// 	}	
// 	while(top!=-1)
// 		prefix[j++]=pop();
// 	prefix[j]='\0';
// }

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
double calculator(char prefix[max],double x){
	int i=0;
	double val1,val2,sum=0.0;
	double tmp;
	emptyStack();
	while(prefix[i]!='\0'){
		if(isOperator(prefix[i])!=1){
			if(prefix[i]!='x')
				pushDb(prefix[i]-48);
			else
				pushDb(x);
		}
		else{
			val1=popDb();
			val2=popDb();
			switch(prefix[i]){
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