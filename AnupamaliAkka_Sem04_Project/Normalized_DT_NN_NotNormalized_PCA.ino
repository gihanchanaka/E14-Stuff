


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
   return ((float)R -  1.0170*1000) / 1.7321;
 }
 
 float normalizeG(int G){
   return ((float)G - 0.6263*1000) / 52.6909;
 }
 float normalizeB(int B){
   return ((float)B - 0.9663*1000) / 8.1445;
 }
 
 
 
 
 void processOneBox(){
   float R=(float)(analogRead(0)); //Red LDR reading pin
   float G=(float)(analogRead(1)); //Green LDR reading pin
   float B=(float)(analogRead(2)); //Blue LDR reading pin



 
    int color=whatColor(R,G,B);
/*   if(color==0)
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
 
*/

 int whatColor(float R,float G,float B){
   float normalized_R=normalizeR(R);
   float normalized_G=normalizeG(G);
   float normalized_B=normalizeB(B);


   Serial.print("The values: ");
   Serial.print(R);
   Serial.print(", ");
   Serial.print(G);
   Serial.print(", ");
   Serial.println(B);

   Serial.print("The normalized values: ");
   Serial.print(normalized_R);
   Serial.print(", ");
   Serial.print(normalized_G);
   Serial.print(", ");
   Serial.println(normalized_B);


   int colorNearestNeighbour=whatColor_NearestNeighbour(normalized_R,normalized_G,normalized_B);
   int colorDecisionTree=whatColor_DecisionTree(normalized_R,normalized_G,normalized_B);
   int colorPCA=whatColor_PCA(R,G,B);
   
   Serial.print("Nearest Neighbour=");
   Serial.println(colorToString(colorNearestNeighbour));
   Serial.print(" DecisionTree=");
   Serial.println(colorToString(colorDecisionTree));
   Serial.print(" PCA Algo=");
   Serial.println(colorToString(colorPCA));
   
   return colorDecisionTree; //********************
 }
 

String colorToString(int C){
  if(C==0) return "Red";
  else if(C==1) return "Green";
  else return "Blue"; 
}
   
    
   
   
    

           

 int whatColor_PCA(float R,float G,float B){
         
   float eigenVectorR=-0.0680; //This value should be tuned
   float eigenVectorG=0.7017; //This value should be tuned
   float eigenVectorB=0.7092; //This value should be tuned
   
   float PCA_ar[3]={-461.8374, -454.2711, -550.1367}; //These values should be tuned
   float projection=R*eigenVectorR + G*eigenVectorG + B*eigenVectorB;
 
   int color=0;
   for(int i=0;i<3;i++)if(abs(projection-PCA_ar[i])<abs(projection-PCA_ar[color]))color=i;
   return color;
   
 }
 
 int whatColor_NearestNeighbour(float R,float G,float B){
/*   
    
            
    
    
*/ 
   float colorsRGB[6][3]={{-1.1547,-0.4998,0.6958},{ 0.5774,-0.6516,0.4502},{0.5774,1.1514,-1.1460}};
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
   if(R<0) return 0;
   else if(B>G) return 2;
   else return 1;
 }


//void loop() {
  // put your main code here, to run repeatedly:

//}

