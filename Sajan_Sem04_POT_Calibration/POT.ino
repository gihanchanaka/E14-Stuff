float calibration[]={0f,0.125f,0.250f,0.375f,0.500f,0.625f,0.750f,0.875f};
int max=0;
int reading=0;

void setup(){
	/*
	pinMode(0,ANALOGIN);
	pinMode(1,ANALOGIN);
	*/ //No need
}


void loop(){
	max=analogRead(1);
	reading=analogRead(0);
	Serial.println("Week = "+whichWeek());
	delay(1);
}

int whichWeek(){
	float ratio=(float)reading/(float)max;
	Serial.println("Ratio = "+ratio);
	if(ratio< calibration[0])return 0;
	int w;
	for(w=1;w<8;w++)if(ratio<calibration[w]){
		if( abs(calibration[w]-ratio) < abs(calibration[w-1]-ratio) ){
			return w;
		}
		else return w-1;
	}
	return 7;
}