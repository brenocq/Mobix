#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "robot.h"
#include "parameters.h"
using namespace std;

//---------- Defines ---------//
#define windowWidth 628
#define windowHeight 628

//---------- Variables ---------//
vector<Robot*> robots;

//---------- Functions ---------//
void draw();
void timer(int);

void createRobots();

//---------- Main ---------//
int main(int argc, char** argv) {
  srand(42);
  createRobots();


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Mobix 2D Simulation");
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glutDisplayFunc(draw);
  glutTimerFunc(0, timer, 0);// Define qual será a função de loop
  glutMainLoop();


  return 0;
}

//------------------ Draw -----------------//
void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  for (auto robot : robots) {
    robot->draw();
  }
  glutSwapBuffers();
}

//------------------ Timer -----------------//
void timer(int){
  for (int i=0 ; i<int(robots.size()) ; i++) {
    vector<Robot*> nearestRobots;
    vector<float> robotPos = robots[i]->getPos();

    //---------- Calculate nearest robots ----------//
    Robot *nextRight=NULL, *nextLeft=NULL;
    for (int j=0 ; j<int(robots.size()) ; j++) {
      if(i==j)continue;
      vector<float> otherPos = robots[j]->getPos();
      if(abs(robotPos[1]-otherPos[1])<0.99f){// Same level
        // Check if robot is the next to the right
        if(otherPos[0]>robotPos[0]){
          if(nextRight==NULL){
            nextRight = robots[j];
            continue;
          }else if(abs(otherPos[0]-robotPos[0])<abs(nextRight->getPos()[0]-robotPos[0])){
            // If this robot is closer
            nextRight = robots[j];
            continue;
          }
        }
        // Check if robot is the next to the left
        if(otherPos[0]<robotPos[0]){
          if(nextLeft==NULL){
            nextLeft = robots[j];
            continue;
          }else if(abs(otherPos[0]-robotPos[0])<abs(nextLeft->getPos()[0]-robotPos[0])){
            // If this robot is closer
            nextLeft = robots[j];
            continue;
          }
        }
      }
      // Check robots above and below
    }
    if(nextRight!=NULL)
      nearestRobots.push_back(nextRight);
    if(nextLeft!=NULL)
      nearestRobots.push_back(nextLeft);

    //---------- Calculate forces ----------//
    vector<float> force(2, 0);// {x,y}
    if(robots[i]->getBeltState()==1){
      force[0]--;
    }else if(robots[i]->getBeltState()==2){
      force[0]++;
    }

    // Avoid colision
    for (int j=0 ; j<int(robots.size()) ; j++) {
      if(j==i)continue;
      if(robots[i]->getPos()[1]-robots[j]->getPos()[1]<0.99f &&
         abs(robots[j]->getPos()[0]-robots[i]->getPos()[0])<=1.0f){// Same level and making contact
        //Check if it makes contact on the left
        if(robots[i]->getPos()[0]>robots[j]->getPos()[0]){
          force[0]<0 ? force[0]=0 : force[0];
        }
        //Check if it makes contact on the right
        if(robots[i]->getPos()[0]<robots[j]->getPos()[0]){
          force[0]>0 ? force[0]=0 : force[0];
        }
      }
    }
    // Move robot up
    for (int j=0 ; j<int(robots.size()) ; j++) {
      if(j==i)continue;
      if(robots[i]->getPos()[1]-robots[j]->getPos()[1]<0.99f &&
         abs(robots[j]->getPos()[0]-robots[i]->getPos()[0])<=1.1f){// Same level and making contact
        //Check if it makes contact on the left
        if(robots[i]->getPos()[0]>robots[j]->getPos()[0]){
          if(robots[i]->getBeltState()==0){
            if(robots[j]->getBeltState()==1){
              force[1]+=0.5f;
            }
          }
        }
        //Check if it makes contact on the right
        if(robots[i]->getPos()[0]<robots[j]->getPos()[0]){
          if(robots[i]->getBeltState()==0){
            if(robots[j]->getBeltState()==2){
              force[1]+=0.5f;
            }
          }
        }
      }
    }
    //---------- Run ----------//
    robots[i]->run(nearestRobots, force);
  }
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, 0);
}

//--------- Auxiliar functions -------------//
void createRobots(){
  robots.resize(qtyRobots);
  for (int i = 0; i < qtyRobots; i++) {
    robots[i] = new Robot();
    robots[i]->setPos(vector<float>{float(i*2),0});
    robots[i]->setColor(vector<float>{rand()%100/100.0f,rand()%100/100.0f,rand()%100/100.0f});
    robots[i]->setId(i);
  }
}
