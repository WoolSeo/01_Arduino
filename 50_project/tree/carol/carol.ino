int speakerPin = 9;
 
//Jingle Bells
int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
 
////Ding Dong Merrily on High
//int length = 73;
//char notes[] = "ggagsed deggsgg ggagsed deggsgg DCbCDbCbabCabagabgagsgasgsesgeseddeggsgg "; // a space represents a rest
//int beats[] = { 2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,2,2,2,2,2,2,4,2,2 };
 
////God Rest Ye Merry Gentlemen
//int length = 69;
//char notes[] = "ddaagfedcdefga ddaagfedcdefga avgavCDagfdefgfgavaagfedfedgfgavCDagfed";
//int beats[] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,1,1,2,4,2,2,2,2,2,2,2,2,2,2,8 };
 
////O Little Town of Bethlehem
//int length = 71;
//char notes[] = "cfffgagavCavafggfcfffgagavCavafggffaCDCvagfgavCcfagfccfffgagavCavafggf ";
//int beats[] = { 2,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,2,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,1,1,3,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,4,4,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,2 };
 
////While Shephards Watched
//int length = 29;
//char notes[] = "faagfvvagaCCbCaDCvagfeagffef ";
//int beats[] = { 2,3,1,2,2,2,2,2,2,2,2,2,2,6,2,3,1,2,2,2,2,2,2,2,2,2,2,6,2 };
 
////In The Bleak Midwinter
//int length = 51;
//char notes[] = "aavCagfgagdgavCaggfgagff vavCDDaaCagfecavCagfgagff ";
//int beats[] = { 2,3,1,2,2,4,4,3,1,2,2,8,3,1,2,2,3,1,4,2,2,3,1,6,2,3,1,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,4,4,2,2,3,1,8,8};
 
////Hark the Herald
//int length = 77;
//char notes[] = "cffefaagCCCvagacffefaagCffeedcCCCfvaagCCCfvaagDDDCvavgavCffgaDDDCvavgavCffgf ";
//int beats[] = {2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,1,1,3,1,2,2,4,3,1,2,2,2,2,4,2,1,1,3,1,2,2,4,8};
 
////O come all Ye Faithful
//int length = 64;
//char notes[] = "ggdgadbabCbaggsesgabsedd DCbCbabgasedggsgagdbbabCbabCbagsgCbagg ";
//int beats[] = { 2,4,2,2,4,4,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,3,1,6,2,4,2,2,4,4,2,2,2,2,3,1,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,4,3,1,6,8 };
 
////O Come O Come Emmanuel
//int length = 63;
//char notes[] = "egbbbaCbagabgegasedeaaeesgsedgabbbaCbag DD bb baCdagabgegasede ";
//int beats[] = { 2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,4,2,2,6,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,4,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,8,8 };
 
int tempo = 150;
 
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
 
void playNote(char note, int duration) {
  
char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' };
int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };
 
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
 
void setup() {
  pinMode(speakerPin, OUTPUT);
}
 
void loop() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
 
    // pause between notes
    delay(tempo / 2); 
  }
}

