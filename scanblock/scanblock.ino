int Pin0 = 52;//definition digital 8 pins as pin to control the IN1 (ULN24L01)
int Pin1 = 53;//definition digital 9 pins as pin to control the IN2 (ULN24L01)
int Pin2 = 51;//definition digital 10 pins as pin to control the IN3 (ULN24L01)
int Pin3 = 49;//definition digital 11 pins as pin to control the IN4 (ULN24L01)
int Irhpin=A12;
int Pn0 = 41;//definition digital 8 pins as pin to control the IN1 (ULN24L01)
int Pn1 = 43;//definition digital 9 pins as pin to control the IN2 (ULN24L01)
int Pn2 = 45;//definition digital 10 pins as pin to control the IN3 (ULN24L01)
int Pn3 = 47;//definition digital 11 pins as pin to control the IN4 (ULN24L01)
int Irvpin=A13;
int _speed = 1;
int thres=500;
int thres2=300 ;
int j=0;
int i;
int k=0;
int t=-1;
int m=0;

struct blocks
{
  int pos;
  long vol;
  };
  struct blocks B[4];
void setup()
{
 pinMode(Pin0, OUTPUT);//Set digital 8 port mode, the OUTPUT for the output
 pinMode(Pin1, OUTPUT);//Set digital 9 port mode, the OUTPUT for the output
 pinMode(Pin2, OUTPUT);//Set digital 10 port mode, the OUTPUT for the output
 pinMode(Pin3, OUTPUT);//Set digital 11 port mode, the OUTPUT for the output
 pinMode(Pn0,OUTPUT);
 pinMode(Pn1,OUTPUT);
 pinMode(Pn2,OUTPUT);
 pinMode(Pn3,OUTPUT);
 pinMode(Irhpin,INPUT);
 pinMode(Irvpin,INPUT);
 Serial.begin(9600);
}

void loop()
{
  if(analogRead(Irvpin)>thres)
  {
  scanblock();
  delay(1000);//delay 2S
  }
  else if(t==2)
  led_blink_order();
}
void led_blink_order()
     {
      for(i=0;i<4;i++)
      {
        int f=B[i].pos;
        for(int h=0;h<f;h++)
        {
          digitalWrite(13,HIGH);
          delay(300);
          digitalWrite(13,LOW);
          delay(300);
          }
          delay(1500);
        
        }
      }

     void scanblock()
     {
      if(analogRead(Irvpin)>thres)
      {
      Stepv(700);//Stepper motor forward 512 steps ---- 360 angle    
      delay(200);// delay 2S
      Step(700);
      delay(200);
      Step(-700);
       delay(200);  
       Stepv(-m);//Stepper motor backward 512 steps ---- 360 angle    
       delay(2000);//delay 2S
       led_blink(t+2);
       t++;
       B[t].pos=t+1;
       Serial.println(t+1);
       Serial.println(j*k);
       Serial.println(" ");
       B[t].vol=j*k;
       j=0;
       k=0;
       //pid_goleft();
       }

      }

      void sortvol()
      {
        struct blocks temp;
        for(i=0;i<3;i++)
        {
          for(int l=0;l<3-1;l++)
          {
            if(B[l].vol<B[l+1].vol)
            {
              temp=B[l];
              B[l]=B[l+1];
              B[l+1]=temp;
              }
          }
          }
        }

     void led_blink(int n)
     {
      for(i=0;i<n;i++)
      {
        digitalWrite(13,HIGH);
        delay(300);
        digitalWrite(13,LOW);
        delay(300);
      }
      }
     
void Stepv(int _step)//Stepper motor rotation
{
  if(_step>=0){  // Stepper motor forward
    for(int i=0;i<_step;i++){   
     setStepv(0, 0, 0, 1);
      delay(_speed);
      setStepv(0, 0, 1, 1);
      delay(_speed);
      setStepv(0, 0, 1, 0);
      delay(_speed);
      setStepv(0, 1, 1, 0);
      delay(_speed);
      setStepv(0, 1, 0, 0);
      delay(_speed);
      setStepv(1, 1, 0, 0);
      delay(_speed);
      setStepv(1, 0, 0, 0);
      delay(_speed);
      setStepv(1, 0, 0, 1);
      delay(_speed);
       int frnt=analogRead(Irvpin);
      Serial.println(frnt);
      m++;
      if(frnt>thres)
      {
        k++;
      }
      else if(m-k>150)
      break;
    }
  }else{ // Stepper motor backward
     for(int i=_step;i<0;i++){  
      setStepv(1, 0, 0, 1);
      delay(_speed); 
      setStepv(1, 0, 0, 0);
      delay(_speed);
      setStepv(1, 1, 0, 0);
      delay(_speed);
      setStepv(0, 1, 0, 0);
      delay(_speed);
      setStepv(0, 1, 1, 0);
      delay(_speed);
      setStepv(0, 0, 1, 0);
      delay(_speed);
      setStepv(0, 0, 1, 1);
      delay(_speed); 
      setStepv(0, 0, 0, 1);
      delay(_speed);
      
    }
   }
}

