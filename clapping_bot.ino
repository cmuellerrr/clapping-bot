/*
 * Clapping Bot by Chris Mueller
 *
 * An Arduino-powered robot that performs Steve Reich's "Clapping Music"
 * Currently a proof of concept with LEDs instead of solenoids.
 */

const int beatLength = 160;
int lastBeat = 0;
int timePassed = 0;

const int numNotes = 12;
const int numReps = 8;
const int numPhases = 12;
int curNote; 
int curRep;
int curPhase;

int pattern1[] = {1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};
int pattern2[] = {1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};

const int PIN_p1 = 3;
const int PIN_p2 = 4;
const int PIN_status = 5;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(PIN_p1, OUTPUT);
  pinMode(PIN_p2, OUTPUT);
  pinMode(PIN_status, OUTPUT);
  
  start();
}

void start() {  
  //start at -1 so we being with the first note
  curNote = -1; 
  curRep = 0;
  curPhase = 0;
  
  for (int i = 0; i < 4; i++) {
    digitalWrite(PIN_status, HIGH);
    delay(beatLength);
    digitalWrite(PIN_status, LOW);
    delay(beatLength);
  }
  
  lastBeat = millis();
  timePassed = millis();
}

// the loop routine runs over and over again forever:
void loop() {
  if (curPhase <= numPhases) {
    update();

    if (curRep == numReps - 1 && curNote == numNotes - 2) digitalWrite(PIN_status, HIGH);
    //TODO - if you stop it, make sure to turn off the LED
    if (curRep == 0) digitalWrite(PIN_status, LOW);

    if (pattern1[curNote]) digitalWrite(PIN_p1, HIGH);
    if (pattern2[curNote]) digitalWrite(PIN_p2, HIGH);
    
    delay(beatLength/2);
    
    digitalWrite(PIN_p1, LOW);
    digitalWrite(PIN_p2, LOW);
  }
}


void update() {
  timePassed = millis() - lastBeat;
  
  while(timePassed < beatLength) {
    timePassed = millis() - lastBeat;
  }
  
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
}
