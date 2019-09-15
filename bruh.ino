int irr=A2;
int r;

int irl=A1;
int l;



int data;
int moto1 = 2;
int moto2 = 3;
int moto3 = 4;
int moto4 = 5;
int en = 6;
int x;
int pot = A6;
void setup() {
  // put your setup code here, to run once:
  pinMode(irr,INPUT);
  pinMode(irl,INPUT);
Serial.begin(9600);
pinMode(pot,INPUT);

  pinMode(moto1, OUTPUT);
  pinMode(moto2, OUTPUT);
  pinMode(moto3, OUTPUT);
  pinMode(moto4, OUTPUT);
  pinMode(en, OUTPUT);
  digitalWrite(en,HIGH);
  

}

void loop() {
  // put your main code here, to run repeatedly:
    
    r=digitalRead(irr);
    l=digitalRead(irl);
    x=analogRead(pot);
Serial.print("right=");
Serial.print(r);
Serial.println(l);
//digitalWrite(moto2,HIGH);//RB
//digitalWrite(moto1,HIGH);//RF
//digitalWrite(moto3,HIGH);//LB
//digitalWrite(moto4,HIGH);//LF
 
analogWrite(en,x);   
 if(l==0&&r==0){
  digitalWrite(moto4,HIGH);
  digitalWrite(moto2,LOW);
  digitalWrite(moto1,HIGH);
    digitalWrite(moto3,LOW);

} 
 

if(r==1&&l==0){
  digitalWrite(moto1,LOW);
digitalWrite(moto3,LOW);
digitalWrite(moto2,HIGH);
digitalWrite(moto4,HIGH);


}


if(l==1&&r==0){
  digitalWrite(moto4,LOW);
  digitalWrite(moto2,LOW);
  digitalWrite(moto1,HIGH);
    digitalWrite(moto3,HIGH);

}

}