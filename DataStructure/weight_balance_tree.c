#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define BLOCKSIZE 256
#define MAX_SIZE 1000
typedef int object_t;
typedef int key_t;
typedef struct tr_n_t { key_t        key;
                    struct tr_n_t  *left;
                    struct tr_n_t *right;
                    int           weight; 
                  } tree_node_t;

tree_node_t *currentblock = NULL;
int    size_left;
tree_node_t *free_list = NULL;

tree_node_t *get_node()
{ tree_node_t *tmp;
  if( free_list != NULL )
  {  tmp = free_list;
     free_list = free_list -> left;
  }
  else
  {  if( currentblock == NULL || size_left == 0)
     {  currentblock = 
                (tree_node_t *) malloc( BLOCKSIZE * sizeof(tree_node_t) );
        size_left = BLOCKSIZE;
     }
     tmp = currentblock++;
     size_left -= 1;
  }
  return( tmp );
}


void return_node(tree_node_t *node)
{  node->left = free_list;
   free_list = node;
}


void left_rotation(tree_node_t *n)
{  tree_node_t *tmp_node;
   key_t        tmp_key;
   tmp_node = n->left; 
   tmp_key  = n->key;
   n->left  = n->right;        
   n->key   = n->right->key;
   n->right = n->left->right;  
   n->left->right = n->left->left;
   n->left->left  = tmp_node;
   n->left->key   = tmp_key;
}

void right_rotation(tree_node_t *n)
{  tree_node_t *tmp_node;
   key_t        tmp_key;
   tmp_node = n->right; 
   tmp_key  = n->key;
   n->right = n->left;        
   n->key   = n->left->key;
   n->left  = n->right->left;  
   n->right->left = n->right->right;
   n->right->right  = tmp_node;
   n->right->key   = tmp_key;
}

object_t *find(tree_node_t *tree, key_t query_key){
  tree_node_t *tmp_node;
  if( tree->left == NULL )
    return(NULL);
  else{
    tmp_node = tree;
    while( tmp_node->right != NULL ){
      if( query_key < tmp_node->key )
	tmp_node = tmp_node->left;
      else
	tmp_node = tmp_node->right;
    }
    if( tmp_node->key == query_key )
      return( (object_t *) tmp_node->left );
    else
      return( NULL );
  }
}


void check_tree( tree_node_t *tr, int depth, int lower, int upper )
{  if( tr->left == NULL )
   {  printf("Tree Empty "); return; }
   if( tr->key < lower || tr->key >= upper )
         printf("Wrong Key Order ");
   if( tr->right == NULL ){
     if( *( (int *) tr->left) == 10*tr->key + 2 )
       printf("%d(%d)  ", tr->key, depth );
     else{
       printf("Wrong Object ");
     }
   }
   else
   {  check_tree(tr->left, depth+1, lower, tr->key ); 
      check_tree(tr->right, depth+1, tr->key, upper ); 
   }
}



tree_node_t *make_top_down_tree(tree_node_t *list){
  typedef struct { tree_node_t  *node1;
    tree_node_t  *node2; 
    int number; } st_item;
  st_item current, left, right;
  st_item stack[MAX_SIZE]; int st_p = 0;
  tree_node_t *tmp, *root;
  int length = 0;
  for( tmp = list; tmp != NULL; tmp = tmp->right )
    length += 1; /* find length of list */
   
  root = get_node();
  current.node1 = root; /* put root node on stack */
  current.node2 = NULL; 
  current.number = length;/* root expands to length leaves */
  stack[ st_p++ ] = current;
  while( st_p >0 ){/* there is still unexpanded node */
    current = stack[ --st_p ];
    if( current.number > 1 ){ /* create (empty) tree nodes */
      left.node1 = get_node();
      left.node2 = current.node2;
      left.number = current.number / 2;
      right.node1 = get_node();
      right.node2 = current.node1;
      right.number = current.number - left.number;
      (current.node1)->left  = left.node1;
      (current.node1)->right = right.node1;
      stack[ st_p++ ] = right;
      stack[ st_p++ ] = left;
    }
    else{ /* reached a leaf, must be filled with list item */
      (current.node1)->left  = list->left;   /* fill leaf */
      (current.node1)->key   = list->key;    /* from list */
      (current.node1)->right = NULL;
      if( current.node2 != NULL )
           /* insert comparison key in interior node */
	(current.node2)->key   = list->key;
      tmp = list;          /* unlink first item from list */
      list = list->right;  /* content has been copied to */
      return_node(tmp);    /* leaf, so node is returned */
    }
  }
  return( root );
}

