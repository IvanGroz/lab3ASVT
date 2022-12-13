#pragma once
#include "Collection.h"


template <typename K, typename T>
class BSTree : public Collection<K, T>
{

	void insert(K key, typename Collection<K, T>::Node* root, T value);
	void clear(typename Collection<K, T>::Node* root);
	typename Collection<K, T>::Node* remove(typename Collection<K, T>::Node* root, K key);

	static typename Collection<K, T>::Node* max(typename Collection<K, T>::Node* root);	// Получение максимального элемента
	static typename Collection<K, T>::Node* min(typename Collection<K, T>::Node* root);	// Получение минимального элемента

	
	void bypassTheScheme(typename Collection<K, T>::Node* root, ostream& os);		// Вывод элементов в указанный поток по обратной схеме (Lt -> Rt -> t)
protected:
	
	Collection<K, T>::Node* root = nullptr;
	typename Collection<K, T>::Node* search(K key, typename Collection<K, T>::Node* root);
	

public:
	int countMovingInsert = 0;				// Кол-во пройденных элементов при выполнении операции - вставка
	int countMovingDelete = 0;				// Кол-во пройденных элементов при выполнении операции - удаление
	int countMovingFind = 0;				// Кол-во пройденных элементов при выполнении операции - поиск

	BSTree() {};
	BSTree(Collection<K, T>::Node* rootLike) { this->root = rootLike; };
	~BSTree();

	int size();
	void clear();
	bool empty();

	void insert(K key, T value);
	void remove(K key);
	int getOrder(K key); //получение порядка узла
	T get(K key);
	void put(K key, T value);

	void showByScheme(ostream& os);



	class iterator
	{
	protected:
		typename Collection<K, T>::Node* LP(typename Collection<K, T>::Node* t, typename Collection<K, T>::Node* x);
		typename Collection<K, T>::Node* RP(typename Collection<K, T>::Node* t, typename Collection<K, T>::Node* x);

		typename Collection<K, T>::Node* root;
		typename Collection<K, T>::Node* current;
	public:
		iterator();
		iterator(typename BSTree<K, T>& tree);
		iterator(typename Collection<K, T>::Node* current);
		iterator(const iterator& iterator);
		~iterator() {}

		T& operator*();				// Доступ по чтению
		K& showKey(); //Показ ключа
		iterator& operator++();		// Оператор префиксного инкремента
		iterator& operator--();		// Оператор префиксного декремента

		iterator& operator=(const iterator& iterator);	// Присваивание новой ссылки
		bool operator==(const iterator& iterator);		// Проверка равенства
		bool operator!=(const iterator& iterator);		// Проверка неравенства
	};

	class reverse_iterator : public iterator
	{
	public:
		reverse_iterator() : iterator() {}
		reverse_iterator(typename Collection<K, T>::Node* current) : iterator(current) {}
		reverse_iterator(const iterator& iterator) : iterator(iterator) {}
		~reverse_iterator() {}

		reverse_iterator& operator++() {
			typename Collection<K, T>::Node* t = iterator::current;
			if (iterator::current->left)
			{
				iterator::current = max(iterator::current->left);
				return *this;
			}
			iterator::current = iterator::RP(iterator::root, iterator::current);
			if (iterator::current)
				return *this;
			else
				//тут компилятор ругался
				return *new BSTree<K, T>::reverse_iterator();
		}

		reverse_iterator& operator--() {
			typename Collection<K, T>::Node* t = iterator::current;
			if (iterator::current->right)
			{
				iterator::current = min(iterator::current->right);
				return *this;
			}
			iterator::current = iterator::LP(iterator::root, iterator::current);
			if (iterator::current)
				return *this;
			else
				return *&BSTree<K, T>::reverse_iterator();
		}
	};

	iterator begin();
	iterator end();

	reverse_iterator rbegin();
	reverse_iterator rend();

	void showDirectly(ostream& os);
	void showBack(ostream& os);
};



template<typename K, typename T>
void BSTree<K, T>::insert(K key, typename Collection<K, T>::Node* root, T value)
{
	if (key < root->key)
	{
		if (root->left != nullptr) {
			countMovingInsert++;
			insert(key, root->left, value);
		}
		else
			root->left = new typename Collection<K, T>::Node(key, value);
	}
	else if (key >= root->key)
	{
		if (root->right != nullptr) {
			countMovingInsert++;
			insert(key, root->right, value);
		}
		else
			root->right = new typename Collection<K, T>::Node(key, value);
	}
}

