#include <MCP23S17.h>
MCP23S17 mcp(10);
MCP23S17 mcp2(9);

// Encoder A
byte encPins[]={2,3,11,12};
const int encCount=sizeof(encPins)/sizeof(encPins[0]);
byte rows[]={0,1,2,3};
const int rowCount=sizeof(rows)/sizeof(rows[0]);
byte cols[]={12,13,14,15};
const int colCount=sizeof(cols)/sizeof(cols[0]);
byte keys[colCount][rowCount];
  int enc0PinALast= mcp2.read1(encPins[2]);
  int enc0PinBLast= mcp2.read1(encPins[3]);


void setup() {
  Serial.begin(115200);
  SPI.begin();
  mcp.begin();
  mcp2.begin();

  for(int x=0;x<colCount; x++){
    Serial.print(rows[x]); Serial.println(" as input");
    mcp.pinMode1(cols[x], INPUT);
  }
  for(int x; x<colCount;x++){
    Serial.print(cols[x]); Serial.println(" as input-Pullup");
    mcp.pinMode1(cols[x], INPUT_PULLUP);
  }
  for(int x=0;x<encCount;x++){
    Serial.print(encPins[x]);Serial.println(" as  enc input");
    mcp2.pinMode1(encPins[x],INPUT);
  }



}

void readMatrix(){
  //Iterate Columns
  for(int colIndex=0;colIndex<colCount;colIndex++){
    //col: set to output LOW
    byte curCol=cols[colIndex];
    mcp.pinMode1(curCol,OUTPUT);
    mcp.write1(curCol,LOW);

    //Row: iterate through rows
    for(int rowIndex=0;rowIndex<rowCount; rowIndex++){
      byte rowCol=rows[rowIndex];
      mcp.pinMode1(rowCol, INPUT_PULLUP);
      keys[colIndex][rowIndex]=mcp.read1(rowCol);
      mcp.pinMode1(rowCol, INPUT);
    }
    mcp.pinMode1(curCol,INPUT);
    }
  }

  void printMatrix(){
    for(int rowIndex=0;rowIndex<rowCount;rowIndex++){
      if(rowIndex<10)
      Serial.print(F("0"));
    Serial.print(rowIndex);Serial.print(F(": "));

    for (int colIndex=0;colIndex<colCount;colIndex++){
      Serial.print(keys[colIndex][rowIndex]);
      if(colIndex<colCount)
        Serial.print(F(", "));
    }
    Serial.println("");
    }
    Serial.println("");
  }

void loop() {
int enc0PinAState = mcp2.read1(encPins[2]);
int enc0PinBState = mcp2.read1(encPins[3]);

/*  if (enc0PinAState != enc0PinALast && enc0PinAState==1) {
    if (mcp2.read1(encPins[2]) == HIGH) {
      Serial.println("CCW");
    } 
    else{
      Serial.println("CW");
    }
    enc0PinALast = enc0PinAState;
    enc0PinBLast = enc0PinBState;
  }
*/
if(enc0PinAState==HIGH&&enc0PinBState==LOW){
  Serial.println("CW");
  delay(50);
}
if(enc0PinAState==LOW&&enc0PinBState==HIGH){
  Serial.println("CCW");
  delay(50);
}
  readMatrix();
  if(Serial.read()=='!')
    printMatrix();

}