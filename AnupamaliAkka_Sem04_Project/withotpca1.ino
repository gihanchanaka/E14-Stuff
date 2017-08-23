


#include <Servo.h>

Servo myservo0;  
Servo myservo1;
Servo myservo2;// create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position









//void setup() {
  // put your setup code here, to run once:
void setup() {
   // put your setup code here, to run once:
   // put your setup code here, to run once:
Serial.begin(9600);
myservo0.attach(9); 
myservo1.attach(10);
myservo2.attach(11);// attaches the servo on pin 9 to the servo object
}

void loop() {
delay(200);
  // put your main code here, to run repeatedly:
int sensorvaluered=analogRead(A0);
int sensorvaluegreen=analogRead(A1);
int sensorvalueblue=analogRead(A2);

Serial.println(sensorvaluered);
Serial.print("\t");
delay(100);
Serial.println(sensorvaluegreen);
Serial.print("\t");
delay(100);
Serial.println(sensorvalueblue);
Serial.println();
//delay(2000);
processOneBox();
}
// }
 
// void loop() {
  // processOneBox();
 //}
              
 float normalizeR(int R){
   return ((float)R -  1.0180*1000) / 1.0000;
 }
 
 float normalizeG(int G){
   return ((float)G - 0.5693*1000) / 40.2036;
 }
 float normalizeB(int B){
   return ((float)B - 0.9737*1000) / 12.8582;
 }
 
 
 
 
 void processOneBox(){
   float R=normalizeR(analogRead(0)); //Red LDR reading pin
   float G=normalizeG(analogRead(1)); //Green LDR reading pin
   float B=normalizeB(analogRead(2)); //Blue LDR reading pin

   Serial.print("The normalized values: ");
   Serial.print(R);
   Serial.print(", ");
   Serial.print(G);
   Serial.print(", ");
   Serial.println(B);
 
    int color=whatColor(R,G,B);
   if(color==0)
   {
    Serial.println("this is red");
   myservo0.write(120);
delay(5000);
myservo0.write(0);
delay(5000);
   }
   else if(color==1)
   {
     myservo1.write(120);
delay(5000);
myservo1.write(0);
delay(5000);
     Serial.println("this is green");
   //  rotateMotor(1,color%2);
   }
  else if(color==2)
   { myservo2.write(120);
delay(5000);
myservo2.write(0);
delay(5000);
   //rotateMotor(2,color%2);
   Serial.println("this is blue");
   }
   else{
    Serial.println("No decision");
        myservo0.write(120);
delay(5000);
myservo0.write(0);
delay(5000);
   }
   delay(200);//This is the time box goes from motor 2 to the exit
 
  
 } 
 void rotateMotor(int motor,int side){
   //motor =0,1,2
   //side= clockwise 0, counterclockise 1
   //Try to implement this please, I dont know the pins
   //Tell me if u cannot
 }
 


 int whatColor(float R,float G,float B){
   
   int colorNearestNeighbour=whatColor_NearestNeighbour(R,G,B);
   int colorDecisionTree=whatColor_DecisionTree(R,G,B);
   int colorPCA=whatColor_PCA(R,G,B);
   
   Serial.print("Nearest Neighbour=");
   Serial.println(colorNearestNeighbour);
   Serial.print(" DecisionTree=");
   Serial.print(colorDecisionTree);
   Serial.print(" PCA Algo=");
   Serial.println(colorPCA);
   
   return colorDecisionTree; //********************
 }
 


   
    


           

 int whatColor_PCA(float R,float G,float B){
         
   float eigenVectorR=-0.0680; //This value should be tuned
   float eigenVectorG=0.7017; //This value should be tuned
   float eigenVectorB=0.7092; //This value should be tuned
   
   float PCA_ar[3]={0.9435 ,  0.6741 ,   -1.6177}; //These values should be tuned
   float projection=R*eigenVectorR + G*eigenVectorG + B*eigenVectorB;
 
   int color=0;
   for(int i=0;i<3;i++)if(abs(projection-PCA_ar[i])<abs(projection-PCA_ar[color]))color=i;
   return color;
   
 }
 
 int whatColor_NearestNeighbour(float R,float G,float B){
/*   
    
         
*/ 
   float colorsRGB[6][3]={{-1.0000,0.5140,0.7259},{ 1.0000, 0.6384, 0.4148},{0,-1.1525,-1.1406}};
   int color=0;
   double minDistance=pow(colorsRGB[0][0]-R,2)+pow(colorsRGB[0][1]-G,2)+pow(colorsRGB[0][2]-B,2);
   for(int i=1;i<3;i++){
     if((pow(colorsRGB[i][0]-R,2)+pow(colorsRGB[i][1]-G,2)+pow(colorsRGB[i][2]-B,2)) < minDistance){
       color=i;
       minDistance=pow(colorsRGB[i][0]-R,2)+pow(colorsRGB[i][1]-G,2)+pow(colorsRGB[i][2]-B,2);
     }
   }
   return color;
 }
 
 int whatColor_DecisionTree(float R,float G,float B){
   if(B<0) return 2;
   else if(B>G) return 0;
   else return 1;
 }


//void loop() {
  // put your main code here, to run repeatedly:

//}

