#pragma once
#include"BSTree.h"
#include "Collection.h"

//Randomize Binary Search Tree (RBST)
template <typename K, typename T>
class RBSTree : public BSTree<K,T>
{
	
public:
	
	//class Collection<K,T>::Node : public Collection<K,T>::Node{
	//public:
	//	Collection<K,T>::Node* right;			// Указатель на правый элемент поддерева
	//	Collection<K,T>::Node* left;			// Указатель на левый элемент поддерева
	//	
	//	Collection<K,T>::Node() { sizeNode = 1; }		// Конструктор по умолчанию
	//	Collection<K,T>::Node(K key, T value,Collection<K,T>::Node* left,Collection<K,T>::Node* right ) :Node( key,  value,left, right) {
	//		right = right;
	//		left = left;
	//		fixsize();
	//	} // Конструктор с параметрами

	//	~Collection<K,T>::Node() {}				// Деструктор
	//	int sizeNode; //размер поддерева
	//	int getRNodesize(Collection<K,T>::Node* p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
	//	{
	//		if (!p) return 0;
	//		return p->sizeNode;
	//	}
	//	void fixsize() {
	//		this->sizeNode = getRNodesize(this->left) + getRNodesize(this->right) + 1;
	//	}

	//};

	void insert(K key, T value);
	RBSTree() {  }
	~RBSTree() {}
protected:
	
	Collection<K,T>::Node* insert(Collection<K,T>::Node*& rootF, K key, T value) {
		srand((int)time(0));
		if (rootF == nullptr) {
			return new typename Collection<K, T>::Node(key, value); 
		}
		if ((rand() % (rootF->sizeNode + 1)) == 0) {
			return insertroot(rootF, key, value);
		}

		if (rootF->key > key)
		{//if(rootF->left != nullptr)
			rootF->left = insert(rootF->left, key, value);
		}
		else
		{	//if (rootF->left != nullptr)
			rootF->right = insert(rootF->right, key, value);
		}
		rootF->fixsize();
		return rootF;
	}
	Collection<K,T>::Node* insertroot(Collection<K,T>::Node*& rootF, K key, T value) {
		if (rootF == nullptr) return new typename Collection<K,T>::Node(key, value);
		if (key < rootF->key)
		{
			rootF->left = insertroot(rootF->left, key, value);
			return 	rotateright(rootF);
		}
		else
		{
			rootF->right = insertroot(rootF->right, key, value);
				return rotateleft(rootF);
		}
	}
	Collection<K,T>::Node* rotateright(typename Collection<K,T>::Node*& p) // правый поворот вокруг узла p
	{
		typename Collection<K,T>::Node* q = p->left;
		if (q == nullptr) return p;
		p->left = q->right;
		q->right = p;
		q->sizeNode = p->sizeNode;
		p->fixsize();
		return q;
	}
	Collection<K,T>::Node* rotateleft(typename Collection<K,T>::Node*& q) // левый поворот вокруг узла q
	{
		typename Collection<K,T>::Node* p = q->right;
		if (p == nullptr) return q;
		q->right = p->left;
		p->left = q;
		p->sizeNode = q->sizeNode;
		q->fixsize();
		return p;
	}
};

template<typename K, typename T>
void RBSTree<K, T>::insert(K key, T value)
{
	if (this->root != nullptr)
		insert(this->root, key, value);
	else
		this->root = new typename Collection<K,T>::Node(key, value);//В случае пустого
	Collection<K, T>::_size++;
	
}

//template<typename K, typename T>
//RBSTree<K, T>::Collection<K,T>::Node* RBSTree<K, T>::insert(Collection<K,T>::Node* root, K key, T value)
//{
//	 if (rand() % (this->root->size + 1) == 0)
//	 
//		 return insertroot(root, key, value);
//	 
//
//	 if (root->key > key)
//		 root->left = insert(root->left, key, value);
//	 else
//		 root->right = insert(root->right, key, value);
//	 root->fixsize();
//}

 //template<typename K, typename T>
 //RBSTree<K, T>::Collection<K,T>::Node* RBSTree<K, T>::insertroot(Collection<K,T>::Node* root, K key, T value)
 //{
	// if( !root ) return new Collection<K,T>::Node(key,value); 
	//if( key < root->key ) 
	//{
	//	root->left = insertroot(root->left,key,value); 
	//	return rotateright(root); 
	//}
	//else 
	//{
	//	root->right = insertroot(root->right,key,value);
	//	return rotateleft(root);
	//}
 //}