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

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  processOneBox();
}

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

  int color=whatColor(R,G,B);
  delay(100); //This is the time the box goes from start to motor 0
  if(color<2)rotateMotor(0,color);
  
  delay(100);//This is the time the box goes from motor 0 to motor 1
  if(color<4)rotateMotor(1,color%2);

  delay(100);//This is the time the box goes from motor 1 to motor 2
  if(color<6)rotateMotor(2,color%2);

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

  
  Serial.print(colorPCA);
  Serial.print(" ");
  Serial.print(colorNearestNeighbour);
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

