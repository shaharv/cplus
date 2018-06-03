#include "include/BinarySearchTree.h"

#include <iostream>

void test_BST_print_empty();
void test_BST_int_tree_01();
void test_BST_int_tree_02();
void test_BST_int_tree_03();
void test_BST_strings_01();
void test_BST_strings_02();

using std::cerr;
using std::cout;
using std::endl;

int main()
{
	test_BST_print_empty();
	test_BST_int_tree_01();
	test_BST_int_tree_02();
	test_BST_int_tree_03();
	test_BST_strings_01();
	test_BST_strings_02();

	return 0;
}

void test_BST_print_empty()
{
	BinarySearchTree<int32_t> tree;

	// Print empty tree
	tree.print();
}

void test_BST_int_tree_01()
{
	BinarySearchTree<int32_t> tree;

	tree.insert(5);
	tree.insert(2);
	tree.insert(3);
	tree.insert(6);
	tree.insert(4);
	tree.insert(1);

	tree.print();
}

void test_BST_int_tree_02()
{
	BinarySearchTree<int32_t> tree;

	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(1);

	tree.print();
}

void test_BST_int_tree_03()
{
	BinarySearchTree<int32_t> tree;

	tree.insert(4);
	tree.insert(2);
	tree.insert(1);
	tree.insert(3);
	tree.insert(6);
	tree.insert(5);
	tree.insert(7);
	tree.print();
}

void test_BST_strings_01()
{
	BinarySearchTree<std::string> tree;

	tree.insert("so");
	tree.insert("long");
	tree.insert("and");
	tree.insert("thanks");
	tree.insert("for");
	tree.insert("all");
	tree.insert("the");
	tree.insert("fish");
	tree.insert("...");
	tree.print();
}

void test_BST_strings_02()
{
	BinarySearchTree<std::string> tree;

	tree.insert("PHP");
	tree.insert("is");
	tree.insert("a");
	tree.insert("minor");
	tree.insert("evil");
	tree.insert("perpetrated");
	tree.insert("and");
	tree.insert("created");
	tree.insert("by");
	tree.insert("incompetent");
	tree.insert("amateurs");
	tree.insert("whereas");
	tree.insert("Perl");
	tree.insert("is");
	tree.insert("a");
	tree.insert("great");
	tree.insert("and");
	tree.insert("insidious");
	tree.insert("evil");
	tree.insert("perpetrated");
	tree.insert("by");
	tree.insert("skilled");
	tree.insert("but");
	tree.insert("perverted");
	tree.insert("professionals.");
	tree.print();

	if (!tree.findDFSRecursive("amateurs"))
	{
		cerr << "Test failed! \"amateurs\" not find in tree search." << endl;
	}
	else
	{
		cout << "Recursive DFS search: OK." << endl;
	}

	if (!tree.findDFSIterative("amateurs"))
	{
		cerr << "Test failed! \"amateurs\" not find in tree search." << endl;
	}
	else
	{
		cout << "Iterative DFS search: OK." << endl;
	}

	cout << endl;
	return;
}
