//ITHAMAR BARON

#pragma warning(disable : 4996)
#pragma once	
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree.h"
typedef enum { false, true } bool;
#define MAX(param1, param2) ((param1) > (param2) ? (param1) : (param2))

void DebugNode(BinTreePtr node,char* msg)
{
	puts(msg);
	printf("Node At :%X [%d]\n LEFT %X RIGHT %X\n LEFT %d RIGHT %d\n", node, node->info, node->left, node->right, node->left, node->right);
}


//1(helper)
void InsertToBST(BinTreePtr originalTree, Tree_Info num)
{

	bool found = false;
	BinTreePtr treeTraverse = originalTree;
	while (!found && treeTraverse != NULL)
	{
		if (num < treeTraverse->info)
		{
			if (treeTraverse->left == NULL)
			{
				SetLeft(&treeTraverse, num);
				found = true;
			}
			else
			{
				treeTraverse = treeTraverse->left;
			}
		}
		else
		{
			if (treeTraverse->right == NULL)
			{
				SetRight(&treeTraverse, num);
				found = true;
			}
			else
			{
				treeTraverse = treeTraverse->right;
			}
		}
	}
}

//1 
BinTreePtr ArrayToBST(Tree_Info* arr, int length) 
{
	BinTreePtr BST = BuildTree(NULL,NULL,*arr);

	for (size_t i = 1; i < length; i++)
		InsertToBST(BST, *(arr + i));
	
	return BST;
}

//1.2
void PrintPreorder(BinTreePtr tree)
{
	if (tree == NULL)
		return;
	printf("[%d] ", tree->info);
	PrintPreorder(tree->left);
	PrintPreorder(tree->right);
}


//1.3
void PrintPostorder(BinTreePtr tree)
{
	if (tree == NULL)
		return;
	PrintPostorder(tree->left);
	PrintPostorder(tree->right);
	printf("[%d] ", tree->info);

}

//1.4
void PrintInorder(BinTreePtr tree)
{
	if (tree == NULL)
		return;
	PrintInorder(tree->left);
	printf("[%d] ", tree->info);
	PrintInorder(tree->right);

}


//2
int CountNodes(BinTreePtr tree)
{
	if (tree == NULL)
		return 0;
	int nodesLeft = CountNodes(tree->left);
	int nodesRight = CountNodes(tree->right);
	return nodesLeft + nodesRight+1;

}

//4
bool isLeaf(BinTreePtr node)
{
	return node->right == NULL && node->right == NULL;
}

//3
int CountLeaves(BinTreePtr tree)
{
	if (tree == NULL)
		return 0;
	int leavesLeft = CountLeaves(tree->left);
	int leavesRight = CountLeaves(tree->right);
	if (isLeaf(tree))
		return leavesLeft + leavesRight + 1;
	return leavesLeft + leavesRight;
}

//5
int MinValueInBST(BinTreePtr tree)
{
	BinTreePtr treeTraverse = tree;
	while (treeTraverse != NULL)
	{
		if (treeTraverse->left == NULL)
			return treeTraverse->info;
		treeTraverse = treeTraverse->left;
	}
	return NULL;
}

//6
int MaxValueInBST(BinTreePtr tree)
{
	BinTreePtr treeTraverse = tree;
	while (treeTraverse != NULL)
	{
		if (treeTraverse->right == NULL)
			return treeTraverse->info;
		treeTraverse = treeTraverse->right;
	}
	return NULL;
}

//7-8
int WhereIs(BinTreePtr tree, Tree_Info target)
{
	if (tree == NULL)
		return NULL;
	if (tree->info == target)
		return tree;
	WhereIs(tree->left,target);
	WhereIs(tree->right,target);
}

//9
int CalcHight(BinTreePtr tree)
{
	if (tree == NULL)
		return 0;
	int hightLeft = CalcHight(tree->left);
	int hightRight = CalcHight(tree->right);
	return MAX(hightLeft, hightRight) + 1;//this is so epic xD
}

//10
bool IsStrictBinTree(BinTreePtr tree)
{
	int leaves = CountLeaves(tree);
	int totalNodes = CountNodes(tree);
	leaves <<= 1;
	return ((leaves - 1) == totalNodes);
}

//11(helper)
void PrintLevel(BinTreePtr tree, int level)
{
	if (tree == NULL)
		return;
	if (level == 1)
		printf("[%d] ", tree->info);
	else if(level>1)
	{
		PrintLevel(tree->left, level - 1);
		PrintLevel(tree->right, level - 1);
	}

}

