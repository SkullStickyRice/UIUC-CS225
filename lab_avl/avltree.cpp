/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
  // your code here
	Node *temp = t->right;
	t->right = temp->left;
	temp->left = t;
	//t -> height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;

	t -> height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
	temp -> height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
	t = temp;

	
	
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);

	
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	Node *temp = t->left;
	t->left = temp->right;
	temp->right = t;
	//t -> height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;

	t -> height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
	temp -> height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
	t = temp;
	
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	rotateRight(t->right);
	rotateLeft(t);

	
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
	if (subtree == NULL) {
		return;
	}
    // your code here
	int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
	//int leftbalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
	//int rightbalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
	
	if (balance == -2) {
		int leftbalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
		if (leftbalance == -1) {
			rotateRight(subtree);
		}
		else {
			rotateLeftRight(subtree);
		}
	}
	if (balance == 2) {
		int rightbalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
		if (rightbalance == 1) {
			rotateLeft(subtree);
		}
		else {
			rotateRightLeft(subtree);
		}
	}
	subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here

	if (subtree == NULL) {
		subtree = new Node(key, value);
	}
	else if (key < subtree->key) {
		insert(subtree->left,key,value);
	//cout<<"insert left"<<endl;
		rebalance(subtree);
	}
	else if (key > subtree->key) {
		insert(subtree->right, key, value);
	//cout<<"insert right"<<endl;
		rebalance(subtree);
	}
	//subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right))+1; 
	

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
	remove(subtree->left,key);
	//rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
	remove(subtree->right,key);
	//rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) { 
            /* no-child remove */
            // your code here
		delete subtree;
		subtree = NULL;
		//cout<<"nochild"<<endl;
        } else if (subtree->left != NULL && subtree->right != NULL) { 
            /* two-child remove */
		Node *iop = subtree->left;
		//cout<<"start iop key"<<iop->key<<endl;
		while (iop->right != NULL) {
			iop = iop->right;
		}
		//cout<<"final iop key"<<iop->key<<endl;
		swap(subtree,iop);
		//cout<<"swap iop key"<<iop->key<<endl;
	//	cout<<"swap subtree key"<<subtree->key<<endl;
		remove(subtree->left,key);
	

        } else { 
            /* one-child remove */
            // your code here

		if (subtree->left == NULL) {
			swap(subtree,subtree->right);
			remove(subtree->right,key);
			//cout<<"one child right"<<endl;
		}
		else {
			swap(subtree,subtree->left);
			remove(subtree->left,key);
			//cout<<"one child left"<<endl;
		}
		
        }
        // your code here
    }

	/*if (subtree != NULL) {
		subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right))+1; 
	}*/
	//cout<<"before belance"<<endl;
	rebalance(subtree);
	//cout<<"rebalance"<<endl;
	

}

