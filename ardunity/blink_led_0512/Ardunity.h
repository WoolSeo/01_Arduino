/*
  Ardunity.h - Ardunity Arduino library
  Copyright (C) 2015 ojh6t3k.  All rights reserved.
*/

#ifndef Ardunity_h
#define Ardunity_h

#include "Arduino.h"
#include "ArdunityController.h"

// Do not edit below contents
#define MAX_ARGUMENT_BYTES    116
#define CMD_START         0x80 // start
#define CMD_EXIT	      0x81 // exit
#define CMD_UPDATE        0x82 // update
#define CMD_EXECUTE       0x83 // execute
#define CMD_READY         0x84 // ready
#define CMD_PING	      0x85 // ping



class ArdunityAppClass
{
public:
	ArdunityAppClass();

	// for application
	void begin();
	void begin(long speed);
	void begin(Stream *s);
    void resolution(int pwm, int adc);
    void timeout(unsigned long millisec);
    void process(void);
	void process(Stream *s);
    void attachController(ArdunityController* controller);
	void detachController(ArdunityController* controller);

    // for module
    int maxPWM;
    int maxADC;
    
	void select(byte id);
	void flush();
	boolean push(BOOL value);
	boolean push(UINT8 value);
	boolean push(INT8 value);
	boolean push(UINT16 value);
	boolean push(INT16 value);
	boolean push(UINT32 value);
	boolean push(INT32 value);
	boolean push(FLOAT32 value);
	boolean push(STRING value);
	boolean pop(BOOL* value);
	boolean pop(UINT8* value);
	boolean pop(INT8* value);
	boolean pop(UINT16* value);
	boolean pop(INT16* value);
	boolean pop(UINT32* value);
	boolean pop(INT32* value);
	boolean pop(FLOAT32* value);
	boolean pop(STRING value, int maxSize);

private:
    Stream* commSocket;
	ArdunityController* firstController;

    boolean connected;
    unsigned long preTime;
    unsigned long timeoutMillis;
	boolean readyReceived;
	byte processUpdate;
	byte ID;
	byte numData;
	byte currentNumData;
    byte storedData[MAX_ARGUMENT_BYTES + (MAX_ARGUMENT_BYTES / 8) + 1];
	byte numArgument;
	byte storedArgument[MAX_ARGUMENT_BYTES];
	
    void Reset(void);
	boolean push(byte* value, int size);
	boolean pop(byte* value, int size);
};

extern ArdunityAppClass ArdunityApp;

#endif

