#include <MyWiFi.hh>
#include <Decode.hh>
#include <MyLaser.hh>
#include <MyServo.hh>
#include <MyProgramController.hh>



MyServo servoA;
MyServo servoB;
static const int servoPinA = 12;
static const int servoPinB = 14;


static const int laserPin = 32;
Laser laser;

MyWiFi mywifi;



    // ServoA 90° in 220ms;
    // ServoB 170° in 400ms;

    // => 90° / 250ms = 3,6° / 10ms = 0,36°/ms 

static const bool SERIAL_PRINTLN = false;
bool firstClientConnected = false;



// Client variables 
char linebuf[80];
int charcount=0;


void setupServos(){
  servoA.setup(
        servoPinA, 
        0.0,
        "Servo A",
        0,
        90,
        544, //853,
        1550 //1859
    );

  servoB.setup(
        servoPinB,
        0.0,
        "Servo B",
        -85,
        85
    );
    
}

void setupLaser(){
  laser.setup(laserPin);
  laser.onWithDelay();
  laser.offWithDelay();
}

void randomWait(){
  Serial.println("begin randomWait");
  long waitTimeInSeconds = random(30,150);
  for (long i=0; i < (waitTimeInSeconds*10); i++){
    if(mywifi.client){
      if (mywifi.client.connected()){
        //Serial.println("client connnected");
        if (mywifi.client.available()){
          //Serial.println("client available");
          break;
        }
      }
    }else{
      //Serial.println("check for client available");
      mywifi.client = mywifi.server.available();
    }
    delay(100); // 0.1 seconds
  }
  Serial.println("end randomWait");
}





void setup() 
{
  Serial.begin(115200);
  while(!Serial) {
  }
  //initial Serial Lines get dropped
  Serial.println("");
  Serial.println("");
  
  mywifi.setup();
  setupServos();
  setupLaser();

  
  delay(5000);
  servoA.initMove();
  servoB.initMove();
  //program(255);
  
  

  
}
 
void loop() 
{
  static floatResult orderForServoA,orderForServoB;
  static intResult orderForProgram;
  static boolResult orderForLaser, orderForLoop;
  static int programNumber = 0;
  static bool loopActive = false;
  static MyProgramController progCont(servoA, servoB, laser);
  // int64_t now = esp_timer_get_time();
  
  // listen for incoming clients

  
  if (mywifi.client) 
  {
    firstClientConnected = true;
    Serial.println("New client");
    memset(linebuf,0,sizeof(linebuf));
    charcount=0;
 
    while (mywifi.client.connected()) 
    {
      //Serial.write("connected loop");
      
      if (mywifi.client.available()) 
      {
        //Serial.write("available loop");
        
        char c = mywifi.client.read();
        
        if (charcount<sizeof(linebuf)-1){
          linebuf[charcount]=c;
          charcount++;
        } 
        
        if (c == '\n' && charcount > 5) 
        {
          if (SERIAL_PRINTLN) {
            Serial.write(linebuf,charcount);
          }

          
          if (orderForLoop.evaluate(linebuf, "loop="))
          {
            loopActive = orderForLoop.value;            
          }
                    
          if (orderForProgram.evaluate(linebuf, "prog="))
          {
            programNumber = orderForProgram.value;
            progCont.program(programNumber);
            if (programNumber == MyProgramController::RANDOM_PROG_NUMBER){
              randomWait();
            }
          }else{
            if (orderForServoA.evaluate(linebuf, "posA=")){
              servoA.moveAbs(orderForServoA.value);
            } 
            if (orderForServoB.evaluate(linebuf, "posB=")){
              servoB.moveAbs(orderForServoB.value);
            }
            if (orderForLaser.evaluate(linebuf, "Laser=")){
              laser.setState(orderForLaser.value);
            }
          }
          
          // you're starting a new line
          memset(linebuf,0,sizeof(linebuf));
          charcount=0;
        }
      }
      else{
        if (loopActive){
          progCont.program(programNumber);
          if (programNumber == MyProgramController::RANDOM_PROG_NUMBER){
            randomWait();
          }
        }
      }
      delay(1);
    }
 
    // close the connection:
    mywifi.client.stop();
    Serial.println("client disconnected");
  }else{
    mywifi.keepAlive();
    mywifi.client = mywifi.server.available();
    if (!mywifi.client && !firstClientConnected && (esp_timer_get_time() > 120000000LL)){
      progCont.randProgram();
      randomWait();
    }
    delay(1);
  }
}

