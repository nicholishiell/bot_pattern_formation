#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "StateImpulseSpeed.h"
#include "StateCruise.h"
#include "StateCatchUp.h"
#include "StateAlign.h"
#include "StateEvade.h"
#include "StateHalt.h"

#include "State.h"

#include "FSM.h"

StateEvade::StateEvade(){
  name = "Evade"; 
  
  /* initialize random seed: */
  srand (time(NULL));

  deltaT = 5.;

  time(&timeStamp);
  timerExpired = false;

  first = true;
};

void StateEvade::Enter(){};

void StateEvade::Execute(StateManager * fsm){
  //printf("Executing behaviour %s...\n", name.c_str());

  // This speed is half the standard speed 
  fsm->SetTransSpeed(2);
  
  // This value should depend on formationHeadingError
  float trackingError = fsm->GetFormationHeadingError();
  float kp = fsm->GetProportionalGain();  
  
  fsm->SetRotSpeed(kp*trackingError);

};

void StateEvade::Exit(){};

State * StateEvade::Transition(bool* stimuli){

  SetStimuli(stimuli);
   
  time_t currentTime;
  time(&currentTime);
  // Check if manvouver has finished yet

  if(difftime(currentTime, timeStamp) > deltaT){
    timerExpired = true;
  }

  if(friendAhead and (friendLeft or friendRight) ){
    return new StateCruise();
  }
  else if(friendAhead and not friendBehind ){
    return new StateCatchUp();
  }
  else if(not aligned ){
    return new StateAlign();
  }
  else if( frontProx ){
    return new StateEvade();
  }
  else if( friendBehind and not friendAhead){
    return new StateHalt();
  }
  else{
    return NULL;
  }

};

std::string StateEvade::GetNameString(){
  return name;
};

void StateEvade::Print(){
  printf("%s\n",name.c_str());
};
