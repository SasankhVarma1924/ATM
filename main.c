#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
//#include <windows.h>
FILE *p,*q;
int balance;
unsigned int generate_acc()
{
	unsigned int digit,acc_no=0;
	for(int i=1;i<=9;i++)
	{
		digit=rand()%10;
		if(digit==0&&i==1)
		  digit=1;
		acc_no=(acc_no*10)+digit;
	}
	return acc_no;
}
int generate_pin()
{
	int acc_pin=0,digit;
	for(int i=1;i<=4;i++)
	{
		digit=rand()%10;
		if(digit==0)
		   digit=1;
		acc_pin=(acc_pin*10)+digit;
	}
	return acc_pin;
}
void create_account()
{
	q=fopen("acc_details.txt","a");
	unsigned int acc=generate_acc();
    int pin=generate_pin();
    printf("Please wait your Account Number and Pin Number are generating");

        for(int i=0;i<7;i++)
    {
      	printf(".");
        usleep(500000);
    }
    printf("\nYOUR ACCOUNT NO : %u",acc);
    printf("\nYOUR PIN NO : %d\n",pin);
    int amount;
    printf("Enter amount to deposit to your account : ");
    scanf("%d",&amount);
    fprintf(q,"%u:%d:%d\n",acc,pin,amount);
    fclose(q);
}
void bala(int n)
{
	int ba=0;
	q=fopen("acc_details.txt","r");
	fseek(q,n,0);
	char c;
	while(!feof(q))
	{
		c=fgetc(q);
		if(c=='\n')
		{
			break;
		}
		else
		{
		    ba=(ba*10)+((int)c-48);
		}
	}
	balance=ba;
}
int verify_pin(int n)
{
	q=fopen("acc_details.txt","r");
	fseek(q,n,0);
	char e[5];
	printf("Enter the Pin : ");
	scanf("%s",&e);
	int len=strlen(e);
	if(len!=4)
	   return 0;
	char c,d[4];
	int i=0,j;
	while(!feof(q))
	{
		c=fgetc(q);
		if(c==':')
		{
		  j=strncmp(d,e,4);
		  if(j==0)
		  {
		  	int x=ftell(q);
		  	bala(x);
		  	fclose(q);
		  	return x;
		  }
		  break;
		}
		 d[i]=c;
		 i++;
	}
	fclose(q);
	return 0;
}
int verify_acc()
{
	q=fopen("acc_details.txt","r");
	char rc[10];
	printf("Enter the Account number : ");
	scanf("%s",&rc);
	int len=strlen(rc);
	if(len!=9)
	   return 0;
	char _c[9];
	int i=0,n,d;
	while(!feof(q))
	{
		char e=fgetc(q);
		if(e==':')
		{
		  d=strncmp(_c,rc,9);
		  if(d==0)
		  {
		      n=ftell(q);
		      fclose(q);
		      return n;
 	  	   break;
		  }
		  else
		  {
		  while(fgetc(q)!='\n')
		  {}
		  }
		  i=0;
		}
		else
		{
		   _c[i]=e;
		   i++;
		}
	}
	fclose(q);
	return 0;
}
void deposit()
{
   int amount;
   printf("Enter the amount to deposit : ");
   scanf("%d",&amount);
   balance=balance+amount;
}
void withdraw()
{
   int amount;
   printf("Enter the amount to withdraw : ");
   scanf("%d",&amount);
   if(amount>balance)
      printf("you only have %d\n",balance);
   else
      balance=balance-amount;
}
void update_details(int n)
{
	q=fopen("acc_details.txt","r");
	p=fopen("update.txt","w");
	while(!feof(q))
	{
	   char c=fgetc(q);
	   int x=ftell(q);
	   if(x==n)
	   {
	   	fputc(':',p);
	   	fprintf(p,"%d\n",balance);
	   	while(fgetc(q)!='\n'){}
	   }
	   else if(feof(q))
	       break;
	   else
	   {
	   	fputc(c,p);
	   }
    }
	fclose(p);
	fclose(q);
	q=fopen("acc_details.txt","w");
	p=fopen("update.txt","r");
	while(!feof(p))
	{
		char c=fgetc(p);
		if(feof(p))
		   break;
		fputc(c,q);
	}
	fclose(p);
	fclose(q);
}
void atm()
{
	char c;
	int choice;
	printf("Do you have an account(y/n): ");
	scanf("%c",&c);
	if(c=='n')
	  create_account();
	abcdef:
	do
	{
    int x=verify_acc();
	if(x==0){
	   printf("Please check your Acc no\n");
	   goto abcdef;
	}
	int y=verify_pin(x);
    if(y==0){
	   printf("Please check your Pin no\n");
	   goto abcdef;
    }
		printf("choose 1 : deposit\n");
		printf("choose 2 : withdraw\n");
		printf("choose 3 : check balance\n");
		printf("choose 4 : cancel\n");
		scanf("%d",&choice);
	switch(choice)
	{
		case 1:
		   deposit();
		   update_details(y);
		   break;
		case 2:
		   withdraw();
		   update_details(y);
		   break;
		case 3:
		   printf("The balance in your account is %d\n",balance);
		   break;
		case 4:
		   printf("THANK YOU , PLEASE VISIT AGAIN\n");

		   int qw=5;
     	   while(qw--){usleep(900000);}
		   system("cls");
		   break;
	}
	}while(choice!=0);
}
int main()
{
	srand(time(0));
	atm();
	return 0;
}