template<typename K, typename T>
typename Collection<K, T>::Node* BSTree<K, T>::search(K key, typename Collection<K, T>::Node* root)
{
	if (root != nullptr)	//Если узел //инициализирован
	{
		countMovingFind++;
		if (key == root->key)	//И ключевое значение //узла совпадает с //искомым ключевым //значением.
			return root;	//Возвращается указатель на //найденный элемент.
		if (key < root->key)	//Иначе, если 
			//искомое ключевое //значение меньше //ключевого значения узла
			return search(key, root->left);	//Вызывается эта же функция //для левого потомка.
		else							//Иначе
			return search(key, root->right);	//Вызывается эта же функция //для правого потомка.
	}
	else
		return nullptr;					//Иначе возвращается NULL.
}

template<typename K, typename T>
void BSTree<K, T>::clear(typename Collection<K, T>::Node* root)
{
	if (root->left != nullptr) clear(root->left);
	if (root->right != nullptr) clear(root->right);
	root->left = root->right = nullptr;
	delete root;
}

template<typename K, typename T>
typename Collection<K, T>::Node* BSTree<K, T>::remove(typename Collection<K, T>::Node* root, K key)
{
	if (root == nullptr)
		throw out_of_range("Значение для этого ключа не было найдено!");
	if (root->key > key) {
		countMovingDelete++;
		root->left = remove(root->left, key);
	}
	else
		if (root->key < key) {
			countMovingDelete++;
			root->right = remove(root->right, key);
		}
		else
			if (root->key == key)
				if (root->left == nullptr)
				{
					typename Collection<K, T>::Node* tmp = root;
					root = tmp->right;
					tmp->left = tmp->right = nullptr;
					delete tmp;
					return nullptr;
				}
				else
					if (root->right == nullptr)
					{
						typename Collection<K, T>::Node* tmp = root;
						root = tmp->left;
						tmp->left = tmp->right = nullptr;
						delete tmp;
						return nullptr;
					}
					else
					{
						typename Collection<K, T>::Node* tmp = new typename Collection<K, T>::Node(*max(root->left));
						countMovingDelete++;
						remove(root, tmp->key);
						tmp->right = root->right;
						tmp->left = root->left;
						root->right = root->left = nullptr;
						if (root == BSTree::root)
							BSTree::root = tmp;
						delete root;
						return tmp;
					}
	return root;
}

template<typename K, typename T>
BSTree<K, T>::~BSTree()
{
	clear();
}

template<typename K, typename T>
int BSTree<K, T>::size()
{
	return Collection<K, T>::_size;
}

template<typename K, typename T>
void BSTree<K, T>::clear()
{
	if (this->root != nullptr)
	{
		clear(root);
		root = nullptr;
		Collection<K, T>::_size = 0;
	}
}

template<typename K, typename T>
bool BSTree<K, T>::empty()
{
	return root == nullptr;
}

template<typename K, typename T>
void BSTree<K, T>::insert(K key, T value)
{
	if (root != nullptr)
		insert(key, root, value);
	else
		root = new typename Collection<K, T>::Node(key, value);
	Collection<K, T>::_size++;
}

template<typename K, typename T>
void BSTree<K, T>::remove(K key)
{
	if (root == nullptr)
		throw out_of_range("Коллекция пуста!");
	else
		remove(root, key);
	Collection<K, T>::_size--;
}

template<typename K, typename T>
 int BSTree<K, T>::getOrder(K key)
{ 
	 this->countMovingFind = 0;
	 if (root == nullptr)
		 throw out_of_range("Коллекция пуста!");
	 typename Collection<K, T>::Node* temp = search(key, root);
	 if (temp != nullptr)
		 return this->countMovingFind;
	 else
		 throw out_of_range("Значение для этого ключа не было найдено!");
}

template<typename K, typename T>
T BSTree<K, T>::get(K key)
{
	if (root == nullptr)
		throw out_of_range("Коллекция пуста!");
	typename Collection<K, T>::Node* temp = search(key, root);
	if (temp != nullptr)
		return temp->value;
	else
		throw out_of_range("Значение для этого ключа не было найдено!");
}

template<typename K, typename T>
void BSTree<K, T>::put(K key, T value)
{
	typename Collection<K, T>::Node* temp = search(key, root);
	if (temp != nullptr)
		temp->value = value;
	else
		throw out_of_range("Значение для этого ключа не было найдено!");
}

template<typename K, typename T>
void BSTree<K, T>::bypassTheScheme(typename Collection<K, T>::Node* root, ostream& os)
{
	if (!root) return;
	 os << root->key << "\t" << root->value << endl;  
	bypassTheScheme(root->left, os );
	bypassTheScheme(root->right, os);
}


template<typename K, typename T>
void BSTree<K, T>::showByScheme(ostream& os)
{
	if (root == nullptr)
		throw out_of_range("Коллекция пуста!");
	bypassTheScheme(root, os);
}

