#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <math.h>
#include <iostream>
#include "robot.h"
#include "parameters.h"

using namespace std;

Robot::Robot(){
  _pos.resize(2);
  _color.resize(3);
  _isConnected = false;
  _robotConnected = NULL;
  _beltState = 0;
  _lastAngleAnimationBelt = 0;
  _id = 0;
}

Robot::~Robot(){

}

void Robot::run(vector<Robot*>nearestRobots, vector<float>force){
  if(_id==3){
    cout<<"("<<force[0]<<","<<force[1]<<") size:"<<nearestRobots.size()<<endl;
    cout<<"\tPOS "<<_pos[0]<<","<<_pos[1]<<endl;
  }

  //---------- Force result ----------//
  _pos[0] += 0.01f*force[0];
  _pos[1] += 0.01f*force[1];
  //---------- Approach the farthest robot ----------//
  Robot* farthest=NULL;
  float maxDist=0;

  for(auto robot : nearestRobots){
    if(_id==3){
      cout<<"\t"<<robot->getPos()[0]<<endl;
      cout<<"\t"<<robot->getPos()[1]<<endl;
    }

    if(abs(robot->getPos()[1]-_pos[1])<0.99f){// Same level
      float dist = robot->getPos()[0]-_pos[0];

      // Find the fasthest
      if(abs(dist)>1.01f && abs(dist)>abs(maxDist)){
        farthest = robot;
        maxDist = dist;
      }
    }
  }
  if(farthest!=NULL){
    if(_isConnected){
      _robotConnected->setIsConnected(false);
      setIsConnected(false);
    }
    if(maxDist>0){
      _beltState = 2;
      return;
    }else{
      _beltState = 1;
      return;
    }
  }

  //---------- Connect to closer robot ----------//
  // Check if is far from some robot
  bool someConnectedCloser = false;
  for(auto robot : nearestRobots){
    if(robot->getIsConnected()){
      someConnectedCloser = true;
      break;
    }
  }
  if(!someConnectedCloser && nearestRobots.size()>0){
    _robotConnected = nearestRobots[0];
    nearestRobots[0]->setRobotConnected(this);
    _isConnected = true;
    nearestRobots[0]->setIsConnected(true);
  }

  if(nearestRobots.size()==2){
    if(nearestRobots[0]->getIsConnected() && nearestRobots[1]->getIsConnected()){
      if(_isConnected){
        _robotConnected->setIsConnected(false);
        setIsConnected(false);
      }
    }
  }
  //---------- Move behavior ----------//

  if(_isConnected){
    // Start spinning belt
    if(_robotConnected->getPos()[0]>_pos[0]){
      _beltState = 2;
    }else{
      _beltState = 1;
    }
  }else{
    if(nearestRobots.size()==1){
      if(nearestRobots[0]->getPos()[0]>_pos[0])
        _beltState = 1;
      else
        _beltState = 2;
    }else{
      _beltState = 0;
    }
  }
}

void Robot::draw(){
  //---------- Draw robot ----------//
  glColor3f(_color[0], _color[1], _color[2]);
  glBegin(GL_POLYGON);
  // Robot left bottom
  float screenX = (2.0f/maxScreenSize)*_pos[0]-1;
  float screenY = (2.0f/maxScreenSize)*_pos[1]-1;
  float w = 2.0f/maxScreenSize;
  float h = 2.0f/maxScreenSize;

  glVertex2d(screenX, screenY);
  glVertex2d(screenX, screenY+h);
  glVertex2d(screenX+w, screenY+h);
  glVertex2d(screenX+w, screenY);
  glEnd();
  //---------- Draw belt ----------//
  glColor3f(0, 0, 0);

  switch(_beltState){
    case 1:
      _lastAngleAnimationBelt+=5;
      _lastAngleAnimationBelt>360?_lastAngleAnimationBelt-=360:_lastAngleAnimationBelt;
      break;
    case 2:
      _lastAngleAnimationBelt-=5;
      _lastAngleAnimationBelt<0?_lastAngleAnimationBelt+=360:_lastAngleAnimationBelt;
      break;
  }

  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=5) {
    glVertex2d( w/12*cos(i/180.0*M_PI) + screenX+w/2+w/3*cos(_lastAngleAnimationBelt/180.0*M_PI),
                w/12*sin(i/180.0*M_PI) + screenY+h/2+w/3*sin(_lastAngleAnimationBelt/180.0*M_PI));
  }
  glEnd();
  glBegin(GL_POLYGON);
  for (int i = 0; i < 360; i+=5) {
    glVertex2d( w/12*cos(i/180.0*M_PI) + screenX+w/2+w/3*cos((_lastAngleAnimationBelt+180)/180.0*M_PI),
                w/12*sin(i/180.0*M_PI) + screenY+h/2+w/3*sin((_lastAngleAnimationBelt+180)/180.0*M_PI));
  }
  glEnd();
  //---------- Draw connection ----------//
  if(_isConnected){
    float screenXCon = (2.0f/maxScreenSize)*_robotConnected->getPos()[0]-1;
    float screenYCon = (2.0f/maxScreenSize)*_robotConnected->getPos()[1]-1;

    glColor3f(0.8, 0.0, 0);
    glBegin(GL_LINES);
    glVertex2d(screenX+w/2, screenY + h/2);
    glVertex2d(screenXCon+w/2, screenYCon+h/2);
    glEnd();
  }
}

//------------------ Setter and Getters ------------------//
void Robot::setPos(vector<float> pos){
  _pos = pos;
}
vector<float> Robot::getPos() const{
  return _pos;
}
void Robot::setColor(vector<float> color){
  _color = color;
}
void Robot::setIsConnected(bool isConnected){
  _isConnected = isConnected;
  if(!_isConnected){
    _robotConnected = NULL;
  }
}
bool Robot::getIsConnected() const{
  return _isConnected;
}
void Robot::setRobotConnected(Robot* robot){
  _robotConnected = robot;
}
int Robot::getBeltState() const{
  return _beltState;
}
void Robot::setId(int id){
  _id = id;
}
int Robot::getId() const{
  return _id;
}
