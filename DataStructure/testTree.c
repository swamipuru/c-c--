#define alpha 0.20
#define EPSILON 0.005

int insert(tree_node_t *tree, key_t new_key, object_t *new_object)
{  int n;
long threshold;
tree_node_t *tmp_node;
   if( tree->left == NULL )
   {  tree->left = (tree_node_t *) new_object;
      tree->key  = new_key;
      tree->weight = 1;
      tree->right  = NULL; 
   }
   else
   {  tree_node_t * path_stack[100]; int  path_st_p = 0;
      tmp_node = tree; 
      while( tmp_node->right != NULL )
      {   path_stack[path_st_p++] = tmp_node;
          if(  new_key < tmp_node->key )
               tmp_node = tmp_node->left;
          else
               tmp_node = tmp_node->right;
      }
      /* found the candidate leaf. Test whether key distinct */
      if( tmp_node->key == new_key )
         return( -1 );
      /* key is distinct, now perform the insert */ 
      {  tree_node_t *old_leaf, *new_leaf;
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
         if( tmp_node->key < new_key )
         {   tmp_node->left  = old_leaf;
             tmp_node->right = new_leaf;
             tmp_node->key = new_key;
         } 
         else
         {   tmp_node->left  = new_leaf;
             tmp_node->right = old_leaf;
         } 
         tmp_node->weight = 2;
         
         // rebalcing with alpha weight balance 
         threshold = log(n)/(log(1/(1-alpha)));
if(path_st_p < threshold)
{
	printf("no need to do rebalancing");
}
else
{
	tree_node_t *make_list(tree_node_t *tree)
{  tree_node_t *list, *node;
   if( tree->left == NULL )
   { return_node( tree );
     return( NULL );
   } 
   else
   {  tree_node_t *stack[100]; int st_p =0;
      stack[ st_p++ ] = tree;
      list = NULL;
      while( st_p > 0 )
      {  node = stack[ --st_p ];
         if( node->right == NULL )
         { node->right = list;
           list = node;
         }
         else
         { stack[ st_p++ ] = node->left ;
           stack[ st_p++ ] = node->right ;
           return_node( node );
         }
      }
      return( list );
   }
}
    tree_node_t *list1, *list2, *list3, *tmp, *tmp1;
    new_leaf->left = tmp;// here there is the currebt inserted object after insertion. so after insertion this should be our current position from where we should go upward
    //function to concatenate 2 linked lists 
		tree_node_t *concat(tree_node_t *list1, tree_node_t *list2)
	{
		tree_node_t *tmp1;
	
	if(list1 == NULL){
		list1 = list2;
	}
	else
	{
		tmp1 = list1;
		while(tmp1->next != NULL){
			tmp1 = tmp1->next;
		}
		tmp1->next = list2;
	}
	return;
}

	if(tmp_node->key < new_key){
	tmp_node = tmp->upper;
	list1 = make_list(tmp_node->left);// right subtree linked list
	tmp_node = tmp_node->upper;
	list2 = make_list(tmp_node->left);// left subtree linked list 
	// concatenating 2 lists 
list3 = concat(list1,list2);
}
else
{
		tmp_node = tmp->upper;
	list1 = make_list(tmp_node->left);// left subtree linked list
	tmp_node = tmp_node->upper;
	list2 = make_list(tmp_node->right);// right subtree linked list 
	// concatenating 2 lists 
list3 = concat(list1,list2);
}
