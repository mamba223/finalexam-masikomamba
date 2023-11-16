//
// ========================================
// HW3: Implement a Vector Class
// ========================================
// 
// In this assignment, we will implement 
// a vector class based on array, pointer 
// and dynamic memory allocation. 
// 
// The class has two private member 
// variables and some member functions. 
// Their designs are explained below. 
// 
// You can add new member functions 
// but not new member variables. In 
// addition, you cannot use any existing 
// vector-related library or function. 
// 
// 


#include <iostream>
using namespace std;

// 
// ======= Task =======
// Design and implement all member 
// functions of the MyVector class. 
// 
class MyVector {

public:

	// The "vsize" function returns the size 
	// of the current vector.  
	int vsize();

	// The "empty" function returns 1 if the 
	// current vector has no element and 0 otherwise. 
	int empty();

	// The "at" function returns the idx_th element 
	// of the vector. It also returns -1 if "idx" 
	// is outside the range of the current vector.
	int at(int idx);

	// The "resize" function resizes the current 
	// vector into a vector of size n. Note there 
	// are two scenarios (in lecture slides) which 
	// may need to be addressed separately. 
	void resize(int n);

	// The "push_back" function adds a new element 
	// "x" to the end of the current vector. Note 
	// the vector size increases after addition. 
	void push_back(int x);

	// The "pop_back" function removes the last 
	// element from the current vector, but does 
	// nothing if the current vector is empty. 
	// Note the vector size decreases after pop. 
	void pop_back();

	// The "insert" function inserts a new element 
	// "x" as the idx_th element in the current vector.
	// It also does nothing if "idx" is outside the 
	// range of the current vector. 
	void insert(int idx, int x);

	// The "erase" function removes the idx_th element 
	// from the vector. It also does nothing if the 
	// current vector is empty or if "idx" is outside 
	// the range of the current vector. 
	void erase(int idx);

	// The constructor should initialize 
	// pointer "p" to NULL and "size" to 0. 
	MyVector() {
		p = nullptr;
		size = 0;
	}

	// This is a destructor for the MyVector class.
	// It is responsible for cleaning up any dynamically allocated memory
	// used by the object. In this case, it deletes the array pointed to by 'p'.
	~MyVector() {
		delete[] p;
	}



private:

	int* p; // This pointer holds the vector (or,essentially, 
	// address of an array that holds the vector elements.)
	// Do remember to update it after some vector operations.

	int size; // This integer holds the size of the current 
	// vector. Do remember to update it after some 
	// vector operations. 
};

int MyVector::vsize() {
	// Returns the current size of the vector.
	return size;
}

int MyVector::empty() {
	// Checks if the vector is empty and returns 1 if empty, 0 otherwise.
	if (size != 0) {
		return 0;
	}
	else {
		return 1;
	}
}

int MyVector::at(int idx) {
	// Returns the element at the specified index 'idx' if it's a valid index,
	// otherwise, returns -1 to indicate an out-of-bounds access.
	if (idx >= 0 && idx < size) {
		return p[idx];
	}
	else {
		return -1;
	}
}

void MyVector::resize(int n) {
	// Resizes the vector to have 'n' elements.
	if (size == n) {
		return; // No need to resize if the new size is the same as the current size.
	}

	int* p2 = new int[n]; // Create a new array of size 'n'.

	if (size < n) {
		// Copy existing elements to the new array.
		for (int i = 0; i < size; i++) {
			p2[i] = p[i];
		}

		// Initialize any additional elements to 0.
		for (int i = size; i < n; i++) {
			p2[i] = 0;
		}
	}
	else {
		// Copy elements up to the new size.
		for (int i = 0; i < n; i++) {
			p2[i] = p[i];
		}
	}

	delete[] p; // Deallocate memory of the old array.
	p = p2; // Update the pointer to the new array.
	size = n; // Update the size.
}

void MyVector::push_back(int x) {
	// Appends an element 'x' to the end of the vector.
	resize(size + 1); // Resize the vector to accommodate the new element.
	p[size - 1] = x; // Assign the value 'x' to the last element.
}

void MyVector::pop_back() {
	if (size > 0) {
		resize(size - 1); // Remove the last element by resizing the vector.
	}
	else {
		delete[] p; // Deallocate memory if the vector is already empty.
		p = nullptr; // Set the pointer to nullptr to indicate an empty vector.
	}
}

void MyVector::insert(int idx, int x) {
	if (idx < 0 || idx > size) {
		return; // Index is out of bounds; nothing to insert.
	}

	resize(size + 1); // Resize the vector to accommodate the new element.
	int* p2 = new int[size]; // Create a new array with the updated size.

	// Copy elements from the old array to the new array, adjusting for the inserted element.
	for (int i = 0; i < idx; i++) {
		p2[i] = p[i];
	}

	p2[idx] = x; // Insert the new element at the specified index.

	for (int i = idx; i < size - 1; i++) {
		p2[i + 1] = p[i];
	}

	delete[] p; // Deallocate memory of the old array.
	p = p2; // Update the pointer to the new array.
}

void MyVector::erase(int idx) {
	if (idx < 0 || idx >= size || size == 0) {
		return; // Index is out of bounds or vector is empty; nothing to erase.
	}

	// Create a new array with one less element.
	int* p2 = new int[size - 1];

	// Copy elements from the old array to the new array, excluding the element at idx.
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (i != idx) {
			p2[j] = p[i];
			j++;
		}
	}

	delete[] p; // Deallocate memory of the old array.
	p = p2; // Update the pointer to the new array.
	size--; // Decrease the size.
	// Optionally, you might want to update capacity and perform capacity management.
}

	

// The main function has been completed for you. 
// It is used to test your implmentation. 
// You should not modify it (unless there is typo).
int main()
{
	MyVector x;

	int mode;
	int new_size, idx, data;
	int temp;

	cin >> mode; // This decides which function to test. 
	cin >> new_size >> idx >> data;

	// Mode 0: test push_back(), vsize() and at()
	if (mode == 0) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 1: test resize()
	else if (mode == 1)
	{
		while (cin >> temp) {
			x.push_back(temp);
		}

		x.resize(new_size);

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 2: test pop_back()
	else if (mode == 2) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		x.pop_back();

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 3: test insert()
	else if (mode == 3) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		x.insert(idx, data);

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	// Mode 4: test erase()
	else if (mode == 4) {

		while (cin >> temp) {
			x.push_back(temp);
		}

		x.erase(idx);

		cout << x.vsize() << '\n';

		for (int i = 0; i < x.vsize(); i++) {
			cout << x.at(i) << '\n';
		}
	}
	else {
		cout << "Wrong Mode Input!";
	}

	return 0;
}
