#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>



#define printDetails(bstree) printf("ISBN:%3d   Name:%15s   Supplier:%15s   Price:%5d    Quantity:%2d    Discount:%2.2f\n",bstree->data->ISBN,bstree->data->name,bstree->data->supplierName,bstree->data->price,bstree->data->quantity,bstree->data->discount);
typedef struct details
{
	int ISBN;
	char name[20];	//name of the medicine
	char supplierName[20];
	int price;
	float discount;
	int quantity;
	int diseaseNumber;	//no. of diseases cured by the given medicine
	char **disease;		//all the diseases cured by the medicine
}DETAILS;

typedef DETAILS NODE;

struct BSTREE
{
	struct details *data;
    struct BSTREE *left,*right;
};

typedef struct Transaction
{
    DETAILS data;
    struct TRANSACTION *next;
}TRANSACTION;

typedef struct
{
    int length;

}LENGTH;

typedef struct
{
    DETAILS details;
    LENGTH len;
    struct STACK *next;


}STACK;

typedef struct transactions{
	char S[50];
	int itemsCount;
	NODE* data;
	struct transactions* next;
}TRANS;

#include "034-assign12.c"
#include "007-assign12.c"
#include "090-assign12.c"
#include "033-assign12.c"


void admin()
{
    int OPTION=5,ISBN,len,check=-2;
	FILE *f = fopen("inventory.txt","r");
    DETAILS *node;
    STACK *head;

   head=make_inventory(f);
   head=Min_sort(head);
   printf("\nADMIN:\n\n");
   
   fclose(f);
   
   //sunil
   f = fopen("transactions.txt","r");
	char S[500];
	node=NULL;
	int j,k=0,i;
	char temp[2][500];
	TRANS *list,*new;
	list = NULL;
	
	while( fscanf(f,"%s",S) > 0 )
	{
		i=0;
		k=0;
		while( S[k] != '\0')
		{
			j=0;
			while(S[k] != ',')
			{
				temp[i][j] = S[k];
				k++;
				j++;
			}	
			temp[i][j] = '\0';
			k++;
			i++;
		}	

		new = (TRANS*) malloc(sizeof(TRANS));
		new->itemsCount = 0;
		strcpy(new->S,temp[0]);
		new->itemsCount = atoi(temp[1]);
		new->next = NULL;
		new->data = (NODE*) malloc(new->itemsCount * sizeof(NODE));
		//printf("%d-%s\n",new->itemsCount,new->S);

		for(i=0;i<new->itemsCount;i++)
		{
			fscanf(f,"%s ",S);
			//printf("%s\n",S);
			createItemTransaction( S,&(new->data[i]) ) ;
		}
		//printf("Reached\n");
		list=insert(list,new);	
	}
	int b;
	int a;
	char customername[100];
	char suppliername[100];
	char name[100];
	int y;
	int isbn;
	char dsuppliername[100];
	char dcustomername[100];
   
    fclose(f);
    while(OPTION!=8)
    {
    printf("Enter the required option\n");
	printf("1.Add to Inventory\n2.Delete Inventory by ISBN\n3.View Inventory\n4.View All Transactions\n5.Search transactions by Customer Name\n6.Search transactions by medicine name\n7.Update Admin Password\n8.Exit\n");
	printf("Enter your choice:");
    scanf("%d",&OPTION);
    printf("\n");

            switch(OPTION)
            {
               case 1:
               			system("clear");
                       head=add_inventory(head);
                       head=Min_sort(head);
                       break;
               case 2:
               		system("clear");
                   while(check!=1)
                   {
                       printf("\nEnter The  Correct ISBN To Be Deleted\n\n");
                       scanf("    %d",&ISBN);
                       check=check_ISBN(head,ISBN);
                       if(check==0)
                       printf("\nISBN Entered Does Not Exist......TRY AGAIN\n\n");
                       else if(check==1)
                       {
                           check=-1;
                           break;
                       }

                   }
                       head=delete_inventory(head,ISBN);
                       printf("\nInventory Got Deleted\n\n");
                       break;
               case 3:
               			system("clear");
                       view_inventory_details(head);
                       break;
                       
               case 4:
			{
				system("clear");
				ViewAllInventory(list);
				printf("\n");
				break;
			}

			case 5:
			{
				system("clear");
				printf("please enter the customerName to search:");
				scanf("%s",customername);				
				searchTransactionByCustomerName(list,customername);
				printf("\n");
				break;
			}

			case 6:
			{
				system("clear");
				printf("please enter the medicineName to search:");
				scanf("%s",name);
				searchTransactionByName(list,name);
				printf("\n");
				break;
			}

			case 7:
			{
				system("clear");
				updatePassword();
				/*printf("Displaying Last Five Transactions\n");
				displayLastFiveTransactions(list);
				printf("\n");*/
				break;
			}        
                       
               default:
               			system("clear");
               			f = fopen("inventory.txt","w");
						saveChangesFromLinkedList(head,f);
						fclose(f);
                        printf("\nThank You For Using.....\n\n");
                        break;
            }
     printf("..........................................................................................\n\n\n\n");
    }
}

