//
//	Edited by Garrett Crites on 5/4/2021
//

#include "object.h"
#include "dlinkedlist.h"

#include <string>
using std::string;

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList &other){
	this->DoubleLinkedList::Clear();
	for (size_t i = 0; i < other.Size(); ++i) {
		this->DoubleLinkedList::Insert(other.Get(i), i);
	}
}

DoubleLinkedList &DoubleLinkedList::operator=(const DoubleLinkedList &rhs) {
	if (!this->Equals(rhs)) {
		DoubleLinkedList *newList = new DoubleLinkedList(rhs);
		return *newList;
	}
	else {
		return *this;
	}
}

DoubleLinkedList::DoubleLinkedList(){
	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}

DoubleLinkedList::~DoubleLinkedList() {
	//Node* tmp = nullptr;

//	if (_head != nullptr) {
//		tmp = _tail;
//		while (_tail != nullptr) {
//			_tail = tmp->previous;
//			if (tmp->data != nullptr) {
//				delete tmp->data;
//			}
//			delete tmp;
//			tmp = _tail;
//		}
//	}
	if (this->Size() != 0) {

		Node* currNode = nullptr;
		Node* prevNode = nullptr;
		Node* deleteNode = nullptr;

		currNode = _tail;
		prevNode = _tail->previous;
		while (currNode->previous != nullptr) {
			deleteNode = currNode;
			currNode = prevNode;
			if (currNode->previous != nullptr) {
				prevNode = currNode->previous;
			}
			_tail = currNode;
      delete deleteNode->data;
			delete deleteNode;
			--_size;
		}
    delete currNode->data;
    delete currNode;
		_size = 0;
	}
}

bool DoubleLinkedList::Insert(Object *element, size_t position) {
	Node* newNode = new Node;
	Node* currNode = nullptr;
	Node* prevNode = nullptr;

	newNode->data = element;
	newNode->next = nullptr;
	newNode->previous = nullptr;

	if (position > _size) {
		delete newNode;
		return false;
	}
	else if (position == 0 && IsEmpty()) {
		_head = newNode;
		_tail = newNode;
		_size = 1;
		return true;
	}
	else if (position == 0) {
		currNode = _head;
		newNode->next = currNode;
		currNode->previous = newNode;
		_head = newNode;
		++_size;
		return true;
	}
	else if (position == _size) {
		currNode = _tail;
		newNode->previous = currNode;
		currNode->next = newNode;
		_tail = newNode;
		++_size;
		return true;
	}
	else {
		if (position > _size / 2) {
			currNode = _tail;
			prevNode = _tail->previous;
			for (size_t i = _size - 1; i >= 0; --i) {
				if (i == position) {
					newNode->next = currNode;
					newNode->previous = prevNode;
					prevNode->next = newNode;
					currNode->previous = newNode;
					++_size;
					return true;
				}
				else {
					currNode = currNode->previous;
					prevNode = currNode->previous;
				}
			}
		}
		else {
			currNode = _head;
			for (size_t i = 0; i <= _size; ++i) {
				if (i == position) {
					newNode->next = currNode;
					newNode->previous = prevNode;
					prevNode->next = newNode;
					currNode->previous = newNode;
					++_size;
					return true;
				}
				else {
					prevNode = currNode;
					currNode = currNode->next;
				}
			}
		}
	}

	delete newNode;
	return false;
}

int DoubleLinkedList::IndexOf(const Object *element) const {
	Node* tmp = nullptr;

	tmp = _head;
	for (int i = 0; i < static_cast<int>(_size); ++i) {
		if (tmp->data->Equals(*element)) {
			return i;
		}
		else {
			tmp = tmp->next;
		}
	}

	return -1;
}

Object *DoubleLinkedList::Remove(size_t position) {
	Node* currNode = nullptr;
	Node* prevNode = nullptr;
	Node* succNode = nullptr;
	Object* retVal = nullptr;

	if (IsEmpty()) {
		return nullptr;
	}
	else if (position == _size) {
		return nullptr;
	}
	else if (position == _size - 1) {
		currNode = _tail;
		prevNode = _tail->previous;
		prevNode->next = nullptr;
		_tail = prevNode;
		retVal = currNode->data;
		delete currNode;
		--_size;
		return retVal;
	}
	else if (position == 0) {
		currNode = _head;
		succNode = _head->next;
		succNode->previous = nullptr;
		_head = succNode;
		retVal = currNode->data;
		delete currNode;
		--_size;
		return retVal;
	}
	else {
		if (position > _size / 2) {
			currNode = _tail;
			prevNode = _tail->previous;
			for (size_t i = _size - 1; i >= 0; --i) {
				if (i == position) {
					prevNode->next = succNode;
					succNode->previous = prevNode;
					retVal = currNode->data;
					delete currNode;
					--_size;
					return retVal;
				}
				else {
					currNode = prevNode;
					succNode = currNode->next;
					prevNode = currNode->previous;
				}
			}
		}
		else {
			currNode = _head;
			succNode = _head->next;
			for (size_t i = 0; i < _size; ++i) {
				if (i == position) {
					prevNode->next = succNode;
					succNode->previous = prevNode;
					retVal = currNode->data;
					delete currNode;
					--_size;
					return retVal;
				}
				else {
					currNode = succNode;
					succNode = currNode->next;
					prevNode = currNode->previous;
				}
			}
		}
	}

	return nullptr;
}

Object *DoubleLinkedList::Get(size_t position) const {
	Node* tmp = nullptr;

	if (position == 0) {
		return _head->data;
	}
	else if (position == _size - 1) {
		return _tail->data;
	}
	else if (position > _size / 2) {
		tmp = _tail;
		for (size_t i = _size; i > 0; --i) {
			if (i == position) {
				return tmp->data;
			}
			else {
				tmp = tmp->next;
			}
		}
	}
	else {
		tmp = _head;
		for (size_t i = 0; i < _size; ++i) {
			if (i == position) {
				return tmp->data;
			}
			else {
				tmp = tmp->next;
			}
		}
	}

	return nullptr;
}

string DoubleLinkedList::ToString() const {
	return "";
}

void DoubleLinkedList::Clear() {
	if (this->Size() != 0) {

		Node* currNode = nullptr;
		Node* prevNode = nullptr;
		Node* deleteNode = nullptr;

		currNode = _tail;
		prevNode = _tail->previous;
		while (currNode->previous != nullptr) {
			deleteNode = currNode;
			currNode = prevNode;
			if (currNode->previous != nullptr) {
				prevNode = currNode->previous;
			}
			_tail = currNode;
			delete deleteNode;
			--_size;
		}
		_size = 0;
	}
}
