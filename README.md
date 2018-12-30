# Contact List
It was implemented a Contact list in C language. Each contact held the following data

* ID
* Name
* Last Name
* Email
* Phone Number
* Salary

The program at first reads a CSV file. If the file is found, the user can load the list as a two differents data structures: **Linked List** or **AVL Tree**.
After that, the user can perform the following operations

* Change the type of data structure - This implies removing all the modifications made previously

* Show contacts ordered by ID

* Search an contact by name

* Search an contact by ID

* Insert a new contact

* Remove a contact

* Exit Program

The Contact List in both methods were increasingly ordered by name. In order to compare the difference of complexity of time between the data structures, after each operation it is printed in output the its running time.

The images below contain the time of operations measured in 5 different tests for each method

![](https://github.com/bfs07/Contact-List/blob/master/OperationsInLinkedList.png)
![](https://github.com/bfs07/Contact-List/blob/master/OperationsInAVLTree.png)
