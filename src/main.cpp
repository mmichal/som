using namespace std;
#include "Som.hpp"
#include <iostream>


void printNodes(vector<vector<vector<Node*>*>*>& nodes) {

  for (auto zz = nodes.begin(); zz <  nodes.end(); zz++) {
    for (auto yy = (*zz)->begin(); yy < (*zz)->end(); yy++) {
      for (auto node = (*yy)->begin(); node <  (*yy)->end(); node++) {
        cout 
          << " | " 
          << (*node)->getData()[0] 
          << " " 
          << (*node)->getData()[1] 
          << " " 
          << (*node)->getData()[2] 
          << " | ";
      }
      cout << endl;
    }
  }

}

int main() {
  srand(time(NULL));
  Som* som = new Som(3, 2, 5, 2, 0.3);
  auto nodes = som->getNodes();
  printNodes(nodes);
  auto probe = new vector<double>();
  probe->push_back(0.1);
  probe->push_back(0.2);
  probe->push_back(0.3);
  auto result = som->match(*probe);
  cout << endl << result[0] << " " << result[1] << endl << endl; 
  printNodes(nodes);
  return 1;
}

