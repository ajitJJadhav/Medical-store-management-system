/*
Data Structures Project
Semester II
Project P019 - Medical Store Management System
Arvind Deshraj

*/




/*
getch() function is used for taking in the password without echoing in the terminal
It is based on the <conio.h> implementation of getch() in Windows systems
It uses termios.h and unistd.h
*/
int getch() 
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}




/*
encodeDecodePassword()
We have encoded our passwords using a rot13 system where each alphabet is rotated by 13 places
Since we have rotated by 13 we can use the same encoding system for decoding as well simply by 
using a (% 26) to loop back alphabets
*/
void encodeDecodePassword(char str[])
{
	for(int i = 0; str[i] !='\0' ; i++)
	{
		if(str[i] >= 97  && str[i] <= 122 )
			str[i] = (str[i] - 'a'+ 13) % 26 + 'a';
		else if (str[i] >= 65 && str[i] <= 90)
			str[i] = (str[i] - 'A'+ 13) % 26 + 'A';
	}
}



/*
passwordVerification()
passwordVerification is the function used to test whether user has admin access or not
Here "user" enters the password and the encoded password is taken from the file and decoded
If password matches encoded string then user is given admin access
*/
int passwordVerification()
{
	char c,inputbuffer[20],password[20];
    int i=0;
    FILE *fp = fopen("notpassword.txt","r");
    fscanf(fp,"%s",password); // scans encoded password from file
    //printf("%s",password);
    encodeDecodePassword(password);
    //printf("%s",password);
    printf("Enter the password:\n");
	while( (c=getch())!= '\n')
	{ // termination for the while loop is the enter key
	
        inputbuffer[i] = c;
        if(inputbuffer[i] != 8)
           // printf("%c",'*');
        if(inputbuffer[i] == 8)
       	{
       	    //fflush(stdin)
       		//printf("%c %c",'\b','\b');
       		i--;
       		if(i < 0)
       		{
       		    i = 0 ; // incase user enters backspace too many times
            }
       	}
        i++;
    }
    inputbuffer[i] = '\0';
    fclose(fp);
    //printf(" %s\n",inputbuffer);
    return strcmp(inputbuffer,password);
}

/*
updatePassword() is the function created to change the admin password
Admin is verified by requesting the old password
Admin is then prompted for the new password which is then encoded and stored in the file */
void updatePassword()
{
	getch();//based on how the fnction is called this stops the program from bypassing the password input
	char newpassword[20],c;
	printf("Please enter the old password:\n");
	if(passwordVerification() == 0)
	{
		printf("Please enter the new password(max. 20 characters)\n(Passwords longer than 20 characters will be truncated)\n");
		int i = 0;
		while( (c=getch())!= '\n' && i < 20) // termination is enter and also to stop user from entering more than 20 charcters
		{
        	newpassword[i] = c;
        	//printf("%c",'*');
        	if(newpassword[i] == 8)
       		{
       		   // fflush(stdin);
       			//printf("%c %c",'\b','\b');
       			i--;
       			if( i < 0 )
       			{
       			    i = 0;
       			}
       		}
        	i++;
    	}
    	newpassword[i] = '\0'; // terminating the new password
    	//printf("%s",newpassword);
    	encodeDecodePassword(newpassword);
    	FILE *fp = fopen("notpassword.txt","w");
		fprintf(fp,"%s\n",newpassword);
		printf("Password succesfully updated!!!");
		fclose(fp);
	}
	else
	{
		printf("Password entered is incorrect!!!");
	}
}

struct Transaction *start = NULL;
/*start is the head pointer for the Transaction structure* used to store the current transaction */

/*searchByISBNAddToTransaction is the function used to add a medicine to the current transcation by searching for
the medicine in the BST using the ISBN code*/
void searchByISBNAddToTransaction(struct BSTREE *bstree, int searchISBN , struct Transaction *node,int quantity)
{

    if(bstree == NULL)
        return;

    if( bstree->data->ISBN == searchISBN )
    {
        if( bstree->data->quantity >= quantity )
        {
            node->data = *bstree->data;
            bstree->data->quantity -= quantity;
        }
        else
            printf("\nOnly %d medicines are available\n\n",bstree->data->quantity);//check if requested quantity exceeds available quantity
        return;
    }
    searchByISBNAddToTransaction(bstree->left,searchISBN,node,quantity);
    searchByISBNAddToTransaction(bstree->right,searchISBN,node,quantity);
    return;
}

/*searchByNameAddToTransaction is the function used to add a medicine to the current transcation by searching for
the medicine in the BST using the medicine name*/
void searchByNameAddToTransaction(struct BSTREE *bstree,char str[],struct Transaction *node,int quantity)
{
    if(bstree == NULL)
        return;

    if( strcmp(bstree->data->name,str) == 0 )
    {
        if( bstree->data->quantity >= quantity )
        {
            node->data = *bstree->data;
            bstree->data->quantity -= quantity;
        }
        else
            printf("\nOnly %d medicines are available\n\n",bstree->data->quantity);
        return;
    }

    if( strcmp(bstree->data->name,str) > 0 )
        searchByNameAddToTransaction(bstree->left,str,node,quantity);
    else
        searchByNameAddToTransaction(bstree->right,str,node,quantity);

    return;
}


/*addToTransactionLinkedList adds each selected medicine to the linked list*/
void addToTransactionLinkedList(struct Transaction *np)
{
    if(start == NULL)
    {
        start = np;
        start->next  = NULL;
    }
    else
    {
        np->next = start;
        start = np;
    }
}