//11
void PrintByLevels(BinTreePtr tree)
{
	int levels = CalcHight(tree);
	for (size_t i = 1; i < levels+1; i++)
	{
		printf("Layer %d:\t",i);
		PrintLevel(tree, i);
		puts("");
	}
}


//12
BinTreePtr BuildMirror(BinTreePtr tree)
{
	if (tree == NULL)
		return NULL;
	BinTreePtr left = BuildMirror(tree->left);
	BinTreePtr right = BuildMirror(tree->right);
	BinTreePtr newTree = BuildTree(right, left, tree->info);
	return newTree;
}

//13
bool IsSimilar(BinTreePtr tree1, BinTreePtr tree2)
{
	if (tree1 == NULL && tree2 == NULL)
		return true;
	if (tree1 == NULL || tree2 == NULL)
		return false;
	return(IsSimilar(tree1->left,tree2->left) && IsSimilar(tree1->right,tree2->right));
}

//14
void IterateInorder(BinTreePtr tree)
{
	//based on Morris Traversal (source: https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/)

	printf("\nInorder Iterative Traversal: ");
	BinTreePtr current = tree;
	while (current != NULL)
	{
		if (current->left == NULL)
		{
			printf("[%d] ", current->info);
			current = current->right; // going back to the temp link
		}
		else
		{
			BinTreePtr before = current->left;
			while (before->right != NULL && before->right != current)
			{
				before = before->right;
			}
			if (before->right == NULL)
			{
				before->right = current; //create a temp link so we can return
				current = current->left;
			}
			else
			{
				before->right = NULL; // Remove the temp link
				printf("[%d] ", current->info);
				current = current->right;
			}

		}
	}
	puts("");


}

//15
BinTreePtr BuildExpressionTree(char** input)
{
	//Expression Tree acording to Keren's presentation
	BinTreePtr T = NULL;
	char ch = **input; 
	(*input)++;        

	if (ch == '\0')
		return T;

	if (isdigit(ch)) 
	{
		T = BuildTree(NULL, NULL, ch);
	}
	else if (ch == '(') 
	{
		BinTreePtr T1 = BuildExpressionTree(input);

		char op = **input;
		(*input)++;

		BinTreePtr T2 = BuildExpressionTree(input);

		T = BuildTree(T1, T2, op);

		if (**input == ')')
			(*input)++;
	}

	return T;
}


int main()
{

	int arr[] = { 10, 5, 15, 3, 7, 12, 18};
	int length = sizeof(arr) / sizeof(arr[0]);

	BinTreePtr BSTree = ArrayToBST(arr, length);
	BinTreePtr BSTree2 = ArrayToBST(arr, length-2);

	printf("\nInorder Traversal of BST: \n");
	PrintInorder(BSTree);
	printf("\nPostorder Traversal of BST: \n");
	PrintPostorder(BSTree);
	printf("\nPreorder Traversal of BST: \n");
	PrintPreorder(BSTree);
	printf("\nCount Of Nodes In Tree: %d\n", CountNodes(BSTree));
	printf("Count Of Leaves In Tree: %d\n", CountLeaves(BSTree));
	printf("Min Value In Tree: %d\n",MinValueInBST(BSTree));
	printf("max Value In Tree: %d\n",MaxValueInBST(BSTree));
	int target = 18;
	printf("Value %d is at Node %X\n", target, WhereIs(BSTree,target));
	printf("Hight Of Tree Is: %d\n", CalcHight(BSTree));
	printf("Is Tree Strict? (N:0|Y:1)  %d\n", IsStrictBinTree(BSTree));
	puts("Tree By Levels:");
	PrintByLevels(BSTree);
	BinTreePtr mirror = BuildMirror(BSTree);
	puts("Mirror Tree By Levels:");
	PrintByLevels(mirror);
	printf("Is Tree Similar to Tree2 ((N:0|Y:1)) %d\n", IsSimilar(BSTree, BSTree2));
	printf("Is Tree Similar to Tree ((N:0|Y:1)) %d\n", IsSimilar(BSTree, BSTree));
	IterateInorder(BSTree);

	//BEFORE TAKING OUT OF COMMENT MODIFY Tree_Info TO CHAR!!!!!! + MODIFY PrintInorder()'s Print to %c from %d !!!!!
	/*
	char* expression = "((3*4)+2)";
	BinTreePtr T = BuildExpressionTree(&expression);
	PrintInorder(T);*/






	return 0;
}