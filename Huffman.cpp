#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define CAPACITY 95
#define DEBUG

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

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

int main(int argc, char** argv)
{
	std::string sampleFile;
#ifndef DEBUG
	std::cout << "Please enter the sample file for occurrence counting: ";
	std::cin >> sampleFile;
#else
	sampleFile = "D:\\e.txt";
#endif
	CharInfo* dict = new CharInfo[CAPACITY];
	CountOccurrence(sampleFile, dict);

	TreeNode* root = HuffmanTreeConstruct(dict);

	std::string sourceFile;
	std::string codeFile;
	std::string decompressedFile;
#ifndef DEBUG
	std::cout << "Please enter the file to be compressed: ";
	std::cin >> sourceFile;
#else
	sourceFile = "D:\\s.txt";
#endif
#ifndef DEBUG
	std::cout << "Please enter the file storing compressed code: ";
	std::cin >> codeFile;
#else
	codeFile = "D:\\c.hcc";
#endif
#ifndef DEBUG
	std::cout << "Please enter the target file path";
	std::cin >> decompressedFile;
#else
	decompressedFile = "D:\\d.txt";
#endif

	Compress(sourceFile, codeFile, dict);
	Decompress(codeFile, decompressedFile, root);

	return 0;
}

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

CharInfo::CharInfo()
	: ch(0)
	, huffmanCode(0)
	, huffmanCodeBits(0)
	, count(0)
{
}

CharInfo::CharInfo(char ch)
	: ch(ch)
	, huffmanCode(0)
	, huffmanCodeBits(0)
	, count(0)
{
}

CharInfo::CharInfo(char ch, int count)
	: ch(ch)
	, huffmanCode(0)
	, huffmanCodeBits(0)
	, count(count)
{
}

void CharInfo::AttachCode(int huffmanCode, char huffmanCodeBits)
{
	this->huffmanCode = huffmanCode;
	this->huffmanCodeBits = huffmanCodeBits;
}

TreeElem::TreeElem()
	: ch(0)
	, isLeaf(true)
	, totalCount(0)
{
}

TreeNode::TreeNode()
	: value(TreeElem())
	, l(nullptr)
	, r(nullptr)
{
}

TreeNode::TreeNode(char ch, CharInfo* dictionary)
	: value(TreeElem())
	, l(nullptr)
	, r(nullptr)
{
	value.ch = ch;
	value.isLeaf = true;
	value.totalCount = dictionary[ch - 32].count;
}

TreeNode::TreeNode(TreeNode* sub1, TreeNode* sub2)
	: value(TreeElem())
	, l(sub1)
	, r(sub2)
{
	value.ch = 0;
	value.isLeaf = false;
	value.totalCount = sub1->value.totalCount + sub2->value.totalCount;
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

const bool
TreeNode::operator<(const TreeNode& operand2) const
{
	return value.totalCount < operand2.value.totalCount;
}

IBuffer::IBuffer(std::string filePath)
	: buffer(0)
	, remaining(0)
	, ifs(filePath, std::ios::binary | std::ios::in)
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
		else
		{
			remaining = 8;
			ifs.read(&buffer, 1);
		}
	}

	return rv;
}

bool IBuffer::PeekBit()
{
	char mask = 1 << (remaining - 1);
	return mask & buffer ? true : false;
}

OBuffer::OBuffer(std::string filePath)
	: buffer(0)
	, remaining(0)
	, ofs(filePath, std::ios::binary | std::ios::out)
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
		buffer = 0;
	}
}

void OBuffer::PutBit(int bits, int bitNum)
{
	for (int i = 0; i < bitNum; i++)
	{
		PutBit(bits & (1 << (bitNum - i - 1)));
	}
}

void OBuffer::FixEnd()
{
	while (remaining != 0)
	{
		PutBit(false);
	}
}

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

	ifs.close();
}

TreeNode* HuffmanTreeConstruct(CharInfo* dictionary)
{
	TreeNode* arr[CAPACITY];
	int remaining = CAPACITY;

	for (int i = 0; i < CAPACITY; i++)
	{
		arr[i] = new TreeNode(i + 32, dictionary);
	}

	TreeNode* temp = nullptr;

	while (remaining > 1)
	{
		for (int i = 0; i < CAPACITY - 1; i++)
		{
			for (int j = CAPACITY - 2; j >= i; j--)
			{
				if (arr[j + 1] == nullptr)
				{
					continue;
				}
				else if (arr[j] == nullptr)
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
				else if (arr[j]->value.totalCount > arr[j + 1]->value.totalCount)
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}

		TreeNode* combined = new TreeNode(arr[0], arr[1]);
		arr[0] = combined;
		arr[1] = nullptr;
		remaining--;
	}

	TreeNode* res = arr[0];

	res->DictionaryFixing(dictionary);

#ifdef DEBUG
	for (int i = 0; i < CAPACITY; i++)
	{
		std::cout << dictionary[i].ch << '\t';
		std::cout << (int)(dictionary[i].huffmanCodeBits) << '\t';
		std::cout << dictionary[i].count << '\t';
		for (int mask = 1 << (dictionary[i].huffmanCodeBits - 1); mask > 0; mask >>= 1)
		{
			std::cout << ((mask & dictionary[i].huffmanCode) ? '1' : '0');
		}
		std::cout << std::endl;
	}
#endif

	return res;
}

void Compress(std::string sourceFilePath, std::string outputFilePath, CharInfo* dictionary)
{
	std::ifstream ifs(sourceFilePath, std::ios::in);

	OBuffer ob(outputFilePath);

	char ch = 0;
	int totalBits = 0;

	while (!ifs.eof())
	{
		ch = ifs.get();
		totalBits += dictionary[ch - 32].huffmanCodeBits;
		ob.PutBit(dictionary[ch - 32].huffmanCode, dictionary[ch - 32].huffmanCodeBits);
	}
	ifs.close();
	ob.Destroy();

	std::ofstream ofs(outputFilePath, std::ios::app | std::ios::binary);
	ofs.write((char*)&totalBits, 4);
	ofs.close();
}

void Decompress(std::string compressedFilePath, TreeNode* root)
{
	std::ifstream detectingIfs(compressedFilePath, std::ios::in | std::ios::binary);

	int totalBits;
	detectingIfs.seekg(-4, std::ios::end);
	detectingIfs.read((char*)(&totalBits), 4);
	detectingIfs.close();

	IBuffer ib(compressedFilePath);
	TreeNode* rootCopy = root;

	while (totalBits > 0)
	{
		totalBits--;
		rootCopy = ib.GetBit() ? rootCopy->r : rootCopy->l;
		if (rootCopy->value.isLeaf)
		{
			std::cout << rootCopy->value.ch;
			rootCopy = root;
		}
	}

	ib.Destroy();
}

void Decompress(std::string compressedFilePath, std::string outputFilePath, TreeNode* root)
{
	std::ifstream detectingIfs(compressedFilePath, std::ios::in | std::ios::binary);
	std::ofstream ofs(outputFilePath, std::ios::out);

	int totalBits;
	detectingIfs.seekg(-4, std::ios::end);
	detectingIfs.read((char*)&totalBits, 4);
	detectingIfs.close();

	IBuffer ib(compressedFilePath);
	TreeNode* rootCopy = root;

	while (totalBits > 0)
	{
		totalBits--;
		rootCopy = ib.GetBit() ? rootCopy->r : rootCopy->l;
		if (rootCopy->value.isLeaf)
		{
			ofs << rootCopy->value.ch;
			rootCopy = root;
		}
	}

	ib.Destroy();
	ofs.close();
}
