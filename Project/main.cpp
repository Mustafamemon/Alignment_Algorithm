#include"Local.h"
#include"Global.h"
#include"Semi_Global.h"
#include<iostream>
using namespace std;
int main()
{
	remove("Output.txt");
	Global("Input.txt", "Output.txt");
	Local("Input.txt", "Output.txt");
	Semi_Global("Input.txt", "Output.txt");
	return 0;
}
