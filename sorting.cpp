#include <iostream>
#include <climits>
#include <cmath>
#include <cstring>
#include<cstdlib>

using namespace std;

// Print function
void print(int A[], int len) {
    for(int i=0; i<len; i++)
        cout << A[i] << " ";
    cout << endl;
}

// Selection Sort
void selectionSort(int A[], int len) {
	int temp, min;
	for(int i=0; i<len; i++) {
		min = i;
		for(int j=i+1; j<len; j++) {
			if(A[j] < A[min])
				min = j;		
		}
		temp = A[i];
		A[i] = A[min];
		A[min] = temp;	
	}
}

// Bubble Sort
void bubbleSort(int A[], int len) {
	int temp;
	for(int i=0; i<len-1; i++) {
		for(int j=0; j<len-i-1; j++) {
			if(A[j] > A[j+1]) {
				temp = A[j];
				A[j] = A[j+1];
				A[j+1] = temp;
			}		
		}
	}
}

// Insertion Sort
void insertionSort(int A[], int len) {
	int j, temp;
	for(int i=0; i<len; i++) {
		temp = A[i];
		for(j=i-1; j >=0 && A[j]>temp; j--) {
			A[j+1] = A[j];		
		}
		A[j+1] = temp;
	}
}

// Merge Sort
void merge(int A[], int mid, int len) {
	int *B = new int[len];
	int i = 0, j = mid, k = 0;
	while(i < mid && j < len) {
		if(A[i] < A[j])
			B[k++] = A[i++];
		else
			B[k++] = A[j++];	
	}
	while(i < mid)
		B[k++] = A[i++];
	while(j < len)
		B[k++] = A[j++];
		
	for(i=0; i<len; i++)
		A[i] = B[i];
	
	delete[] B;
}
void mergeSort(int A[], int len) {
	if(len <= 1)
		return;
	int mid = len/2;
	mergeSort(A, mid);
	mergeSort(A+mid, len-mid);
	merge(A, mid, len);
}

// Heap Sort
void heapify(int A[], int pos, int len) {
	int i = pos, l, r, temp, max;
	while(i < len) {
	    l = 2*i + 1;
		r = l + 1;
		max = i;
		if(l < len && A[l] > A[max])
			max = l;
		if(r < len && A[r] > A[max])
			max = r;
	
		if(max == i)
			break;
		else {
			temp = A[max];
			A[max] = A[i];
			A[i] = temp;
			i = max;
		}
	}
}
void buildHeap(int A[], int len) {
	for(int i=len-1; i>=0; i--)
		heapify(A, i, len);
}
void heapSort(int A[], int len) {
    int temp;
    buildHeap(A, len);
    for(int i=0; i<len; i++) {
        temp = A[0];
        A[0] = A[len-i-1];
        A[len-i-1] = temp;
        heapify(A, 0, len-i-1);
    }
}

// Counting Sort
void countingSort(int A[], int len, int max) {
	int C[max], B[len];
	for(int i=0; i<max; i++)
		C[i] = 0;
		
	for(int i=0; i<len; i++)
		C[A[i]]++;
		
	for(int i=1; i<max; i++)
		C[i] += C[i-1];
		
	for(int i=len-1; i>=0; i--) {
		B[C[A[i]]-1] = A[i];
		C[A[i]]--;
	}
	
	for(int i=0; i<len; i++)
		A[i] = B[i];
}

// Radix Sort
void radixSort(int A[], int len) {
	
	int C[10], B[len];
	int divN = 1;
	
	while(divN <= 1000) {
		for(int i=0; i<10; i++) 
			C[i] = 0;
		
		for(int i=0; i<len; i++)
			C[(A[i]/divN)%10]++;
			
		for(int i=1; i<len; i++)
			C[i] += C[i-1];
			
		for(int i=len-1; i>=0; i--) {
			B[C[(A[i]/divN)%10]-1] = A[i];
			C[(A[i]/divN)%10]--;
		}

		for(int i=0; i<len; i++)
			A[i] = B[i];
			
		divN *= 10;
	}
}

// Quick Sort
int partition(int A[], int len) {
	int temp, p = A[len-1];
	
	int j=-1;
	for(int i=0; i<len-1; i++) {
		if(A[i] <= p) {
			temp = A[i];
			A[i] = A[++j];
			A[j] = temp;
		}
	}
	A[len-1] = A[++j];
	A[j] = p;
	
	return j;
}
void quickSort(int A[], int len) {
	if(len <= 1)
		return;
		
	int p = partition(A, len);
	quickSort(A, p);
	quickSort(A+p+1, len-p-1);
}

// Merge Sort - Linked Lists
class Node {
	public:
		int data;
		Node *next;
};
Node *splitMid(Node *head) {
	Node *ptr1, *ptr2, *prev;
	ptr1 = ptr2 = head;
	prev = NULL;
	
	while(ptr2) {
		if(!ptr2->next)
			break;
			
		prev = ptr1;
		ptr1 = ptr1->next;
		ptr2 = ptr2->next->next;
		
	}
	prev->next = NULL;
	return ptr1;
}
Node *createList(int A[], int len) {
	Node temp, *prev;
	prev = &temp;
	int i = 0;
	while(i < len) {
		prev->next = new Node();
		prev = prev->next;
		prev->data = A[i];
		prev->next = NULL;
		i++;
	}
	return temp.next;
}
void printList(Node *head) {
	while(head) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

Node *merge(Node *A, Node *B) {
	Node temp, *prev;
	prev = &temp;
	
	while(A && B) {
		if(A->data < B->data) {
			prev->next = A;
			prev = prev->next;
			A = A->next;
		}
		else {
			prev->next = B;
			prev = prev->next;
			B = B->next;
		}	
	}
	A = (A)?A:B;
	while(A) {
		prev->next = A;
		prev = prev->next;
		A = A->next;
	}
	
	return temp.next;
}
Node *mergeSortLL(Node *head) {
	if(!head->next)
		return head;
	Node *left, *right, *mid;
	mid = splitMid(head);
	left = mergeSortLL(head);
	right = mergeSortLL(mid);
	return merge(left, right);
}

// Wave Sort
void waveSort(int A[], int len) {
	int temp;
	for(int i=0; i<len-1; i++) {
		if((i%2 == 0 && A[i] < A[i+1]) || (i%2 == 1 && A[i] > A[i+1])) {
			temp = A[i+1];
			A[i+1] = A[i];
			A[i] = temp;
		}
	}
}

int main() {
    int A[] = {1, 21, 6, 562, 5, 843, 5, 345, 5, 89, 111};
	print(A, 11);

	bubbleSort(A, 11);
	print(A, 11);
	return 0;
}