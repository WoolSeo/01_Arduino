/* A simple example to controll your arduino board via bluetooth of your android smartphone or tablet. Tested with Android 4.
Requirements:
Arduino Board
Bluetooth shield
Android Smartphone (Android 2.3.3 min.)
Ketai library for processing
Jumper D0 to TX
Jumper D1 to RX
Set bluetooth, bluetooth admin and internet sketch permissions in processing.
Processing Code:
*/

//required for BT enabling on startup

import android.content.Intent;
import android.os.Bundle;
import ketai.net.bluetooth.*;
import ketai.ui.*;
import ketai.net.*;

PFont fontMy;
boolean bReleased = true; //no permament sending when finger is tap
KetaiBluetooth bt;
boolean isConfiguring = true;
String info = "";
KetaiList klist;
ArrayList devicesDiscovered = new ArrayList();

//********************************************************************
// The following code is required to enable bluetooth at startup.
//********************************************************************

void onCreate(Bundle savedInstanceState) {
 super.onCreate(savedInstanceState);
 bt = new KetaiBluetooth(this);
}

void onActivityResult(int requestCode, int resultCode, Intent data) {
 bt.onActivityResult(requestCode, resultCode, data);
}

void setup() {
 size(displayWidth, displayHeight);
 frameRate(10);
 orientation(PORTRAIT);
 background(0);
 
 //start listening for BT connections
 bt.start();
 //at app start select device…
 isConfiguring = true;
 //font size
 fontMy = createFont("SansSerif", 40);
 textFont(fontMy);
}

void draw() {
 //at app start select device
 if (isConfiguring)
 {
  ArrayList names;
  background(78, 93, 75);
  klist = new KetaiList(this, bt.getPairedDeviceNames());
  isConfiguring = false;
 }
 else
 {
  background(0,50,0);
  if((mousePressed) && (bReleased == true))
  {
 //send with BT
  byte[] data = {'s','w','i','t','c','h','\r'};
  bt.broadcast(data);
 //first tap off to send next message
  bReleased = false;
  }
  if(mousePressed == false)
  {
  bReleased = true; //finger is up
  }
 //print received data
  fill(255);
  noStroke();
  textAlign(LEFT);
  text(info, 20, 104);
 }
}

void onKetaiListSelection(KetaiList klist) {
 String selection = klist.getSelection();
 bt.connectToDeviceByName(selection);
 //dispose of list for now
 klist = null;
}

//Call back method to manage data received
void onBluetoothDataEvent(String who, byte[] data) {
 if (isConfiguring)
 return;
 //received
 info += new String(data);
 //clean if string to long
 if(info.length() > 150)
 info = "";
}