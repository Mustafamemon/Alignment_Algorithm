#ifndef GLOBAL_H
#define GLOBAL_H

#include<iostream>
#include<fstream>
#include<string>
#include<stack>
using namespace std;
int match_g=10 , m_match_g = -2 ,  gap_g=-5 , flag_g=0;
stack<int> s_g;
int **fill_array_g(int row , int col)
{
	int **array = new int*[row+1];
	for(int i=0;i<row+1;i++)
	array[i]=new int[col+1];
	int gap_g1=0;
	for(int i=0;i<col+1;i++)
	{
		array[0][i]=gap_g1;
		gap_g1=gap_g1+gap_g;
	}
	gap_g1=gap_g;
	for(int i=1;i<row+1;i++)
	{
		array[i][0]=gap_g1;
		gap_g1=gap_g1+gap_g;
	}
	return array ;
}
int **Global_alignment(string sequence1 , string sequence2 , int row , int col)
{
	int left , top , diagonal , greater ;
	int **array=fill_array_g(row,col);
	for(int i=1;i<row+1;i++)
	{
		for(int j=1;j<col+1;j++)
		{
			left=array[i][j-1]+gap_g;
			top=array[i-1][j]+gap_g;
			if(sequence1[i-1]==sequence2[j-1])
			{
				diagonal=array[i-1][j-1]+match_g;	
			}
			else
			{	
				diagonal=array[i-1][j-1]+m_match_g;	
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
int trace_back_g(string sequence1 , string sequence2 , int i , int j,int **array)
{
	int left , top , diagonal , greater,direction;
	left=array[i][j-1]+gap_g;
	top=array[i-1][j]+gap_g;
	if(sequence1[i-1]==sequence2[j-1])
	{
		diagonal=array[i-1][j-1]+match_g;	
	}
	else
	{	
		diagonal=array[i-1][j-1]+m_match_g;	
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
	if(flag_g==0)
	{
		if(greater==diagonal && direction!=3)
		{
			flag_g=1;
			s_g.push(i-1); s_g.push(j-1);
		}
		else if(greater==top && direction!=2)
		{
			flag_g=1;
			s_g.push(i-1); s_g.push(j);
		}
		else if(greater==left && direction!=1)
		{
			flag_g=1;
			s_g.push(i); s_g.push(j-1);
		}
		if(flag_g==1)
		{
			s_g.push(i) ; s_g.push(j);
		}
	}
	return direction ;
}
void Ouput_Sequence_g(string sequence1 , string sequence2 , int row , int col, ofstream &output)
{
	char *O_sequence1 , *O_sequence2 ;
	int **array=Global_alignment(sequence1,sequence2,row,col);
	int i,j,temp=gap_g*col*row,high=row+col;
	O_sequence1=new char[high];
	O_sequence2=new char[high];
	i=row; j=col; 
	high--;
	again:
	while(i>0 && j>0)
	{
		int direction=trace_back_g(sequence1,sequence2,i,j,array);
		if(flag_g==1)
		{
			s_g.push(high);
			flag_g=2;
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
	if(!s_g.empty())
	{
		flag_g=0;
		output<<endl<<endl;
		high=s_g.top(); s_g.pop();
		int b=s_g.top(); s_g.pop();
		int a=s_g.top(); s_g.pop();
		j=s_g.top(); s_g.pop();
		i=s_g.top(); s_g.pop();
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
int Global(string filename, string filename1)
{
	ofstream output(filename1.c_str(), ios::app);
	ifstream input(filename.c_str());
	if(input && output)
	{
		output<<"************Global_Alignment*************\n\n";
		string sequence1,sequence2;
		input>>sequence1;
		input>>sequence2;
		int row=sequence1.length();
		int col=sequence2.length();
		Ouput_Sequence_g(sequence1,sequence2,row,col, output);
	}
	else
	{
		cout<<"File not found!\n";
	}
	output.close();
	input.close();
}

#endif
