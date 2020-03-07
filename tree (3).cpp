#include <iostream>
using namespace std;
#include "tree.h"

// Insert an item into the subtree rooted at "root".
// If x is already in the tree, it does nothing.
// Returns the new root.
// Should take time O(depth).
node* insert (node *root, int x){

	if(root == NULL){
		root  =  new node(x);
		root->left = root->right = NULL;
		root->parent = NULL;
	}
	else if(x < root->value){
		root->left = insert(root->left, x);
		root->left->parent = root;
	}

	else if(x > root->value){
		root-> right  = insert(root->right, x);
		root->right->parent = root;

	}
	if(root){
		root->size = 1;
		if(root->left){
			root->size = root->left->size + root->size;

		}
		if(root->right){
			root->size = root->right->size + root->size;
		}
	}

	return root;
}
// Erases the node containing value "x" from the subtree rooted at "root".
// Returns the new root.
// Should take time O(depth).
node* erase (node *root, int x){
	if(root == NULL){
		return  root;
	}
	if(x > root->value){
		root->right = erase(root->right, x);
	}
	else if(x < root->value){
		root->left = erase(root->left, x);
	}

	//node to be deleted is found, ready to be deleted
	else{
        if(!root->left && !root->right){
        // no child
        delete root;
root = NULL;
        }

        else if(root->left == nullptr){     //right child only
        node* temp = root;
	    root = root->right;
	    root->parent = temp->parent;
	    delete temp;


        }

        else if(root->right == nullptr){// left child only
	    node* temp = root;
	    root = root->left;
	    root->parent = temp->parent;
	    delete temp;

        }

        else{ // 2 children
	         	node*temp = find_min(root->right);
		        root->value = temp->value;
		        root->right = erase(root->right, temp->value);
	            }


	}
	if(root){
		root->size = 1;
		if(root->left){
			root->size = root->left->size + root->size;

		}
		if(root->right){
			root->size = root->right->size + root->size;
		}
	}

	return root;
	}

// Searches for a node with value "x" in the subtree rooted at "root",
// and returns a pointer to such node if found.
// Else it returns nullptr.
// Should take time O(depth).
node* find (node *root, int x){

if(root == nullptr){
	return NULL;
}
if(root->value == x){

	return root;

}
if(x > root->value){
return find(root->right, x);
}
if(x < root->value){
return find(root->left, x);
}
return NULL;
}


// Frees all nodes in the subtree rooted at "root".
// Should take time O(n).
void clear (node *root){
	if(root){
		node* l;
		node* r;
		l  = root->left;
		r = root->right;
		delete root;
		if(l){
			clear(l);
		}

		if(r){
			clear(r);
		}

}
}

// Makes a copy of the subtree rooted at "root", returns a pointer to the new root.
// Should take time O(n).
node* copy (node *root){
	if(!root){
		return nullptr;
	}

	node *new_root = new node(root->value);
    if(root->right){
    new_root->right = copy(root->right);
    new_root->right->parent = new_root;
    new_root->size = new_root->right->size + new_root->size;
    }



    if(root->left){
    new_root->left = copy(root->left);
    new_root->left->parent = new_root;
    new_root->size = new_root->left->size + new_root->size;
    }

return new_root;
}
node* find_min (node *root){
node*cur = root;
	while(cur->left!=NULL){
		cur  = cur->left;
	}
	return cur;
}

// Finds the maximum of subtree rooted at "root".
// Should take time O(depth).
node* find_max (node *root){
	node*cur = root;
		while(cur->right!=NULL){
			cur  = cur->right;
		}
		return cur;

}

// Finds the predecessor of the node "which".
// If "which" is nullptr, or the minimum node,
// should return nullptr.
// Should take time O(depth).
node* predecessor (node *which){
if(which->left){
	return find_max(which->left);
}
while(which->parent && which == which->parent->left){
	which = which->parent;
}
return which->parent;
}

// Finds the predecessor of the node "which".
// If "which" is nullptr, or the maximum node,
// should return nullptr.
// Should take time O(depth).
node* successor (node *which){

	if(which->right){
		return find_min(which->right);
	}
	while(which->parent && which == which->parent->right){
		which = which->parent;
	}
	return which->parent;
	}



// Finds the depth of the subtree rooted at "root".
// If the tree is empty, should return -1.
// Should take time O(n).
int depth (node *root){
	if(!root){
		return -1;
	}
	int l = depth(root->left) + 1;
	int r = depth(root->right) + 1;
	return max(r, l);
}

// Finds the kth smallest node in the subtree rooted at "root".
// If no such node exists, should return nullptr.
// Should take time O(depth).
node* find_by_rank (node *root, size_t k){

        if(root->size == 0){
        return nullptr;
        }

        if(k==0){
        	return find_min(root);
        }

        if(k>=root->size){
        return nullptr;
        }

        if(!root->left){

        	return find_by_rank(root->right, k-1);
        }

        else{
          	if(k<root->left->size){
            		return find_by_rank(root->left, k);
            	}

            	else if(k>root->left->size){
            		return find_by_rank(root->right, k-root->left->size-1);
            	}

            	else{
            		return root;
            	}
        }

        return nullptr;

}
