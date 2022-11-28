#define OUT_X1 PORTK
#define OUT_X2 PORTF
byte cnt=0;
float X01,X11,X02,X22,X03,X33,X04,X44,a,c;
byte Xb1,Xb2,Xb3;
//---------------------------
unsigned long t_ant = 0;
unsigned long t_delay = 0;  

//Lorez condiciones Iniciales
float p = 10.0;
float b = 8/3;
float r = 28;
float ts = 0.00438;
bool Florenz,FRossler,Fchen=false;
//float ts = 0.001376;
//condiciones iniciales
float x1 = .1;
float y1 = -10;
float z1 = .1;
float x, y, z;
unsigned int cx;
unsigned int cy;
unsigned int cz;

//---------------------------
void setup() {
  // Dsiponibles port PORTC,PORTA,PORTK,PORTB
  //DDRD = 0x00; // All pins in PORTD are inputs
  DDRD = 0xFF; // All pins in PORTD are outputs
  DDRK = 0xFF; // All pins in PORTD are outputs
  DDRF = 0xFF; // All pins in PORTD are outputs
  DDRL = 0xFF; // All pins in PORTD are outputs
  Serial.begin(115200);
  // create seed
  X01=10.0;
  X02=9.0;
  X03=0.0;
  X04=0.0;
 // a=0.1;
 // b=1.2;
 Florenz=false;
 FRossler=false;
 Fchen=false;
}

void loop() {
  // Sistema_Lorez();
  // Sistema_Roosler();
   Sistema_Chen();

}
//---------------------------
void Sistema_Chen(){
  //------------------------------- carga condicones iniciales 1er timen
  if(Fchen==false){
    Fchen=true;
    a = 3.5;
    b = 0.3;
    c = 2.8;
    x1 = 0.1;
    y1 = -1.0; 
    z1 = 0.1; 
    ts =  0.00438;  
   // while(true){Serial.print("aqui...");}
     
    }
 //-------------------
   unsigned long t_ant = micros();
    x = x1 + a*ts*(y1-x1);
    y = y1 + ts*((c-a)*x1 -(x1*z1) + (c*y1) );
    z = z1 + ts*((x1*y1)-(b*z1));

// scala a DAC de 0 a 255 data entre -5 y 8
// V0 = 19.62Vi + 98.08
    cx= 19.62*x + 98.08;
    cz = 19.62*z + 98.08;
    cy= 19.62*y + 98.08;
   
    PORTL=cz;
    OUT_X1 = cy;
    OUT_X2 = cz;
  
    x1 = x;
    y1 = y;
    z1 = z;
  
   Serial.println('A');
    Serial.println(x);
    Serial.println('B');
    Serial.println(y);
    Serial.println('C');
    Serial.println(z);
    
   //Serial.println('t');
   
    unsigned long t_act = micros();
    t_delay=4380-(t_act-t_ant);

    delayMicroseconds(t_delay);
  //Serial.println((t_act-t_ant));

    //----------------------------
  }
//--------------------
void Sistema_Roosler(){
  //------------------------------- carga condicones iniciales 1er timen
  if(FRossler==false){
    FRossler=true;
    a=0.2;
    b=0.2;
    c=5.7;  
    ts =  0.00438;
    x1 = -3.0;
    y1 = 0.0;
    z1 = 0.0;     
    }
//-------------------------------  
    // put your main code here, to run repeatedly:
     unsigned long t_ant = micros();
  // declaración (s);
    x = x1 - ts*((y1+z1));
    y = y1 + ts*(x1+a*y1);
    z = z1 + ts*(b + z1*(x1-c));
 // scala a DAC de 0 a 255 data entre -15 y 24
    cx= (x +16)*8.2;
    cz = (z )*10.2;
    cy= (y +16)*8.2;
   
    PORTL=cz;
    OUT_X1 = cy;
    OUT_X2 = cz;
  
    x1 = x;
    y1 = y;
    z1 = z;
  
   Serial.println('A');
    Serial.println(x);
    Serial.println('B');
    Serial.println(y);
    Serial.println('C');
    Serial.println(z);
    
   //Serial.println('t');
   
    unsigned long t_act = micros();
    t_delay=4380-(t_act-t_ant);

    delayMicroseconds(t_delay);
  //Serial.println((t_act-t_ant));
  }

//-------------------
void Sistema_Lorez(){
//------------------------------- carga condicones iniciales 1er timen
  if(Florenz==false){
    Florenz=true;
    p = 10.0;
    b = 8/3;
    r = 28;
    ts = 0.00438;
    x1 = -.1;
    y1 = 1.0;
    z1 = -.1;  
    
    }
    // put your main code here, to run repeatedly:
     unsigned long t_ant = micros();
  // declaración (s);
    x = x1 + ts*(p*(y1-x1));
    y = y1 + ts*(x1*(r-z1)-y1);
    z = z1 + ts*(x1*y1-b*z1);
   // cx= (x+20)*5;
   // cz = ((z+30)*2);
   // cy= (y+20)*5;
    cx= (x +27.97)*2.9;
    cz = (z +27.97)*2.9;
    cy= (y +27.97)*2.9;
   
    PORTL=cz;
    OUT_X1 = cx;
    OUT_X2 = cz;
  
    x1 = x;
    y1 = y;
    z1 = z;
  
    Serial.println('A');
    Serial.println(x);
    Serial.println('B');
    Serial.println(y);
    Serial.println('C');
    Serial.println(z);
    
   //Serial.println('t');
    
    unsigned long t_act = micros();
    t_delay=4380-(t_act-t_ant);
   // t_delay=1376-(t_act-t_ant);
    delayMicroseconds(t_delay);
  //Serial.println((t_act-t_ant));
  }
//------------------ send hex


