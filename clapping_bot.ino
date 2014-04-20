/*
 * Clapping Bot by Chris Mueller
 *
 * An Arduino-powered robot that performs Steve Reich's "Clapping Music"
 * Currently a proof of concept with LEDs instead of solenoids.
 */

const int beatLength = 150;
int lastBeat = 0;
int timePassed = 0;

const int numNotes = 12;
const int numReps = 8;
const int numPhases = 12;
int curNote; 
int curRep;
int curPhase;
boolean justShifted;

int pattern1[] = {1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};
int pattern2[] = {1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};

const int player1 = 3;
const int player2 = 4;
const int statusLED = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(player1, OUTPUT);
  pinMode(player2, OUTPUT);
  pinMode(statusLED, OUTPUT);
  
  start();
}

void start() {
  justShifted = false;
  
  //start at -1 so we being with the first note
  curNote = -1; 
  curRep = 0;
  curPhase = 0;
  
  for (int i = 0; i < 4; i++) {
    digitalWrite(statusLED, HIGH);
    delay(250);
    digitalWrite(statusLED, LOW);
    delay(250);
  }
  
  lastBeat = millis();
  timePassed = millis();
}

// the loop routine runs over and over again forever:
void loop() {
  if (curPhase <= numPhases) {
    update();
    
    if (pattern1[curNote]) digitalWrite(player1, HIGH);
    if (pattern2[curNote]) digitalWrite(player2, HIGH);
    
    delay(beatLength/2);
    
    digitalWrite(player1, LOW);
    digitalWrite(player2, LOW);
  }
}


void update() {
  timePassed = millis() - lastBeat;
  
  if (justShifted) digitalWrite(statusLED, HIGH);
  
  while(timePassed < beatLength) {
    timePassed = millis() - lastBeat;
  }
  
  if (justShifted) digitalWrite(statusLED, LOW); justShifted = false;
  
  curNote++;
  if (curNote >= numNotes) {
    curNote = 0;
    curRep++;
    if (curRep >= numReps) {
      curRep = 0;
      curPhase++;
      shift();
    } 
  }
  
  lastBeat = millis();
}

void shift() {
  int temp = pattern2[0];
  for (int i = 0; i < numNotes-1; i++) {
    pattern2[i] = pattern2[i+1];
  }
  pattern2[numNotes-1] = temp;
  justShifted = true;
}
