#ifndef SEMI_GLOBAL_H
#define SEMI_GLOBAL_H

#include<iostream>
#include<string>
#include<stack>
#include<fstream>
using namespace std;
int match_s=1 , m_match_s = -1 ,  flag_s=0;
stack<int> s_s;
int **fill_array_s(int row , int col)
{
	int **array = new int*[row+1];
	for(int i=0;i<row+1;i++)
	array[i]=new int[col+1];
	for(int i=0; i<row+1; i++)
		array[i][0]=-0;
	for(int j=0; j<col+1; j++)
		array[0][j]=-0;
	return array;
}
int **Semi_Global_alignment(string sequence1 , string sequence2 , int row , int col)
{
	int left , top , diagonal , greater;
	int **array=fill_array_s(row,col);
	for(int i=1;i<row+1;i++)
	{
		for(int j=1;j<col+1;j++)
		{
			left=array[i][j-1]-2;
			top=array[i-1][j]-2;
			if(sequence1[i-1]==sequence2[j-1])
			{
				diagonal=array[i-1][j-1]+match_s;
			}
			else
			{	
				diagonal=array[i-1][j-1]+m_match_s;	
			}
			if(left>top)
			{
				greater=left;
			}
			else
			{
				greater=top;
			}
			if(greater<diagonal)
			{
				greater=diagonal;
			}
			array[i][j]=greater;
		}
	}
	return array; 
}
int trace_back_s(string sequence1 , string sequence2 , int i , int j,int **array)
{
	int left , top , diagonal , greater,direction;
	left=array[i][j-1]-2;
	top=array[i-1][j]-2;
	if(sequence1[i-1]==sequence2[j-1])
	{
		diagonal=array[i-1][j-1]+match_s;	
	}
	else
	{	
		diagonal=array[i-1][j-1]+m_match_s;	
	}
//	cout<<left<<" "<<top<<" "<<diagonal<<endl;
	if(left>top)
	{
		direction=1;
		greater=left;
	}
	else
	{
		direction=2;
		greater=top;
	}
	if(greater<diagonal)
	{
		direction=3;
		greater=diagonal;
	}
	if(flag_s==0)
	{
		if(greater==diagonal && direction!=3)
		{
			flag_s=1;
			s_s.push(i-1); s_s.push(j-1);
		}
		else if(greater==top && direction!=2)
		{
			flag_s=1;
			s_s.push(i-1); s_s.push(j);
		}
		else if(greater==left && direction!=1)
		{
			flag_s=1;
			s_s.push(i); s_s.push(j-1);
		}
		if(flag_s==1)
		{
			s_s.push(i) ; s_s.push(j);
		}
	}
	return direction ;
}
void Ouput_Sequence_s(string sequence1 , string sequence2 , int row , int col, ofstream &output)
{
	char *O_sequence1 , *O_sequence2 ;
	int **array=Semi_Global_alignment(sequence1,sequence2,row,col);
	int i,j,temp=-2*col*row,high=row+col;
	O_sequence1=new char[high];
	O_sequence2=new char[high];
	i=row; j=col; 
	high--;
	again:
	while(i>0 && j>0)
	{
		int direction=trace_back_s(sequence1,sequence2,i,j,array);
		if(flag_s==1)
		{
			s_s.push(high);
			flag_s=2;
		}
			
		if(direction==1)
		{
			O_sequence1[high]='-';
			O_sequence2[high]=sequence2[j-1];
			j--;
		}
		else if(direction==2)
		{
			O_sequence1[high]=sequence1[i-1];
			O_sequence2[high]='-';
			i--;
		}
		else if(direction==3)
		{
			O_sequence1[high]=sequence1[i-1];
			O_sequence2[high]=sequence2[j-1];
			i--;
			j--;
		}
		high--;
	}
	while(i>0)
	{
		O_sequence1[high]=sequence1[i-1];
		O_sequence2[high]='-';
		i--;
		high--;
	}
	while(j>0)
	{
		O_sequence1[high]='-';
		O_sequence2[high]=sequence2[j-1];
		j--;
		high--;
	}
	for(int c=high+1;c<row+col;c++)
		output<<O_sequence1[c];
	output<<endl;
	for(int c=high+1;c<row+col;c++)
		output<<O_sequence2[c];
	if(!s_s.empty())
	{
		flag_s=0;
		output<<endl<<endl;
		high=s_s.top(); s_s.pop();
		int b=s_s.top(); s_s.pop();
		int a=s_s.top(); s_s.pop();
		j=s_s.top(); s_s.pop();
		i=s_s.top(); s_s.pop();
		if(a-1==i && b-1==j)
		{
			O_sequence1[high]=sequence1[a-1];
			O_sequence2[high]=sequence2[b-1];
		}
		else if(a-1==i)
		{
			O_sequence1[high]=sequence1[a-1];
			O_sequence2[high]='-';
		}
		else if(b-1==j)
		{
			O_sequence1[high]='-';
			O_sequence2[high]=sequence2[b-1];
		} 
		high--;
		goto again ;
	}
}
int Semi_Global(string filename, string filename1)
{
		ofstream output(filename1.c_str(), ios::app);
	ifstream input(filename.c_str());
	if(input && output)
	{
		output<<"\n\n**********Semi-Global_Alignment**********\n\n";
		string sequence1,sequence2;
		input>>sequence1;
		input>>sequence2;
		int row=sequence1.length();
		int col=sequence2.length();
		Ouput_Sequence_s(sequence1,sequence2,row,col, output);
	}
	else
	{
		cout<<"File not found!\n";
	}
	output.close();
	input.close();
}

#endif
