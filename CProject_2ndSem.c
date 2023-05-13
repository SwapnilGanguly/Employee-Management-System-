#include <stdio.h>
#include <stdlib.h>

//Structure containing employee id, name, job title and salary
typedef struct employee{
	int id;
	char name[20];
	char job[20];
	float salary;
}employee;

//Function to create account(s)
void create(){
	employee *s;
	FILE *fp;
	int n, i;
	printf("Enter number of employees: ");
	scanf("%d",&n);	
	s = (employee*)calloc(n, sizeof(employee));
	fp = fopen("employee.txt","w");

	for(i=0;i<n;i++){
		printf("EMPLOYEE %d\n",(i+1));
		printf("Enter employee id:\t");
		scanf("%d",&s[i]);
		fflush(stdin);
		printf("Enter name:\t\t");
		scanf("%[^\n]s",&s[i].name);
		printf("Enter salary:\t\t");
		scanf("%f",&s[i].salary);
		printf("Enter job title:\t");
		scanf("%s",&s[i].job);
		fwrite(&s[i],sizeof(employee),1,fp);
	}
	fclose(fp);
}

//Function to display the records
void display(){
	employee s1;
	FILE *fp;
	fp = fopen("employee.txt","r");
	printf("ID\tNAME\t\t   JOB\t\t\tSALARY");
	while(fread(&s1,sizeof(employee),1,fp)){
		printf("\n%-5d%-20s%-20s%-10f",s1.id,s1.name,s1.job,s1.salary);
	}
	fclose(fp);
}

//Function to add a new record
void append(){
	employee *s;
	FILE *fp;
	int n, i;
	printf("Enter number of employees: ");
	scanf("%d",&n);	
	s = (employee*)calloc(n, sizeof(employee));
	fp = fopen("employee.txt","a");

	for(i=0;i<n;i++){
		printf("EMPLOYEE %d\n",(i+1));
		printf("Enter employee id:\t");
		scanf("%d",&s[i]);
		fflush(stdin);
		printf("Enter name:\t\t");
		scanf("%[^\n]s",&s[i].name);
		printf("Enter salary:\t\t");
		scanf("%f",&s[i].salary);
		printf("Enter job title:\t");
		scanf("%s",&s[i].job);
		fwrite(&s[i],sizeof(employee),1,fp);
	}
	fclose(fp);
}

//Function to calculate and display the number of records
void noofrec(){
	employee s1;
	FILE *fp;
	fp = fopen("employee.txt","r");
	fseek(fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(employee);
	printf("\n\nNO. OF RECORDS = %d",n);
	fclose(fp);	
}

//Function to search for a particular record(account)
void search(){
	employee s1;
	FILE *fp;
	int id, found=0;
	fp = fopen("employee.txt","r");
	printf("Enter employee id to search: ");
	scanf("%d",&id);
	
	while(fread(&s1,sizeof(employee),1,fp)){
		if(s1.id==id){
			found = 1;
			printf("\n%-5d%-20s%-20s%-10f",s1.id,s1.name,s1.job,s1.salary);
		}
	}
	if(!found)
		printf("\nRECORD NOT FOUND\n");
	fclose(fp);
}

//Function to update a particular record
void update(){
	employee s1;
	FILE *fp, *fp1;
	int id, found=0;
	fp = fopen("employee.txt","r");
	fp1 = fopen("temp.txt","w");
	printf("Enter employee id to update: ");
	scanf("%d",&id);
	
	 
	while(fread(&s1,sizeof(employee),1,fp)){
		if(s1.id==id){
			found = 1;
			fflush(stdin);
		printf("Enter name:\t\t");
		scanf("%[^\n]s",&s1.name);
		printf("Enter salary:\t\t");
		scanf("%f",&s1.salary);
		printf("Enter job title:\t");
		scanf("%s",&s1.job);
		
		
		}
		fwrite(&s1,sizeof(employee),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	if(found){
		fp1 = fopen("temp.txt","r");
		fp = fopen("employee.txt","w");
		
		while(fread(&s1,sizeof(employee),1,fp1)){
			fwrite(&s1,sizeof(employee),1,fp);
		}
		
		fclose(fp);
		fclose(fp1);
	}
	
}

//Function to delete a record(account)
void deleterec(){
	employee s1;
	FILE *fp, *fp1;
	int j, id, found=0;
	fp = fopen("employee.txt","r");
	fp1 = fopen("temp.txt","w");
	printf("Enter employee id to delete: ");
	scanf("%d",&id);
	 
	while(fread(&s1,sizeof(employee),1,fp)){
		if(s1.id==id){
			found = 1;
		}
		else
			fwrite(&s1,sizeof(employee),1,fp1);

		
	}
	fclose(fp);
	fclose(fp1);
	if(found){
		fp1 = fopen("temp.txt","r");
		fp = fopen("employee.txt","w");
		
		while(fread(&s1,sizeof(employee),1,fp1)){
			fwrite(&s1,sizeof(employee),1,fp);
		}
		
		fclose(fp);
		fclose(fp1);
	}
	
}

//main(), from where the execution starts
int main()
{
	printf("WELCOME TO OUR EMPLOYEE MANAGEMENT SOFTWARE!");
	int ch;
	do{
		printf("\n\n1. CREATE ACCOUNT(S)");
		printf("\n2. DISPLAY DATABASE");
		printf("\n3. APPEND NEW EMPLOYEE DATA");
		printf("\n4. NO. OF RECORDS");
		printf("\n5. SEARCH FOR AN EMPLOYEE");
		printf("\n6. UPDATE EMPLOYEE DATA");
		printf("\n7. DELETE RECORDS OF AN EMPLOYEE");
		printf("\n0. EXIT FROM SYSTEM");
		printf("\n\nEnter your choice: ");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1: create();
					break;
			case 2: display();
					break;
			case 3: append();
					break;
			case 4: noofrec();
					break;
			case 5: search();
					break;
			case 6: update();
					break;
			case 7: deleterec();
					break;
			case 0: printf("\nTHANK YOU!\n");
					return 0;
		}
	}while(ch!=0);
	return 0;	
}
