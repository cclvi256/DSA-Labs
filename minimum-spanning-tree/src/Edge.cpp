#include "Edge.h"

void ESet::MergeSort(int mergeSize)
{
}

void ESet::Add(int v1, int v2, int weight)
{
	ENode* newHead = new ENode(v1, v2, weight, this->start);
	start = newHead;
}

ENode::ENode(int v1, int v2, int weight)
{
	this->v1 = v1;
	this->v2 = v2;
	this->weight = weight;
	this->next = nullptr;
}

ENode::ENode(int v1, int v2, int weight, ENode* base)
{
	this->v1 = v1;
	this->v2 = v2;
	this->weight = weight;
	this->next = base;
}
