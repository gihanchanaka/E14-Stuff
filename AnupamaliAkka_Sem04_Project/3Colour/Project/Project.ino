/* MATLAB CODE

			threeColours=[[1019,667,976];
			            [1020,655,960];
			            [1022,711,994];
			            ]
			RGBmeans=mean(threeColours)
			RGBsdtDev=sqrt(var(threeColours))

			normalizedThreeColours=zeros(3,3);

			for i=1:3
			    for j=1:3
			        normalizedThreeColours(i,j)= (threeColours(i,j)-RGBmeans(j)) /RGBsdtDev(j);
			    end
			end
			normalizedThreeColours

			corelationM=(normalizedThreeColours' * normalizedThreeColours);

			[V,D]=eig(corelationM);

			eigenVec=V(:,3)

			unitV=eigenVec/abs(eigenVec);

			for x=1:3
			    projectedM(x)=(normalizedThreeColours(x,:) * eigenVec);
			end

			projectedM


MATLAB RESULT
		threeColours =

		        1019         667         976
		        1020         655         960
		        1022         711         994


		RGBmeans =

		   1.0e+03 *

		    1.0203    0.6777    0.9767


		RGBsdtDev =

		    1.5275   29.4845   17.0098


		normalizedThreeColours =

		   -0.8729   -0.3618   -0.0392
		   -0.2182   -0.7688   -0.9798
		    1.0911    1.1305    1.0190


		eigenVec =

		    0.5469
		    0.6103
		    0.5731


		projectedM =

		   -0.7206   -1.1501    1.8707

*/



#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position









//void setup() {
  // put your setup code here, to run once:
void setup() {
   // put your setup code here, to run once:
   // put your setup code here, to run once:
Serial.begin(9600);
myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
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
   return ((float)R - 1.0203*1000) / 1.5275;
 }
 
 float normalizeG(int G){
   return ((float)G - 0.6777*1000) / 29.4845;
 }
 float normalizeB(int B){
   return ((float)B - 0.9767*1000) / 17.0098;
 }
 
 
 
 
 void processOneBox(){
   float R=normalizeR(analogRead(0)); //Red LDR reading pin
   float G=normalizeG(analogRead(1)); //Green LDR reading pin
   float B=normalizeB(analogRead(2)); //Blue LDR reading pin

   Serial.println(R);
   Serial.print(", ");
   Serial.println(G);
   Serial.print(", ");
   Serial.println(B);
 
   int color=whatColor(R,G,B);
   if(color==0)
   {
    Serial.println("this is red");
   //rotateMotor(0,color);
   }
   else if(color==1)
   {
    
     Serial.println("this is green");
   //  rotateMotor(1,color%2);
   }
 	else if(color==2)
   {
   //rotateMotor(2,color%2);
   Serial.println("this is blue");
   }
   else{
   	Serial.println("No decision");
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
   int colorPCA=whatColor_PCA(R,G,B);
   int colorNearestNeighbour=whatColor_NearestNeighbour(R,G,B);
   int colorDecisionTree=whatColor_DecisionTree(R,G,B);
 
   
   Serial.println(colorPCA);
   Serial.print(" ");
   Serial.println(colorNearestNeighbour);
   Serial.print(" ");
   Serial.println(colorDecisionTree);
   
   
   
   if(colorPCA==colorNearestNeighbour and colorPCA==colorDecisionTree) return colorPCA;
   else return 6;
 }
 
 int whatColor_PCA(float R,float G,float B){
         
   float eigenVectorR=0.5469; //This value should be tuned
   float eigenVectorG=0.6103; //This value should be tuned
   float eigenVectorB=0.5731; //This value should be tuned
   
   float PCA_ar[3]={-0.7206 ,  -1.1501 ,   1.8707}; //These values should be tuned
   float projection=R*eigenVectorR + G*eigenVectorG + B*eigenVectorB;
 
   int color=0;
   for(int i=0;i<3;i++)if(abs(projection-PCA_ar[i])<abs(projection-PCA_ar[color]))color=i;
   return color;
   
 }
 
 int whatColor_NearestNeighbour(float R,float G,float B){
 
   float colorsRGB[6][3]={{-0.8729 , -0.3618 ,  -0.0392},{ -0.2182  , -0.7688  , -0.9798},{1.0911  ,  1.1305 ,   1.0190}};
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
   if(G>0) return 2;
   else if(G>R) return 0;
   else return 1;
 }


//void loop() {
  // put your main code here, to run repeatedly:

//}
