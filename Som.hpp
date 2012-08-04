#ifndef _SOM
#define _SOM

#include <string>
#include <vector>
#include <exception>
#include "Node.hpp"
using namespace std;
class Som {

protected:
  int size;
  int inputDim;
  int mapDim;
  double timeConstant;
  unsigned long iteration;
  double radius;
  double startRadius;
  double startLearnigRate;
  double learningRate;
  vector<vector<vector<Node*>*>*> nodes;

public:
  Som();
  Som(int inputDim, int mapDim, int size, unsigned long timeConstant, double learningRate);

  void initialize(
      int inputDim,
      int mapDim,
      int size,
      unsigned long timeConstant, 
      double learningRate
  );
  vector<int> match(vector<double>);
  static vector<vector<double>> getNeibourghs(vector<int>, double, int, int);
  string* toJson();
  bool fromJson(const string&);
  virtual ~Som();
  vector<vector<vector<Node*>*>*>& getNodes();
};

#endif

