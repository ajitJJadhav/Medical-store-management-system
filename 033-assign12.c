void createItemTransaction(char S[],NODE *node)
{
	char temp[20];
	int i=0,j=0,k=0,index=0;

	while( S[k] != '\0')
	{
		j=0;
		while(S[k] != ',')
		{
			temp[j] = S[k];
			k++;
			j++;
		}	
		temp[j] = '\0';
		//printf("%s\n",temp[i]);
		k++;
		
		switch(i)
		{
			case 0:
				node->ISBN = atoi(temp);
				break;
			case 1:
				strcpy(node->name,temp);
				break;
			case 2:
				strcpy(node->supplierName,temp);
				break;
			case 3:
				node->price = atoi(temp);
				break;
			case 4:
				node->discount = atof(temp);
				break;
			case 5:
				node->quantity = atoi(temp);
				break;
			case 6:
				node->diseaseNumber = atoi(temp);
				node->disease = (char **) malloc( node->diseaseNumber * sizeof(char*));
				for(int z=0;z<node->diseaseNumber;z++)
					node->disease[z] = (char *) malloc(20 * sizeof(char));
				break;
			default:
				strcpy(node->disease[index],temp);
				index++;
				break;						
		};
		i++;
	}	
	
}

void ViewAllInventory(TRANS *new)
{
	if(new==NULL)
		printf("YOUR INVENTORY IS EMPTY\n");
	while(new!=NULL)
	{
		printf("%s\n",new->S);
		for(int i=0;i<new->itemsCount;i++)
		{	
			printf("%d %s %s %d %.2f %d ",new->data[i].ISBN,new->data[i].name,new->data[i].supplierName,new->data[i].price,new->data[i].discount,new->data[i].quantity);
			for(int j=0;j<new->data[i].diseaseNumber;j++)
				printf(" %s ",new->data[i].disease[j]);
			printf("\n");
		}	
	new=new->next;
	}
	
}

TRANS *insert(TRANS *head,TRANS *new){
	if(head==NULL){
		return new;	
	}
	else{
		new->next=head;
		return new;
	}
}

void saveChangesFromLinkedList(STACK *temp,FILE *f)
{
	
    while(temp!=NULL )
	{
	//printf("ISBN:%d  NAME:%s  SUPPLIERNAME:%s  PRICE:%d   DISCOUNT:%.2f  QUANTITY:%d\n",head->details.ISBN,head->details.name,head->details.supplierName,head->details.price,head->details.discount,head->details.quantity);
		char S[5][20];
		int i;

		sprintf(S[0],"%d",temp->details.ISBN);
		sprintf(S[1],"%d",temp->details.price);
		sprintf(S[2],"%.2f",temp->details.discount);
		sprintf(S[3],"%d",temp->details.quantity);
		sprintf(S[4],"%d",temp->details.diseaseNumber);


		fprintf(f,"%s,%s,%s,%s,%s,%s,%s,",S[0],temp->details.name,temp->details.supplierName,S[1],S[2],S[3],S[4] );
		
		for(i=0;i<temp->details.diseaseNumber;i++)
			fprintf(f, "%s,",temp->details.disease[i] );
		
		fprintf(f, "\n");
			temp=temp->next;
	}
}


TRANS *searchTransactionByName(TRANS* new,char *name)
{
	int count=0;
	while(new!=NULL)
	{
		for(int i=0;i<new->itemsCount;i++)
		{	
			if(strcmp(new->data[i].name,name)==0)
			{
			printf("%s\n",new->S);
			for(int i=0;i<new->itemsCount;i++)
		{	
			printf("%d %s %s %d %.2f %d ",new->data[i].ISBN,new->data[i].name,new->data[i].supplierName,new->data[i].price,new->data[i].discount,new->data[i].quantity);
			for(int j=0;j<new->data[i].diseaseNumber;j++)
				printf(" %s ",new->data[i].disease[j]);
			printf("\n");
		}
		count++;
			}
		}
		new=new->next;
	}
	if(count==0)
		printf("\nSupplierName not found\n");
}



TRANS *searchTransactionByCustomerName(TRANS* new,char *customername)
{
	int count=0;
	while(new!=NULL)
	{
		if(strcmp(new->S,customername)==0)
		{
			printf("%s\n",new->S);
		for(int i=0;i<new->itemsCount;i++)
		{	
			printf("%d %s  %s %d %.2f %d ",new->data[i].ISBN,new->data[i].name,new->data[i].supplierName,new->data[i].price,new->data[i].discount,new->data[i].quantity);
			for(int j=0;j<new->data[i].diseaseNumber;j++)
				printf(" %s ",new->data[i].disease[j]);
			printf("\n");
		}
		count++;
		}
		new=new->next;
	}
	if(count==0)
		printf("\nCustomerName not found\n");
}

void displayLastFiveTransactions(TRANS *head)
{
	int length = getLengthOfLinkedList(head);
	TRANS *temp = head;
	for(int i =0 ; i < length - 4;i++)
	{
		temp = temp->next;
	}
	ViewAllInventory(temp);

	//TO FREE THE SPACE
	while(head != NULL)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

int getLengthOfLinkedList(TRANS *head)
{
	int count = 0 ;
	TRANS *trav = head;
	while(trav  != NULL)
	{
		trav = trav->next;
		count++;
	}
	return count;
}

void displayLast5Transactions()
{
	FILE *f = fopen("transactions.txt","r");
	char S[500];
	NODE *node=NULL;
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
			createItemTransaction( S,&(new->data[i]) );
		}
		//printf("Reached\n");
		list=insert(list,new);	
	}

	fclose(f);
	displayLastFiveTransactions(list);
}