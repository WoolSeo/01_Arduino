import processing.serial.*;
import controlP5.*;

ControlP5 cp5;

PFont f;

public static final char HEADER = 'H';
public static final char LED_TAG = 'L';

Serial myPort;


int led1_state = 0;
int led2_state = 0;

int temp0;
int humi0;

int temp1;
int temp2;

void setup() {
  size(700,400);
  noStroke();
  
  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
  
  // Create the font
  printArray(PFont.list());
  f = createFont("Georgia-Bold", 20, true);
  textFont(f);
  
  cp5 = new ControlP5(this);
  
  // create a new button with name 'buttonA'
  cp5.addButton("LED1")
     .setValue(0)
     .setPosition(50,50)
     .setSize(200,50)
     ;
  cp5.addButton("LED2")
     .setValue(0)
     .setPosition(50,130)
     .setSize(200,50)
     ;
}

void draw() {
  background(100,200,150);
  if(led1_state == 1) {
    fill(255,255,0);
    rect(40, 40, 220, 70);
  }
  if(led2_state == 1) {
    fill(255,255,0);
    rect(40, 120, 220, 70);
  }
  
  textAlign(RIGHT);
  fill(255);
  text("temp0", width * 0.75, 100);
  text(temp0, width * 0.9, 100);
  text("temp1", width * 0.75, 150);
  text(temp1, width * 0.9, 150);
  text("temp2", width * 0.75, 200);
  text(temp2, width * 0.9, 200);
  
}

public void controlEvent(ControlEvent theEvent) {
  println(theEvent.getController().getName());
}

// function colorA will receive changes from 
// controller with name colorA
public void LED1(int theValue) {
  println("a button event from colorA: "+theValue);
  if(led1_state == 0) {
    //led1_state = 1;
    sendMessage(LED_TAG, 1, 1);
  }
  else {
    //led1_state = 0;
    sendMessage(LED_TAG, 1, 0);
  }
}
public void LED2(int theValue) {
  println("a button event from colorB: "+theValue);
  sendMessage(LED_TAG, 2, 1);
  if(led2_state == 0) {
    //led2_state = 1;
    sendMessage(LED_TAG, 2, 1);
  }
  else {
    //led2_state = 0;
    sendMessage(LED_TAG, 2, 0);
  }
}

void sendMessage(char tag, int led, int button)
{
  print("Send to Arduino: ");
  println("H " + tag + " 0 " + led + " 0 " + button);
  myPort.write(HEADER);//H
  myPort.write(tag);//L
  myPort.write(0);  // msb
  myPort.write(led);  // lsb 1,2,3,4
  myPort.write(0);  // msb
  myPort.write(button);  // lsb  0, 1
}

void serialEvent(Serial p)
{
  String message = myPort.readStringUntil(10);  
  if(message != null)
  {
    print("Received: ");
    println(message);
    
    int []data = int(split(message, ','));
    
    print("led1 state : ");
    print(data[1]);
    led1_state = data[1];
    
    print("  led2state : ");
    println(data[2]);
    led2_state = data[2];
    
    print("temp0 state : ");
    print(data[3]);
    temp0 = data[3];
    
    print("  temp1 state : ");
    print(data[4]);
    temp1 = data[4];
    
    print("  temp2 state : ");
    println(data[5]);
    temp2 = data[5];
  }
  

}