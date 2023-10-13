#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define CAPACITY 95

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
	TreeNode(TreeNode& sub1, TreeNode& sub2);

	void DictionaryFixing(CharInfo* dictionary);
	void DictionaryFixing(CharInfo* dictionary, int depth, int position);

	const bool operator<(const TreeNode& operand2) const;
};

struct IBuffer
{
	char buffer;
	char remaining;

	IBuffer(std::string filePath, int totalLength);

	bool GetBit();
	bool PeekBit();
};

struct OBuffer
{
	char buffer;
	char remaining;

	OBuffer(std::string filePath);

	void PutBit(bool bit);
	void PutBit(int bits, int num);
	void FixEnd();
};

struct Heap
{
	TreeNode* root;
	int capacity;
	int currentIndex;

	Heap();
	Heap(int capacity);

	void Push(TreeNode& value);
	void Pop();
};

void CountOccurrence(std::string filePath, CharInfo* countArray);
void Compress(std::string sourceFilePath, std::string outputFilePath);
void Decompress(std::string compressedFilePath);
void Decompress(std::string compressedFilePath, std::string outputFilePath);

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/

int main(int argc, char** argv)
{
	return 0;
}

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/

CharInfo::CharInfo() :
	ch(0),
	huffmanCode(0),
	huffmanCodeBits(0),
	count(0)
{
}

CharInfo::CharInfo(char ch) :
	ch(ch),
	huffmanCode(0),
	huffmanCodeBits(0),
	count(0)
{
}

CharInfo::CharInfo(char ch, int count) :
	ch(ch),
	huffmanCode(0),
	huffmanCodeBits(0),
	count(count)
{
}

void CharInfo::AttachCode(int huffmanCode, char huffmanCodeBits)
{
}

/*********************************************************************************/

TreeElem::TreeElem() :
	ch(0),
	isLeaf(true),
	totalCount(0)
{
}

TreeNode::TreeNode() :
	value(TreeElem()),
	l(nullptr),
	r(nullptr)
{
}

TreeNode::TreeNode(char ch, CharInfo* dictionary) :
	value(TreeElem()),
	l(nullptr),
	r(nullptr)
{
	value.ch = ch;
	value.isLeaf = true;
	value.totalCount = dictionary[ch - 32].count;
}

TreeNode::TreeNode(TreeNode& sub1, TreeNode& sub2) :
	value(TreeElem()),
	l(&sub1),
	r(&sub2)
{
	value.ch = 0;
	value.isLeaf = false;
	value.totalCount = sub1.value.totalCount + sub2.value.totalCount;
}

void TreeNode::DictionaryFixing(CharInfo* dictionary)
{
	DictionaryFixing(dictionary, 0, 0);
}

void TreeNode::DictionaryFixing(CharInfo* dictionary, int depth, int position)
{
	if (value.isLeaf)
	{
		dictionary[value.ch - 32].AttachCode(position, depth);
	}
	else
	{
		(*l).DictionaryFixing(dictionary, depth + 1, position * 2);
		(*r).DictionaryFixing(dictionary, depth + 1, position * 2 + 1);
	}
}

const bool TreeNode::operator<(const TreeNode& operand2) const
{
	return value.totalCount < operand2.value.totalCount;
}

/*********************************************************************************/

IBuffer::IBuffer(std::string filePath, int totalLength)
{
}

bool IBuffer::GetBit()
{
	return false;
}

bool IBuffer::PeekBit()
{
	return false;
}

/*********************************************************************************/

OBuffer::OBuffer(std::string filePath)
{
}

void OBuffer::PutBit(bool bit)
{
}

void OBuffer::PutBit(int bits, int num)
{
}

void OBuffer::FixEnd()
{
}

/*********************************************************************************/

Heap::Heap()
{
}

Heap::Heap(int capacity)
{
}

void Heap::Push(TreeNode& value)
{
}

void Heap::Pop()
{
}

/*********************************************************************************/

void CountOccurrence(std::string filePath, CharInfo* countArray)
{
}

void Compress(std::string sourceFilePath, std::string outputFilePath)
{
}

void Decompress(std::string compressedFilePath)
{
}

void Decompress(std::string compressedFilePath, std::string outputFilePath)
{
}
