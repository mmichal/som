#include "Som.hpp"
#include <cmath>
#include <climits>
#include <iostream>

using namespace std;

Som::Som() {
}

Som::~Som() {

}

Som::Som(
    int inputDim,
    int mapDim, 
    int size, 
    unsigned long timeConstant,
    double learningRate
    ) {
  this->initialize(inputDim, mapDim, size, timeConstant, learningRate);
}

vector<vector<double>> Som::getNeibourghs(
    vector<int> coords, 
    double radius,
    int mapDim, 
    int mapSize) {
  vector<vector<double>> result;

  int xMax = mapDim - 2 > 0 ? coords[0] + radius : 0;
  int yMax = mapDim - 1 > 0 ? coords[1] + radius : 0;
  int zMax = coords[2] + radius;

  int xMin = mapDim - 2 > 0 ? coords[0] - radius: 0;
  int yMin = mapDim - 1 > 0 ? coords[1] - radius: 0;
  int zMin = coords[2] - radius;

  if (xMin < 0) xMin = 0;
  if (yMin < 0) yMin = 0;
  if (zMin < 0) zMin = 0;
  if (xMax >= mapSize) xMax = mapSize - 1;
  if (yMax >= mapSize) yMax = mapSize - 1;
  if (zMax >= mapSize) zMax = mapSize - 1;

  for (int xx = xMin; xx <= xMax; xx++) {
    for(int yy = yMin; yy <= yMax; yy++) {
      for(int zz = zMin; zz <= zMax; zz++) {
        double distance = sqrt(
          pow(coords[0] - xx, 2) + pow(coords[1] - yy, 2) + pow(coords[2] - zz, 2)
        );
        cout << xx << " " << yy << " " << zz << " - " << radius << endl; 
        if (distance <= radius) {
          vector<double>* tempVec = new vector<double>(4);
          (*tempVec)[0] = xx;
          (*tempVec)[1] = yy;
          (*tempVec)[2] = zz;
          (*tempVec)[3] = distance;
          result.push_back(*tempVec);
        }
      }
    }
  }

  return result;
}

void Som::initialize(
    int inputDim, 
    int mapDim, 
    int size, 
    unsigned long timeConstant,
    double learningRate
  ) {
  this->mapDim = mapDim;
  this->size = size;
  int xSize = mapDim - 2 > 0 ? size : 1;
  int ySize = mapDim - 1 > 0 ? size : 1;
  int zSize = size;

  this->startRadius = size / 2;
  this->timeConstant = timeConstant;
  this->iteration = 1;
  this->startLearnigRate = learningRate;

  vector<vector<Node*>*>* tempVec1;
  vector<Node*>* tempVec2;
  Node* tempNode;

  for (int xx = 0; xx < xSize; xx++) {
    tempVec1 = new vector<vector<Node*>*>();

    for (int yy = 0; yy < ySize; yy++) {
      tempVec2 = new vector<Node*>();

      for (int zz = 0; zz < zSize; zz++) {
        tempNode = new Node(inputDim);
        tempVec2->push_back(tempNode);
      }

      tempVec1->push_back(tempVec2);
    }

    this->nodes.push_back(tempVec1);
  }
}

vector<int> Som::match(vector<double> data) {
  int xx = 0;
  int yy = 0;
  int zz = 0;

  double maxFoundDistance = -1;

  int bmuX = -1;
  int bmuY = -1;
  int bmuZ = -1;

  double currentDistance;

  for (auto yVec: this->nodes) {
    yy = 0;
    for (auto zVec: *yVec) {
      zz = 0;
      for (auto node: *zVec) {
        currentDistance = node->compare(data);
        if (currentDistance < maxFoundDistance || maxFoundDistance < 0) {
          maxFoundDistance = currentDistance;
          bmuX = xx;
          bmuY = yy;
          bmuZ = zz;
        }
        cout << currentDistance << " " << maxFoundDistance << " " << xx << " " << yy << " "<<  zz <<endl;
        zz++;
      }
      yy++;
    }
    xx++;
  }

  vector<int> tempBmu(3);
  tempBmu[0] = bmuX;
  tempBmu[1] = bmuY;
  tempBmu[2] = bmuZ;
 
  this->radius = this->startRadius * exp(
    -((double)this->iteration) / this->timeConstant
  );

  cout << this->radius << endl;
  vector<vector<double>> points = Som::getNeibourghs(
    tempBmu, 
    this->radius,
    this->mapDim,
    this->size
  );
  
  this->learningRate = this->startLearnigRate * exp(
    -((double)this->iteration)/this->timeConstant
  );

  cout << points.size() << endl;
  for(auto &point: points) {
    double modifier = this->learningRate * exp(
        pow(point[3],2)/(2 * pow(this->radius, 2))
    );
    
    (*(*this->nodes[point[0]])[point[1]] )[point[2]]->correct(data, modifier);
    cout << point[0] << " " << point[1] << " "<< point[2] <<endl;
  }

  if (this->iteration < ULONG_MAX) this->iteration++;
  vector<int> result(this->mapDim);
  for (int ii = 0; ii < this->mapDim; ii++) {
    result[ii] = tempBmu[this->mapDim  - ii];
  }
  return result;
}

string* Som::toJson() {
  return new string();
}

bool Som::fromJson(const string& json) {
  return false;
} 

vector<vector<vector<Node*>*>*>& Som::getNodes() {
  return this->nodes;
}

