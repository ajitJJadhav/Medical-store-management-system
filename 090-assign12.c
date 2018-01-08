/*
      NAME-SIDDHARTH KUMAR
      ROLL-201601090
      Branch:CSE

      FUNCTIONS WRITTEN:

        a)For ADMIN part:
          1.Add Inventory
          2.Delete Inventory
          3.view inventory

        b)For CUSTOMER part:
          4.Display Transactions Customer
          5.Avail Discounts
          6.Computing Total payment(displaying total bill)
          7.Save file(maintaining the record of each customer in a file)
*/




//..................................................../*############ ADMIN ###########*/..................................




/*this function is used to link one node of stack with the next */
STACK *link_STACK(DETAILS *node,int i,STACK *prev)
{
    STACK *head,*tail;
    /*for the head node*/
    if(i==0)
    {
        head=(STACK *)malloc(sizeof(STACK));
         tail=(STACK *)malloc(sizeof(STACK));
        head->details=*node;
        tail=head;
        prev=tail;
        head->next=NULL;
        tail->next=NULL;

    }
    else
        /*for linking rest nodes*/
    {
         tail=(STACK *)malloc(sizeof(STACK));
         tail->details=*node;
         tail->next=prev;
         prev=tail;
    }
    return tail;
}





/*this function is creating node,it will read line by line from the file and then store in a node and send for linking*/
STACK *make_inventory(FILE *fp)
{
    int i=0;
    char s[50000];
    DETAILS *node;
    STACK *head,*prev=NULL;
    while( fscanf(fp,"%s",s) > 0 )
    {
        node=createItem(s);//a function for creating node from file(inventory.txt) present in software(1).c
        head=link_STACK(node,i,prev);
        prev=head;//storing previous
        i++;//for calculating the length of link list
    }
    head->len.length=i;//storing the length of link list in length attribute of head

  return head;
}





/*for initial swap of 1st two elements*/
void swapin(STACK *current,STACK *next)
{
   current->next=next->next;//since in case of first two swapping we do not need previous node
   next->next=current;

}



/*for swapping rest*/
 void swaprst(STACK *prev,STACK *current,STACK *next)
{

   prev->next=current->next;
   current->next=next->next;
   next->next=current;
}



/*this function performs min node sorting in the given stack  without **dummy node**/
STACK  *Min_sort(STACK* head)
{
   int i,j,len;
   STACK *next,*prev,*current,*temp=head;
   //storing the length of link list in len
   len=head->len.length;
   for(i=0;i<len;i++)
      {
          //for pointing head to current
        current=temp;

         for(j=0;j<len-i-1;j++)
           {

              if(j==1)
              prev=temp;//for pointing to previous node

              next=current->next;

                if(j==0)
                  {
                      /*for the first two nodes*/
                     if(current->details.ISBN > next->details.ISBN)
                        {
                          swapin(current,next);
                          temp=next;
                        }
                else
                 current=current->next;
                  }

                 else
                   {
                    /*for the next three nodes*/
                     if(j>1)
                     prev=prev->next;//for the first time the previous pointer will be on 1st node so no need for prev->next
                         if(current->details.ISBN > next->details.ISBN)
                            {
                              swaprst(prev,current,next);
                            }
                         else
                              current=current->next;
                    }
            }
   }
   //storing the length of link list in the new head
temp->len.length=len;

   return temp;//returning the new head
}





/*function  for adding new entry to the stack created */
STACK *add_inventory(STACK *head)
{

    int i,check=-1;
    STACK *newhead;
    newhead=(STACK *)malloc(sizeof(STACK));//creating a new node which will be new head



     while(check!=0)
       {
           printf("Enter The ISBN Code: ");
           scanf("%d",&newhead->details.ISBN);
           printf("\n");

           check=check_ISBN(head,newhead->details.ISBN);//for checking ISBN....as it should be unique

           if(check==1)
            printf("ISBN ALREADY EXIST.....TRY ANOTHER ONE\n\n");
       }

    printf("Enter The Name Of Medicine: ");
    scanf("%s",newhead->details.name);
    printf("\n");

    printf("Enter The Name Of Supplier: ");
    scanf("%s",newhead->details.supplierName);
    printf("\n");

    printf("Enter The Price: ");
    scanf("%d",&newhead->details.price);
    printf("\n");

    printf("Enter The % Discount: ");
    scanf("%f",&newhead->details.discount);
    printf("\n");

    printf("Enter The Quantity Of Medicine: ");
    scanf("%d",&newhead->details.quantity);
    printf("\n");

    printf("Enter the Number Of Related Disease: ");
    scanf("%d",&newhead->details.diseaseNumber);
    printf("\n");

//allocating memory (2d space) for diseases related to one
//particular disease
    newhead->details.disease = (char **) malloc( newhead->details.diseaseNumber * sizeof(char*));
    for(i=0;i<newhead->details.diseaseNumber;i++)
    {
    printf("Enter The Disease Name ");
    printf("%d: ",i+1);
    newhead->details.disease[i] = (char*) malloc(20*sizeof(char));
    scanf("%s",newhead->details.disease[i]);
    printf("\n");
    }

  /*linking to prev head of stack*/
    newhead->next=head;
    newhead->len.length=head->len.length;//updating length in the len of new head
    newhead->len.length++;//incrementing length as a new node is added

    return newhead;

}





