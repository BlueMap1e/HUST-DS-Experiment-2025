#include"slink.h"
void initstack(sqstack &S){
	S.top=-1;
}

bool push(sqstack &S,char x){ 
	if(S.top==MAXSIZE-1) 
		return false; 
	S.data[++S.top]=x;
	return true;
}

bool pop(sqstack &S,char &x){ 
	if(S.top==-1) 
		return false;
	x=S.data[S.top--]; 
	return true; 
}

bool isempty(sqstack S) { 
	if(S.top==-1)
		return true; 
	else
		return false;
}


int main(){
	char str[50];
	scanf("%s",str);
	if(check(str))
		printf("匹配成功\n");
	else 
		printf("匹配失败\n");
}
