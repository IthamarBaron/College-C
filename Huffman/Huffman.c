#pragma warning(disable : 4996)
#pragma once	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#define ASCII_MAX 128
#define MAX_TREE_HEIGHT 256

/* ======= START: Debug ======= */
void PrintInorder(BinTreePtr tree)
{
	if (tree == NULL)
		return;
	PrintInorder(tree->left);
	printf("[[%c][%d]] ", tree->info.ch, tree->info.freq);
	PrintInorder(tree->right);

}
void DebugNode(BinTreePtr node, char* msg)
{
	puts(msg);
	printf("Node At :%X [%c] [%d]\n LEFT %X RIGHT %X\n LEFT %d RIGHT %d\n", node, node->info.ch, node->info.freq, node->left, node->right, node->left, node->right);
}
/* ======= END: Debug ======= */

void CountCharFrequency(int* freq /*array of length ASCII_MAX initialized to {0}*/, char* path, int* chars)
{
	FILE* fp = fopen(path, "rt");
	if (fp == NULL)
	{
		fprintf(stderr, "ERROR: File not found in %s at line %d\n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	char currChar;
	while ((currChar = fgetc(fp)) != EOF)
	{
		if (freq[(unsigned char)currChar] == 0)
			(*chars)++;
		freq[(unsigned char)currChar]++;
	}

	fclose(fp);
}

void CastToStruct(int* freq, CharFrequencyPtr** charFreqArr, int allocate)
{
	*charFreqArr = (CharFrequencyPtr*)malloc(allocate * sizeof(CharFrequencyPtr));
	if (*charFreqArr == NULL)
	{
		fprintf(stderr, "ERROR: Memory allocation failed for charFreqArr\n");
		exit(EXIT_FAILURE);
	}

	int lastChar = 0;
	for (int i = 0; i < allocate; i++)
	{
		(*charFreqArr)[i] = (CharFrequencyPtr)malloc(sizeof(CharFrequency));
		if ((*charFreqArr)[i] == NULL)
		{
			fprintf(stderr, "ERROR: Memory allocation failed for charFreqArr[%d]\n", i);
			exit(EXIT_FAILURE);
		}
		for (int j = lastChar; j < ASCII_MAX; j++)
		{
			if (freq[j] >0)
			{
				(*charFreqArr)[i]->ch = j;
				(*charFreqArr)[i]->freq = freq[j];
				lastChar = j + 1;
				break;
			}
		}
	}
}

int CompareFrequency(const void* a, const void* b)
{
	const CharFrequencyPtr cfA = *(const CharFrequencyPtr*)a;
	const CharFrequencyPtr cfB = *(const CharFrequencyPtr*)b;
		
	return cfB->freq - cfA->freq;
}

void SortStructArr(CharFrequencyPtr* charFreqArr, int length)
{
	qsort(charFreqArr, length, sizeof(CharFrequencyPtr), CompareFrequency);
}

void CastToNodes(CharFrequencyPtr* charFreqArr, BinTreePtr** NodeArr, int allocate)
{
	(*NodeArr) = (BinTreePtr*)malloc(allocate * sizeof(BinTreePtr));
	if (*NodeArr == NULL)
	{
		fprintf(stderr, "ERROR: Memory allocation failed for NodeArr\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < allocate; i++)
	{
		(*NodeArr)[i] = InitTree();
		if ((*NodeArr)[i] == NULL)
		{
			fprintf(stderr, "ERROR: Memory allocation failed for NodeArr[%d]\n", i);
			exit(EXIT_FAILURE);
		}
		(*NodeArr)[i]->info.ch = charFreqArr[i]->ch;
		(*NodeArr)[i]->info.freq = charFreqArr[i]->freq;

	}
}

void InsertSorted(BinTreePtr* array, int* length, BinTreePtr newNode)
{
	if (*length < 0)
	{
		fprintf(stderr, "ERROR: Invalid array length\n");
		return;
	}

	int i = *length - 1; 
	while (i >= 0 && array[i]->info.freq < newNode->info.freq)
	{
		array[i + 1] = array[i]; // Shift elements to make room
		i--;
	}

	array[i + 1] = newNode;

	(*length)++;
}

BinTreePtr CreateIndependentTree(BinTreePtr* NodeArr, int length)
{
	BinTreePtr leftClone = InitTree();
	leftClone->info = NodeArr[length - 2]->info;
	leftClone->left = NodeArr[length - 2]->left;
	leftClone->right = NodeArr[length - 2]->right;

	BinTreePtr rightClone = InitTree();
	rightClone->info = NodeArr[length - 1]->info; 
	rightClone->left = NodeArr[length - 1]->left;
	rightClone->right = NodeArr[length - 1]->right;

	Tree_Info rootInfo = { .ch = NULL, .freq = leftClone->info.freq + rightClone->info.freq };
	BinTreePtr newNode = BuildTree(leftClone, rightClone, rootInfo);

	return newNode;
}

BinTreePtr CreateHuffman(BinTreePtr* NodeArr, int length)
{
	while (length != 1)
	{
		BinTreePtr newNode = CreateIndependentTree(NodeArr, length);
		NodeArr[length - 2]->info.ch = NULL;
		NodeArr[length - 2]->info.freq = 0;
		length -= 2;
		InsertSorted(NodeArr, &length, newNode);
	}
	return NodeArr[0];
}

void GenerateCodes(BinTreePtr root, char* code, int depth, char codes[256][MAX_TREE_HEIGHT]) 
{
	if (root == NULL) {
		return;
	}

	
	if (root->left) {
		code[depth] = '0';
		GenerateCodes(root->left, code, depth + 1, codes);
	}

	if (root->right) {
		code[depth] = '1'; // Append '1' for right
		GenerateCodes(root->right, code, depth + 1, codes);
	}

	// If it's a leaf node (both children are NULL), save the code
	if (!root->left && !root->right) {
		code[depth] = '\0'; // Null-terminate the code
		strcpy(codes[(unsigned char)root->info.ch], code); // Save the code in the lookup table
	}
}

void SerializeTree(FILE* file, BinTreePtr root) {
	if (root == NULL) {
		return;
	}

	if (!root->left && !root->right) {
		fputc('1', file);
		fputc(root->info.ch, file);
		return;
	}

	fputc('0', file);

	SerializeTree(file, root->left);
	SerializeTree(file, root->right);
}
BinTreePtr DeserializeTree(FILE* file) {
	int ch = fgetc(file);

	if (ch == EOF) {
		printf("EOF reached\n");
		return NULL;
	}

	if (ch == '1') {
		BinTreePtr leaf = InitTree();
		if (leaf == NULL) {
			fprintf(stderr, "ERROR: Memory allocation failed in DeserializeTree.\n");
			return NULL;
		}
		leaf->info.ch = fgetc(file);
		printf("Deserialized leaf node: [%c]\n", leaf->info.ch);
		return leaf;
	}

	if (ch == '0') {
		BinTreePtr internal = InitTree();
		if (internal == NULL) {
			fprintf(stderr, "ERROR: Memory allocation failed in DeserializeTree.\n");
			return NULL;
		}
		printf("Deserializing internal node...\n");
		internal->left = DeserializeTree(file);
		internal->right = DeserializeTree(file);
		return internal;
	}

	return NULL;
}


void Compress(char* inputPath, char* outputPath, BinTreePtr huffmanTree, char codes[256][MAX_TREE_HEIGHT]) {
	FILE* inputFile = fopen(inputPath, "rt");
	if (inputFile == NULL) {
		fprintf(stderr, "ERROR: Failed to open input file %s at line %d\n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	FILE* outputFile = fopen(outputPath, "wb");
	if (outputFile == NULL) {
		fprintf(stderr, "ERROR: Failed to open output file %s at line %d\n", __FILE__, __LINE__);
		fclose(inputFile);
		exit(EXIT_FAILURE);
	}

	int totalChars = 0;
	while (fgetc(inputFile) != EOF) {
		totalChars++;
	}
	rewind(inputFile); 

	
	fwrite(&totalChars, sizeof(int), 1, outputFile);

	
	SerializeTree(outputFile, huffmanTree);
	fputc('|', outputFile);

	unsigned char buffer = 0;
	int bitCount = 0;
	char ch;

	while ((ch = fgetc(inputFile)) != EOF) {
		const char* code = codes[(unsigned char)ch];
		for (int i = 0; code[i] != '\0'; i++) {
			buffer = (buffer << 1) | (code[i] - '0');
			bitCount++;

			if (bitCount == 8) {
				fputc(buffer, outputFile);
				buffer = 0;
				bitCount = 0;
			}
		}
	}

	// Write any remaining bits in the buffer
	if (bitCount > 0) {
		buffer = buffer << (8 - bitCount);
		fputc(buffer, outputFile);
	}

	fclose(inputFile);
	fclose(outputFile);

	printf("File successfully compressed to: %s\n", outputPath);
}

void Decompress(char* inputPath, char* outputPath) {
	FILE* inputFile = fopen(inputPath, "rb");
	if (inputFile == NULL) {
		fprintf(stderr, "ERROR: Failed to open input file %s at line %d\n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	FILE* outputFile = fopen(outputPath, "wt");
	if (outputFile == NULL) {
		fprintf(stderr, "ERROR: Failed to open output file %s at line %d\n", __FILE__, __LINE__);
		fclose(inputFile);
		exit(EXIT_FAILURE);
	}

	int totalChars;
	fread(&totalChars, sizeof(int), 1, inputFile);

	BinTreePtr huffmanTree = NULL;
	int ch;

	// Read and deserialize the tree until the delimiter '|'
	while ((ch = fgetc(inputFile)) != '|') {
		if (ch == EOF) {
			fprintf(stderr, "ERROR: Invalid file format, delimiter not found.\n");
			fclose(inputFile);
			fclose(outputFile);
			exit(EXIT_FAILURE);
		}
		ungetc(ch, inputFile);
		huffmanTree = DeserializeTree(inputFile);
	}

	// Decode the compressed data
	BinTreePtr current = huffmanTree;
	int decodedChars = 0;

	while ((ch = fgetc(inputFile)) != EOF && decodedChars < totalChars) {
		for (int i = 7; i >= 0; i--) {
			int bit = (ch >> i) & 1;
			current = bit ? current->right : current->left;

			if (!current->left && !current->right) {
				fputc(current->info.ch, outputFile);
				decodedChars++;
				if (decodedChars == totalChars) {
					break; // to avoid duplicates at the end caused by the padding in compress, ducktape fix but oh well.... 
				}
				current = huffmanTree;
			}
		}
	}

	fclose(inputFile);
	fclose(outputFile);

	printf("File successfully decompressed to: %s\n", outputPath);
}

void DoCompressing(char* textFile)
{
	int freq[ASCII_MAX] = { 0 };
	int chars = 0;
	CharFrequencyPtr* arr;
	BinTreePtr* nodeArr;

	CountCharFrequency(freq, textFile, &chars);
	CastToStruct(freq, &arr, chars);
	SortStructArr(arr, chars);
	CastToNodes(arr, &nodeArr, chars);
	BinTreePtr huff = CreateHuffman(nodeArr, chars);

	char codes[256][MAX_TREE_HEIGHT] = { 0 }; // Lookup table for codes
	char code[MAX_TREE_HEIGHT];             // Temporary buffer
	GenerateCodes(huff, code, 0, codes);

	// Replace extension with `.huff`
	char outputFile[256];
	const char* dot = strrchr(textFile, '.');
	if (dot) {
		size_t prefixLength = dot - textFile;
		strncpy(outputFile, textFile, prefixLength);
		outputFile[prefixLength] = '\0';
	}
	else {
		strcpy(outputFile, textFile);
	}
	strcat(outputFile, ".huff");

	Compress(textFile, outputFile, huff, codes);

}

void DoDecompress(char* huffFile)
{
	// Replace the `.huff` extension with `.txt`
	char outputFile[256];
	const char* dot = strrchr(huffFile, '.'); 
	if (dot) {
		size_t prefixLength = dot - huffFile;
		strncpy(outputFile, huffFile, prefixLength);
		outputFile[prefixLength] = '\0';
	}
	else {
		strcpy(outputFile, huffFile);
	}
	strcat(outputFile, ".txt");

	Decompress(huffFile, outputFile);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Invalid number of parameters!\nUsage: Huffman <option> <path>\n");
        return 1;
    }

    if (strcmp(argv[2], "c") == 0)
    {
		printf("Compressing");
        DoCompressing(argv[1]);
    }
    else if (strcmp(argv[2], "d") == 0)
    {
		printf("Decompressing");
        DoDecompress(argv[1]);
    }
    else
    {
        printf("Invalid option! Use 'c' for compress or 'd' for decompress.\n");
    }

    return 0;
}