/*addToTransaction is the container function from which the user(through the receptionist) adds medicines to the linked list*/
void addToTransaction(struct BSTREE *bstree)
{
    char choice,searchName[20];
    int searchISBN;
    int medicineQuantity;
    struct Transaction *np = (struct Transaction*)malloc(sizeof(struct Transaction));
    if(!np)
    {
        printf("Memory Allocation Error!!!\n\n");
        exit(2);
    }

    np->next = NULL;

    printf("Do you want to add add a medicine by name or by ISBN:\nEnter 1 for name\nEnter 2 for ISBN");
    scanf(" %c",&choice);

    switch(choice)
    {
        case '1':
        {
            printf("Enter the name of the medicine you want to add:\n");
            scanf("%s",searchName);
            //search and add stores values of the details structure into the np that will be added to the transaction linked list
            printf("Enter the quantity of the medicine that you require:");
            scanf("%d",&medicineQuantity);
            searchByNameAddToTransaction(bstree,searchName,np,medicineQuantity);
            break;
        }
        case '2':
        {
            printf("Enter the ISBN code of the medicine you want to buy:");
            scanf("%d",&searchISBN);
            printf("Enter the quantity of the medicine that you require:");
            scanf("%d",&medicineQuantity);
            searchByISBNAddToTransaction(bstree,searchISBN,np,medicineQuantity);
            break;
        }
    }
    if( medicineQuantity <= np->data.quantity )
        {
            //printf("1\n");
            addToTransactionLinkedList(np);
            np->data.quantity  = medicineQuantity;
        }
        else
            free(np);

}


/*deleteMedicineUsingNameFromLinkedList deletes medicines from the current transcation by searching for it using the medicine name*/
void deleteMedicineUsingNameFromLinkedList(char searchName[])
{
    if(start == NULL)
    {
        return;
    }

    struct Transaction *temp = start,*prev = NULL,*del;

    if(strcmp(start->data.name,searchName) == 0)
    {
        start = start->next;
        free(temp);
    }   

    else
    {
        while(strcmp(temp->data.name,searchName) != 0 && temp != NULL)
        {
            prev = temp;
            temp = temp->next;
        }
        if(strcmp(temp->data.name,searchName) == 0)
        {
            //del = temp;
            prev->next = temp->next;
            free(temp);
        }
    }   
}


/*deleteMedicineUsingISBNFromLinkedList deletes medicines from the current transcation by searching for it using the ISBN code*/
void deleteMedicineUsingISBNFromLinkedList(int searchISBN)
{
    if(start == NULL)
    {
        return;
    }

    struct Transaction *temp = start,*prev = NULL;

    if( start->data.ISBN == searchISBN )
    {
        start = start->next;
        free(temp);
    }

    else
    {
        while(temp->data.ISBN != searchISBN && temp != NULL)
        {
            prev = temp;
            temp = temp->next;
        }
        if(temp->data.ISBN == searchISBN)
        {
            //del = temp;
            prev->next = temp->next;
            free(temp);
        }
    }   
}


/*removeMedicineFromTransaction is the container function from which the user(through the receptionist) deletes medicines from the current transaction*/
void removeMedicineFromTransaction()
{
    char choice,searchName[20];
    int searchISBN;
    printf("Do you want to remove the medicine by name or by ISBN?\nEnter 1 for name\nEnter 2for ISBN");
    scanf(" %c",&choice);
    switch (choice)
    {
        case '1':
        {
            printf("Enter the name of the medicine you want to delete:");
            scanf("%s",searchName);
            deleteMedicineUsingNameFromLinkedList(searchName);
            printf("The required medicine has been removed from the transaction.");
            break;
        }
        case '2':
        {
            printf("Enter the ISBN code of the medicine you want to remove:");
            scanf("%d",&searchISBN);
            deleteMedicineUsingISBNFromLinkedList(searchISBN);
            printf("The required medicine has been removed from the transaction.");
            break;
        }
    }
}


/*modifyQuantityOfMedicineUsingISBN modifies quantity of the medicine searched by ISBN code*/
void modifyQuantityOfMedicineUsingISBN(int searchISBN)
{
    struct Transaction *traversal = start;
    while(traversal != NULL)
    {
        if(traversal->data.ISBN == searchISBN)
        {
            printf("The current quantity of the medicine is:%d\n",traversal->data.quantity);
            printf("Enter the new quantity for the medicine:");
            scanf("%d",&traversal->data.quantity);
            printf("The quantity of the medicine has been succesfully modified.\n");
            return;
        }
        traversal = traversal->next;
    }
    free(traversal); 
}


/*modifyQuantityOfMedicineUsingName modifies quantity of the medicine searched by name*/
void modifyQuantityOfMedicineUsingName(char searchName[])
{
    struct Transaction *traversal = start;
    while(traversal != NULL)
    {
        if(strcmp(traversal->data.name,searchName) == 0)
        {
            printf("The current quantity of the medicine is:%d\n",traversal->data.quantity);
            printf("Enter the new quantity for the medicine:");
            scanf("%d",&traversal->data.quantity);
            printf("The quantity of the medicine has been succesfully modified.\n");
            return;
        }
        traversal = traversal->next;
    }
    free(traversal);
}




/*displayTransaction is used to display the items currently in the transaction before printing the final bill*/
void displayTransaction()
{
    struct Transaction *traversal = start;
    while(traversal != NULL)
    {
        printf("Name:%15s    Quantity:%2d   Price:%4.2f\n",traversal->data.name,traversal->data.quantity,(100.0 - traversal->data.discount)/100 * traversal->data.price);
        traversal = traversal->next;
    }
}
