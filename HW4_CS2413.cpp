//
// ========================================
// HW4: Implement a Singly List Class
// ========================================
//
// In this assignment, we will implement
// a singly linked list class based on
// a node class.
//
// The Node class has been defined to you.
// Do not modify it.
//
// The List class has been partly defined
// for you. It has one private variable
// "head" and several public functions.
// The constructor and Print function have been
// defined for you (do not modify them), and
// your task is to implement other functions.
//
// You can add new member functions to the
// List class but not new member variables.
// In addition, you cannot use any existing
// list-related library or function.
//
//
#include <iostream>
using namespace std;
// The Node class has been defined for you.
// Do not modify it.
class Node {
private:
	int SID;
	float GPA;
	Node* p_next;
public:
	void Set_SID(int x);
	void Set_GPA(float y);
	int Get_SID();
	float Get_GPA();
	void Set_Pnext(Node* p);
	Node* Get_Pnext();
	Node();
};
void Node::Set_SID(int x) {
	SID = x;
}
void Node::Set_GPA(float y) {
	GPA = y;
}
int Node::Get_SID() {
	return SID;
}
float Node::Get_GPA() {
	return GPA;
}
void Node::Set_Pnext(Node* p) {
	p_next = p;
}
Node* Node::Get_Pnext() {
	return p_next;
}
Node::Node() {
	SID = -1;
	GPA = -1;
	p_next = NULL;
}
// The List class has been partly defined for you.
// Complete its undefined member functions.
class List {
private:
	Node* head;
public:
	// List function is defined for you.
	List();
	// Print function is defined for you.
	void PrtSID();
	// Create function creates a singly linked
	// list based on our inputs and assigns its
	// head node's address to the "head" pointer.
	//
	// To be specific, when we run Create(),
	// the program should wait for us to input
	// the SID and GPA of an arbitrary number
	// of students. After Create() is done,
	// the linked list should have been created
	// and accessible through "head".
	//
	// The format of input should be as follows:
	//
	// sid_1 gpa_1 sid_2 gpa_2 sid_3 gpa_3 ......
	//
	// Here, sid_i and gpa_i are SID and GPA of
	// the i_th input student. A new node is always
	// added to the head of the list.
	//
	// Note that this hw does not require you to
	// check duplication of the input/inserted SID's
	// for simplicity. But we should always assume
	// SID is unique for each student.
	//
	// Finally, the process should terminate when
	// an invalid input is given. Note that it is
	// assumed we always input a pair of valid
	// sid and gpa for a new student, so there is
	// no need to deal with the case of a valid sid
	// followed by an invalid gpa.
	//
	// If you are still confused about this function,
	// check how it is used in the main program.
	void Create();
	// Lsize function returns the number
	// of nodes in the list. Return 0 if
	// the list is empty.
	int Lsize();
	// Find function returns address of
	// the node in the list whose SID = key.
	// Return NULL if no match is found.
	Node* Find(int key);
	// Insert function inserts a new node
	// (whose address is stored at "p")
	// as the idx_th node in the list.
	// Return 1 if insertion is successful
	// and return -1 if idx is out of range.
	// A valid range is [1, Lsize+1],
	// where "1" means adding to head
	// and "Lsize+1" means adding to tail.
	int Insert(Node* p, int idx);
	// Remove function removes the idx_th
	// node from the list. Return 1 if
	// removal is successful and -1 if
	// idx is out of range.
	// A valid range is [1, Lsize],
	// where "1" means removing head
	// and "Lsize" means removing tail.
	int Remove(int idx);
	// Reverse function reserves the list.
	// For example, if the current list has
	// three nodes A->B->C, after running
	// Reverse the order should be C->B->A.
	// As another example, if we call the
	// print function and get 246, after
	// running Reverse we should get 642.
	void Reverse();
	// Clear function removes all nodes from
	// the list (so it becomes an empty list).
	void Clear();
};
// The constructor has been defined for you.
List::List() {
	head = NULL;
}
// The print function has been defined for you.
void List::PrtSID() {
	Node* temp = head;
	while (temp != NULL)
	{
		cout << temp->Get_SID();
		temp = temp->Get_Pnext();
	}
}

// This function is responsible for creating a singly linked list of nodes
// based on user input. It reads student IDs (sid) and GPAs (gpa) in pairs
// until an invalid input is detected, and it adds each pair as a new node
// at the beginning of the list.
void List::Create() {
	int sid;
	int gpa;
	while (true) {
		if (!(std::cin >> sid >> gpa)) {
			// Stop if input is invalid
			break;
		}
		Node* temp;
		temp = new Node();
		temp->Set_SID(sid);
		temp->Set_GPA(gpa);
		temp->Set_Pnext(head);
		head = temp;
	}
}

