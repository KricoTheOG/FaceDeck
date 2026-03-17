#include <BleKeyboard.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_SSD1306 display(128,64,&Wire,-1);
BleKeyboard bleKeyboard("FaceDeck","ESP32",100);


// ---------- KEYS ----------

int pins[12]={4,5,13,12,14,27,26,25,33,32,16,17};
bool lastState[12];


// ---------- POPUP ----------

bool showPopup=false;
unsigned long popupTimer=0;
String popupText="";


// ---------- FACE ----------

enum Emotion
{
  IDLE,
  HAPPY,
  LOOK,
  SLEEP
};

Emotion emo=IDLE;

unsigned long tMood=0;
unsigned long tAnim=0;
unsigned long tBlink=0;

float frame=0;
float eyeX=0;
float eyeTX=0;

bool blink=false;



// ---------- SEND ACTION ----------

void sendAction(int i)
{
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_ALT);

  switch(i)
  {
    case 0: bleKeyboard.press('1'); popupText="Dolphin"; break;
    case 1: bleKeyboard.press('2'); popupText="VSCode"; break;
    case 2: bleKeyboard.press('3'); popupText="Settings"; break;
    case 3: bleKeyboard.press('4'); popupText="TLauncher"; break;
    case 4: bleKeyboard.press('5'); popupText="Steam"; break;
    case 5: bleKeyboard.press('6'); popupText="Lutris"; break;
    case 6: bleKeyboard.press('7'); popupText="Arduino"; break;
    case 7: bleKeyboard.press('8'); popupText="OBS"; break;
    case 8: bleKeyboard.press('9'); popupText="Vivaldi"; break;
    case 9: bleKeyboard.press('t'); popupText="Konsole"; break;
  }

  bleKeyboard.releaseAll();

  showPopup=true;
  popupTimer=millis();

  emo=HAPPY;
  tMood=millis();
}



// ---------- INPUT ----------

void updateKeys()
{
  if(!bleKeyboard.isConnected()) return;

  for(int i=0;i<12;i++)
  {
    bool s=digitalRead(pins[i]);

    if(s==LOW && lastState[i]==HIGH)
    {
      if(i<10)
      {
        sendAction(i);
      }
    }

    lastState[i]=s;
  }
}



// ---------- EMOTION ----------

void updateEmotion()
{
  if(millis()-tMood>2000)
    emo=IDLE;

  if(emo==IDLE && random(0,2000)==0)
  {
    emo=SLEEP;
    tMood=millis();
  }
}



// ---------- BLINK ----------

void updateBlink()
{
  if(millis()-tBlink>3000)
  {
    blink=true;
    tBlink=millis();
  }

  if(blink && millis()-tBlink>120)
  {
    blink=false;
    tBlink=millis();
  }
}



// ---------- ANIMATION ----------

void updateAnimation()
{
  if(millis()-tAnim<16) return;

  tAnim=millis();

  frame++;

  eyeX+=(eyeTX-eyeX)*0.1;

  if(random(0,40)==0)
    eyeTX=random(-5,5);
}



// ---------- FACE ----------

void drawFace()
{
  int y=28+sin(frame*0.05)*2;

  int ex1=44+eyeX;
  int ex2=84+eyeX;

  display.drawLine(34,y-12,48,y-9,WHITE);
  display.drawLine(80,y-9,94,y-12,WHITE);

  if(blink || emo==SLEEP)
  {
    display.drawLine(ex1-7,y,ex1+7,y,WHITE);
    display.drawLine(ex2-7,y,ex2+7,y,WHITE);
  }
  else
  {
    display.fillCircle(ex1,y,7,WHITE);
    display.fillCircle(ex2,y,7,WHITE);
  }

  int mx=64;
  int my=48;

  if(emo==HAPPY)
    display.drawLine(mx-10,my,mx+10,my+4,WHITE);
  else
    display.drawLine(mx-8,my,mx+8,my,WHITE);
}



// ---------- POPUP ----------

void drawPopup()
{
  display.clearDisplay();

  display.drawRect(0,0,128,64,WHITE);

  display.setTextColor(WHITE);
  display.setTextSize(2);

  int x = (128 - popupText.length()*12)/2;

  display.setCursor(x,25);
  display.print(popupText);

  display.display();
}



// ---------- UI ----------

void drawUI()
{
  if(showPopup)
  {
    drawPopup();

    if(millis()-popupTimer>5000)
      showPopup=false;

    return;
  }

  display.clearDisplay();

  display.drawRect(0,0,128,64,WHITE);

  drawFace();

  display.display();
}



// ---------- SETUP ----------

void setup()
{
  Wire.begin(SDA_PIN,SCL_PIN);

  display.begin(SSD1306_SWITCHCAPVCC,0x3C);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.display();

  bleKeyboard.begin();

  for(int i=0;i<12;i++)
  {
    pinMode(pins[i],INPUT_PULLUP);
    lastState[i]=HIGH;
  }

  randomSeed(millis());
}



// ---------- LOOP ----------

void loop()
{
  updateKeys();
  updateEmotion();
  updateBlink();
  updateAnimation();
  drawUI();
}
