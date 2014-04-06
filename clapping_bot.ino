/*
 * Clapping Bot by Chris Mueller
 *
 * An Arduino-powered robot that performs Steve Reich's "Clapping Music"
 * Currently a proof of concept with LEDs instead of solenoids.
 */


int lastBeat = 0;
int timePassed = 0;
const int beatLength = 200;

int p1[] = {1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};
int p2[] = {1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};
int curNote = 0;
int curRep = 0;
int curPhase = 0;

const int numNotes = 12;
const int numReps = 8;

int led1 = 3;
int led2 = 4;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  delay(3000);
  
  lastBeat = millis();
  timePassed = millis();
}

// the loop routine runs over and over again forever:
void loop() {
  update();
  
  if (p1[curNote]) digitalWrite(led1, HIGH);
  if (p2[curNote]) digitalWrite(led2, HIGH);
  
  delay(beatLength/2);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}


void update() {
  timePassed = millis() - lastBeat;
  while(timePassed < beatLength) {
    timePassed = millis() - lastBeat;
  }
  
  curNote++;
  if (curNote == numNotes) {
    curNote = 0;
    curRep++;
    if (curRep == numReps) {
      curRep = 0;
      curPhase++;
      shift();
    } 
  }
  
  lastBeat = millis();
}

void shift() {
  int temp = p2[0];
  for (int i = 0; i < numNotes-1; i++) {
    p2[i] = p2[i+1];
  }
  p2[numNotes-1] = temp;
}
