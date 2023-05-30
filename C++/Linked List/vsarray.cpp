//
// Created by Arias Arevalo, Carlos on 5/6/20.
// Edited by Crites, Garrett  on 5/13/21
//

#include "object.h"
#include "list.h"
#include "vsarray.h"

#include <string>
using std::string;

VSArray::VSArray(size_t capacity, double increasePercentage) : _capacity(capacity), _delta(increasePercentage) {
	_data = new Object*[capacity];
	for (size_t i = 0; i < _capacity; ++i) {
		_data[i] = nullptr;
	}
	_size = 0;
}
VSArray::VSArray(const VSArray& list){
	for (size_t i = 0; i < _size; ++i) {
		delete _data[i];
	}
	delete[] _data;
	_size = 0;

	for (size_t i = 0; i < list.Size(); ++i) {
		Insert(list.Get(i), i);
	}
}
VSArray::~VSArray(){
	if (!IsEmpty()) {
		for (size_t i = 0; i < _capacity; ++i) {
			delete _data[i];
		}
		delete[] _data;
	}

}
const VSArray& VSArray::operator=(const VSArray& rhs){
	return *this;
}

bool VSArray::Insert(Object* element, size_t position){

	if (position > _capacity) {
		return false;
	}
	else if (position > _size) {
		return false;
	}
	else if (position == _size && position == _capacity) {
		Resize();
		_data[position] = element;
		_size++;
		return true;
	}
	else {
		if (_size + 1 > _capacity) {
			Resize();
			_size++;
			for (size_t i = _size - 1; i > position; --i) {
				_data[i] = _data[i - 1];
			}
			_data[position] = element;
			return true;
		}
		else {
			++_size;
			for (size_t i = _size - 1; i > position; --i) {
				_data[i] = _data[i - 1];
			}
			_data[position] = element;
			return true;
		}
	}

	return false;
}
int VSArray::IndexOf(const Object* element)const{

	for (size_t i = 0; i < _size; ++i) {
		if (_data[i]->Equals(*element)) {
			return static_cast<int>(i);
		}
	}

	return -1;
}
Object* VSArray::Remove(size_t position){

	Object* retVal = nullptr;

	if (position >= _capacity) {
		return nullptr;
	}
	else if (position >= _size) {
		return nullptr;
	}
	else {
		retVal = _data[position];
		_data[position] = nullptr;
		for (size_t i = position; i < _size; ++i) {
			_data[i] = _data[i + 1];
		}
		--_size;
		return retVal;
	}

	return nullptr;
}
Object* VSArray::Get(size_t position)const{
	if (position >= _size) {
		return nullptr;
	}
	else {
		return _data[position];
	}
}
string VSArray::ToString()const{
	return "";
}
void VSArray::Clear(){

	for (size_t i = 0; i < _size; ++i) {
		delete _data[i];
	}

	_size = 0;
}

void VSArray::Resize() {
	size_t newCapacity = _capacity + (_capacity * _delta);
	Object** data = new Object*[newCapacity];
	for (size_t i = 0; i < _capacity; ++i) {
    if (i < _size) {
      data[i] = _data[i];
    }
    else {
      data[i] = nullptr;
    }
	}

  delete[] _data;
	_data = data;
	_capacity = newCapacity;
}

size_t VSArray::GetCapacity() const {
	return _capacity;
}
