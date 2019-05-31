#include <stdio.h>
#include <stdlib.h>
#include <conio.h>		
#include <string.h>	
#define PUPIL 10	
#define COURSE 5	
#define TITLE  7	
#define LENGTH 12
#define eLENGTH 20
struct Transcript
{
	char idnum[LENGTH];
	char cname[LENGTH];
	char ename[eLENGTH];
	int score[COURSE];
	char grade[COURSE];
	double average;
	double gpa;
	int rank;
};
typedef struct Transcript Transcripts;
FILE *fptr;
char subject[TITLE][LENGTH];
char esubject[TITLE][eLENGTH];	
int credit[COURSE];	
Transcripts cc1b[PUPIL];
double mean[COURSE];
double gpamean[COURSE];
int total = 0;
int show = 0;
void OpenFile( char fn[] );		
void ReadFile();
void Grade();
void Average();
void Ranking();
void PrintScore();
void Menu();
void Sorting(int choice);
int main(int argc, char *argv[])
{    
	char option;
	int choice,k;
	OpenFile("mydata4.txt");
	ReadFile();
	fclose(fptr);
	Grade();
	Average();
	Ranking();
	choice = 1;
	do
	{   
		Sorting(choice);
		PrintScore();
		Menu();
		do
			{  
				option = getch();
			} 
		while (option < '0' || option > '9');
		putch(option);
		if('1' <= option && option <= '9')
			choice = option - '0';
		else
			if(option == '0')
			{
				show = show ^ 1;
			 } 
	} 
	while (choice != 9);
	if(show==0)
	{
		printf("\n\n..再見..\n\n");
	}
	else
		printf("\n\n..Bye-Bye..\n\n");
	system("PAUSE");
	return 0;
}
void OpenFile( char fn[] )
	{	fptr = fopen(fn, "rt");
		if (!fptr)
		{   printf("輸入檔案 %s 開檔失敗!!!  \n", fn);
			system("PAUSE");
			exit(1);
		}	

	}
void ReadFile()
	{	int i, j, k;
		for (k=0; k<TITLE; k++)		
			fscanf(fptr, "%s", subject[k]);
		for (k=0; k<TITLE; k++)
		    fscanf(fptr, "%s", esubject[k]);
		for (j=0; j<COURSE; j++)
			fscanf(fptr, "%d", &credit[j]);
		for (i=0; i<PUPIL; i++)
			{   fscanf(fptr, "%s", cc1b[i].idnum);
				fscanf(fptr, "%s", cc1b[i].cname);
				fgets(cc1b[i].ename, 20, fptr);
				for (j=0; j<COURSE; j++)	
					fscanf(fptr, "%d", &cc1b[i].score[j]);
			}
	}
void Grade()
{
	int i,j,k;
	double point[COURSE],total=0,totalmean[COURSE];
	for(i=0;i<PUPIL;i++)
	{
		for(j=0;j<COURSE;j++)
		{
			if(cc1b[i].score[j]>=80)
			{
				cc1b[i].grade[j] = 'A';
				point[j]=4;
			}
			else if(cc1b[i].score[j]<80&&cc1b[i].score[j]>=70)
			{
				cc1b[i].grade[j] = 'B';
				point[j]=3;
			}
			else if(cc1b[i].score[j]<70&&cc1b[i].score[j]>=60)
			{
				cc1b[i].grade[j] = 'C';
				point[j]=2;
			}
			else if(cc1b[i].score[j]<60&&cc1b[i].score[j]>=50)
			{
				cc1b[i].grade[j] = 'D';
				point[j]=1;
			}
			else
			{
				cc1b[i].grade[j] = 'E';
				point[j]=0;
			}
		}
		for(j=0;j<COURSE;j++)
		{
			total += point[j]*credit[j];
			totalmean[j] += point[j];
		}
		cc1b[i].gpa = total / 12;
		
		total = 0;
		for(j=0;j<COURSE;j++)
		{
		 point[j]=0; 
	}	
}
	for(j=0;j<COURSE;j++)
		{
			gpamean[j] = totalmean[j]/PUPIL;
		}
}
void Average()
	{   int i, j;
		int sum;
		total = 0;
		for (j=0; j<COURSE; j++)
			total += credit[j];	
		for (i=0; i<PUPIL; i++)		
			{   
				sum = 0;
				for (j=0; j<COURSE; j++)
					sum += cc1b[i].score[j] * credit[j];
				cc1b[i].average = 1.0 * sum/ total;
			}
		for (j=0; j<COURSE; j++)
			{   
				sum=0;
				for (i=0; i<PUPIL; i++)
					sum += cc1b[i].score[j];
				mean[j] = 1.0 * sum / PUPIL;
			}
	}
