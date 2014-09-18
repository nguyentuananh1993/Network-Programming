#include <stdio.h>
#include <string.h>

int main(){
	float x;
	int i,n=-1;
	float ct;
	float sum=1;
	printf("Nhap n:");
	do{
	scanf("%d",&n);
	if(n<=0) printf("n must be large than or equal to 1\n");
	}while(n<=0);
	printf("Nhap x: ");
	scanf("%f",&x);
	ct=1;
	for(i=1;i<=n;i++){
			ct=ct*x/i;
			sum+=ct;
	}
	printf("%f",sum);
}
