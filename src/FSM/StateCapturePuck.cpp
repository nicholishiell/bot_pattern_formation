#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "StateCapturePuck.h"
#include "FSM.h"

StateCapturePuck::StateCapturePuck(){
  name = "CapturePuck"; 
};

void StateCapturePuck::Enter(){};

void StateCapturePuck::Execute(StateManager* fsm){
  printf("Executing behaviour %s...\n",name.c_str());

  // Close the puck lock!
  fsm->CloseServo();

};

void StateCapturePuck::Exit(){};
  

// seePuck, havePuck, seeGoal, atGoal, movingForward, puck2Close2Goal, prox
State * StateCapturePuck::Transition(bool* stimuli){
  
  
  if(stimuli[6] == true){
    return new StateEvade();
  }
  else if(stimuli[0] == true and stimuli[1] == false){
    return new StateTrackPuck();
  }
  else if(stimuli[5] == true){
    return new StateDepositPuck();
  }
  else{
    return new StateSearchGoal();
  }
  
};
std::string StateCapturePuck::GetNameString(){
  return name;
};

void StateCapturePuck::Print(){
  printf("%s\n",name.c_str());
};