void Step(int _step)//Stepper motor rotation
{
  if(_step>=0){  // Stepper motor forward
    for(int i=0;i<_step;i++){   
     setStep(0, 0, 0, 1);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 1);
      delay(_speed);
       int a=analogRead(Irhpin);
      Serial.println(a);
      if(a>thres2)
      {
        j++;
      }
    }
  }else{ // Stepper motor backward
     for(int i=_step;i<0;i++){  
      setStep(1, 0, 0, 1);
      delay(_speed); 
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed); 
      setStep(0, 0, 0, 1);
      delay(_speed);
      
    }
   }
}
void setStep(int a, int b, int c, int d)  
{  
    digitalWrite(Pin0, a);     
    digitalWrite(Pin1, b);     
    digitalWrite(Pin2, c);     
    digitalWrite(Pin3, d);     
}

void setStepv(int a, int b, int c, int d)  
{  
    digitalWrite(Pn0, a);     
    digitalWrite(Pn1, b);     
    digitalWrite(Pn2, c);     
    digitalWrite(Pn3, d);     
}
/*
void Stepv(int _step)//Stepper motor rotation
{
  if(_step>=0){  // Stepper motor forward
    for(int i=0;i<_step;i++){   
     setStepv(0, 0, 0, 1);
      delay(_speed);
      setStepv(0, 0, 1, 1);
      delay(_speed);
      setStepv(0, 0, 1, 0);
      delay(_speed);
      setStepv(0, 1, 1, 0);
      delay(_speed);
      setStepv(0, 1, 0, 0);
      delay(_speed);
      setStepv(1, 1, 0, 0);
      delay(_speed);
      setStepv(1, 0, 0, 0);
      delay(_speed);
      setStepv(1, 0, 0, 1);
      delay(_speed);
       int a=analogRead(Irhpin);
      Serial.println(a);
      if(a>200)
      {
        j++;
      }
    }
  }else{ // Stepper motor backward
     for(int i=_step;i<0;i++){  
      setStepv(1, 0, 0, 1);
      delay(_speed); 
      setStepv(1, 0, 0, 0);
      delay(_speed);
      setStepv(1, 1, 0, 0);
      delay(_speed);
      setStepv(0, 1, 0, 0);
      delay(_speed);
      setStepv(0, 1, 1, 0);
      delay(_speed);
      setStepv(0, 0, 1, 0);
      delay(_speed);
      setStepv(0, 0, 1, 1);
      delay(_speed); 
      setStepv(0, 0, 0, 1);
      delay(_speed);
      
    }
   }
}

void Step(int _step)//Stepper motor rotation
{
  if(_step>=0){  // Stepper motor forward
    for(int i=0;i<_step;i++){   
     setStep(0, 0, 0, 1);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 1);
      delay(_speed);
       int a=analogRead(Irhpin);
      Serial.println(a);
      if(a>200)
      {
        j++;
      }
    }
  }else{ // Stepper motor backward
     for(int i=_step;i<0;i++){  
      setStep(1, 0, 0, 1);
      delay(_speed); 
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed); 
      setStep(0, 0, 0, 1);
      delay(_speed);
      
    }
   }
}
void setStep(int a, int b, int c, int d)  
{  
    digitalWrite(Pin0, a);     
    digitalWrite(Pin1, b);     
    digitalWrite(Pin2, c);     
    digitalWrite(Pin3, d);     
}

void setStepv(int a, int b, int c, int d)  
{  
    digitalWrite(Pn0, a);     
    digitalWrite(Pn1, b);     
    digitalWrite(Pn2, c);     
    digitalWrite(Pn3, d);     
}
*/
