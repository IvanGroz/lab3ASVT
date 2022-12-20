#pragma once
#include <iostream>
using namespace std;

template <typename K, typename T>
class Collection
{
 
public:
	class Node				// Класс для элемента связной структуры
	{
	public:
		Node();			// Конструктор по умолчанию 
		Node(K key, T value, Node* left = nullptr, Node* right = nullptr); // Конструктор с параметрами
		Node(const Node& node);	// Конструктор копирования
		~Node();			// Деструктор

		K key;
		T value;			// Значение данных
		Node* left;			// Указатель на левый элемент поддерева
		Node* right;			// Указатель на правый элемент поддерева
		int sizeNode;	//размер поддерева
		int getRNodesize(Node* p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
			{
					if (p == nullptr) return 0;
					return p->sizeNode;
			}
		void fixsize() {
			this->sizeNode = getRNodesize(this->left) + getRNodesize(this->right) + 1;
			}
		K getKey() {
			return key;
		}
	};
	int _size = 0;			// Размер коллекции (число элементов с данными)
	virtual int size() = 0;		// Опрос значения текущего размера
	virtual void clear() = 0;		// Очищает коллекцию полностью
	virtual bool empty() = 0;		// Проверка коллекции на пустоту

	virtual void insert(K key, T value) = 0;	// Добавление нового элемента (в конец коллекции)
	virtual void remove(K key) = 0;	// Удаление значения по указанной позиции

	virtual T get(K key) = 0;	// Получение значения элемента по ключу
	virtual void put(K key, T value) = 0;	// Изменение значения элемента коллекции по ключу

	virtual ~Collection() {}	// Виртуальный деструктор
};

template<typename K, typename T>
Collection<K, T>::Node::Node()
{
	this->value = nullptr;
	this->right = nullptr;
	this->left = nullptr;
}

template<typename K, typename T>
Collection<K, T>::Node::Node(K key, T value, Node* left, Node* right)
{
	this->key = key;
	this->value = value;
	this->left = left;
	this->right = right;
	this->sizeNode = 1;
}

template<typename K, typename T>
Collection<K, T>::Node::Node(const Node& node)
{
	this->key = node.key;
	this->value = node.value;
	this->left = node.left;
	this->right = node.right;
}

template<typename K, typename T>
Collection<K, T>::Node::~Node()
{
	//delete this->left;
	//delete this->right;
}

