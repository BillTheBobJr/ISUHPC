# ifndef __NODE_H__
# define __NODE_H__

typedef struct node node;
struct node
{
int value;
int position;
node* next;
};

// Functions associated with struct node
void Push(node** top, const int input);
void Pop(node** top, int* output);
void Peek(node** top, int* output);
void DisplayStack(node* top);
void PrintNode(node* top);
void PreformOperation(node** top, const char operation);
void GetStackSize(node* top, int* stack_size);
void Flush();



#endif