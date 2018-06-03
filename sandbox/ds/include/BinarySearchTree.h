#pragma once

#include "StackArray.h"

#include <iostream>
#include <stdint.h>
#include <string>

// BST without duplicates.
// Order: left < root <= right.
template <typename T>
class BinarySearchTree
{
private:
	class Node
	{
	public:
		Node(const T& nodeVal) : val(nodeVal), left(NULL), right(NULL) {}
		const T val;
		Node* left;
		Node* right;
	};

public:
	BinarySearchTree() : _root(NULL), _size(0) {}

	~BinarySearchTree()
	{
		// bfs or dfs
	}

	void insert(const T& val)
	{
		if (_size == 0)
		{
			_root = new Node(val);
			_size = 1;
			return;
		}

		Node* node = _root;
		Node* parent = NULL;

		while(node != NULL)
		{
			const T& currVal = node->val;
			parent = node;
			if (val == currVal)
			{
				return;
			}
			else if (val < currVal)
			{
				node = node->left;
			}
			else
			{
				node = node->right;
			}
		}

		if (val < parent->val)
		{
			parent->left = new Node(val);
		}
		else
		{
			parent->right = new Node(val);
		}

		_size++;
	}

	void print()
	{
		if (_root == NULL)
		{
			return;
		}

		std::cout << _root->val << std::endl;
		printSubtree(_root, "");
		std::cout << std::endl;
	}

	bool findDFSRecursive(const T& val)
	{
		return (findDFSRecursive(_root, val) != NULL);
	}

	bool findDFSIterative(const T& val)
	{
		return (findDFSIterative(_root, val) != NULL);
	}

private:
	// preorder recursive DFS
	Node* findDFSRecursive(Node* root, const T& val)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->val == val)
		{
			return root;
		}

		Node* found = findDFSRecursive(root->left, val);

		if (found != NULL)
		{
			return found;
		}

		return findDFSRecursive(root->right, val);
	}

	// preorder iterative DFS
	Node* findDFSIterative(Node* root, const T& val)
	{
		if (root == NULL)
		{
			return NULL;
		}

		StackArray<BinarySearchTree<T>::Node*> stack;
		stack.push_back(root);

		while (!stack.empty())
		{
			Node* node = stack.top();

			if (node->val == val)
			{
				return node;
			}

			Node* rightChild = node->right;
			Node* leftChild = node->left;
			stack.pop_back();

			if (leftChild != NULL)
			{
				stack.push_back(leftChild);
			}

			if (rightChild != NULL)
			{
				stack.push_back(rightChild);
			}
		}

		return NULL;
	}

	void printSubtree(Node* root, const std::string& prefix)
	{
		if (root == NULL)
		{
			return;
		}

		bool hasLeft = (root->left != NULL);
		bool hasRight = (root->right != NULL);

		if (!hasLeft && !hasRight)
		{
			return;
		}

		std::cout << prefix;
		std::cout << ((hasLeft  &&  hasRight) ? "├── " : "");
		std::cout << ((!hasLeft &&  hasRight) ? "└── " : "");

		if (hasRight)
		{
			bool printStrand = (hasLeft && hasRight && (root->right->right != NULL || root->right->left != NULL));
			std::string newPrefix = prefix + (printStrand ? "│   " : "    ");
			std::cout << root->right->val << std::endl;
			printSubtree(root->right, newPrefix);
		}

		if (hasLeft)
		{
			std::cout << (hasRight ? prefix : "") << "└── " << root->left->val << std::endl;
			printSubtree(root->left, prefix + "    ");
		}
	}

	Node* _root;
	int32_t _size;
};
