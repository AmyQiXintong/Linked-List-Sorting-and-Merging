// this program aims to use linked list to perform sorting and merging
 
#include <iostream>
 
using namespace std;
 
class Node
{
public:
    int data;
    Node* next;
};
 
// build the linked list
void add(Node** start, int value)
{
    Node* tmp = new Node;
    Node* ptr;
    tmp->data = value;
    tmp->next = NULL;
 
    if (*start == NULL) {
        *start = tmp;
    }
    else {
        ptr = *start;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = tmp;
    }
}
 
Node* build(int arr[], int n)
{
    Node* start = NULL;
    for (int i = 0; i < n; i++) {
        add(&start, arr[i]);
    }
    return start;
}
 
// remove duplicates
void duplicates(Node* start)
{
    Node* ptr1, * ptr2, * tmp;
    ptr1 = start;
 
    while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2 = ptr1;
 
        while (ptr2->next != NULL)
        {
            if (ptr1->data == ptr2->next->data)
            {
                tmp = ptr2->next;
                ptr2->next = ptr2->next->next;
                delete(tmp);
            }
            else{
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
}
 
// sort the lists using bubble sort
int findSize(Node* start) {
    Node* count = start;
    int size = 1;
    while (count->next != NULL)
    {
        size++;
        count = count->next;
    }
    return size;
}
 
Node* swap(Node* ptr1, Node* ptr2)
{
    Node* tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}
 
void bubbleSort(Node** start, int count)
{
    Node** sta;
    int i, j, swapped;
    for (i = 0; i <= count; i++)
    {
        sta = start;
        swapped = 0;
        for (j = 0; j < count - i - 1; j++)
        {
            Node* p1 = *sta;
            Node* p2 = p1->next;
            if (p1->data > p2->data)
            {
                *sta = swap(p1, p2);
                swapped = 1;
            }
            sta = &(*sta)->next;
        }
        if (swapped == 0)
            break;
    }
}
 
// print the content
void print(Node* start)
{
    while (start != NULL) {
        cout << start->data << " ";
        start = start->next;
    }
}
 
// merge the lists
Node* merge(Node* a, Node* b)
{
    Node* result = NULL;
 
    if (a == NULL)
        return(b);
    else if (b == NULL)
        return(a);
 
    if (a->data <= b->data)
    {
        result = a;
        result->next = merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = merge(a, b->next);
    }
    return(result);
}
 
// the main function
int main()
{
    // get user input and store them in two lists
    cout << "Please input the count of the numbers: ";
    int num1, num2;
    cin >> num1 >> num2;
    int* list1 = NULL;
    int* list2 = NULL;
    list1 = new int[num1];
    list2 = new int[num2];
    cout << "Please input the content of the numbers of first linked list: ";
    for (int i = 0; i < num1; i++)
    {
        cin >> list1[i];
    }
    cout << "Please input the content of the numbers of second linked list: ";
    for (int i = 0; i < num2; i++)
    {
        cin >> list2[i];
    }
 
    //build the linked list
    Node* start1 = build(list1, num1);
    Node* start2 = build(list2, num2);
 
    // remove the duplicates
    duplicates(start1);
    duplicates(start2);
 
    // sort the linked lists
    int size1 = findSize(start1);
    int size2 = findSize(start2);
    bubbleSort(&start1,size1);
    bubbleSort(&start2,size2);
 
    //show the result
    Node* result = merge(start1, start2);
 
    // remove duplicates
    duplicates(result);
 
    // give the result
    cout << endl;
    cout << "The merged linked list is: ";
    print(result);
 
    // release the memory space
    delete[] list1, list2;
    list1 = NULL, list2 = NULL;
}