void receptionist()
{
	int flag,operation,x;
	char S[100];
	struct BSTREE *root;
	FILE *f;

	root = createBST();

	flag = 1;
	while(flag == 1)
	{
		printf("Enter your choice\n");
		printf("1.View Inventory\n2.Search Medicine by name\n3.Search Medicine by Disease\n4.Search Medicine by ISBN\n5.Search by Supplier Name\n6.Search for quantity by name\n");
		printf("7.Search for quantity by ISBN\n8.Update discount by name\n9.Update discount by ISBN\n10.Add item to bill\n11.Remove item from bill\n12.Display current bill\n13.Display Last 5 Transactions\n14.Exit\n\n");
		scanf("%d",&operation);
		switch(operation)
		{
			case 1:
				system("clear");
				printf("The required inventory is:\n");
				viewInventory(root);
				break;
			case 2:
				system("clear");
				printf("Enter the name of the medicine to search with:\n");
				scanf("%s",S);
				searchByName(root,S);
				break;
			case 3:
				system("clear");
				printf("Enter the name of the disease to search with:\n");
				scanf("%s",S);
				searchByDisease(root,S);
				break;
			case 4:
				system("clear");
				printf("Enter the ISBN code to search with:\n");
				scanf("%d",&x);
				searchByISBNCode(root,x);
				break;
			case 5:
				system("clear");
				printf("Enter the supplier name to search with:\n");
				scanf("%s",S);
				searchBySupplierName(root,S);
				break;
			case 6:
				system("clear");
				printf("Enter the medicine name to search for the quantity:\n");
				scanf("%s",S);
				searchQuantityByName(root,S);
				break;
			case 7:
				system("clear");
				printf("Enter the ISBN code to search for the quantity:\n");
				scanf("%d",&x);
				searchQuantityByISBNCode(root,x);
				break;
			case 8:
				system("clear");
				printf("Enter the medicine name whose discount you want to update:\n");
				scanf("%s",S);
				printf("Enter new discount : ");
				updateDiscountByName(root,S);
				break;
			case 9:
				system("clear");
				printf("Enter the ISBN of the medicine whose discount you want to update:\n");
				scanf("%d",&x);
				printf("Enter new discount : ");
				updateDiscountByISBN(root,x);
				break;
			case 10:
				system("clear");
				addToTransaction(root);
				break;
			case 11:
				system("clear");
				removeMedicineFromTransaction();
				break;
			case 12:
				system("clear");
				displayTransaction();
				break;
			case 13:
				system("clear");
				displayLast5Transactions();
				break;
			default:
				system("clear");
				f = fopen("inventory.txt","w");
				saveChanges(root,f);
				fclose(f);
				flag = 0;
		};
	}
}

void  customer()
{
    int OPTION=5,ISBN,len,*count,dec;
    char coupon[10],name[20];
    float discount,*total;
	FILE *f = fopen("transactions.txt","a");
    DETAILS *node;
    STACK *head;

	 count=(int *)malloc(sizeof(int));
     total=(float *)malloc(sizeof(float));
     *count=0;
     *total=0;
     Display_Transaction_Coustmer(count,total);

     printf("\n\nBILL: %f\n\n",*total);

     printf("PRESS 1 To Avail Special Discount\nPRESS 2 To Make Payment\n");
     scanf("%d",&dec);
     if(dec==1)
     {
         printf("Enter The Coupon Code");
         scanf("%s",coupon);
         discount=Avail_Discount(coupon);
         if(discount==0)
         {
             printf("\n\nINVALID COUPON CODE\n\n");
         }
         else
         {
             *total -= (*total) * discount/100;
             printf("\n\nYour Total After Availing Discount\n\n");
         printf("\n\n%f\n\n",*total);
         }
     }

     else
     {
            printf("\n\n YOUR TOTAL BILL: %f\n\n",*total);
     }

     printf("Enter Your Name & Confirm Payment\n");
     scanf(" %[^\n]s",name);

     fprintf(f,"%s,",name);
     sprintf(name,"%d",*count);
     fprintf(f,"%s,\n",name);

     save_items(f);
     fclose(f);
}

void adminGateway()
{
	int passwordresult,count;
	count =0 ;
	do
	{
		count++;
		passwordresult = passwordVerification();
		switch(passwordresult)
		{
			
			case 0:
			{
				printf("\nAccess Granted!!!!Welcome back admin!!\n");
				admin();
				break;
			}
			default:
			{
				printf("\nAccess Denied!!! Incorrect password entered!!\nYou have %d tries remaining\n",3 - count );
				break;
			}
		}	
	}while(count < 3 && passwordresult != 0);  
	if(passwordresult != 0 && count >= 3)
	{
		printf("You have exhausted all your attempts\n"); 
		return;
	}
}

int main()
{
	int code = 0 ;
	
	printf("Medical store billing system\n\n");

	while(code != 4)
	{
		printf("1.Admin\n2.Receptionist\n3.Customer\n4.Exit\n\n");
		scanf("%d",&code);

		switch(code)
		{
			case 1:
				getch();
				system("clear");
				adminGateway();
				break;
			case 2:
				system("clear");
				receptionist();
				break;
			case 3:
				system("clear");
				customer();
				break;
			default:
				system("clear");
				break;
		};
	}
	return 0;
}