template<typename K, typename T>
typename BSTree<K, T>::iterator BSTree<K, T>::begin()
{
	return min(root);
}

template<typename K, typename T>
typename BSTree<K, T>::iterator BSTree<K, T>::end()
{
	return max(root)->right;
}

template<typename K, typename T>
typename BSTree<K, T>::reverse_iterator BSTree<K, T>::rbegin()
{
	return max(root);
}

template<typename K, typename T>
typename BSTree<K, T>::reverse_iterator BSTree<K, T>::rend()
{
	return min(root)->left;
}

template<typename K, typename T>
void BSTree<K, T>::showDirectly(ostream& os)
{
	if (empty()) throw out_of_range("Коллекция пуста!");
	iterator it(*this);
	os << "\nСимметричный показ дерева: \n";
	for (it = begin(); it != end(); ++it) {
		os << *it << " - значение; " << it.showKey() << " - ключ" << endl;
	}
}

template<typename K, typename T>
void BSTree<K, T>::showBack(ostream& os)
{
	if (empty()) throw out_of_range("Коллекция пуста!");
	reverse_iterator rit(*this);
	os << "\nОбратный показ дерева: \n";
	for (rit = rbegin(); rit != rend(); ++rit) {
		os << *rit << " - значение; " << rit.showKey() << " - ключ" << endl;
	}
}

template<typename K, typename T>
typename Collection<K, T>::Node* BSTree<K, T>::max(typename Collection<K, T>::Node* root)
{
	if (root->right == nullptr) return root;
	return max(root->right);
}

template<typename K, typename T>
typename Collection<K, T>::Node* BSTree<K, T>::min(typename Collection<K, T>::Node* root)
{
	if (root->left == nullptr) return root;
	return min(root->left);
}

template<typename K, typename T>
typename Collection<K, T>::Node* BSTree<K, T>::iterator::LP(typename Collection<K, T>::Node* t, typename Collection<K, T>::Node* x)
{
	if (t == x) return nullptr;
	if (x->key < t->key)
	{
		typename Collection<K, T>::Node* lp = LP(t->left, x);
		if (lp) return lp;
		return t;
	}
	return LP(t->right, x);
}

template<typename K, typename T>
typename Collection<K, T>::Node* BSTree<K, T>::iterator::RP(typename Collection<K, T>::Node* t, typename Collection<K, T>::Node* x)
{
	if (t == x) return nullptr;
	if (x->key > t->key)
	{
		typename Collection<K, T>::Node* rp = RP(t->right, x);
		if (rp) return rp;
		return t;
	}
	return RP(t->left, x);

}

template<typename K, typename T>
BSTree<K, T>::iterator::iterator()
{
	this->current = nullptr;
}

template<typename K, typename T>
BSTree<K, T>::iterator::iterator(typename BSTree<K, T>& tree)
{
	this->root = tree.root;
}

template<typename K, typename T>
BSTree<K, T>::iterator::iterator(typename Collection<K, T>::Node* current)
{
	this->current = current;
}

template<typename K, typename T>
BSTree<K, T>::iterator::iterator(const iterator& iterator)
{
	this->current = iterator.current;
	this->root = iterator.root;
}

template<typename K, typename T>
T& BSTree<K, T>::iterator::operator*()
{
	if (current == nullptr)
		throw out_of_range("-1");
	return this->current->value;
}

template<typename K, typename T>
 K& BSTree<K, T>::iterator::showKey()
{
	 if (current == nullptr)
		 throw out_of_range("-1");
	 return this->current->key;
}

template<typename K, typename T>
typename BSTree<K, T>::iterator& BSTree<K, T>::iterator::operator++()
{
	typename Collection<K, T>::Node* t = current;
	if (current->right)
	{
		current = min(current->right);
		return *this;
	}
	current = LP(root, current);
	if (current)
		return *this;
	else//тут компилятор ругался
		return *(new BSTree<K, T>::iterator());
}

template<typename K, typename T>
typename BSTree<K, T>::iterator& BSTree<K, T>::iterator::operator--()
{
	typename Collection<K, T>::Node* t = current;
	if (current->left)
	{
		current = max(current->left);
		return *this;
	}
	current = RP(root, current);
	if (current)
		return *this;
	else
		return *&BSTree<K, T>::iterator();
}

template<typename K, typename T>
typename BSTree<K, T>::iterator& BSTree<K, T>::iterator::operator=(const iterator& iterator)
{
	this->current = iterator.current;
	return *this;
}

template<typename K, typename T>
bool BSTree<K, T>::iterator::operator==(const iterator& iterator)
{
	return this->current == iterator.current;
}

template<typename K, typename T>
bool BSTree<K, T>::iterator::operator!=(const iterator& iterator)
{
	return !(this->current == iterator.current);
}
