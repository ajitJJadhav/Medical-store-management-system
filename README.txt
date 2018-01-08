Software structure

Admin (password protected) :
	1. viewInventory
	2. deleteInventory
	3. addInventory
	4. seeAllTransactions 
	5. seeTransactionsByName
	6. seeTransactionsBySupplier
	7. updatePassword	
Receptionist:
	1.  viewInventory
	2.  searchByName
	3.  searchByDisease
	4.  searchByISBNCode
	5.  searchBySupplierName
	6.  searchQuantityByName 
	7.  searchQuantityByISBNCode
	8.  updateDiscountByName
	9.  updateDiscountByISBNCode 	
	10. addToTransaction:
		1.  addToTransactionByName	
		2.  addToTransactionByISBNCode
	11. removeMedicineFromTransaction	
		1.  removeFromBillByName 
		2. removeFromBillByISBNCode 
	12. displayTransaction	
	13.  displayLast5Transactions 	
Customer:
	1. displayTheBill
	2. availSpecialDiscount
	3. confirmTheBillAndPay
	4. saveTheTransaction  



Ajit Jadhav (Team Leader) ( 201601034 ):
	Functions:	
		1.  createBST
		2.  createNode
		3.  viewInventory
		4.  searchByName
		5.  searchByDisease
		6.  searchByISBNCode
		7.  searchBySupplierName
		8.  searchQuantityByName 
		9.  searchQuantityByISBNCode
		10. updateDiscountByName
		11. updateDiscountByISBNCode
		12. saveChanges

	Datastructure used : Binary Search Tree

	Reason:
		The aim of the above sub-tasks is to search the data nodes based on the given field and make certain changes to the node data in some cases.
		The Binary Search Tree is created based on the names of the medicines. This reduces the time complexity of searching the medicines by name which is the most commonly used search.
		For search based on other parameters we can traverse the whole tree and print the required details or manipulate the data as required.

	Functions explanation:	
		1.  createBST:
			To create a BST based on the names of the medicines.

		2.  createNode:
			Creates a node containing all the information related to a medicine.

		3.  viewInventory:
			To view all the medicines and their information.

		4.  searchByName:
			To search for the details of the medicine of a given name.

		5.  searchByDisease:
			To find the details of all the medicines that can cure a given disease.

		6.  searchByISBNCode:
			Search the details of a medicine by given ISBN code.

		7.  searchBySupplierName:
			To search the details of the medicines supplied by a particular supplier.

		8.  searchQuantityByName:
			Check the quantity of a particular medicine by name.

		9.  searchQuantityByISBNCode:
			Check the quantity of a medicine by using ISBN code of the medicine.

		10. updateDiscountByName:
			To update the discount of the medicine by using its name.

		11. updateDiscountByISBNCode:
			To update the discount of a medicine by using its ISBN code.

		12. saveChanges:
			To update the inventory information in the file containing the inventory details.



