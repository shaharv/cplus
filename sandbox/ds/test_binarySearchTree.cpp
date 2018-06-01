#include "include/BinarySearchTree.h"

void test_BST();

int main()
{
	test_BST();

	return 0;
}

void test_BST()
{
	BinarySearchTree<int32_t> tree, tree2, tree3;

	// Print empty tree
	tree.print();

	tree.insert(5);
	tree.insert(2);
	tree.insert(3);
	tree.insert(6);
	tree.insert(4);
	tree.insert(1);
	tree.print();

	tree2.insert(2);
	tree2.insert(3);
	tree2.insert(4);
	tree2.insert(5);
	tree2.insert(6);
	tree2.insert(1);
	tree2.print();

	tree3.insert(4);
	tree3.insert(2);
	tree3.insert(1);
	tree3.insert(3);
	tree3.insert(6);
	tree3.insert(5);
	tree3.insert(7);
	tree3.print();

	BinarySearchTree<std::string> stree, stree2;

	stree.insert("so");
	stree.insert("long");
	stree.insert("and");
	stree.insert("thanks");
	stree.insert("for");
	stree.insert("all");
	stree.insert("the");
	stree.insert("fish");
	stree.insert("...");
	stree.print();

	stree2.insert("PHP");
	stree2.insert("is");
	stree2.insert("a");
	stree2.insert("minor");
	stree2.insert("evil");
	stree2.insert("perpetrated");
	stree2.insert("and");
	stree2.insert("created");
	stree2.insert("by");
	stree2.insert("incompetent");
	stree2.insert("amateurs");
	stree2.insert("whereas");
	stree2.insert("Perl");
	stree2.insert("is");
	stree2.insert("a");
	stree2.insert("great");
	stree2.insert("and");
	stree2.insert("insidious");
	stree2.insert("evil");
	stree2.insert("perpetrated");
	stree2.insert("by");
	stree2.insert("skilled");
	stree2.insert("but");
	stree2.insert("perverted");
	stree2.insert("professionals.");
	stree2.print();

	return;
}