/*function for deleting a particular entry on basis of ISBN from the stack */
STACK *delete_inventory(STACK* head,int ISBN)
{
    STACK *temp=head;
    STACK *prev=head;

    int len,i;
       len=head->len.length;//since the length will be altered therefore,storing length for updating
    while(temp!=NULL)
    {
        if(temp->details.ISBN==ISBN)
        break;
        prev=temp;//will store the previous
         temp=temp->next;//temp will point at the node to be deleted

    }

    printf("\nISBN:%d  NAME:%s  SUPPLIERNAME:%s  PRICE:%d   DISCOUNT:%.2f  QUANTITY:%d\n",temp->details.ISBN,temp->details.name,temp->details.supplierName,temp->details.price,temp->details.discount,temp->details.quantity);
     for(i=0;i<temp->details.diseaseNumber;i++)
    {
        printf("DISEASE");
        printf("%d:",i+1);
        printf("%s  ",temp->details.disease[i]);
    }
    printf("\n\n");

    if(temp==head)//if the node to be deleted is first node itself
    {
        if(temp!=NULL)
        {

                 head=temp->next;//updating head
                 len--;
                head->len.length=len;//storing new entry of length to updated head

        }
    }

    else//if the node deleted is not the first node
    {
        prev->next=temp->next;
        head->len.length--;//updating length of head

    }
    return head;
}




/*function for viewing new whole inventory*/
void view_inventory_details(STACK *head)
{
    char s[500];
    int i;

    while(head!=NULL )
    {
    printf("ISBN:%d  NAME:%s  SUPPLIERNAME:%s  PRICE:%d   DISCOUNT:%.2f  QUANTITY:%d\n",head->details.ISBN,head->details.name,head->details.supplierName,head->details.price,head->details.discount,head->details.quantity);
    for(i=0;i<head->details.diseaseNumber;i++)
    {
        printf("DISEASE");
        printf("%d:",i+1);
        printf("%s  ",head->details.disease[i]);
    }
    printf("\n\n");
    head=head->next;
    }

}





/*function for checking repeated ISBN numbers whether they are already present in stack or not*/
int check_ISBN(STACK *head,int ISBN)
{
    while(head!=NULL)
    {
        if(head->details.ISBN==ISBN)
            return 1;//if ISBN found return 1
        head=head->next;
    }
    return 0;//if ISBN not found return 0
}




//......................................./*########## CUSTOMER ###########*/.............................




/*function for displaying transaction to customer as well as calculating the total billing*/
void Display_Transaction_Coustmer(int *count,float *total)
{
    TRANSACTION *traversal = start;//to traverse in link list

    while(traversal != NULL)
    {
        printf("Name:%15s    Quantity:%2d   Price:%2.4f\n",traversal->data.name,traversal->data.quantity,(100.0 - traversal->data.discount)/100 * traversal->data.price);

        (*count)++;//for counting the of medicines bought

        *total = *total + (traversal->data.quantity) * (100.0 - traversal->data.discount)/100.0 * (traversal->data.price);//calculating the total

        traversal = traversal->next;
    }
}





/*function to check if coupon enter is valid or not if applicable then the coupon will be valid
if not then no discount and the coupon will be deemed as invalid*/
float Avail_Discount(char coupon[])
{
    float dis;
    char ch,inp[10],disc[10];
    FILE *fp=fopen("coupon.txt","r");//opening file coupon.txt for avaling coupon

    while( fscanf(fp,"%[^,]s",inp) > 0 )
    {
        fscanf(fp,"%c",&ch);//for excluding ","

        fscanf(fp,"%[^,]s",disc);

        fscanf(fp,"%c",&ch);//for excluding "\0"

        fscanf(fp,"%c",&ch);//for excluding ","

        dis=atof(disc);//converting discount to float

        if(strcmp(coupon,inp)==0)//if coupon available
            return dis;          //return the discount related to the coupon

    }
    return 0;//if no coupon is INVALID
}





/*function for saving back to file: all the transaction related to a particular customer is
saved in the file and can be accessed any time if wanted*/
void save_items(FILE *f)
{
    int i;
    char S[5][20];

    TRANSACTION *trav=start;

    while(trav!=NULL)
    {
        sprintf(S[0],"%d",trav->data.ISBN);//to save ISBN to S[0]

        sprintf(S[1],"%d",trav->data.price);//to save price to S[1]

        sprintf(S[2],"%.2f",trav->data.discount);//to save discount to S[2]

        sprintf(S[3],"%d",trav->data.quantity);//to save quantity to S[3]

        sprintf(S[4],"%d",trav->data.diseaseNumber);//to save disease number to S[4]

        fprintf(f,"%s,%s,%s,%s,%s,%s,%s,",S[0],trav->data.name,trav->data.supplierName,S[1],S[2],S[3],S[4] );

        for(i=0;i<trav->data.diseaseNumber;i++)
        {
            fprintf(f, "%s,",trav->data.disease[i] );
        }

        fprintf(f, "\n");

        trav=trav->next;
    }
}
