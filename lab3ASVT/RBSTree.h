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
	void remove(K key);
	bool firstTime = 1;
	RBSTree() {  }
	~RBSTree() {}
protected:
	typename Collection<K,T>::Node* remove(typename Collection<K,T>::Node* rootF,K key);
	typename Collection<K, T>::Node* join(typename Collection<K, T>::Node* l, typename Collection<K, T>::Node* r);
	Collection<K,T>::Node* insert(Collection<K,T>::Node* rootF, K key, T value) {
		
		srand((int)time(0));
		if (rootF == nullptr) {
			return new typename Collection<K, T>::Node(key, value); 
		}
		if (rand() < RAND_MAX/(rootF->sizeNode + 1)) {
			typename Collection<K,T>::Node* temp = insertroot(rootF, key, value);
			if (firstTime) { this->root = temp; firstTime = 0;}
			return temp;
		}
		firstTime = 0;
		if (rootF->key > key)
		{//if(rootF->left != nullptr)
			this->countMovingInsert++;
			rootF->left = insert(rootF->left, key, value);

		}
		else
		{	//if (rootF->left != nullptr)
			this->countMovingInsert++;
			rootF->right = insert(rootF->right, key, value);
		}
		rootF->fixsize();
		return rootF;
	}
	Collection<K,T>::Node* insertroot(Collection<K,T>::Node* rootF, K key, T value) {
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
	Collection<K,T>::Node* rotateright(typename Collection<K,T>::Node* p) // правый поворот вокруг узла p
	{
		typename Collection<K,T>::Node* q = p->left;
		if (q == nullptr) return p;
		p->left = q->right;
		q->right = p;
		q->sizeNode = p->sizeNode;
		p->fixsize();
		q->fixsize();
		return q;
	}
	Collection<K,T>::Node* rotateleft(typename Collection<K,T>::Node* q) // левый поворот вокруг узла q
	{
		typename Collection<K,T>::Node* p = q->right;
		if (p == nullptr) return q;
		q->right = p->left;
		p->left = q;
		p->sizeNode = q->sizeNode;
		q->fixsize();
		p->fixsize();
		return p;
	}
};

template<typename K, typename T>
void RBSTree<K, T>::insert(K key, T value)
{
	if (this->root != nullptr) {
		firstTime = 1;
		insert(this->root, key, value);

	}
	else
		this->root = new typename Collection<K,T>::Node(key, value);//В случае пустого
	Collection<K, T>::_size++;
	
}

template<typename K, typename T>
 void RBSTree<K, T>::remove(K key)
{
	 if (this->root == nullptr)
		 throw out_of_range("Коллекция пуста!");
	 else {
		 this->firstTime = 1;
		 remove(this->root, key);
	 }
	 this->_size--;
}

 template<typename K, typename T>
 typename Collection<K, T>::Node* RBSTree<K, T>::remove(typename Collection<K, T>::Node* rootF, K key)
 {
	 if (rootF == nullptr) {
		 return rootF;
	 }
	 if (rootF->key == key) {
		 typename Collection<K, T>::Node* q = join(rootF->left, rootF->right);
		 delete rootF;
		 if (this->firstTime) { this->root = q; this->firstTime = 0; }
		 return q;
	 }
	 else if (key < rootF->key) {

		 this->firstTime = 0;
		 this->countMovingDelete++;
		 rootF->left = remove(rootF->left, key);
	 }
	 else {

		 this->firstTime = 0;
		 this->countMovingDelete++;
		 rootF->right = remove(rootF->right, key);
	 }
	 return rootF;
 }

 template<typename K, typename T>
  typename Collection<K, T>::Node* RBSTree<K, T>::join(typename Collection<K, T>::Node* l, typename Collection<K, T>::Node* r)
 {
	  if (l == nullptr) { return r; }
	  if (r == nullptr) { return l; }
	  if ( (rand() / (RAND_MAX / (l->sizeNode + r->sizeNode + 1))) < l->sizeNode) {
		  l->right = join(l->right, r);
		  l->fixsize();
		  return l;
	  }
	  else {
		  r->left = join(l, r->left);
		  r->fixsize();
		  return r;
	  }
 }