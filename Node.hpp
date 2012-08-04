#ifndef _NODE
#define _NODE

#include <vector>
using namespace std;
class Node {
protected: 
  vector<double> data;
public:
  Node();
  Node(const Node&);
  Node(int dataSize);

  void initialize(int dataSize);
  
  virtual ~Node();
  double compare(vector<double>&);
  void correct(vector<double>&, double);
  vector<double>& getData();
  void setData(const vector<double>& data);
};
#endif