void print_list(tree_node_t *list){
  tree_node_t *list_node = list;
  for(list_node;list_node != NULL; list_node = list_node->right)
    printf("%d ",list_node->key);
  printf("\n");
}

void print_stack(tree_node_t *stack[MAX_SIZE], int st_p){
  int i=0;
  for(i=0;i<st_p;i++)
    printf("%d ",stack[i]->key);
  printf("\n");
}


tree_node_t *make_tree_list(tree_node_t *tree){
  tree_node_t *list, *node;
  if( tree->left == NULL ){
    return_node( tree );
    return( NULL );
  }
  else{
    tree_node_t *stack[MAX_SIZE]; int st_p =0;
    stack[ st_p++ ] = tree;
    list = NULL;
    while( st_p > 0 ){
      node = stack[ --st_p ];
      if( node->right == NULL ){
	node->right = list;
	list = node;
      }
      else{
	stack[ st_p++ ] = node->left;
	stack[ st_p++ ] = node->right;
        return_node( node );
      }
    }
    return( list );
  }
}


tree_node_t *make_list(tree_node_t *tree){
  tree_node_t *list, *node;
  if( tree->left == NULL ){
    return_node( tree );
    return( NULL );
  }
  else{
    tree_node_t *stack[MAX_SIZE]; int st_p =0;
    stack[ st_p++ ] = tree;
    list = NULL;
    while( st_p > 0 ){
      node = stack[ --st_p ];
      if( node->right == NULL ){/*append node->right to front of the list */
	if(list == NULL){
	  list = (tree_node_t*)malloc(sizeof(tree_node_t));
	  list->key = node->key;
	  list->left = NULL;
	  list->right = NULL;
	}else{
	  tree_node_t *tmp = (tree_node_t*)malloc(sizeof(tree_node_t));
	  tmp->key = node->key;
	  tmp->right = list;
	  tmp->left = NULL;
	  list = tmp;
	}
      }
      else{
	stack[ st_p++ ] = node->left;
	stack[ st_p++ ] = node->right;
      }
    }
    return( list );
  }
}

tree_node_t *concatenate_list(tree_node_t *left_list, tree_node_t *right_list){
  tree_node_t *list, *tmp = left_list;
  list = tmp;
  while(tmp->right != NULL){
    tmp = tmp->right;
  }
  tmp->right = right_list;
  return( list );
}


tree_node_t *create_tree(void)
{  tree_node_t *tmp_node;
   tmp_node = get_node();
   tmp_node->left = NULL;
   return( tmp_node );
}


#define ALPHA 0.25// (1/4)

