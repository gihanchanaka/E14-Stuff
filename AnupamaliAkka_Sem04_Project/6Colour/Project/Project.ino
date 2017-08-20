void setup() {
  // put your setup code here, to run once:

}

void loop() {
  processOneBox();
}


void processOneBox(){
  int R=analogRead(0); //Red LDR reading pin
  int G=analogRead(1); //Green LDR reading pin
  int B=analogRead(2); //Blue LDR reading pin

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

int whatColor(int R,int G,int B){
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

int whatColor_PCA(int R,int G,int B){
/*  
          sixColours=[[7.89,4.62,7.75];
                      [7.86,5.24,7.58];
                      [7.88,5.66,7.60];
                      [7.89,6.61,7.64];
                      [7.81,5.14,7.64];
                      [7.77,4.48,7.65];
                      ];
          sixColours=(1023/10)*sixColours;
          RGBmeans=mean(sixColours);
          
          for x=1:3
              diffMatrix(:,x)=sixColours(:,x)-RGBmeans(x);
          end
          
          corelationM=(diffMatrix' * diffMatrix);
          
          [V,D]=eig(corelationM);
          
          eigenVec=V(:,3);
          ###eigenVec=-0.0356953548010913,-0.998876566529159,0.0311680362638030
          
          for x=1:6
              projectedM(x)=(sixColours(x,:) * eigenVec);
          end
          ###projectedM= -476.195636323197  -539.982875706655 -582.909869157874 -679.894665019580 -529.390477284667 -461.770378972807
 */
  float eigenVectorR=0.356953548010913; //This value should be tuned
  float eigenVectorG=-0.998876566529159; //This value should be tuned
  float eigenVectorB=0.0311680362638030; //This value should be tuned
  
  float PCA_ar[]={-476.19,  -539.98, -582.90, -679.89, -529.39, -461.77}; //These values should be tuned
  float projection=(float)R*eigenVectorR + (float)G*eigenVectorG + (float)B*eigenVectorB;

  int color=0;
  for(int i=0;i<6;i++)if(abs(projection-PCA_ar[i])<abs(projection-PCA_ar[color]))color=i;
  return color;
  
}

int whatColor_NearestNeighbour(int R,int G,int B){
  /*
  sixColours=[[7.89,4.62,7.75];
              [7.86,5.24,7.58];
              [7.88,5.66,7.60];
              [7.89,6.61,7.64];
              [7.81,5.14,7.64];
              [7.77,4.48,7.65];
              ];
  sixColours=(1023/10)*sixColours;

    807.147000000000  472.626000000000  792.825000000000
    804.078000000000  536.052000000000  775.434000000000
    806.124000000000  579.018000000000  777.480000000000
    807.147000000000  676.203000000000  781.572000000000
    798.963000000000  525.822000000000  781.572000000000
    794.871000000000  458.304000000000  782.595000000000
   */
  int colorsRGB[6][3]={{807,472,792},{804,536,775},{806,579,777},{807,676,781},{798,525,781},{794,458,782}};
  int color=0;
  double minDistance=pow(colorsRGB[0][0]-R,2)+pow(colorsRGB[0][1]-G,2)+pow(colorsRGB[0][2]-B,2);
  for(int i=1;i<6;i++){
    if((pow(colorsRGB[i][0]-R,2)+pow(colorsRGB[i][1]-G,2)+pow(colorsRGB[i][2]-B,2)) < minDistance){
      color=i;
      minDistance=pow(colorsRGB[i][0]-R,2)+pow(colorsRGB[i][1]-G,2)+pow(colorsRGB[i][2]-B,2);
    }
  }
  return color;
}

int whatColor_DecisionTree(int R,int G,int B){
  //Need to see the data to implement this. 
  //Let us do this if we have time
  return whatColor_PCA(R,G,B);
}

