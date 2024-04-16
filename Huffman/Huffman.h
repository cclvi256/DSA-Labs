#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct CharInfo
{
	char ch;
	char huffmanCodeBits;
	int count;
	int huffmanCode;

	CharInfo();
	CharInfo(char ch);
	CharInfo(char ch, int count);
	void AttachCode(int huffmanCode, char huffmanCodeBits);
};

struct TreeElem
{
	char ch;
	bool isLeaf;
	int totalCount;

	TreeElem();
};

struct TreeNode
{
	TreeElem value;
	TreeNode* l;
	TreeNode* r;

	TreeNode();
	TreeNode(char ch, CharInfo* dictionary);
	TreeNode(TreeNode* sub1, TreeNode* sub2);

	void DictionaryFixing(CharInfo* dictionary);
	void DictionaryFixing(CharInfo* dictionary, int depth, int position);

	const bool operator<(const TreeNode& operand2) const;
};

struct IBuffer
{
	char buffer;
	char remaining;
	std::ifstream ifs;

	IBuffer(std::string filePath);

	bool GetBit();
	bool PeekBit();
	inline void Destroy()
	{
		ifs.close();
	}
};

struct OBuffer
{
	char buffer;
	char remaining;
	std::ofstream ofs;

	OBuffer(std::string filePath);

	void PutBit(bool bit);
	void PutBit(int bits, int bitNum);
	void FixEnd();
	inline void Destroy()
	{
		ofs.close();
	}
};

void CountOccurrence(std::string filePath, CharInfo* countArray);
TreeNode* HuffmanTreeConstruct(CharInfo* dictionary);
void Compress(std::string sourceFilePath, std::string outputFilePath, CharInfo* dictionary);
void Decompress(std::string compressedFilePath, TreeNode* root);
void Decompress(std::string compressedFilePath, std::string outputFilePath, TreeNode* root);


// TODO: 在此处引用程序需要的其他标头。
