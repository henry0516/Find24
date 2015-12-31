#include "Find24.h"
#define N 4
char opera[4] = { '/', '-', '*', '+' };

void main(){
	//Fraction v[N] = { Fraction(2), Fraction(3), Fraction(5), Fraction(4) };
	//Fraction v[N] = { Fraction(3), Fraction(3), Fraction(8), Fraction(8) };
	//Fraction v[N] = { Fraction(12), Fraction(7), Fraction(10), Fraction(10) };
	//Fraction v[N] = { Fraction(2), Fraction(3), Fraction(5), Fraction(12) };
	Fraction v[N];
	int inputValue;	
	
	cout << "Input Four Integers ";
	for (int i = 0; i < 4; ++i){
		cin >> inputValue;
		v[i].setValue(inputValue);
	}										
	
	char o[N] = {0};
	cout << "Your input ";
	for (int i = 0; i < N; ++i){
		 v[i].printValue();
		if (i != N-1){
			cout<< ",";
		}
	}
	cout << endl;
	
	permValue(v, 0);

	/*	
	Fraction v[N] = { Fraction(8), Fraction(3), Fraction(8), Fraction(3) };
	generate(v, opera); 
	*/
	system("pause");
}

void permValue(Fraction* num, int i) {
	if (i < N) {
		int j;
		for (j = i; j < N; j++) {
			Fraction to[N];
			copy(num, to);
			rotate(to, i, j);
			permValue(to, i + 1);
		}
	}
	else { 
		char o[N] = { 0 };
		permOperator(num, o, 0);		
	}
}

void rotate(Fraction* num, int i, int j) {
	Fraction tmp = num[j];
	int k;
	for (k = j; k > i; k--) {
		num[k] = num[k - 1];
	}
	num[i] = tmp;
}

void copy(Fraction* from, Fraction* to) {
	int i;
	for (i = 0; i < N; i++) {
		to[i] = from[i];
	}
}

void permOperator(Fraction* num, char* chr, int i){
	if (i < N-1) {		
		//for (int j = i; j < N; j++) {			
			for (int k = 0; k < N; ++k){			
				chr[i] = opera[k];
				char to[N];
				copyOperator(chr, to);
				permOperator(num, to, i + 1);
			}
		//}
	}
	else {
		//print(chr);
		generate(num, chr);
	}	
}

void copyOperator(char* from, char* to) {
	int i;
	for (i = 0; i < N; i++) {
		to[i] = from[i];
	}
}

void rotateOperator(char* chr, int i, int j) {	
	for (int k = j; k < i; ++k) {
		chr[k] = opera[j];
	}
}
void generate(Fraction vArray[], char oArray[]){
	Fraction TARGET(24, 1);
	Fraction ZERO(0, 1);
	Fraction temp;
	string result[13];
	string postfixStr[13];
	//case (((aOb)Oc)Od)	case1
	int parentheses[5][6] = {	{ 0, 1, 2, 6, 9, 12 },
	//case ((aO(bOc))Od)	case2
								{ 0, 1, 4, 8, 9, 12 },
	//case (aO((bOc)Od))	case3
								{ 0, 3, 4, 8, 11, 12 },
	//case (aO(bO(cOd)))	case4
								{ 0, 3, 6, 10, 11, 12 },
	//case ((aOb)O(cOd))	case5
								{ 0, 1, 7, 5, 11, 12 }};	
	int vIndex;
	int oIndex;
	for (int i = 0; i < 13; ++i){		
		result[i] = " ";
	}
	for (int j = 0; j < 5; ++j){
		vIndex = 0;
		oIndex = 0;		
		for (int i = 0; i < 13; ++i){
			result[i] = " ";
			for (int k = 0; k < 6; ++k){							
				if (i == parentheses[j][k]){
					if (k < 3){
						result[i] = "(";						
					}
					else{
						result[i] = ")";
					}
				}
			}	
			if (result[i].compare(" ") == 0 && (vIndex < 4 && oIndex < 4)){
				if (vIndex == oIndex){
					result[i] = vArray[vIndex++].returnValue();			
				}
				else{
					result[i] = oArray[oIndex++];
				}				
			}			
		}		
		//postfix
		inToPostfix(result, postfixStr);	
		if (computePostfix(postfixStr).compare("24") == 0){
			/*cout <<" posfix ";
			for (int i = 0; i < 13; ++i){
				cout << postfixStr[i];
			}
			cout << " ";*/
			for (int i = 0; i < 13; ++i){
				cout << result[i];
			}
			cout <<"=24"<<endl;
		}	
		
		}
		for (int i = 0; i < 13; ++i){
			postfixStr[i] = "";
		}		

}

void inToPostfix(string* infix, string* postfix) {
	char stack[13] = { '\0' };
	int i, j, top;
	for (i = 0, j = 0, top = 0; i<13; i++) {				
		char temp = infix[i].c_str()[0];
		switch (temp){
			case '(':              // 運算子堆疊 
				stack[++top] = temp;
			break;
			case '+': case '-': case '*': case '/':
				while (priority(stack[top]) >= priority(temp)) {
					postfix[j++] = stack[top--];
				}
				stack[++top] = temp; // 存入堆疊 
				break;
			case ')':
				while (stack[top] != '(') { // 遇 ) 輸出至 ( 
					postfix[j++] = stack[top--];
				}
				top--;  // 不輸出 ( 
				break;
			default:  // 運算元直接輸出 
				postfix[j++] = infix[i];
				//postfix[j++] = temp;				
		}
	}
	while (top > 0) {
		postfix[j++] = stack[top--];
	}
	
}

int priority(char op) {
	switch (op) {
		case '+': case '-': return 1;
		case '*': case '/': return 2;
		default:            return 0;
	}
}

string computePostfix(string* source){
	Fraction stack[4];
	Fraction tempResult;
	for (int i = 0, top = 0; i < 7; ++i){		
		char temp = source[i].c_str()[0];
		switch (temp){
			case '+':						
				tempResult = stack[top - 2] + stack[top - 1];			
				//cout << stack[top - 2].returnValue() << "," << stack[top - 1].returnValue() << tempResult.returnValue() << endl;
				top-=2;				
				stack[top++] = tempResult;
				break;
			case '-': 			
				tempResult = stack[top - 2] - stack[top - 1];			
				//cout << stack[top - 2].returnValue() << "," << stack[top - 1].returnValue() << tempResult.returnValue() << endl;
				top -= 2;
				stack[top++] = tempResult;
				break;
			case '*': 			
				tempResult = stack[top - 2] * stack[top - 1];	
				//cout << stack[top - 2].returnValue() << "," << stack[top - 1].returnValue() << tempResult.returnValue() << endl;
				top -= 2;
				stack[top++] = tempResult;	
				break;
			case '/':							
				try {
					tempResult = stack[top - 2] / stack[top - 1];
				}
				catch (std::logic_error){
					cout << "divide by zero"<<endl;
				}				
				//cout << stack[top - 2].returnValue() << "," << stack[top - 1].returnValue() << tempResult.returnValue() << endl;
				top -= 2;
				stack[top++] = tempResult;
				break;
			default:
				//cout << "[" << atoi(source[i].c_str()) << "]";
				stack[top++] = Fraction(atoi(source[i].c_str()));
		}		
	}
	return stack[0].returnValue();
}

int gcd(int m, int n) {
	while (n != 0) {
		int r = m % n;
		m = n;
		n = r;
	}
	return m;
}

int lcm(int m, int n) {
	return m * n / gcd(m, n);
}
