struct details *createItem(char S[])
/*
creates a node containing all the information related to a medicine
parameter S is the line scanned from the file containing information related to a particular medicine

this nodes can be used to create datastructures using this node for storing information
*/
{
	char temp[20];
	int i=0,j=0,k=0,index=0,z;
	struct details *node;

	node = (struct details*) malloc(sizeof(struct details));
	//extracting the information from the string and putting the information in respective fields
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
				for(z=0;z<node->diseaseNumber;z++)
					node->disease[z] = (char *) malloc(20 * sizeof(char));
				break;
			default:
				strcpy(node->disease[index],temp);
				index++;
				break;
		};
		i++;
	}

	return node;
}

void viewInventory(struct BSTREE *bstree)
// to view all the medicines and their information
{
	if(bstree == NULL)
		return;

	printDetails(bstree);
	//printf("ISBN:%3d   Name:%15s   Supplier:%15s   Price:%5d    Quantity:%2d    Discount:%2.2f\n",bstree->data->ISBN,bstree->data->name,bstree->data->supplierName,bstree->data->price,bstree->data->quantity,bstree->data->discount);
	viewInventory(bstree->left);
	viewInventory(bstree->right);
	return;
}

void searchByDisease(struct BSTREE *bstree,char *S)
//to find the details of all the medicines that can cure a given disease
{
    int i;

	if(bstree == NULL)
		return;

	for(i=0;i<bstree->data->diseaseNumber;i++)
	{
		if( strcmp(bstree->data->disease[i],S) == 0 )
		{
			printDetails(bstree);
			//printf("%d %s %s %d %.2f %d\n",bstree->data->ISBN,bstree->data->name,bstree->data->supplierName,bstree->data->price,bstree->data->discount,bstree->data->quantity);
			break;
		}
	}
	searchByDisease(bstree->left,S);
	searchByDisease(bstree->right,S);
	return;
}

void searchByName(struct BSTREE *bstree,char *S)
//to search for the details of the medicine of a given name
{
	if(bstree == NULL)
		return;

	if( strcmp(bstree->data->name,S) == 0 )
	{
		printDetails(bstree);
		//printf("%d %s %s %d %.2f %d\n",bstree->data->ISBN,bstree->data->name,bstree->data->supplierName,bstree->data->price,bstree->data->discount,bstree->data->quantity);
		return;
	}

	if( strcmp(bstree->data->name,S) > 0 )
		searchByName(bstree->left,S);
	else
		searchByName(bstree->right,S);

	return;
}

void searchQuantityByName(struct BSTREE *bstree,char *S)
//check the quantity of a particular medicine by name
{
	if(bstree == NULL)
		return;

	if( strcmp(bstree->data->name,S) == 0 )
		printf("Quantity : %2d\n",bstree->data->quantity);
	searchQuantityByName(bstree->left,S);
	searchQuantityByName(bstree->right,S);
	return;
}

void searchByISBNCode(struct BSTREE *bstree,int x)
//search the details of a medicine by given ISBN code
{
	if(bstree == NULL)
		return;

	if( bstree->data->ISBN == x )
		printDetails(bstree);
		//printf("%d %s %s %d %.2f %d\n",bstree->data->ISBN,bstree->data->name,bstree->data->supplierName,bstree->data->price,bstree->data->discount,bstree->data->quantity);
	searchByISBNCode(bstree->left,x);
	searchByISBNCode(bstree->right,x);
	return;
}

void searchQuantityByISBNCode(struct BSTREE *bstree,int x)
// check the quantity of a medicine by using ISBN code of the medicine
{
	if(bstree == NULL)
		return;

	if( bstree->data->ISBN == x )
		printf("Quantity : %2d\n",bstree->data->quantity);
	searchQuantityByISBNCode(bstree->left,x);
	searchQuantityByISBNCode(bstree->right,x);
	return;
}

void searchBySupplierName(struct BSTREE *bstree,char *S)
//to search the details of the medicines supplied by a particular supplier
{
	if(bstree == NULL)
		return;

	if( strcmp(bstree->data->supplierName,S) == 0 )
		printDetails(bstree);
		//printf("%d %s %s %d %.2f %d\n",bstree->data->ISBN,bstree->data->name,bstree->data->supplierName,bstree->data->price,bstree->data->discount,bstree->data->quantity);
	searchBySupplierName(bstree->left,S);
	searchBySupplierName(bstree->right,S);
	return;
}

void updateDiscountByName(struct BSTREE *bstree,char *S)
//to update the discount of the medicine by using its name
{
	if(bstree == NULL)
		return;

	if( strcmp(bstree->data->name,S) == 0 )
		scanf("%f",&(bstree->data->discount) );

	updateDiscountByName(bstree->left,S);
	updateDiscountByName(bstree->right,S);
	return;
}

void updateDiscountByISBN(struct BSTREE *bstree,int x)
//to update the discount of a medicine by using its ISBN code
{
	if(bstree == NULL)
		return;

	if( bstree->data->ISBN == x )
		scanf("Enter new discount: %f\n",&(bstree->data->discount) );

	updateDiscountByISBN(bstree->left,x);
	updateDiscountByISBN(bstree->right,x);
	return;
}

void saveChanges(struct BSTREE *bstree,FILE *f)
//to update the inventory information in the file containing the inventory details
{
    int i;
	if(bstree == NULL)
		return;

	char S[5][20];

	// to convert the non string values into strings so that they can be saved into the file
	sprintf(S[0],"%d",bstree->data->ISBN);
	sprintf(S[1],"%d",bstree->data->price);
	sprintf(S[2],"%.2f",bstree->data->discount);
	sprintf(S[3],"%d",bstree->data->quantity);
	sprintf(S[4],"%d",bstree->data->diseaseNumber);


	fprintf(f,"%s,%s,%s,%s,%s,%s,%s,",S[0],bstree->data->name,bstree->data->supplierName,S[1],S[2],S[3],S[4] );
	for(i=0;i<bstree->data->diseaseNumber;i++)
		fprintf(f, "%s,",bstree->data->disease[i] );
	fprintf(f, "\n");
	saveChanges(bstree->left,f);
	saveChanges(bstree->right,f);
	return;
}

void insertElement(struct BSTREE *root,struct BSTREE *node)
// to add an element to the binary search tree of medicines based on their names
{
    if( (root->left == NULL) && (strcmp(root->data->name,node->data->name)) > 0 )
        root->left = node;
    else if( (root->right == NULL) && ( strcmp(root->data->name,node->data->name) <= 0 ) )
        root->right = node;
    else
	{
		if( strcmp(root->data->name,node->data->name) > 0 )
			insertElement(root->left,node);
		else
			insertElement(root->right,node);
	}
}

struct BSTREE *createBST()
//to create a BST based on the names of the medicines
{
	FILE *f = fopen("inventory.txt","r");
	char S[500];
	struct details *node;
	struct BSTREE *root,*element;
	int flag=1,operation,x;
	//printf("HELLO\n");
	while( fscanf(f,"%s",S) > 0 )
	{
		node = createItem(S);
		element = (struct BSTREE*)malloc(sizeof(struct BSTREE));
		element->left = element->right = NULL;
		element->data = node;

		if(flag == 0)
			insertElement(root,element);
		else
		{
			flag = 0;
			root = element;
		}
	};

	fclose(f);

	return root;
}
