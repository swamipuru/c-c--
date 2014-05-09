#include<stdio.h>
#include<stdlib.h>
/* Max Size of Stack */
#define MAX_SIZE 100

/*Tree Node */
typedef struct node{
  int data;
  struct node *left;
  struct node *right;
}node;

/* Stack */
typedef struct{
  int top;
  node* contents[MAX_SIZE];
}stack;

/* 
 *Push data(Tree node) to stack till overflow
 *Logic: if top: less than MAX_SIZE
 *          Insert
 *       else:
 *           Overflow
*/
void push(stack *s, node* data){
  if(s->top < MAX_SIZE)
    s->contents[++(s->top)] = data;
  else
    printf("Stack Overflow....\n");
}

/*
 *Pop a node from the stack
 *Logic: if top: non-negative
 *          return the top element and decrment top by one.
 *        else:
 *           underflow
*/

node* pop(stack *s){
  if(s->top > -1){
    return s->contents[(s->top)--];
  }
  else{
    //    printf("Stack Underflow....\n");
    return NULL;
  }
}

/*
 *see the top element in the stack
 * return : stack[top]
*/
node* peek(stack s){
  return  s.contents[s.top];
}

/*
* PrintStack:
* print all the elements of stack
* LIFO - order
*/
void printStack(stack s){
  int i = s.top;
  printf("\nStack is : ");
  for(;i>=0;i--)
    printf("%d ",s.contents[s.top]->data);
  printf("\n");
}

/*
*Insert a node as left child of current node in the tree
*/
void insertLeft(node *ptr){
  ptr->left = (node*)malloc(sizeof(node));
  printf("Enter left child of %d:",ptr->data);
  scanf("%d",&ptr->left->data);
  ptr->left->left = NULL;
  ptr->left->right = NULL;
}

/*
*Insert a node as right child of current node in the tree
*/
void insertRight(node *ptr){
  printf("Enter right child of %d:",ptr->data);
  ptr->right = (node*)malloc(sizeof(node));
  scanf("%d",&ptr->right->data);
  ptr->right->left = NULL;
  ptr->right->right = NULL;
}

/*
*Create - sub tree of current node:
*Logic: if: there exist left child
*          insertLeft
*       else: 
*           make leftChild as NULL 
*       if : there exist right child
*           insertRight
*       else:
*           make rightChild as NULL
* call recursively for each node
*/
void createSubTree(node *ptr){
  char ch;
  printf("Sub tree of %d\n",ptr->data);  
  fflush(stdin);
  getchar();
  printf("Is left child 'y':");
  scanf("%c",&ch);
  if(ch == 'y' || ch == 'Y')
    insertLeft(ptr);
  printf("Is right child 'y':");
  fflush(stdin);
  getchar();
  scanf("%c",&ch);
  if(ch == 'y' || ch == 'Y')
    insertRight(ptr);
  if(ptr->left != NULL){
    printf("\nCreate sub tree of %d:\n",ptr->left->data);
    createSubTree(ptr->left);
  }
  if(ptr->right != NULL){
    printf("\nCreate sub tree of %d:\n",ptr->right->data);
    createSubTree(ptr->right);
  }
}

/*
* Create a Tree
* input: root Node of the tree
* create root node and then call creatSubtree of root
*/
void createTree(node **ptr){
  char ch;
  if(*ptr == NULL){
    *ptr = (node*)malloc(sizeof(node));
    (*ptr)->left = NULL;
    (*ptr)->right = NULL;
  }
  printf("Enter element: ");
  scanf("%d",&(*ptr)->data);
  createSubTree(*ptr);
}

/*
* Preorder Traversal:
* termination:
* if: node is NULL
* 
* print the node
* call Recursively for left child
* call Recusively for right child
*/
void preorderTraversalRecursive(node *ptr){
  if(ptr==NULL)
    return;
  printf("%d ",ptr->data);
  preorderTraversalRecursive(ptr->left);
  preorderTraversalRecursive(ptr->right);
}

/*
* Preorder traversal Non-recursive
* Logic:
*     maintains a stack to push the nodes, need to be visited later
*  Loop:
*     print the node
*     if: exists right child
*         push to stack
*     if: exists left child
*         push to stack
*         current node = pop a node from stack
*    continue loop till node is not NULL
*/
void preorderTraversalNonRecursive(node *ptr){
  stack s;
  s.top = -1;
  while(ptr != NULL){
  printf("%d ",ptr->data);
  if(ptr->right != NULL)
    push(&s,ptr->right);
  if(ptr->left != NULL)
    push(&s,ptr->left);
  ptr = pop(&s);
  }
  printf("\n");
}

/*
* Inorder Traversal:
* termination:
* if: node is NULL
* 
* call Recursively for left child
* print the node
* call Recusively for right child
*/
void inorderTraversalRecursive(node *ptr){
  if(ptr == NULL)
    return;
  inorderTraversalRecursive(ptr->left);
  printf("%d ",ptr->data);
  inorderTraversalRecursive(ptr->right);
}


