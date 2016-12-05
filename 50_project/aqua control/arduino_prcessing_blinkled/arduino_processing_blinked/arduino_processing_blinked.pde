import processing.serial.*;
import controlP5.*;

ControlP5 cp5;

int myColor = color(255);

int c1,c2;

float n,n1;


Serial myPort;


void setup() {
  size(400,600);
  noStroke();
  
  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
  
  cp5 = new ControlP5(this);
  
  // create a new button with name 'buttonA'
  cp5.addButton("colorA")
     .setValue(0)
     .setPosition(100,100)
     .setSize(200,19)
     ;
}

void draw() {
  background(myColor);
  myColor = lerpColor(c1,c2,n);
  n += (1-n)* 0.1; 
}

public void controlEvent(ControlEvent theEvent) {
  println(theEvent.getController().getName());
  n = 0;
}

// function colorA will receive changes from 
// controller with name colorA
public void colorA(int theValue) {
  println("a button event from colorA: "+theValue);
  c1 = c2;
  c2 = color(0,160,100);
  myPort.write('a');
}