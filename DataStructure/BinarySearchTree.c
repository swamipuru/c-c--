#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
  int data;
  struct Node *left;
  struct Node *right;
}Node;


Node* getNode(int data){
  Node *node = (Node*)malloc(sizeof(Node));
  if(node){
    node->data = data;
    node->left = NULL;
    node->right = NULL;
  }
  return node;
}

void inorderTraversal(Node *node,int ht){
  if(node == NULL)
    return;
  inorderTraversal(node->left,ht+1);
  printf("%d : %d\n",node->data,ht);
   //printf("%d ",node->data);
  inorderTraversal(node->right,ht+1);
}

void insertLeft(Node *node, int data){
  node->left = getNode(data);
}

void insertRight(Node *node, int data){
  node->right = getNode(data);
}

void insertNode(Node **root,int data){
  if(*root == NULL){
    (*root) = getNode(data);
  }else{
    Node *ptr = *root;
    while(ptr->left != NULL && data <= ptr->data){
      ptr = ptr->left;
    }
    while(ptr->right != NULL && data > ptr->data){
      ptr = ptr->right;
    }
    if(data == ptr->data){
      printf("Adding duplicate %d to left.\n",data);
      insertLeft(ptr,data);
    }
    if(data < ptr->data)
      insertLeft(ptr,data);
    else
      insertRight(ptr,data);
  }
}


int getMaxHeight(Node *node){
  if(node == NULL)
    return 0;
  int ld = getMaxHeight(node->left);
  int rd = getMaxHeight(node->right);
  if(ld > rd)
    return ld + 1;
  else
    return rd + 1;
}

void calculateHeight(Node *node, int *ht){
  *ht = getMaxHeight(node);
}

void calcualteDepth(Node *node, int *dp){
  *dp = getMaxHeight(node)-1;
}


int getBalanceFactor(Node *node){
  if(node == NULL)
    return 0;
  int rh = getMaxHeight(node->right);
  int lh = getMaxHeight(node->left);
  return lh-rh;
}


void rightRotation(Node **node){
  Node *newNode = (*node)->left;
  Node *nr = newNode->right;
  newNode->right = (*node);
  (*node)->left = nr;
  (*node) = newNode;
}

void leftRotation(Node **node){
  Node *newNode = (*node)->right;
  newNode->left = (*node);
  (*node)->right = newNode->left;
  (*node) = newNode;
}

void balanceTree(Node *node){
  if(node == NULL)
    return;

  printf("node is %d bf: ",node->data);
  int bf = getBalanceFactor(node);
  int bfLeft = getBalanceFactor(node->left);
  int bfRight = getBalanceFactor(node->right);
  printf("%d\n",bfLeft);
  if(bf > 1){
     rightRotation(&(node));
   }
  else if(bf< -1){
    leftRotation(&node);
  }
  inorderTraversal(node,0);
  printf("\n");
  getchar();
  balanceTree(node->left);
  balanceTree(node->right);
}


int strcmp(char *s1, char *s2){
  int i=0,flag=1;
  while(s1[i] && s2[i]){
    if(s1[i] != s2[i])
      flag = 0;
    i++;
  }
  if(s1[i] || s2[i])
    flag = 0;
  return flag;
}
int main(int argc, char **argv){
  Node *root ;
  int hd=0;
  /*size_t nBytes=5;
  char *ch = (char*)malloc(nBytes+1);
  ch[0] = 10;
  printf("Enter end to break....");
  getline(&ch,&nBytes,stdin);
  while(strcmp(ch,"end\n")==0){
    printf("no is %d\n",atoi(ch));
    insertNode(&root,atoi(ch));
    getline(&ch,&nBytes,stdin);
  }*/
  insertNode(&root,10);
  insertNode(&root,20);
  insertNode(&root,15);
  insertNode(&root,8);
  insertNode(&root,9);
  insertNode(&root,7);
  insertNode(&root,30);
  insertNode(&root,25);
  insertNode(&root,5);
  insertNode(&root,3);
  insertNode(&root,2);
  insertNode(&root,1);
  printf("Tree is :\n");
  inorderTraversal(root,0);
  printf("\n");
  calculateHeight(root,&hd);
  printf("height:%d\n",hd);
  calcualteDepth(root,&hd);
  printf("depth: %d\n",hd);
  balanceTree(root);
  printf("\n\n");
  printf("New tree is :\n");
  inorderTraversal(root,0); 
  printf("\n\n"); 
  balanceTree(root);
  printf("New tree is :\n");
  inorderTraversal(root,0);  
  /*  printf("inserting 22\n");
  insertNode(&root,22);
  printf("Tree is:\n");
  inorderTraversal(root,0);
  balanceTree(root);
  printf("Balanced tree:\n");
  inorderTraversal(root,0);*/
  return 0;
}
