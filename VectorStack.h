//
//  VectorStack.h
//  Stack
//
//  Created by Егор on 31.03.2024.
//
#pragma once
#include <cstddef>
#include <iostream>
#include "StackImplementation.h"
#include <vector>

using namespace std;

class VectorStack : public IStackImplementation{
  private:
  vector<ValueType> _data;
public:
  void push(const ValueType &value) override{
    _data.push_back(value);
  }

void pop() override{
  if (!isEmpty())
        _data.pop_back();
  else
        throw out_of_range("Stack is empty");
}

const ValueType &top() const override{
  if (!isEmpty())
    return _data.back();
  else
      throw out_of_range("Stack is empty");
}

bool isEmpty() const override{
  return _data.empty();
}

size_t size() const override{
  return _data.size();
}
};
