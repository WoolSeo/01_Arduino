/*
  DigitalOutput.cpp - Ardunity Arduino library
  Copyright (C) 2015 ojh6t3k.  All rights reserved.
*/

//******************************************************************************
//* Includes
//******************************************************************************
#include "Ardunity.h"
#include "DigitalOutput.h"


//******************************************************************************
//* Constructors
//******************************************************************************

DigitalOutput::DigitalOutput(int id, int pin) : ArdunityController(id)
{
	_pin = pin;
    canFlush = false;
}

//******************************************************************************
//* Override Methods
//******************************************************************************
void DigitalOutput::OnSetup()
{
	digitalWrite(_pin, LOW); // disable PWM
	pinMode(_pin, OUTPUT);
	_value = false;
	OnExecute();
}

void DigitalOutput::OnStart()
{
}

void DigitalOutput::OnStop()
{
	_value = false;
	OnExecute();
}

void DigitalOutput::OnProcess()
{	
}

void DigitalOutput::OnUpdate()
{
	BOOL newValue = _value;	
	ArdunityApp.pop(&newValue);
	if(newValue != _value)
	{
		_value = newValue;
		updated = true;
	}
}

void DigitalOutput::OnExecute()
{
	if(_value)
		digitalWrite(_pin, HIGH);
	else
		digitalWrite(_pin, LOW);
}

void DigitalOutput::OnFlush()
{
}

//******************************************************************************
//* Private Methods
//******************************************************************************