// This function calculates and returns the size of the linked list, i.e.,
// the number of nodes in the list. It iterates through the list and
// counts the nodes until it reaches the end.
int List::Lsize() {
	int counter = 0;
	Node* position = head;
	while (position != nullptr) {
		counter++;
		position = position->Get_Pnext();
	}
	// Return 0 if the list is empty, or return the value of the counter.
	return counter;
}

// This function searches for a node with a given student ID (key) in the
// linked list. It starts from the head of the list and iterates through
// the nodes until it finds a node with the specified SID. It returns
// a pointer to the found node or nullptr if no match is found.
Node* List::Find(int key) {
	Node* current = head;
	while (current != nullptr) {
		if (current->Get_SID() == key) {
			return current;
		}
		current = current->Get_Pnext();
	}
	return nullptr;
}

// This function inserts a new node (whose address is stored at "p") into
// the linked list at the specified index (idx). It returns 1 if the
// insertion is successful and -1 if the index is out of range. A valid
// index range is [1, Lsize+1], where 1 means adding to the head and
// Lsize+1 means adding to the tail.
int List::Insert(Node* p, int idx) {
	if (idx < 1 || idx > Lsize() + 1) {
		return -1; // Index out of range
	}

	if (idx == 1) {
		p->Set_Pnext(head);
		head = p;
	}
	else {
		Node* current = head;
		int count = 1;

		while (count < idx - 1) {
			current = current->Get_Pnext();
			count++;
		}

		p->Set_Pnext(current->Get_Pnext());
		current->Set_Pnext(p);
	}

	return 1;
}

// This function removes a node from the linked list at the specified
// index (idx). It returns 1 if the removal is successful and -1 if
// the index is out of range. A valid index range is [1, Lsize], where
// 1 means removing the head and Lsize means removing the tail.
int List::Remove(int idx) {
	if (idx < 1 || idx > Lsize()) {
		return -1; // Index out of range
	}

	if (idx == 1) {
		Node* temp = head;
		head = head->Get_Pnext();
		delete temp;
	}
	else {
		Node* current = head;
		int count = 1;

		while (count < idx - 1) {
			current = current->Get_Pnext();
			count++;
		}

		Node* temp = current->Get_Pnext();
		current->Set_Pnext(temp->Get_Pnext());
		delete temp;
	}

	return 1;
}

// This function reverses the order of nodes in the linked list. It starts
// from the head of the list and iterates through the nodes, reversing
// the next-pointer of each node to point to the previous node. After
// the loop, the head is updated to the last node, effectively reversing
// the list.
void List::Reverse() {
	Node* current = head;
	Node* prev = NULL;
	Node* next = NULL;

	while (current != NULL) {
		next = current->Get_Pnext();
		current->Set_Pnext(prev);
		prev = current;
		current = next;
	}
	head = prev;
}

// This function removes all nodes from the linked list, effectively making
// it an empty list. It iteratively deletes each node while updating the
// head pointer and freeing the memory occupied by the nodes.
void List::Clear() {
	while (head != nullptr) {
		Node* temp = head;
		head = head->Get_Pnext();
		delete temp;
	}
}




int main()
{
	int mode, key, sid, idx;
	float gpa;
	// The first five inputs are for testing.
	// "mode" determines which function to test.
	// "key" is used to evaluate Find().
	// "sid" and "gpa" are used to evaluate Insert().
	// "idx" is used to evaluate Insert() and Remove().
	//
	// After these inputs, the rest inputs are used
	// to create the initial singly linked list.
	cin >> mode >> key >> sid >> gpa >> idx;
	// declare a singly linked list named "x"
	List x;
	// input data to x.
	// After this, a list should be created
	// and stored at address "head".
	x.Create();
	// Mode 0: test Create()
	if (mode == 0) {
		x.PrtSID();
	}
	// Mode 1: test Lsize()
	else if (mode == 1) {
		cout << x.Lsize();
	}
	// Mode 2: test Find()
	else if (mode == 2) {
		Node* temp = x.Find(key);
		if (temp == NULL) {
			cout << -1;
		}
		else {
			cout << temp->Get_GPA();
		}
	}
	// Mode 3: test Insert()
	else if (mode == 3) {
		Node* temp = new Node;
		temp->Set_SID(key);
		temp->Set_GPA(3.5);
		x.Insert(temp, idx);
		x.PrtSID();
	}
	// Mode 4: test Remove()
	else if (mode == 4) {
		x.Remove(idx);
		x.PrtSID();
	}
	// Mode 5: test Reverse()
	else if (mode == 5) {
		x.Reverse();
		x.PrtSID();
	}
	// Mode 6: test Clear()
	else if (mode == 6) {
		x.Clear();
		cout << x.Lsize();
	}
	return 0;
}
