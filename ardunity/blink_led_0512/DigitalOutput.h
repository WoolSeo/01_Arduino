/*
  DigitalOutput.h - Ardunity Arduino library
  Copyright (C) 2015 ojh6t3k.  All rights reserved.
*/
#ifndef DigitalOutput_h
#define DigitalOutput_h

#include "ArdunityController.h"


class DigitalOutput : ArdunityController
{
public:
	DigitalOutput(int id, int pin);	

protected:
	void OnSetup();
	void OnStart();
	void OnStop();
	void OnProcess();
	void OnUpdate();
	void OnExecute();
	void OnFlush();

private:
    int _pin;
	BOOL _value;
};

#endif

