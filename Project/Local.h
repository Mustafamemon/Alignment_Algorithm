#ifndef LOCAL_H
#define LOCAL_H

#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int match_l=1 , m_match_l =-1 ,  gap_l=-2 , flag_l=0;
int backtrack_l(int **array,int i,int j,string seq1,string seq2);
int **fill_array_l(int row , int col)
{
	int **array = new int*[row+1];
	for(int i=0;i<row+1;i++)
	array[i]=new int[col+1];
	
	int gap_l1=0;
	
	for(int i=0;i<col+1;i++)
	{
		array[0][i]=gap_l1;
	
	}
	for(int i=1;i<row+1;i++)
	{
		array[i][0]=gap_l1;
	
	}
	
	return array ;
}


int **Local_alignment(string sequence1 , string sequence2 , int row , int col)
{
	int left , top , diagonal , greater ;
	
	
	int **array=fill_array_l(row,col);
	
	for(int i=1;i<row+1;i++)
	{
		for(int j=1;j<col+1;j++)
		{
			left=array[i][j-1]+gap_l;
			top=array[i-1][j]+gap_l;
			
			if(sequence1[i-1]==sequence2[j-1])
			{
				diagonal=array[i-1][j-1]+match_l;	
			}
			else
			{	
				diagonal=array[i-1][j-1]+m_match_l;	
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
			
			if(greater>0)
			array[i][j]=greater;
			else
			array[i][j]=0;
		}
	}
	return array;
	
}


void func_l(int **array,int i,int j,string seq1,string seq2, ofstream &output)
{
	char *out1=new char[i+j];
	char *out2=new char[i+j];
	
	int t=i+j;
	int x1=t;
	int y1=t;
	y1--;
	x1--;
	int temp=array[1][1];
	int x=0;
	int y=0;
	for(int a=1;a<=i;a++)
	{
		for(int b=1;b<=j;b++)
		{
			if(temp<array[a][b])
			{
				temp=array[a][b];
				x=a;
				y=b;
			}
		}
	}
	
	i=x;
	j=y;
	int place=0;
	int temp1=array[i][j];
		
	while(temp!=0)
	{
		place=backtrack_l(array,i,j,seq1,seq2);
		if(place==1)
		{
			out1[x1]='-';
			out2[y1]=seq2[j-1];
			j--;
			x1--;
			y1--;	
		}
		else if(place==2)
		{
			out1[x1]=seq1[i-1];
			out2[y1]='-';
			i--;
			x1--;
			y1--;
		}
		else if(place==3)
		{
			out1[x1]=seq1[i-1];
			out2[y1]=seq2[j-1];
			i--;
			j--;
			x1--;
			y1--;
		}
		
		temp=array[i][j];
	}
	
	for(int z=x1+1;z<t;z++)
	{
		output<<out1[z]<<" ";
	}
	output<<endl;
	
	for(int z=y1+1;z<t;z++)
	{
		output<<out2[z]<<" ";
	}
}


int backtrack_l(int **array,int i,int j,string seq1,string seq2)
{
	int up;
	int left;
	int diagnol;
	int greater;
	int direction;
	
	left=array[i][j-1]+gap_l;
	up=array[i-1][j]+gap_l;
	
	if(seq1[i-1]==seq2[j-1])
	diagnol=array[i-1][j-1]+match_l;
	
	else
	diagnol=array[i-1][j-1]+m_match_l;
	
	if(left>up)
	{
		direction=1;
		greater=left;
	}
	else
	{
		direction=2;
		greater=up;
	}
	
	if(diagnol>greater)
	{
		direction=3;
		greater=diagnol;
	}
	return direction;
}

int Local(string filename, string filename1)
{
	ofstream output(filename1.c_str(), ios::app);
	ifstream input(filename.c_str());
	if(input && output)
	{
		output<<"\n\n*************Local_Alignment*************\n\n";
		string sequence1,sequence2;
		input>>sequence1;
		input>>sequence2;
		int row=sequence1.length();
		int col=sequence2.length();
		int **array=Local_alignment(sequence1,sequence2,row,col);	
		func_l(array,row,col,sequence1,sequence2, output);
	}
	else
	{
		cout<<"File not found!\n";
	}
	output.close();
	input.close();
}

#endif
