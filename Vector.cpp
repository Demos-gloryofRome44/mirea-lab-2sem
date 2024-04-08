//
//  main.cpp
//  realization vector
//
//  Created by Егор on 13.03.2024.
//

#include "VectorNew.h"
#include <iostream>
#include <cstdlib>

Vector::Vector(const ValueType* rawArray, const size_t size, float coef) {
    _data = new ValueType[size];
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;
    for (size_t i = 0; i != size; ++i) {
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector &other){
    _size  = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _data = new ValueType[other._size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }

  *this = other;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        if (_capacity < other._size) {
            delete[] _data;
            _data = new ValueType[other._capacity];
            _capacity = other._capacity;
        }
        _size = other._size;
        _multiplicativeCoef = other._multiplicativeCoef;
        for (size_t i = 0; i < other._size; ++i) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept:
    _size(other._size),
    _capacity(other._capacity),
    _multiplicativeCoef(other._multiplicativeCoef),
    _data(other._data)
{
    other._size = 0;
    other._capacity = 0;
    other._data = nullptr;
}


Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] _data;
        
        _size = other._size;
        _multiplicativeCoef = other._multiplicativeCoef;
        _data = other._data;
        other._size = 0;
        other._capacity = 0;
        other._data = nullptr;
    }
    return *this;
}

Vector::~Vector() {
    delete[] _data;
}

void Vector::pushBack(const ValueType& value) {
    if (_size + 1 >= _capacity){
        if (_capacity == 0){
            _capacity++;
        }

        while (_size + 1 >= _capacity) {
            _capacity *= _multiplicativeCoef;
        }
        ValueType *newData = new ValueType[_capacity];
        for (int i = 0; i < _size; i++){
            newData[i] = _data[i];
        }
        delete [] _data;
        _data = newData;
    }
    _data[_size] = value;
    _size++;
}



void Vector::pushFront(const ValueType &value){
    if (_size + 1 >= _capacity){
        if (_capacity == 0){
            _capacity++;
        }
        while (_size + 1 >= _capacity){
            _capacity *= _multiplicativeCoef;
        }
        ValueType *newData = new ValueType[_capacity];
        for (int i = 0; i < _size; i++){
            newData[i] = _data[i];
        }
        delete [] _data;
        _data = newData;
    }

    for (int i = _size; i > 0; i--){
        _data[i] = _data[i-1];
    }
    _data[0] = value;
    _size++;
}

void Vector::insert(const ValueType& value, size_t pos) {
  if (pos <= _size){
    ValueType* newdata = new ValueType[_size + 1];
    for (size_t i = 0; i < pos; ++i) {
        newdata[i] = _data[i];
    }

    newdata[pos] = value;

    for (size_t i = pos; i < _size; ++i) {
        newdata[i + 1] = _data[i];
    }

    delete[] _data;
    _data = newdata;
    _size++;
    _capacity = _size;
}
}

void Vector::insert(const ValueType* values, size_t size, size_t pos) {
  if (pos <= _size){
    ValueType* newdata = new ValueType[_size + size];

    for (size_t i = 0; i < pos; ++i) {
        newdata[i] = _data[i];
    }

    for (size_t i = 0; i < size; ++i) {
        newdata[pos+i] = values[i];
    }

    for (size_t i = pos; i < _size; ++i) {
        newdata[i + size] = _data[i];
    }

    delete[] _data;
    _data = newdata;
    _size += size;
    _capacity = _size;
  }
}

void Vector::insert(const Vector& vector, size_t pos) {
  if (pos <= _size){
    ValueType* newdata = new ValueType[_size + vector._size];

    for (size_t i = 0; i < pos; ++i) {
        newdata[i] = _data[i];
    }

    for (size_t i = 0; i < vector._size; ++i) {
        newdata[pos + i] = vector._data[i];
    }

    for (size_t i = pos; i < _size; ++i) {
        newdata[i + vector._size] = _data[i];
    }

    delete[] _data;
    _data = newdata;
    _size += vector._size;
    _capacity = _size;
  }
}


void Vector::popBack() {
    if (_size == 0){
        throw "impossible";
    }
    _size--;
}

void Vector::popFront() {
    if (_size == 0){
        throw "impossible";
    }
    for (int i = 0; i < _size; i++) {
        _data[i] = _data[i+1];
    }
    _size--;
}


void Vector::erase(size_t pos, size_t count) {
  if (pos >= _size) {
        throw std::out_of_range("Erase - out of bounds");
    }
    count = std::min(count, _size - pos);
    ValueType *newdata = new ValueType[_size - count];
    
    std::copy(_data, _data + pos, newdata);
    
    std::copy(_data + pos + count, _data + _size , newdata + pos);
    
    delete[] _data;
    _data = newdata;
    _size -= count;
}

void Vector::eraseBetween(size_t begin , size_t end){
    ValueType *newdata = new ValueType[_size - end + begin];
    
    std::copy(_data, _data +begin, newdata);
    
    std::copy(_data + end, _data + _size, newdata + begin);
    
    delete[] _data;
    
    _size = _size + begin - end;
}

size_t Vector::size() const{
    return static_cast<size_t>(_size);
}

size_t Vector::capacity() const{
    return static_cast<size_t>(_capacity);
}

double Vector::loadFactor() const{
    return static_cast<size_t>(_size / _capacity);
}

ValueType& Vector::operator[](size_t idx) {
    return _data[idx];
}

const ValueType& Vector::operator[](size_t idx) const {
    return _data[idx];
}

long long Vector::find(const ValueType & value) const {
    for (size_t i = 0; i < _size; ++i){
        if (_data[i] == value){
            return static_cast<long long>(i);
        }
    }
    return 0;
}

 void Vector::reserve(size_t capacity){
    if (capacity > _capacity){
        ValueType *newdata = new ValueType[capacity];
        for (size_t i = 0; i < _size; ++i)
        {
            newdata[i] = _data[i];
        }
        
        delete[] _data;
        _data = newdata;
        _capacity = capacity;
    }
}

void Vector::shrinkToFit() {

    if (_size == 0) {
        delete[] _data;
        _data = nullptr;
        _capacity = 0;
    } else {
        ValueType* newdata = new ValueType[_size];
        for (size_t i = 0; i < _size; ++i) {
            newdata[i] = _data[i];
        }
        delete[] _data;
        _data = newdata;
        _capacity = _size;
    }
}



Vector::Iterator::Iterator(ValueType* ptr) {
    if (!ptr) {
        _ptr = nullptr;
    } else {
        _ptr = ptr;
    }
 }

 ValueType& Vector::Iterator::operator*() {
    return *_ptr;
 }

 const ValueType& Vector::Iterator::operator*() const {
    return *_ptr;
 }

 ValueType* Vector::Iterator::operator->() {
    return _ptr;
 }

const ValueType* Vector::Iterator::operator->() const {
    return _ptr;
}

 Vector::Iterator Vector::Iterator::operator++() {
    ++_ptr;
    return *this;
 }

  Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator tmp(_ptr);
    ++(*this);
    return tmp;
 }

bool Vector::Iterator::operator==(const Iterator& other) const {
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const {
    return _ptr != other._ptr;
}

Vector::Iterator Vector::begin() {
    return Iterator(&_data[0]);
}

Vector::Iterator Vector::end() {
    return Iterator(&_data[_size - 1]);
}
