#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

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
	std::ifstream ifs;

	IBuffer(std::string filePath, int totalLength);

	bool GetBit();
	bool PeekBit();
	void Destroy();
};

struct OBuffer
{
	char buffer;
	char remaining;
	std::ofstream ofs;

	OBuffer(std::string filePath);

	void PutBit(bool bit);
	void PutBit(int bits, int num);
	void FixEnd();
	void Destroy();
};

struct Heap
{
	TreeNode* root;
	int capacity;
	int currentIndex;

	Heap(int capacity);

	void Push(TreeNode& value);
	void Pop();
};

void CountOccurrence(std::string filePath, CharInfo* countArray);
TreeNode* HuffmanTreeConstruct(CharInfo* dictionary);
void FixDictionary(CharInfo* dictionary, TreeNode* huffmanTreeRoot);
void Compress(std::string sourceFilePath, std::string outputFilePath);
void Decompress(std::string compressedFilePath);
void Decompress(std::string compressedFilePath, std::string outputFilePath);

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

int main(int argc, char** argv)
{
	return 0;
}

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

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
	this->huffmanCode = huffmanCode;
	this->huffmanCodeBits = huffmanCodeBits;
}

/**************************************************************************************/

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

/**************************************************************************************/

IBuffer::IBuffer(std::string filePath, int totalLength) :
	buffer(0),
	remaining(0),
	ifs(filePath, std::ios::binary | std::ios::in)
{
	if (!ifs.is_open())
	{
		std::cout << "Failed to open the file, ";
		std::cout << "please check if the file exists ";
		std::cout << "or is open by another program" << std::endl;

		exit(0);
	}

	if (ifs.eof())
	{
		std::cout << "Your file is empty!" << std::endl;

		exit(0);
	}

	remaining = 8;
	ifs.read(&buffer, 1);
}

bool IBuffer::GetBit()
{
	char mask = 1 << (remaining - 1);
	bool rv = mask & buffer ? true : false;
	remaining--;

	if (remaining == 0)
	{
		if (ifs.eof())
		{
			std::cout << "Out of file range!" << std::endl;
		}
		remaining = 8;
		ifs.read(&buffer, 1);
	}

	return rv;
}

bool IBuffer::PeekBit()
{
	char mask = 1 << (remaining - 1);
	return mask & buffer ? true : false;
}

void IBuffer::Destroy()
{
	ifs.close();
}

/**************************************************************************************/

OBuffer::OBuffer(std::string filePath) :
	buffer(0),
	remaining(0),
	ofs(filePath, std::ios::binary | std::ios::out)
{
	if (!ofs.is_open())
	{
		std::cout << "Failed to open the file, ";
		std::cout << "please check if the file exists ";
		std::cout << "or is open by another program" << std::endl;

		exit(0);
	}
}

void OBuffer::PutBit(bool bit)
{
	remaining++;
	buffer = buffer << 1;
	buffer += bit ? 1 : 0;

	if (remaining == 8)
	{
		ofs.write(&buffer, 1);
		remaining = 0;
	}
}

void OBuffer::PutBit(int bits, int num)
{
	for (int i = 0; i < num; i++)
	{
		PutBit(bits & (1 << (num - 1)));
	}
}

void OBuffer::FixEnd()
{
	while (remaining != 0)
	{
		PutBit(false);
	}
}

void OBuffer::Destroy()
{
	ofs.close();
}

/**************************************************************************************/

Heap::Heap(int capacity) :
	root(new TreeNode[CAPACITY + 1]),
	capacity(CAPACITY + 1),
	currentIndex(0)
{
}

void Heap::Push(TreeNode& value)
{
	currentIndex++;
	root[currentIndex] = value;

	TreeNode temp;

	int copy = currentIndex;
	while (copy > 1)
	{
		if (root[copy] < root[copy << 1])
		{
			temp = root[copy];
			root[copy] = root[copy << 1];
			root[copy << 1] = temp;
		}
	}
}

void Heap::Pop()
{
	TreeNode* last = root + currentIndex;
	currentIndex--;

	TreeNode* temp = nullptr;
	int location = 1;

	while (location * 2 < currentIndex)
	{
		if (root[location * 2] < root[location * 2 + 1])
		{
			if (*last < root[location * 2])
			{
				root[location] = *last;
				break;
			}
			else
			{
				root[location] = root[location * 2];
				location *= 2;
			}
		}
		else
		{
			if (*last < root[location * 2 + 1])
			{
				root[location] = *last;
				break;
			}
			else
			{
				root[location] = root[location * 2 + 1];
				location *= 2;
				location++;
			}
		}
	}

	if (2 * location == currentIndex)
	{
		root[location * 2 + 1] = *last;
	}
	else if (2 * location > currentIndex)
	{
		root[location * 2] = *last;
	}
}

/**************************************************************************************/

void CountOccurrence(std::string filePath, CharInfo* countArray)
{
	std::ifstream ifs(filePath, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "Failed to open the file, ";
		std::cout << "please check if the file exists ";
		std::cout << "or is open by another program" << std::endl;

		exit(0);
	}

	for (int i = 0; i < CAPACITY; i++)
	{
		countArray[i] = CharInfo(i + 32, 0);
	}

	char ch;
	while (!ifs.eof())
	{
		ch = ifs.get();
		countArray[ch - 32].count++;
	}
}

TreeNode* HuffmanTreeConstruct(CharInfo* dictionary)
{
	Heap heap = Heap(CAPACITY);
}

void FixDictionary(CharInfo* dictionary, TreeNode* huffmanTreeRoot)
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
