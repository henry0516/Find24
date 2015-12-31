#include <iostream>
#include <string>
#include <memory.h>

using namespace std;

int gcd(int m, int n);
int lcm(int m, int n);

class Fraction{
private:
	int denominator;
	int molecular;
public:
	Fraction(){
		molecular = 0;
		denominator = 1;
	}

	Fraction(int a){
		this->molecular = a;
		this->denominator = 1;
	}

	void setValue(int a){
		this->molecular = a;
		this->denominator = 1;
	}

	Fraction(int a, int b){
		this->molecular = a;
		this->denominator = b;
	}

	Fraction operator+(const Fraction &a){
		Fraction tar;
		//same denominator
		if (denominator == a.denominator){
			tar.molecular = this->molecular + a.molecular;
			tar.denominator = this->denominator;
		}
		else{
			if (this->denominator != 0 && a.denominator != 0){
				tar.denominator = lcm(this->denominator, a.denominator);
				tar.molecular = (this->molecular * (tar.denominator / this->denominator)) + (a.molecular * (tar.denominator / a.denominator));
			}
		}
		return tar;
	}

	Fraction operator+=(const Fraction &a){
		Fraction tar;
		//same denominator
		if (denominator == a.denominator){
			tar.molecular = this->molecular + a.molecular;
			tar.denominator = this->denominator;
		}
		else{
			if (this->denominator != 0 && a.denominator != 0){
				tar.denominator = lcm(this->denominator, a.denominator);
				tar.molecular = (this->molecular * (tar.denominator / this->denominator)) + (a.molecular * (tar.denominator / a.denominator));
			}
		}
		this->denominator = tar.denominator;
		this->molecular = tar.molecular;
		return tar;
	}

	Fraction operator-(const Fraction &a){
		Fraction tar;
		//same denominator
		if (denominator == a.denominator){
			tar.molecular = this->molecular - a.molecular;
			tar.denominator = this->denominator;
		}
		else{
			if (this->denominator != 0 && a.denominator != 0){
				tar.denominator = lcm(this->denominator, a.denominator);
				tar.molecular = (this->molecular * (tar.denominator / this->denominator)) - (a.molecular * (tar.denominator / a.denominator));
			}
		}
		return tar;
	}

	Fraction operator-=(const Fraction &a){
		Fraction tar;
		//same denominator
		if (denominator == a.denominator){
			tar.molecular = this->molecular - a.molecular;
			tar.denominator = this->denominator;
		}
		else{
			if (this->denominator != 0 && a.denominator != 0){
				tar.denominator = lcm(this->denominator, a.denominator);
				tar.molecular = (this->molecular * (tar.denominator / this->denominator)) - (a.molecular * (tar.denominator / a.denominator));
			}
		}
		this->denominator = tar.denominator;
		this->molecular = tar.molecular;
		return tar;
	}

	Fraction operator*(const Fraction &a){
		Fraction tar;
		tar.molecular = this->molecular * a.molecular;
		tar.denominator = this->denominator * a.denominator;
		return tar;
	}

	Fraction operator*=(const Fraction &a){
		Fraction tar;
		tar.molecular = this->molecular * a.molecular;
		tar.denominator = this->denominator * a.denominator;
		this->denominator = tar.denominator;
		this->molecular = tar.molecular;
		return tar;
	}

	Fraction operator/(const Fraction &a){
		Fraction tar;
		tar.molecular = this->molecular * a.denominator;
		tar.denominator = this->denominator * a.molecular;
		return tar;
	}

	Fraction operator/=(const Fraction &a){
		Fraction tar;
		tar.molecular = this->molecular * a.denominator;
		tar.denominator = this->denominator * a.molecular;
		this->denominator = tar.denominator;
		this->molecular = tar.molecular;
		return tar;
	}

	Fraction operator=(const Fraction &a){
		Fraction tar;
		this->molecular = a.molecular;
		this->denominator = a.denominator;
		tar.molecular = a.molecular;
		tar.denominator = a.denominator;
		return tar;
	}

	bool operator==(const Fraction &a){
		if (a.molecular == 0 && a.molecular == this->molecular){
			return true;
		}
		int gcdValue = gcd(this->molecular, this->denominator);
		if (gcdValue != 1){
			this->molecular /= gcdValue;
			this->denominator /= gcdValue;
		}
		if (a.molecular == this->molecular &&
			a.denominator == this->denominator)
			return true;
		else{
			return false;
		}
	}

	bool operator!=(const Fraction &a){
		if (a.molecular == 0 && a.molecular == this->molecular){
			return false;
		}
		int gcdValue = gcd(this->molecular, this->denominator);
		if (gcdValue != 1){
			this->molecular /= gcdValue;
			this->denominator /= gcdValue;
		}
		if (a.molecular == this->molecular &&
			a.denominator == this->denominator)
			return false;
		else{
			return true;
		}
	}

	void printValue(){
		int gcdValue = gcd(this->molecular, this->denominator);
		//cout << "gcd"<<gcdValue<<endl;
		if (gcdValue == 1){
			this->molecular = this->molecular / gcdValue;
			this->denominator = this->denominator / gcdValue;
		}
		if (this->denominator != 1){
			cout << this->molecular << "/" << this->denominator;
		}
		else{
			cout << this->molecular;
		}
	}

	string returnValue(){
		string result;
		int gcdValue = gcd(this->molecular, this->denominator);
		//cout << "gcd"<<gcdValue<<endl;
		if (gcdValue == 1){
			this->molecular = this->molecular / gcdValue;
			this->denominator = this->denominator / gcdValue;
		}
		if (this->denominator != 1){
			//	cout << this->molecular << "/" << this->denominator << endl;				
			//sprintf_s(result,"%d/%d\0",m,d);					
			result = result + to_string(this->molecular) + "/" + to_string(this->denominator);
		}
		else{
			//	cout << this->molecular << endl;
			result = result + to_string(this->molecular);
		}
		return result;
	}
};

void generate(Fraction vArray[], char oArray[]);
void swap(int *a, int *b);
void permOperator(int v[], int l);
void permValue(Fraction*, int);
void rotate(Fraction*, int, int);
void copy(Fraction*, Fraction*);
void print(Fraction*);
void permOperator(Fraction* num, char* chr, int i);
void copyOperator(char* from, char* to);
void inToPostfix(string* infix, string* postfix);
int priority(char op);
string computePostfix(string* source);