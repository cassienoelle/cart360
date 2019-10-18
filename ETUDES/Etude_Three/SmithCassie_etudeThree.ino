/********************** ETUDE 3 CART 360 2019 *******************************
 * WELCOME! 
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS). 
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  loopMODE ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE, 
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS 
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 5 // R PIN
#define LED_PIN_G 9 // G PIN
#define LED_PIN_B 6 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration = 200;

// constant for pin to output for buzzer 
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes =0;
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES]; 
int mode =0; // start at off

/*****NEW VARIABLES *****************************************************/
// control to record note only when a new note is pressed
// (avoid entering a continuous data stream into the array)
bool saveTone = false;
// counter for how many notes have been played back
int notesPlayed = 0;
// control to shuffle array of notes only once when loop() is called
bool shuffled = false;

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  pinMode(BUTTON_MODE_PIN, INPUT);
  Serial.begin(9600);
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in 
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and 
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset 
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0. 
 * (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode(){

  // If button is pressed, cycle through modes
  if(digitalRead(BUTTON_MODE_PIN) == HIGH) {
    // If mode is 4, restart from 0
    if(mode >= 4) {
      mode = 0;
    }
    // Otherwise advance mode by one
    else {
      mode++;
      // Reset counter for playback with each mode change since
      // it is used by both play and loop modes
      notesPlayed = 0;
    }
    // 500ms delay to prevent rapid cycling
    delay(500);
    Serial.println(mode);
  }
  
}

/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{
  switch(mode) {
    case 0:
      //RGB LED is off
      analogWrite(LED_PIN_R, 0);
      analogWrite(LED_PIN_G, 0);
      analogWrite(LED_PIN_B, 0);
      break;
    case 1:
      //RGB LED is blue
      analogWrite(LED_PIN_R, 0);
      analogWrite(LED_PIN_G, 0);
      analogWrite(LED_PIN_B, 255);
      break;
    case 2:
      //RBG LED is red
      analogWrite(LED_PIN_R, 255);
      analogWrite(LED_PIN_G, 0);
      analogWrite(LED_PIN_B, 0);
      break;
    case 3:
      //RGB LED is green
      analogWrite(LED_PIN_R, 0);
      analogWrite(LED_PIN_G, 255);
      analogWrite(LED_PIN_B, 0);
      break;
    case 4:
      //RGB LED is purple
      analogWrite(LED_PIN_R, 125);
      analogWrite(LED_PIN_G, 0);
      analogWrite(LED_PIN_B, 255);
      break;
    default:
      break;
  }
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes 
 * to the user pressing the respective buttons. 
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded, 
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if(mode ==0) { 
    reset();
  }
  else if(mode ==1) {
    live();
  }
  else if(mode ==2) {
    record();
  }
  else if(mode ==3) {
    play();
  }
   else if(mode ==4) {
    loopMode();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  // Clear the array once and if there are no
  // notes to clear, don't run the loop again
  if (countNotes > 0) {
    // Clear the array 
    for (int i = 0; i < MAX_NOTES-1; i++) {
      notes[i] = 0;
    }
    // Reset note count to 0
    countNotes = 0;
    saveTone = false;
    shuffled = false;
  }
}
/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{ 
  // Serial.println("live");
  tone(BUZZER_PIN, analogRead(NOTE_IN_PIN), duration);
  // Serial.println(analogRead(NOTE_IN_PIN));
}
/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{
  // Play each note
  tone(BUZZER_PIN, analogRead(NOTE_IN_PIN), duration);
  
  // If the array hasn't been filled, record note 
  if(countNotes < MAX_NOTES-1) {
    // Check if a note is being played and add it to the array once
    if(analogRead(NOTE_IN_PIN) > 0 && saveTone == false) {
      notes[countNotes] = analogRead(NOTE_IN_PIN);
      saveTone = true;
    } 
    // Once the note is over, 
    else if (analogRead(NOTE_IN_PIN) == 0 && saveTone == true) {
      saveTone = false;
      // Serial.println(notes[countNotes]);
      countNotes++;
    }
  
  }
  
}
/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
  // Using an if/else statement makes it easier to switch modes than a for loop, 
  // but I needed to add another global variable to count through the array 
        
  // Check each index in the array for a note
  if (notesPlayed < MAX_NOTES-1) {
    // If a note is found, play it back
    if(notes[notesPlayed] > 0) {
      tone(BUZZER_PIN, notes[notesPlayed], duration);
      // Short delay so notes don't overlap
      delay(duration * 2);
    }
    // Continue moving through array
     notesPlayed++;
  }
  // If counter reaches the end of the array
  // reset to loop back through array from beginning
  else if (notesPlayed >= MAX_NOTES-1) {
    notesPlayed = 0;
  }
}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void loopMode()
{
  // Shuffle array of notes once when function is first called
  // to generate a random sequence
  if (shuffled == false) {
    for (int i = 0; i < MAX_NOTES-1; i++) {
      int r = random(MAX_NOTES);
      int temp = notes[r];
      notes[r] = notes[i];
      notes[i] = temp;
    }
    
    // Update control so loop isn't called again
    shuffled = true;
  }
  
  // Check each index in the shuffled array for a note
  if (notesPlayed < MAX_NOTES-1) {
    // If a note is found, play it back
    if(notes[notesPlayed] > 0) {
      tone(BUZZER_PIN, notes[notesPlayed], duration);
      // Short delay so notes don't overlap
      delay(duration * 2);
    }
    // Continue advancing through array
     notesPlayed++;
  }
  // If counter reaches the end of the array
  // reset to loop back through array from beginning
  else if (notesPlayed >= MAX_NOTES-1) {
    notesPlayed = 0;
  }

}

/**********************ANALYSIS *******************************
  RESISTOR LADDER:
    Higher resistance reduces the current, producing a lower sound frequency.
    On the other hand, lower resistance results in more current and a higher sound frequency
    (explained further below).
    
    As each button is pressed, it opens the circuit at that point allowing current to flow
    through the resistor ladder to the analog input (A0 pin) of the Arduino.

    Since the resistors are in series, their total resistance is additive.
    
    Pressing a button that opens the circuit at the top of the resistor ladder 
    causes current to flow through all of the resistors in the ladder, resulting 
    in a higher total resistance and therefore a lower sound frequency.
    
    Each subsequent button opens the circuit at a different point, skipping another resistor
    in the ladder. Therefore as you move down the row of buttons the total resistance decreases 
    and the frequency of the sound ouput increases.
  
  MODE SELECTOR:
    The mode button is connected to digital pin 2 of the Arduino. When it's at rest the 
    connection between the legs is broken, breaking the circuit. Calling digitalRead() 
    on the pin returns a value of LOW (off / 0V). When the button is pressed, a connection 
    is made, closing the circuit and allowing current to flow. Calling digitalRead() on the 
    pin while th button is pressed will return a value of HIGH (on / 5V).

    Whether the button pin reads HIGH or LOW is used as a control to switch modes and send a 
    signal to the respective cathode leads of the common anode RGB LED.  Each lead controls a 
    different colour and receives a PWM signal, controled by a value between 0 and 255.

    PWM (Pulse Width Modulation) is a way to control an analog device through digital means. 
    The signal sends voltage rapidly varying between high and low to the LED. The duty cycle 
    (or percentage of time spent high vs low, on vs off) controls the brightness of the LED, 
    which is actually flickering on and off with the changes in voltage. However, due to the 
    high frequency of the signal, this flickering is imperceptible and it merely appears to be 
    dimmer or brighter. 

    Between the range of 0 to 255, lower numbers result in more time spent off 
    (resulting in a dimmer appearance) and higher numbers mean more time spent on 
    (giving a brighter appearance). 

    Since each colour within the LED is controled by a separate pin, we can send voltage to the 
    appropriate colours or combination of colours.
  
  VOLTAGE AND SOUND OUTPUT:
    When the buttons are pressed, current moves through the resistor ladder to the
    analog input (A0 pin) of the Arduino. The received voltage is read and converted into
    a discrete number between 0 and 1023 (analog to digital conversion). Each increment is equivalent
    to around 4.9mV, so lower voltage results in a lower number, higher voltage in a higher number.
    
    Those numbers are passed through the tone() function as a square wave with the specified
    frequency. For example, if the voltage input to the A0 pin is read as 600, the tone() function
    will generate a digital square wave of 600 hz. This then needs to be output to the 
    piezo buzzer (an analog device). A square wave translates into alternating high and low voltage.
    A waveform with a freqency of 600hz has 600 cycles per second (it goes high and low, 600
    times per second). The material inside the piezo buzzer grows and shrinks in response to
    these changes in voltage. This creates a pressure wave which is perceived as sound.
    
    It's important to note that the tone() function in Arduino is different than standard PWM. 
    With PWM, you can modulate the duty cycle (the amount of time spent at high vs low
    voltage), but the waveform maintains a consistent frequency, resulting in a consistent tone.
    
    The tone() function automatically uses a 50% duty cycle (equal time spent high and low), 
    but we are able to modulate the frequency of the signal, resulting in different tones. 
    
  
  
**************************************************************************/