void Ranking()
{
	int i,pass;
	double ave[PUPIL],aveg[PUPIL],t1,t2;
	if(show==0)
	{
		for(i = 0;i<PUPIL;i++)
		{
			ave[i] = cc1b[i].average;
		}
		for(pass=1;pass<PUPIL;pass++)
		{
			for(i=0;i<PUPIL-pass;i++)
			{
				if(ave[i]<ave[i+1])
				{
					t1 = ave[i];
					ave[i] = ave [i+1];
					ave[i+1] = t1;
				}		
			}
		}
		for(i=0;i<PUPIL;i++)
		{
			for(pass=0;pass<PUPIL;pass++)
			{
				if(ave[i]==cc1b[pass].average)
				{
					cc1b[pass].rank=i+1;
				}
			}
		}
	}
	else
	{
		for(i = 0;i<PUPIL;i++)
		{
			aveg[i]=cc1b[i].gpa;
		}
		for(pass=1;pass<PUPIL;pass++)
		{
			for(i=0;i<PUPIL-pass;i++)
			{
				if (aveg[i]<aveg[i+1])
				{
					t2=aveg[i];
					aveg[i]=aveg[i+1];
					aveg[i+1]=t2;
				}
			}
		}
		for(i=0;i<PUPIL;i++)
		{
			for(pass=0;pass<PUPIL;pass++)
			{
				if(aveg[i]==cc1b[pass].gpa)
				{
					cc1b[pass].rank=i+1;
				}
			}
		}
	}
}
void PrintScore()
	{    
		int i, j, k;
		printf("\n\n\n\n");
		for (k=1; k<102; k++)
			printf("=");
		printf("\n");
		if(show==0)
		{
			printf("%8s", subject[0]);
			printf("%9s", subject[1]);
			printf("%11s", subject[2]);
			printf("%7s", subject[3]);
			printf("%15s", subject[4]);
			for (k=5; k<TITLE; k++)
				printf("%11s", subject[k]);
			printf("%10s", "個人平均");
			printf("%10s\n","排名");
			printf("%18s", " ");
			printf("%8d", credit[0]);
			printf("%8d", credit[1]);
			for (j=2; j<COURSE; j++)
				printf("%12d", credit[j]);
			printf("%10d\n", total);
		}
		else
		{
			printf("%9s", esubject[0]);
			printf("%12s", esubject[1]);
			printf("%12s", esubject[2]);
			printf("%12s", esubject[3]);
			for(k=4;k<TITLE;k++)
				printf("%12s", esubject[k]);
			printf("%10s", "GPA");
			printf("%10s", "Rank\n");
			printf("%30d", credit[0]);
			printf("%12d", credit[1]);
			printf("%11d", credit[2]);
			for (j=3; j<COURSE; j++)
				printf("%12d", credit[j]);
			printf("%13d\n", total);
	}
		
		
		for (k=1; k<102; k++)
			printf("=");
		printf("\n");		
		if(show == 0)
		{
			for (i=0; i<PUPIL; i++)			
			{	
				printf("%10s", cc1b[i].idnum);		
				printf("%8s", cc1b[i].cname);
				printf("%8d", cc1b[i].score[0]);
				printf("%8d", cc1b[i].score[1]);
				for (j=2; j<COURSE; j++)
					printf("%12d", cc1b[i].score[j]);
				printf("%10.2lf", cc1b[i].average);
				printf("%11d\n",cc1b[i].rank);
		}
	}
		else
		{
			for(i=0;i<PUPIL;i++)
			{
				printf("%10s", cc1b[i].idnum);	
				printf("%8s", cc1b[i].ename);
				printf("%c", cc1b[i].grade[0]);
				printf("%12c", cc1b[i].grade[1]);
				printf("%11c", cc1b[i].grade[2]);
				printf("%12c", cc1b[i].grade[3]);
				printf("%12c", cc1b[i].grade[4]);
				printf("%14.2lf", cc1b[i].gpa);
				printf("%8d\n",cc1b[i].rank);
			}
			
		}
		for (k=1; k<102; k++)
			printf("=");
		printf("\n");
		if(show == 0)
		{
			printf("%19s", " ");
			printf("%8.2lf", mean[0]);
			printf("%8.2lf", mean[1]);
			for (j=2; j<COURSE; j++)
				printf("%12.2lf", mean[j]);
			printf("\n");
		}
		else
		{
			printf("%19s", " ");
			printf("%14.2lf",gpamean[0]);
			printf("%12.2lf",gpamean[1]);
			printf("%11.2lf",gpamean[2]);
			printf("%12.2lf",gpamean[3]);
			printf("%12.2lf",gpamean[4]);
			printf("\n");
		}
		for (k=1; k<102; k++)
			printf("=");
		printf("\n\n");
	}

