#define powerWaterLevel 7
#define detectLight A0
#define detectWaterLevel A1
#define detectPHLevel A2

int waterval = 0;
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

void setup() {
  pinMode(powerWaterLevel, OUTPUT);

  digitalWrite(powerWaterLevel, LOW);

  Serial.begin(9600);
}

void loop() {
  //get the reading from the function below and print it
  int waterlevel = readWaterLevel();
  
  Serial.print("Water level: ");
  Serial.println(waterlevel);

    // reads the input on analog pin A0 (value between 0 and 1023)
  int analogValue = analogRead(A0);

  Serial.print("Analog reading = ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 10) {
    Serial.println(" - Dark");
  } else if (analogValue < 200) {
    Serial.println(" - Dim");
  } else if (analogValue < 500) {
    Serial.println(" - Light");
  } else if (analogValue < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }

  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(detectPHLevel);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");  
  
  delay(1000);
}

//This is a function used to get the reading of Water level
int readWaterLevel() {
  digitalWrite(powerWaterLevel, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  waterval = analogRead(detectWaterLevel);    // Read the analog value form sensor
  digitalWrite(powerWaterLevel, LOW);   // Turn the sensor OFF
  return waterval;             // send current reading
}

int readLightLevel(){
  

}
