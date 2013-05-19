#include <Adafruit_GFX.h>
#include <Adafruit_HX8340B.h>


#define TFT_MOSI  11		// SDI
#define TFT_CLK   13		// SCL
#define TFT_CS    10		// CS
#define TFT_RESET  9		// RESET

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#include <SPI.h>

Adafruit_HX8340B display(TFT_RESET, TFT_CS);

float p = 3.1415926;
volatile int iCTR=0;
int Analog0Val=0; // Oil
int Analog1Val=0;  // Vac
//int hztest=0;
//int hzpin=7;
int paTach[10]={0,0,0,0,0,0,0,0,0,0};  // TachArray
int iTach=0;
float fDisplay=0;
int iVal=0;
int iTic=0;

void setup(void) {
  
  // Existing Stuff for some serial port?
  Serial.begin(9600);
  Serial.print("hello!");
  display.begin();

  Serial.println("init");
  uint16_t time = millis();
  display.fillScreen(BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  

  display.setRotation(3);
  display.fillScreen(BLACK);
  display.setTextSize(2);



  // Draw labels
  display.setTextSize(2);
  display.setCursor(1,1);
  display.print("Tach ");
  display.setCursor(5,20);
  display.setTextSize(1);
  display.print("RPM");
  display.setCursor(1,44);

  display.setTextSize(2);
  display.print("Oil ");
  display.setCursor(5,64);
  display.setTextSize(1);
  display.print("PSI");
  display.setCursor(1,88);

  display.setTextSize(2);
  display.print("Vacuum ");
  display.setCursor(5,108);
  display.setTextSize(1);
  display.print("InHg");


//  pinMode(hzpin, OUTPUT);
//    display.drawFastHLine(0,0,219,YELLOW);

    display.drawFastHLine(0,150,219,CYAN);
//    for (iTic=0; iTic<200;iTic++) {
//      display.drawFastVLine(5+iTic*10,150,10,CYAN);
//    }

    //display.print(fDisplay);    
    for (iTic=0; iTic<16;iTic++) {
      fDisplay =  220*((iTic+1)*250/4000.0);
      display.drawFastVLine(fDisplay,150,5,CYAN);
    }
    for (iTic=0; iTic<8;iTic++) {
      fDisplay =  220*((iTic+1)*500/4000.0);
      display.drawFastVLine(fDisplay,150,10,CYAN);
    }
    display.setTextSize(1);
    for (iTic=0; iTic<3;iTic++) {
      fDisplay =  220*((iTic+1)*1000/4000.0);
      display.drawFastVLine(fDisplay,145,20,CYAN);
      display.setCursor(fDisplay-4,140);
      display.print(iTic+1);
      display.print("K");
    }


//    display.drawFastHLine(0,175,219,BLUE);
  display.setTextSize(3);

}


void myIsr() {
  iCTR++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {


  display.setTextColor(WHITE);


  // Tachometer
  iCTR=0;
  attachInterrupt(0,myIsr,RISING);
  delay(250);
  detachInterrupt(0);
  myDrawLines3(0);
  display.setCursor(100,1);
  iVal=iCTR*60;
  display.print(iVal);

  display.setCursor(10,120);
  fDisplay =  220*(iVal/4000.0);
  //display.print(fDisplay);    
  if (iTach==4) {
    iTach=0;
  }
//  display.drawFastVLine(paTach[iTach],165,10,BLACK);
  display.fillRect(paTach[iTach], 165, 3, 10, BLACK);
  
  paTach[iTach]=fDisplay;
  display.fillRect(paTach[iTach], 165, 3, 10, WHITE);
//  display.drawFastVLine(paTach[iTach],165,10,MAGENTA);
  iTach++;











 

  // Analog Adds
  // OIL Pressure?
  Analog0Val=analogRead(A0);
  myDrawLines3(44);
  display.setCursor(100,44);
//  display.print(Analog0Val);    


  if (Analog0Val<31) {
    display.setTextColor(RED);
    display.print("0");    
  }else if (Analog0Val<31) {
    display.print("10");    
  }else if (Analog0Val<41) {
    display.print("15");    

  }else if (Analog0Val<61) {
    display.print("20");    

  }else if (Analog0Val<76) {
    display.print("25");    

  }else if (Analog0Val<86) {
    display.print("30");    

  }else if (Analog0Val<96) {
    display.print("35");    

  }else if (Analog0Val<118) {
    display.print("40");    

  }else if (Analog0Val<122) {
    display.print("45");    

  }else if (Analog0Val<132) {
    display.print("50");    

  }else if (Analog0Val<140) {
    display.print("55");    

  }else if (Analog0Val<146) {
    display.print("60");    
  

  }else if (Analog0Val<154) {
    display.print("70");    

  }else if (Analog0Val<160) {
    display.print("75");    

  }else if (Analog0Val<166) {
    display.print("80");    

  }else if (Analog0Val<172) {
    display.print("85");    

  }else if (Analog0Val<300) {
    display.setTextColor(RED);    
    display.print("85+");    
  }














  
  // Vacuum Guage
  Analog1Val=analogRead(A1);
  Analog1Val=Analog1Val>>1;
  myDrawLines3(88);
  display.setCursor(100,88);
//  display.print(Analog1Val);
//  return;
  
  
  if (Analog1Val>497) {
    display.setTextColor(RED);
    display.print("0");    
  }else if (Analog1Val>486) {
    display.setTextColor(RED);
    display.print("1");
  }else if (Analog1Val>481) {
    display.setTextColor(RED);
    display.print("2");
  }else if (Analog1Val>467) {
    display.setTextColor(RED);
    display.print("3");
  }else if (Analog1Val>451) {
    display.setTextColor(RED);
    display.print("4");
  }else if (Analog1Val>436) {
    display.setTextColor(RED);
    display.print("5");
  }else if (Analog1Val>425) {
    display.setTextColor(RED);
    display.print("6");
  }else if (Analog1Val>411) {
    display.setTextColor(RED);
    display.print("7");
  }else if (Analog1Val>395) {
    display.setTextColor(RED);
    display.print("8");
  }else if (Analog1Val>381) {
    display.setTextColor(RED);
    display.print("9");
  }else if (Analog1Val>367) {
    display.setTextColor(RED);
    display.print("10");
    
  }else if (Analog1Val>353) {
    display.setTextColor(YELLOW);
    display.print("11");
  }else if (Analog1Val>340) {
    display.setTextColor(YELLOW);
    display.print("12");
  }else if (Analog1Val>325) {
    display.setTextColor(YELLOW);
    display.print("13");
  }else if (Analog1Val>312) {
    display.setTextColor(YELLOW);
    display.print("14");
  }else if (Analog1Val>298) {
    display.setTextColor(YELLOW);
    display.print("15");


  }else if (Analog1Val>284) {
    display.setTextColor(GREEN);
    display.print("16");
  }else if (Analog1Val>269) {
    display.setTextColor(GREEN);
    display.print("17");
  }else if (Analog1Val>255) {
    display.setTextColor(GREEN);
    display.print("18");
  }else if (Analog1Val>244) {
    display.setTextColor(GREEN);
    display.print("19");
  }else if (Analog1Val>227) {
    display.setTextColor(GREEN);
    display.print("20");
  }else if (Analog1Val>213) {
    display.setTextColor(GREEN);
    display.print("21");
  }else if (Analog1Val>203) {
    display.setTextColor(GREEN);
    display.print("22");
  }else if (Analog1Val>188) {
    display.setTextColor(GREEN);
    display.print("23");
  }else if (Analog1Val>176) {
    display.setTextColor(GREEN);
    display.print("24");
  }else if (Analog1Val>159) {
    display.setTextColor(GREEN);
    display.print("25");
  }else if (Analog1Val<154) {
    display.setTextColor(GREEN);
    display.print("25+");




  }else {
    display.print("WTF");
  }  
 
}






///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 176x220
void myDrawLines3(int position) { // Vertical
  int numLines = 22;
  int i=0;
  int spacing=1;
  int start = position;  
  
  for (i=0;i<numLines;i++) {
    display.drawFastHLine(100,start+i*spacing,75,BLACK);
  }
}



void myDrawLines2(int position) { // Vertical
  int numLines = 22;
  int i=0;
  int spacing=1;
  int start = position;  
  
  for (i=0;i<numLines;i++) {
    display.drawFastHLine(0,start+i*spacing,200,BLACK);
  }
}



void myDrawLines() {
  int numLines = 5;
  int i=0;
  int spacing=10;
  int start = 0;  
  
  for (i=0;i<numLines;i++) {
    display.drawFastHLine(0,i*spacing,100,MAGENTA);
  }

  numLines = 5;
  i=0;
  spacing=10;
  start = 50;  
  for (i=0;i<numLines;i++) {
    display.drawFastHLine(0,start + i*spacing,100,YELLOW);
  }
  
  numLines = 5;
  i=0;
  spacing=10;
  start = 100;  
  for (i=0;i<numLines;i++) {
    display.drawFastHLine(0,start + i*spacing,100,GREEN);
  }

  numLines = 5;
  i=0;
  spacing=10;
  start = 150;  
  for (i=0;i<numLines;i++) {
    display.drawFastHLine(0,start + i*spacing,100,BLUE);
  }

}


void myPrintTime() {

//  fiilRect(x,y,w,h,color);
  display.fillRect(0,0,2,2,MAGENTA);
//  display.drawFastVLine(x,y,h,color);
  display.drawFastHLine(0,12,100,MAGENTA);
  display.drawFastHLine(0,13,100,BLACK);
  display.drawFastHLine(0,14,100,BLACK);
  display.drawFastHLine(0,15,100,BLACK);
  display.drawFastHLine(0,16,100,BLACK);
  display.drawFastHLine(0,17,100,BLACK);
  display.drawFastHLine(0,18,100,BLACK);
  display.drawFastHLine(0,19,100,BLACK);
  display.drawFastHLine(0,20,100,MAGENTA);

  display.setCursor(0, 5);

  display.setTextColor(WHITE);
  display.println("Sketch has been running for: ");
  display.setTextColor(MAGENTA);
  display.print(millis() / 1000);
  display.setTextColor(WHITE);
  display.print(" seconds.");
}


void tftPrintTest() {
  display.fillScreen(BLACK);
  display.setCursor(0, 5);
  display.setTextColor(RED);  
  display.setTextSize(1);
  display.println("Hello World!");
  display.setTextColor(YELLOW, GREEN);
  display.setTextSize(2);
  display.println("Hello World!");
  display.setTextColor(BLUE);
  display.setTextSize(3);
  display.println(1234.567);
  delay(1500);
  display.setCursor(0, 5);
  display.fillScreen(BLACK);
  display.setTextColor(WHITE);
  display.setTextSize(0);
  display.println("Hello World!");
  display.setTextSize(1);
  display.setTextColor(GREEN);
  display.print(p, 5);
  display.println(" Want pi?");
  display.print(8675309, HEX); // print 8,675,309 out in HEX!
  display.println(" Print HEX");
  display.setTextColor(WHITE);
  display.println("Sketch has been running for: ");
  display.setTextColor(MAGENTA);
  display.print(millis() / 1000);
  display.setTextColor(WHITE);
  display.print(" seconds.");
}

void foo() {
   
  if (Analog1Val>498) {
    display.print("0");
  }else if (Analog1Val<=453 && Analog1Val>445) {
    display.print("1");
  }else if (Analog1Val<=445 && Analog1Val>484) {
    display.print("2");
  }else if (Analog1Val<=433 && Analog1Val>423) {
    display.print("3");
  }else if (Analog1Val<=423 && Analog1Val>411) {
    display.print("4");
  }else if (Analog1Val<=411 && Analog1Val>397) {
    display.print("5");
  }else if (Analog1Val<=397 && Analog1Val>386) {
    display.print("6");
  }else if (Analog1Val<=386 && Analog1Val>372) {
    display.print("7");
  }else if (Analog1Val<=372 && Analog1Val>360) {
    display.print("8");
  }else if (Analog1Val<=360 && Analog1Val>344) {
    display.print("9");
  }else if (Analog1Val<=344 && Analog1Val>333) {
    display.print("10");
  }else if (Analog1Val<=333 && Analog1Val>318) {
    display.print("11");
  }else if (Analog1Val<=318 && Analog1Val>305) {
    display.print("12");
  }else if (Analog1Val<=305 && Analog1Val>291) {
    display.print("13");
  }else if (Analog1Val<=291 && Analog1Val>278) {
    display.print("14");
  }else if (Analog1Val<=278 && Analog1Val>263) {
    display.print("15");
  }else if (Analog1Val<=263 && Analog1Val>248) {
    display.print("16");
  }else if (Analog1Val<=248 && Analog1Val>235) {
    display.print("17");
  }else if (Analog1Val<=235 && Analog1Val>220) {
    display.print("18");
  }else if (Analog1Val<=220 && Analog1Val>207) {
    display.print("19");
  }else if (Analog1Val<=207 && Analog1Val>200) {
    display.print("20");
  }else {
    display.print(">20");
  }  
}