Arvind Deshraj ( 201601007 ):
	Functions:
		1.  getch
		2.  encodeDecodePassword
		3.  passwordVerification
		4.  updatePassword
		5.  searchByISBNAddToTransaction
		6.  searchByNameAddToTransaction
		7.  addToTransactionLinkedList
		8.  addToTransaction
		9.  deleteMedicineUsingNameFromLinkedList
		10. deleteMedicineUsingISBNFromLinkedList
		11. removeMedicineFromTransaction
		12. modifyQuantityOfMedicineUsingISBN
		13. modifyQuantityOfMedicineUsingName
		14. displayTransaction

	Structure : Transaction
	Data Structure Used: Linked List

	Reason:
		The above sub tasks are mostly adding , modifying and removing items from the current transaction
		The data structure contains the medicine data(details  structure) and the quantity requested by the user.
		Linked List is most appropriate for this as it provides the option to dynamically allocate space as well we are 
		not restricted to stack or queue implementations as that forces us to either delete from the front or the rear
		which is not practical. I have not used another data structure as the trade-offs in search time are not as helpful
		as most of the subtasks are not search based and are  basic adding and deletingutility functions.

	Functions Explanation:

		1.  getch:
			getch() function is used for taking in the password without echoing in the terminal
			It is based on the <conio.h> implementation of getch() in Windows systems
			It uses termios.h and unistd.h

		2.  encodeDecodePassword
			We have encoded our passwords using a rot13 system where each alphabet is rotated by 13 places
			Since we have rotated by 13 we can use the same encoding system for decoding as well simply by 
			using a (% 26) to loop back alphabets

		3.  passwordVerification
			passwordVerification is the function used to test whether user has admin access or not

		4.  updatePassword
			updatePassword() is the function created to change the admin password

		5.  searchByISBNAddToTransaction
			searchByISBNAddToTransaction is the function used to add a medicine to the current transcation by searching for
			the medicine in the BST using the ISBN code

		6.  searchByNameAddToTransaction
			searchByNameAddToTransaction is the function used to add a medicine to the current transcation by searching for
			the medicine in the BST using the medicine name

		7.  addToTransactionLinkedList
			addToTransactionLinkedList adds each selected medicine to the linked list

		8.  addToTransaction
			addToTransaction is the container function from which the user(through the receptionist) adds medicines to the linked list

		9.  deleteMedicineUsingNameFromLinkedList
			deleteMedicineUsingNameFromLinkedList deletes medicines from the current transcation by searching for it using the medicine name

		10. deleteMedicineUsingISBNFromLinkedList
			deleteMedicineUsingISBNFromLinkedList deletes medicines from the current transcation by searching for it using the ISBN code

		11. removeMedicineFromTransaction
			removeMedicineFromTransaction is the container function from which the user(through the receptionist) deletes medicines from the current transaction

		12. modifyQuantityOfMedicineUsingISBN
			modifyQuantityOfMedicineUsingISBN modifies quantity of the medicine searched by ISBN code

		13. modifyQuantityOfMedicineUsingName
			modifyQuantityOfMedicineUsingName modifies quantity of the medicine searched by name

		14. displayTransaction
			displayTransaction is used to display the items currently in the transaction before printing the final bill

	

	Siddharth Kumar ( 201601090 ):

	Structure: STACK
	Data Structure Used: Stack

	Reason:
		The data structure I used for these functions is STACK,that's because it was more effeicient in case of our program.
		The function make inventory will first make nodes and send the nodes to function link_STACK to form the stack.
		Then the function *Min_sort* sorts the whole STACK in ascending order,according to ISBN.
		Used node sotring without dummy node for sorting.

	Functions Written:

	1.For Admin:

		a) add_inventory:the This function only allows admin to add any new entry to the medical data base.
		It includes the name,quantity,ISBN number,price,supplier,diseases related to it.
		It also checks if the inventory's ISBN previously present or not,as the inventory's ISBN should be unique.

		b)delete_inventory:This function allows only admin to delete any inventory on the basis of it's ISBN number entered.
		It also checks whether the ISBN entered is correct or not.

		c)view_inventory-details:This function allows admin to see then details of all the medicines in the inventory.
 
	2.For Customer:

		a)Display_Transaction_Coustmer:It displays the transaction to the customer and also calculates the total bill that the customer has to pay.

		b)Avail_Discount:Checks the coupon code entered by the customer is valid or not and then apply the discount on the total accordingly,and prepares the final bill.

		c)save_items:At the last when the final payment is made by the customer,then it saves the transaction related to the particular customer in the file transaction.txt.  

	
	J. S. Sunil ( 201601033 ):
	Structure: TRANS
	Data Structure Used: Linked List

	Reason:
		In the list of transactions we don't know the no.of transactions beforehand so linked list is used to dynamically add the transactions.

	Functions:
		1. ViewAllInventory
		2. searchTransactionByName
		3. searchTransactionByCustomerName
		4. displayLast5Transactions
		5. saveChangesFromLinkedList

	Functions Explanation:
		(1)ViewAllInventory:
			In this function we are traversing through the linked list and printing all the transaction's information
				
		(2)searchTransactionByName:
			In this function we traverse through the linked list and print the previous details of the customers transactions who have purchased the given medicine.
			
		(3)searchTransactionByCustomerName:
			In this function we traverse through the linked list and print the previous transaction details of the given customer name.

		(4)displayLast5Transactions:
			This functionality is accessable to the receptionist.
			Using this function the receptionist can see the lastest five transactions. 
			
		(5)saveChangesFromLinkedList:
			This function is used in customer section
			In this function we save the current transaction into the list of transactions in the given file.
			we append the current transaction at the end of the file so that the file contains list of transactions from oldest to newest.