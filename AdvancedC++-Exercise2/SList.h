#pragma once

template<class T>
class SList
{

protected:

	class Node {
		T value;
		Node* next;
	};

	Node* root;

	size_t size;

public:
	SList();
	virtual ~SList();
};