int insert(tree_node_t *tree, key_t new_key, object_t *new_object)
{  tree_node_t *tmp_node;
   if( tree->left == NULL )
   {  tree->left = (tree_node_t *) new_object;
      tree->key  = new_key;
      tree->weight = 1;
      tree->right  = NULL; 
   }
   else{
     tree_node_t * path_stack[MAX_SIZE]; int  path_st_p = 0;
     int direction_stack[MAX_SIZE]={0};/*left: 1 right: 2*/
     tmp_node = tree;;
     while( tmp_node->right != NULL ){
       path_stack[path_st_p++] = tmp_node;
       if(  new_key < tmp_node->key){
	 tmp_node = tmp_node->left;
	 direction_stack[path_st_p] = 1;
       }
       else{
	 tmp_node = tmp_node->right;
	 direction_stack[path_st_p]=2;
       }
     }
      /* found the candidate leaf. Test whether key distinct */
     if( tmp_node->key == new_key )
       return( -1 );
      /* key is distinct, now perform the insert */ 
      {  
	tree_node_t *old_leaf, *new_leaf;
	old_leaf = get_node();
	old_leaf->left = tmp_node->left;
	old_leaf->key = tmp_node->key;
	old_leaf->right  = NULL;
	old_leaf->weight = 1;
	new_leaf = get_node();
	new_leaf->left = (tree_node_t *) new_object;
	new_leaf->key = new_key;
	new_leaf->right  = NULL;
	new_leaf->weight = 1;
	if( tmp_node->key < new_key ){
	  tmp_node->left  = old_leaf;
	  tmp_node->right = new_leaf;
	  tmp_node->key = new_key;
	}
	else{
	  tmp_node->left  = new_leaf;
	  tmp_node->right = old_leaf;
	}
	tmp_node->weight = 2;
      }
      /* rebalance  Weight Balance Tree 3.2 */
      tree_node_t *ptr = tree;
      tree_node_t *left_list, *right_list, *list;
      int depth = path_st_p;
      float THRESHOLD;

      /* find THRESHOLD*/
      /* 
       * to calcualte THRESHOLD we need n: 
       * here h: is the number of nodes in the path list
       * (we can take n = total number of nodes in the tree)
       * (need to be clear--- NOT SURE????)
       */
      if(depth > 1){
	THRESHOLD = log(depth)/log((1/(1-ALPHA)));
	if((float)depth > THRESHOLD){/* Required rebalancing Depth is above threshold */
	// calculate THRESHOLD
	  int length = 0;
	  tree_node_t *list_node;
	  tree_node_t *ptr;
	  int node_index;
	  float HEIGHT_THRESHOLD;
	  do{
	    tmp_node = path_stack[--depth];
          /* Left list */
	    ptr = tmp_node->left;
	    left_list = make_list(ptr);

	  /* Right list*/
	    ptr = tmp_node->right;
	    right_list = make_list(ptr);

	  /* Complete list*/
	    list = concatenate_list(left_list, right_list);
	  /* calcualte lenght of complete list and ith node.*/
	    for(list_node = list;  list_node != NULL; list_node = list_node->right){
	      if(list_node->key == new_key)
		node_index = length;
	      length++;
	    }
	    HEIGHT_THRESHOLD = pow(1.0/(1.0 - ALPHA),node_index);
	  }while((float)length > HEIGHT_THRESHOLD && depth > 0);/* the number of leaves in this list is greater than (1/(1-ALPHA))^index*/
	  left_list = make_tree_list(tmp_node->left);
	  right_list = make_tree_list(tmp_node->right);
	  list = concatenate_list(left_list, right_list);
	  if(depth == 0){
	    tree = make_top_down_tree(list);/* Create top down tree from the list.*/
	  }
	  else{
	    int curKey = tmp_node->key;
      	    tree_node_t *ptr = path_stack[--depth];
	    int upperKey = tmp_node->key;
	    tmp_node = make_top_down_tree(list);
	    //	    printf("Upper key :%d current key: %d\n",upperKey, curKey);
	    if(direction_stack[depth] == 1){//curkey < upperkey){
	      /*leftt side*/
	      ptr->left = tmp_node;
	    }else{
	      /*right side*/
	      ptr->right = tmp_node;
	    }
	  }
	  //printf("balanced tree: ");
	  //check_tree(tree,0,-10000,10000);
	}
      }
      //printf("\nend of rebalancing.\n");
      /*end rebalance*/
   }
   /*   printf("balanced tree: ");
   check_tree(tree,0,-10000,10000);
   printf("\n");
   */
   return( 0 );
}