/*
* Preorder traversal Non-recursive
* Logic:
*     maintains a stack to push the nodes, need to be visited later
*     First: push all the left children of root
*  Loop:
*     print the node
*     if: exists right child
*         push to stack
*         push all the left children of current node
*         current node = pop a node from stack
*    continue loop till node is not NULL
*/
void inorderTraversalNonRecursive(node *ptr){
  stack s;
  s.top = -1;
  while(ptr != NULL){
    push(&s,ptr);
    ptr = ptr->left;
  }
  ptr=pop(&s);
  while(ptr != NULL){
    printf("%d ",ptr->data);
    if(ptr->right!=NULL){
      push(&s,ptr->right);
      ptr = ptr->right;
      ptr = ptr->left;
      while(ptr != NULL){
	push(&s,ptr);
	ptr = ptr->left;
      }
    }
    ptr = pop(&s);  
  }
  printf("\n");
}

/*
* Postorder Traversal:
* termination:
* if: node is NULL
* 
* call Recursively for left child
* call Recusively for right child
* print the node
*/
void postorderTraversalRecursive(node *ptr){
  if(ptr == NULL)
    return;
  postorderTraversalRecursive(ptr->left);
  postorderTraversalRecursive(ptr->right);
  printf("%d ",ptr->data);
}

void postorderTraversalNonRecursive(node *ptr){
  stack s;
  s.top = -1;
  while(ptr != NULL){
    push(&s,ptr);
    ptr = ptr->left;
  }
  ptr = pop(&s);
  while(ptr != NULL){
    if(ptr->right != NULL){
      push(&s,ptr->right);
      ptr = ptr->right;
    }else if(ptr->left != NULL){
      push(&s,ptr->left);
      ptr = ptr->left;
      while(ptr != NULL){
	ptr = ptr->left;
	push(&s,ptr);
      }
    }
    printf("%d ",ptr->data);
    ptr = pop(&s);
  }
  printf("\n");
}

/*
 *Create mirror image of a tree
 * Take mirror of tree w.r.t Y-Axis
 * Recursive function
 * Termination condition:
 *       node == NULL
 * Logic:
 *    Make left child as right child of node
 *    Make right as left child of node
 *    (Swap both left and right children)
 *    Call recusively for both left and right subTree
*/

void createMirror(node *ptr){
  if(ptr == NULL)
    return;
  node *ptrLeft = ptr->left;
  node *ptrRight = ptr->right;
  ptr->left = ptrRight;
  ptr->right = ptrLeft;
  createMirror(ptr->left);
  createMirror(ptr->right);
}

/*
*
*/
void findMinMax(node *ptr, int *min, int *max, int hd){
  if(ptr == NULL)
    return;
  if(hd < *min)
    *min = hd;
  else if (hd > *max)
    *max = hd;
  findMinMax(ptr->left, min,max,hd+1);
  findMinMax(ptr->right, min,max,hd-1);
}

/*
*
*/
void printVerticalLine(node *ptr,int lineNo, int hd){
  if(ptr == NULL)
    return;
  if(hd == lineNo)
  printf("%d ",ptr->data);
  printVerticalLine(ptr->left,lineNo,hd+1);
  printVerticalLine(ptr->right,lineNo,hd-1d);
}



/*
*Vertical Traversal
*/

void verticalTraversal(node *ptr){
  int min=0;
  int max=0;
  int lineNo=0;
  int hd = 0;
  findMinMax(ptr, &min, &max, hd);
  printf("Min: %d\nMax :%d\n",min,max);
  for(lineNo = min; lineNo <= max;lineNo++){
    printVerticalLine(ptr,lineNo,0);
    printf("\n");
  }
  /*
  stack vs,s;
  vs.top = -1;
  s.top = -1;
  while(ptr->left!= NULL){
    push(&vs,ptr);
    ptr = ptr->left;
  }
  while(ptr != NULL){
    printf("%d ",ptr->data);
    if(ptr->right != NULL){
      push(&s,ptr->right);
    }
    ptr = pop(&vs);
    if(ptr == NULL){
      ptr = pop(&s);
      while(ptr != NULL){
	printf("%d ",ptr->data);
	ptr = pop(&s);
      }
      printf("\n");
    }
    printf("\n");
    }*/
}

int main(){
  node *root;
  createTree(&root);
  printf("Recursive Pre order traversal\n");
  preorderTraversalRecursive(root);
  printf("\nNonRecursive Pre order traversal\n");
  preorderTraversalNonRecursive(root);
  printf("Recursie Inorder Traversal\n");
  inorderTraversalRecursive(root);
  printf("\nNonRecursive In order traversal\n");
  inorderTraversalNonRecursive(root);
  printf("\nRecursice Postorder traversal\n");
  postorderTraversalRecursive(root);
  printf("\n");//NonRecursive Postorder traversal\n");
  //postorderTraversalNonRecursive(root);
  createMirror(root);
  printf("\nMirrored Tree:\n");
  printf("Recursive Pre order traversal\n");
  preorderTraversalRecursive(root);
  printf("\nNonRecursive Pre order traversal\n");
  preorderTraversalNonRecursive(root);
  printf("Recursie Inorder Traversal\n");
  inorderTraversalRecursive(root);
  printf("\nNonRecursive In order traversal\n");
  inorderTraversalNonRecursive(root);
  printf("\nRecursice Postorder traversal\n");
  postorderTraversalRecursive(root);
  printf("\n");//NonRecursive Postorder traversal\n");
  printf("\nVertical Traversal: \n");
  verticalTraversal(root);
  return 0;
}
