#include "Node.hpp"
#include <numeric>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cmath>
//#include <iostream>
//using namespace std;
Node::Node() {
}

Node::Node(int dataSize) {
  this->initialize(dataSize);
}

Node::Node(const Node& node) {
  this->data = node.data;
}

void Node::initialize(int dataSize) {
  for (int ii = 0; ii < dataSize; ii++) {
    
    this->data.push_back((float) rand() / (float) RAND_MAX);
  }
}
  
Node::~Node() {
}

double Node::compare(vector<double>& vec) {
  double powerSum = 0.0;
  vector<double>::iterator itData = this->data.begin();
  vector<double>::iterator itVec = vec.begin();
  vector<double>::iterator end = this->data.end();
  
  for (itData; itData <= end; itData++, itVec++){
    powerSum += pow(*itVec - *itData, 2);
  }
//  cout << sqrt(powerSum) << endl;
  return sqrt(powerSum);
}

void Node::correct(vector<double>& vec, double modifier) {
  vector<double>::iterator itData = this->data.begin();
  vector<double>::iterator itVec = vec.begin();
  vector<double>::iterator end = this->data.end();

  for (itData; itData < end; itData++, itVec++){
    *itData = *itData +  modifier * (*itVec - *itData);
  }
}


vector<double>& Node::getData(){
  return this->data;
}

void Node::setData(const vector<double>& data) {
  this->data = data;
}