object_t *delete(tree_node_t *tree, key_t delete_key)
{  tree_node_t *tmp_node, *upper_node, *other_node;
   object_t *deleted_object;
   if( tree->left == NULL )
      return( NULL );
   else if( tree->right == NULL )
   {  if(  tree->key == delete_key )
      {  deleted_object = (object_t *) tree->left;
         tree->left = NULL;
         return( deleted_object );
      }
      else
         return( NULL );
   }
   else
   {  tree_node_t * path_stack[100]; int path_st_p = 0;
      tmp_node = tree;
      while( tmp_node->right != NULL )
      {   path_stack[path_st_p++] = tmp_node;  
          upper_node = tmp_node;
          if( delete_key < tmp_node->key )
          {  tmp_node   = upper_node->left; 
             other_node = upper_node->right;
          } 
          else
          {  tmp_node   = upper_node->right; 
             other_node = upper_node->left;
          } 
      }
      if( tmp_node->key != delete_key )
         deleted_object = NULL;
      else
      {  upper_node->key   = other_node->key;
         upper_node->left  = other_node->left;
         upper_node->right = other_node->right;
         upper_node->weight = other_node->weight;
         deleted_object = (object_t *) tmp_node->left;
         return_node( tmp_node );
         return_node( other_node );
      }
      /*start rebalance*/
      //TO DO
      /*end rebalance*/
      return( deleted_object );
   }
}



int main()
{  tree_node_t *searchtree,*secondtree;
   char nextop;
   int i=0,j=0;
   searchtree = create_tree();
   secondtree = create_tree();
   printf("Made Tree: Weight-Balanced Tree\n");
   while( (nextop = getchar())!= 'q' )
   { if( nextop == 'i' )
     { int inskey,  *insobj, success;

       for(j=1,i = 20;j<20,i>0;j++,i--){
	 //       scanf(" %d", &inskey);
	 inskey = 10*i;       
	 insobj = (int *) malloc(sizeof(int));
	 *insobj = 10*inskey+2;
	 success = insert( searchtree, inskey, insobj );
	 if ( success == 0 )
         printf("  insert successful, key = %d, object value = %d, \
                  weight is %d\n",
		inskey, *insobj, searchtree->weight );
	 else
           printf("  insert failed, success = %d\n", success);
	 inskey = 10*j;
	 insobj = (int *)malloc(sizeof(int));
	 *insobj = 10*inskey+2;
	 success = insert( secondtree, inskey, insobj );
	 if ( success == 0 )
         printf("  insert successful, key = %d, object value = %d, \
                  weight is %d\n",
		inskey, *insobj, searchtree->weight );
	 else
           printf("  insert failed, success = %d\n", success);

	 //	 getchar();
       }
     }  
     if( nextop == 'f' )
     { int findkey, *findobj;
       scanf(" %d", &findkey);
       findobj = find( searchtree, findkey);
       if( findobj == NULL )
         printf("  find failed, for key %d\n", findkey);
       else
         printf("  find successful, found object %d\n", *findobj);
     }
     if( nextop == 'd' )
     { int delkey, *delobj;
       scanf(" %d", &delkey);
       delobj = delete( searchtree, delkey);
       if( delobj == NULL )
         printf("  delete failed for key %d\n", delkey);
       else
         printf("  delete successful, deleted object %d, weight is now %d\n", 
             *delobj, searchtree->weight);
     }
     if( nextop == '?' )
     {  printf("  Checking searchtree\n"); 
        check_tree(searchtree,0,-10000,10000);
        printf("\n");
        if( searchtree->left != NULL )
	  printf("key in root is %d, weight of tree is %d\n", 
		 searchtree->key, searchtree->weight );
        printf("  Finished Checking tree\n"); 
	printf("  Checking secondtree\n");;
        check_tree(secondtree,0,-10000,10000);
        printf("\n");
        if( searchtree->left != NULL )
	  printf("key in root is %d, weight of tree is %d\n", 
		 searchtree->key, searchtree->weight );
        printf("  Finished Checking tree\n"); 
     }
   }
   return(0);
}
