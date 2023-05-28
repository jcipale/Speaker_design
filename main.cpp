/*--------------------------------------------------------------------------------------------*/
/* SpeakerEasy - a command-line driven program to compute and plot speaker response data from */
/*               user-input daya or from stored speaker data contained within a soeaker data  */  
/*               base file stored co-located with the applicatin itself.                      */  
/*--------------------------------------------------------------------------------------------*/
/* Change log:                                                                                */  
/*--------------------------------------------------------------------------------------------*/
/* 05/13/2023:                                                                                */  
/* Begin initial cide development.                                                            */  
/*--------------------------------------------------------------------------------------------*/
/* 05/20/2023:                                                                                */  
/* Cleanup use of namespace with std::cout and std::endl.                                     */  
/* Begin coding main menu body and pointer initilization method.                              */  
/*--------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------*/
#include <algorithm>
#include <forward_list>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
     
#define extern
#include "speaker_easy.h"
#undef extern

#include "menus.h"

void create();
void display();
void insert_begin();
void insert_end();
void insert_pos();
void delete_begin();
void delete_end();
void delete_pos();
 
//using namespace std;
using std::cout;
using std::endl;

/*   Global Variables   */
char t_cmd[8];

struct node *start=NULL;

/*---------------------------------------------------------*/
int main()     
{
    /* The code below avoids the potentially messy "using namespace std" declaration */

	splash_screen();

	sleep(3);

    while (strcmp(t_cmd, "Q\n") != 0) {
		cout << "       +------------------------------------------+" << endl;
		cout << "       |               Program Menu               |" << endl;
		cout << "       +------------------------------------------+" << endl;
		cout << "       |  1) Speaker Parameters                   |" << endl;
		cout << "       |  2) Closed Box Design                    |" << endl;
		cout << "       |  3) Vented Box Design                    |" << endl;
		cout << "       |  4) Xover Design                         |" << endl;
		cout << "       |  5) Graph Performance                    |" << endl;
		cout << "       |  6) Write Speaker Data                   |" << endl;
		cout << "       |  7) Read Speaker Data                    |" << endl;
		cout << "       |  8) Exit                                 |" << endl;
		cout << "       +------------------------------------------+" << endl;
																									        		cout << "SpeakEasy: ";
																													fgets(t_cmd, 8, stdin);

        if ((strcmp(t_cmd, "S\n") == 0) || (strcmp(t_cmd, "s\n") == 0) || (strcmp(t_cmd, "1\n") == 0)) {
			cout << "test menu 1 - Speaker Parameters..." << endl;
			create();
		}

		if ((strcmp(t_cmd, "C\n") == 0) || (strcmp(t_cmd, "c\n") == 0) || (strcmp(t_cmd, "2\n") == 0)) {
			cout << "test menu 2 - Closed Box Design..." << endl;
			closed_box_design();
		}

		if ((strcmp(t_cmd, "V\n") == 0) || (strcmp(t_cmd, "v\n") == 0) || (strcmp(t_cmd, "3\n") == 0)) {
			cout << "test menu 3. - Vented Box Design.." << endl;
			vented_box_design();
		}

		if ((strcmp(t_cmd, "X\n") == 0) || (strcmp(t_cmd, "x\n") == 0) || (strcmp(t_cmd, "4\n") == 0)) {
			cout << "test menu 4 - Xover Design..." << endl;
			crossover_design();
		}

		if ((strcmp(t_cmd, "G\n") == 0) || (strcmp(t_cmd, "g\n") == 0) || (strcmp(t_cmd, "5\n") == 0)) {
			cout << "test menu 5 - Graph Performance.." << endl;
			graph_performance();
		}

		if ((strcmp(t_cmd, "W\n") == 0) || (strcmp(t_cmd, "w\n") == 0) || (strcmp(t_cmd, "6\n") == 0)) {
			cout << "test menu 6 - Write Speaker Data..." << endl;
			save_speaker_data();
		}

		if ((strcmp(t_cmd, "R\n") == 0) || (strcmp(t_cmd, "r\n") == 0) || (strcmp(t_cmd, "7\n") == 0)) {
			cout << "test menu 7 - Read Speaker Data..." << endl;
			read_speaker_data();
		}

		if ((strcmp(t_cmd, "E\n") == 0) || (strcmp(t_cmd, "e\n") == 0) || (strcmp(t_cmd, "8\n") == 0)) {
			cout << "test menu 8 - Exit program..." << endl;
			strcpy(t_cmd, "Q\n");
		}
	}

	exit_screen();
}
/*
void create()
{
        struct node *temp,*ptr;
        temp=(struct node *)malloc(sizeof(struct node));
        if(temp==NULL)
        {
                printf("nOut of Memory Space:n");
                exit(0);
        }
        printf("nEnter the data value for the node:t");
        //scanf("%d",&temp->Vol_box);
        scanf("%f",&temp->Vol_box);
        temp->next=NULL;
        if(start==NULL)
        {
                start=temp;
        }
        else
        {
                ptr=start;
                while(ptr->next!=NULL)
                {
                        ptr=ptr->next;
                }
                ptr->next=temp;
        }
}
*/
void display()
{
        struct node *ptr;
        if(start==NULL)
        {
                printf("nList is empty:n");
                return;
        }
        else
        {
                ptr=start;
                printf("nThe List elements are:n");
                while(ptr!=NULL)
                {
                        //printf("%dt",ptr->info );
                        printf("%dt",ptr->Vol_box );
                        ptr=ptr->next ;
                }
        }
}
void insert_begin()
{
        struct node *temp;
        temp=(struct node *)malloc(sizeof(struct node));
        if(temp==NULL)
        {
                printf("nOut of Memory Space:n");
                return;
        }
        printf("nEnter the data value for the node:t" );
        //scanf("%d",&temp->info);
        scanf("%f",&temp->Vol_box);
        temp->next =NULL;
        if(start==NULL)
        {
                start=temp;
        }
        else
        {
                temp->next=start;
                start=temp;
        }
}
void insert_end()
{
        struct node *temp,*ptr;
        temp=(struct node *)malloc(sizeof(struct node));
        if(temp==NULL)
        {
                printf("nOut of Memory Space:n");
                return;
        }
        printf("nEnter the data value for the node:t" );
        scanf("%f",&temp->Vol_box );
        temp->next =NULL;
        if(start==NULL)
        {
                start=temp;
        }
        else
        {
                ptr=start;
                while(ptr->next !=NULL)
                {
                        ptr=ptr->next ;
                }
                ptr->next =temp;
        }
}
void insert_pos()
{
        struct node *ptr,*temp;
        int i,pos;
        temp=(struct node *)malloc(sizeof(struct node));
        if(temp==NULL)
        {
                printf("nOut of Memory Space:n");
                return;
        }
        printf("nEnter the position for the new node to be inserted:t");
        scanf("%d",&pos);
        printf("nEnter the data value of the node:t");
        scanf("%f",&temp->Vol_box) ;
  
        temp->next=NULL;
        if(pos==0)
        {
                temp->next=start;
                start=temp;
        }
        else
        {
                for(i=0,ptr=start;i<pos-1;i++) { ptr=ptr->next;
                        if(ptr==NULL)
                        {
                                printf("nPosition not found:[Handle with care]n");
                                return;
                        }
                }
                temp->next =ptr->next ;
                ptr->next=temp;
        }
}
void delete_begin()
{
        struct node *ptr;
        if(ptr==NULL)
        {
                printf("nList is Empty:n");
                return;
        }
        else
        {
                ptr=start;
                start=start->next ;
                printf("nThe deleted element is :%ft",ptr->Vol_box);
                free(ptr);
        }
}
void delete_end()
{
        struct node *temp,*ptr;
        if(start==NULL)
        {
                printf("nList is Empty:");
                exit(0);
        }
        else if(start->next ==NULL)
        {
                ptr=start;
                start=NULL;
                printf("nThe deleted element is:%ft",ptr->Vol_box);
                free(ptr);
        }
        else
        {
                ptr=start;
                while(ptr->next!=NULL)
                {
                        temp=ptr;
                        ptr=ptr->next;
                }
                temp->next=NULL;
                printf("nThe deleted element is:%ft",ptr->Vol_box);
                free(ptr);
        }
}
void delete_pos()
{
        int i,pos;
        struct node *temp,*ptr;
        if(start==NULL)
        {
                printf("nThe List is Empty:n");
                exit(0);
        }
        else
        {
                printf("nEnter the position of the node to be deleted:t");
                scanf("%d",&pos);
                if(pos==0)
                {
                        ptr=start;
                        start=start->next ;
                        printf("nThe deleted element is:%ft",ptr->Vol_box  );
                        free(ptr);
                }
                else
                {
                        ptr=start;
                        for(i=0;i<pos;i++) { temp=ptr; ptr=ptr->next ;
                                if(ptr==NULL)
                                {
                                        printf("nPosition not Found:n");
                                        return;
                                }
                        }
                        temp->next =ptr->next ;
                        printf("nThe deleted element is:%ft",ptr->Vol_box );
                        free(ptr);
                }
        }
}
/*-------------------------------------------*/
