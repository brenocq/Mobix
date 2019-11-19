#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
using namespace std;

class Robot{
public:
  Robot();
  ~Robot();
  //------------------ Methods ------------------//
  void run(vector<Robot*>nearestRobots, vector<float>force);
  void draw();
  //------------------ Setter and Getters ------------------//
  void setPos(vector<int> pos);
  vector<int> getPos() const;
  void setColor(vector<float> color);
  void setCanConnect(bool canConnected);
  bool getCanConnect() const;
  void setIsConnected(bool isConnected);
  bool getIsConnected() const;
  void setRobotConnected(Robot* robot);
  int getBeltState() const;
  void setId(int id);
  int getId() const;
private:
  //------------------ Private variables ------------------//
  vector<int> _pos;// Robot position
  vector<float> _color;// Robot color
  bool _canConnect;
  bool _isConnected;// If this robot is connected to another robot
  Robot* _robotConnected;
  int _beltState;// 0->stop 1->counter-clockwise 2->clockwise

  //----- Auxiliar variables -----//
  float _lastAngleAnimationBelt;// To animate the belt
  int _id;
};

#endif// ROBOT_H
