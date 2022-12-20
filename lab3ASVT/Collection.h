#pragma once
#include <iostream>
using namespace std;

template <typename K, typename T>
class Collection
{
 
public:
	class Node				// ����� ��� �������� ������� ���������
	{
	public:
		Node();			// ����������� �� ��������� 
		Node(K key, T value, Node* left = nullptr, Node* right = nullptr); // ����������� � �����������
		Node(const Node& node);	// ����������� �����������
		~Node();			// ����������

		K key;
		T value;			// �������� ������
		Node* left;			// ��������� �� ����� ������� ���������
		Node* right;			// ��������� �� ������ ������� ���������
		int sizeNode;	//������ ���������
		int getRNodesize(Node* p) // ������� ��� ���� size, �������� � ������� ��������� (t=NULL)
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
	int _size = 0;			// ������ ��������� (����� ��������� � �������)
	virtual int size() = 0;		// ����� �������� �������� �������
	virtual void clear() = 0;		// ������� ��������� ���������
	virtual bool empty() = 0;		// �������� ��������� �� �������

	virtual void insert(K key, T value) = 0;	// ���������� ������ �������� (� ����� ���������)
	virtual void remove(K key) = 0;	// �������� �������� �� ��������� �������

	virtual T get(K key) = 0;	// ��������� �������� �������� �� �����
	virtual void put(K key, T value) = 0;	// ��������� �������� �������� ��������� �� �����

	virtual ~Collection() {}	// ����������� ����������
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

