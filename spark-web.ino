
//PUT YOUR GLOBAL VARIABLES HERE
    int myDoNormal = 0;   // 0 not yet set,  1 for normal operation, 2 or higher for other numbers for own code
    int mySetWrite = 0;   
    int myCount = 0;
    int pinNumber = 0;
    String  myActivity = "NONE";
    int myLoops = 0;


    
 // Any general setup stuff goes here   
void setup(){
    
    Particle.function("my-main", myMain); 
    Particle.subscribe("mytemp", myHandler, MY_DEVICES);   // for using the DO IFTTT button
    
    //PUT YOUR SETUP CODE HERE. Note: Only three more functions allowed!
    // test everything using the return int from a function!
      
  
    //RGB.control(true);
    //RGB.color(0, 255, 255);  //cyan
    RGB.brightness(1);    // 1=very low light, 255 = max


}





void loop(){
     
// use this area for anything that loops around and around



// here I am testing IFTTT publish

    delay(1);  // slow down the loop
    myLoops ++;
   
    if (myLoops >= 3000){   // wait 3 second betrween measurements actually about 5 seconds
       myLoops = 0;
        pinMode(D7, OUTPUT);
        digitalWrite(D7, 1);   // D7 On
        delay(20);
        
        pinMode(D7, OUTPUT);
        digitalWrite(D7, 0);   // D7 Off
        delay(20);
        
       if (analogRead(A0) >= 1000){
          Spark.publish("It is daytime", "1000", 60, PRIVATE);
       } 

       if (analogRead(A0) <= 30){
          Spark.publish("It is nighttime", "30", 60, PRIVATE);
       } 
    }
      
   

// This is more your own code


    if (myDoNormal == 2) {  // Now you can do your own code here X = 2
      if (myCount <  mySetWrite){
        myCount ++;
       
        pinMode(D7, OUTPUT);
        digitalWrite(D7, 1);   // D7 On
        delay(50);
        
        pinMode(D7, OUTPUT);
        digitalWrite(D7, 0);   // D7 Off
        delay(50);
      } else {
          myDoNormal = 0;
          myCount = 0;
          mySetWrite = 0;
          ;
      }
    }  


}




  void myHandler(const char *event, const char *data)    // for the DO or IF   IFTTT button
  {
        pinMode(D0, OUTPUT);
        digitalWrite(D0, 1);   // D7 On
        delay(2000);
        
        pinMode(D0, OUTPUT);
        digitalWrite(D0, 0);   // D7 Off
        delay(500);
        
        pinMode(D0, OUTPUT);
        digitalWrite(D0, 1);   // D7 On
        delay(2000);
        
        pinMode(D0, OUTPUT);
        digitalWrite(D0, 0);   // D7 Off
        delay(500);
  }





// Probably a good idea to leave this stuff alone

int myMain(String myCode) {
    
    myCode.toUpperCase();           // set argument to uppercase--remove for better security
    
    // used send instead of write since I needed it to be 4 characters long.
    

    // d7-send-1 or d7-send-high or d7-send-on    to turn on D7
    // d7-send-0   or d7-send-low  or d7-send-off to tuurn off D7
    // d5-read    read D5

    // a0-send-0     turn A0 off
    // a0-send-255   turn A0 maximum
    // a1-read       read A1
     
    // Block sets pinNumber for digital 0-7 or analog 10-17 from the number


    pinNumber = myCode.charAt(1) - '0';
    if (pinNumber< 0 || pinNumber >7) return -1; 
    
    if (myCode.startsWith("A")){     // set for analog normal operation
        pinNumber = pinNumber+10;   //+10 is for analog numbers
        myDoNormal = 1;
    }  
    
     if (myCode.startsWith("D")){   // set for digital normal operation
        myDoNormal = 1;
    }  
    
  
    myActivity = myCode.substring(3,7);     // take 4 characters starting at the 3rd.
     
    
    //Following sets the 7 and on characters to integers
    String myOptional = myCode.substring(8);      
    if(myOptional == "HIGH") {mySetWrite = 1;}
        else if(myOptional == "LOW") {mySetWrite = 0; }
            else if(myOptional == "ON") {mySetWrite = 1;}
                else if(myOptional == "OFF") {mySetWrite = 0; }
                   else {mySetWrite = myOptional.toInt();  }  // sets  write value
    
    
    // myCode parsing complete
    
    
    if ( myDoNormal == 1) {   // sets the pins sort of like Tinker 
    
    if (pinNumber < 9) {   // digital pins activated
   
        if (myActivity == "READ"){    //digital read
            pinMode(pinNumber, INPUT_PULLDOWN);
            return digitalRead(pinNumber);
        }
        
        if (myActivity == "SEND"){    //digital write
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            return mySetWrite;
        }        
        
        
    }  else {      // analog pins activated
    
        if (myActivity == "READ"){    //Analog read           // pinMode(pinNumber, INPUT_PULLUP); // sets unknown to max 4095 analog read
           // pinMode(pinNumber, INPUT); // sets to input
           // pinMode(pinNumber, INPUT_PULLDOWN); // sets unknown to 0 min analog read
           // trying nothing, since with the new version of tinker this works
            return analogRead(pinNumber);
        }
        
        if (myActivity == "SEND"){    //Analog Write
            pinMode(pinNumber, OUTPUT);
            analogWrite(pinNumber,  mySetWrite);
            return mySetWrite;
        }        
      }
      
    } // end myDoNormal loop  
    
    
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
    
 
  // Now put your stuff here.
   
    if (myCode.startsWith("X")){   // set for your own codes. 
        myDoNormal = 2;           // communicates with the main loop
       
    }  
   
   
   
   
    if ( myDoNormal == 2) {  // example of your own code.
                             // myDoNormal communicates with the loop procedure
    
   
       if (myCode.startsWith("X1-MINE")){   // notice all capital letters
                                            // you may still use mySetWrite and myActivity
                                            // you have to look at the code to use pinNumber
             myCount = 0;
             return mySetWrite;
        
       }
       
       
       
       
       
      // write your own code here  see the above example
       
       
       
       
       
       
       
       
  
    } // end of if statement myDoNormal
    
    
} // end of funciton myMain

