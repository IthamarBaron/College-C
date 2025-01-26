#pragma once
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>


BinTreePtr InitTree()
{
	BinTreePtr t = (BinTreePtr)malloc(sizeof(BinTree));
	if (t == NULL)
	{
		printf("Memory allocation failed [InitTree]\n");
		return NULL;
	}
	t->info.ch = '\0';  // Initialize to a default character
	t->info.freq = 0;
	t->left = NULL;
	t->right = NULL;
	return t;
}


BinTreePtr BuildTree(BinTreePtr L, BinTreePtr R, Tree_Info x)
{
	BinTreePtr t;
	t = (BinTreePtr)malloc(sizeof(BinTree));
	t->info = x;
	t->right = R;
	t->left = L;
	return t;
}

void SetRight(BinTreePtr* t, Tree_Info x)
{
	BinTreePtr rt = BuildTree(NULL, NULL, x);
	(*t)->right = rt;
}

void SetLeft(BinTreePtr* t, Tree_Info x)
{
	BinTreePtr lt = BuildTree(NULL, NULL, x);
	(*t)->left = lt;
}

BinTreePtr TreeRsub(BinTreePtr t)
{
	return t->right;
}

BinTreePtr TreeLsub(BinTreePtr t)
{
	return t->left;
}

void ChangeLsub(BinTreePtr* t, BinTreePtr new_tree)
{
	(*t)->left = new_tree;
}

void ChangeRsub(BinTreePtr* t, BinTreePtr new_tree)
{
	(*t)->right = new_tree;
}

Tree_Info GetRoot(BinTreePtr t)
{
	return t->info;
}

void SetRoot(BinTreePtr* t, Tree_Info x)
{
	if ((*t))
		(*t)->info = x;
	else
	{
		InitTree(t);
		(*t) = BuildTree(NULL, NULL, x);
	}
}

int IsEmptyTree(BinTreePtr t)
{
	return t == NULL;
}