void Menu()
	{
		if(show == 0)
		{
			printf("排序 (從小到大與從大到小) 依據指定項目：\n\n");
			printf("0.切換成英文成績表\n");
			printf("1.學號 (從小到大)\n");
			printf("2.姓名 (從小到大)\n");
			printf("3.微積分 (從大到小)\n");
			printf("4.物理 (從大到小)\n");
			printf("5.計算機導論 (從大到小)\n");
			printf("6.通訊導論 (從大到小)\n");
			printf("7.電通英文 (從大到小)\n");
			printf("8.個人平均 (從大到小)\n");
			printf("9.離開並結束程式\n\n");
			printf("你的選項是(1,…,9)? ");
		}
		else
		{
			printf("Sorting in ascending/descendant order according to assignment\n\n");
			printf("0.Transfer to the transcript in Chinese\n");
			printf("1.IdNumber (in ascending order)\n");
			printf("2.Name (in ascending order)\n");
			printf("3.Claculatus (in descendant order)\n");
			printf("4.Physics (in descendant order)\n");
			printf("5.Computers (in descendant order)\n");
			printf("6.Comunications (in descendant order)\n");
			printf("7.English (in descendant order)\n");
			printf("8.Average (in descendant order)\n");
			printf("9.Escape and terminate the program\n\n");
			printf("What's your choice(0,…,9)? ");
		}
	}
void Sorting(int choice)
	{    
		char t1[LENGTH],e1[eLENGTH],e2;
		int t2;
		double t3,e3,t4,e4;
		int pass, j, k;
		for (pass = 1; pass < PUPIL; pass++)
		for (j = 0; j < PUPIL - pass; j++)
		{
			if(show==0)
			{
				if ((strcmp(cc1b[j].idnum, cc1b[j+1].idnum) > 0 && choice == 1) ||
				(strcmp(cc1b[j].cname, cc1b[j+1].cname) > 0 && choice == 2) ||
				(cc1b[j].score[choice-3] < cc1b[j+1].score[choice-3]&& choice > 2 && choice < 8) ||
				(cc1b[j].average < cc1b[j+1].average && choice == 8))
				{
					strcpy(t1, cc1b[j].idnum);
					strcpy(cc1b[j].idnum, cc1b[j+1].idnum);	
					strcpy(cc1b[j+1].idnum, t1);											
					strcpy(t1, cc1b[j].cname);
					strcpy(cc1b[j].cname, cc1b[j+1].cname);					
					strcpy(cc1b[j+1].cname, t1);
						for (k = 0; k < COURSE; k++)			
						{
							t2 = cc1b[j].score[k];							
							cc1b[j].score[k] = cc1b[j+1].score[k];						
							cc1b[j+1].score[k] = t2;
							cc1b[j].rank = pass;
							}
					t3 = cc1b[j].average;
					cc1b[j].average = cc1b[j+1].average;						
					cc1b[j+1].average = t3;	
					t4 = cc1b[j].rank;
					cc1b[j].rank = cc1b[j+1].rank;
					cc1b[j+1].rank = t4;
			}
		}
			else
			{
				if ((strcmp(cc1b[j].idnum, cc1b[j+1].idnum) > 0 && choice == 1) ||
				(strcmp(cc1b[j].ename, cc1b[j+1].ename) > 0 && choice == 2) ||
				(cc1b[j].grade[choice-3] > cc1b[j+1].grade[choice-3]&& choice > 2 && choice < 8) ||
				(cc1b[j].gpa < cc1b[j+1].gpa && choice == 8))
				{  
					strcpy(t1, cc1b[j].idnum);
					strcpy(cc1b[j].idnum, cc1b[j+1].idnum);	
					strcpy(cc1b[j+1].idnum, t1);		
					strcpy(e1, cc1b[j].ename);
					strcpy(cc1b[j].ename, cc1b[j+1].ename);
					strcpy(cc1b[j+1].ename, e1);						
					for (k = 0; k < COURSE; k++)			
						{					
							e2 = cc1b[j].grade[k];
							cc1b[j].grade[k] = cc1b[j+1].grade[k];
							cc1b[j+1].grade[k] = e2;				
						}							
					e3= cc1b[j].gpa;
					cc1b[j].gpa = cc1b[j+1].gpa;
					cc1b[j+1].gpa = e3;
					e4 = cc1b[j].rank;
					cc1b[j].rank = cc1b[j+1].rank;
					cc1b[j+1].rank = e4; 
					
			}
			}
		}
	}
