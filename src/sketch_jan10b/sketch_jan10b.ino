#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

char tableGame[3][4];
int firstLine=0;

enum Turn{
  X_TURN, O_TURN
};

int xScore = 0, yScore = 0;
Turn playerTurn = X_TURN;
Turn winner;

void initTable() {
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      tableGame[i][j] = '_';

  for(int i = 0; i < 3; ++i)
      tableGame[i][3] = '\0';
}

bool equalChars(char a, char b, char c) {
  if (a == b && b == c && (a == 'O' || a == 'X')) {
    if(a == 'X')
      winner = X_TURN;
    else
      winner = O_TURN;
    return true;
  }
  return false;
}

bool isEndGame() {
  bool stateGame = false;
  for (int i = 0; i < 2; ++i)
    stateGame = stateGame || equalChars(tableGame[i][0], tableGame[i][1], tableGame[i][2]) || equalChars(tableGame[0][i], tableGame[1][i], tableGame[2][i]);
  return stateGame || equalChars(tableGame[0][0], tableGame[1][1], tableGame[2][2]) || equalChars(tableGame[0][2], tableGame[1][1], tableGame[2][0]);
}

void setup() {

  lcd.setCursor(10, 0);
  lcd.print("X");
  lcd.setCursor(12, 0);
  lcd.print("O");

  lcd.begin(16, 2);
  firstLine = 0;
  pinMode(19, INPUT);  // RESET
  pinMode(20, INPUT);  // UP
  pinMode(21, INPUT);  // DOWN

  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);
  digitalWrite(21, HIGH);

  attachInterrupt(digitalPinToInterrupt(19), reset, CHANGE);
  attachInterrupt(digitalPinToInterrupt(20), moveUp, CHANGE);
  attachInterrupt(digitalPinToInterrupt(21), moveDown, CHANGE);
  Serial.begin(9600);
  initTable();
}

void moveUp() {
  //Serial.print("UP");
  firstLine = 0;
}

void moveDown() {
  //Serial.print("DOWN");
  firstLine = 1;  
 }

void reset() {
  xScore = 0;
  yScore = 0;
  firstLine = 0;
  initTable();    
}

void printLines() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(tableGame[firstLine]);
  lcd.setCursor(3, 0);
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(tableGame[firstLine + 1]);
  lcd.setCursor(3, 1);
  lcd.print(firstLine + 1);
}

char checkPlayerTurn() {
  if(playerTurn == X_TURN) {
    playerTurn = O_TURN;
    return 'X';
  }
  playerTurn = X_TURN;
  return 'O';
}

void serialRead() {
  int lin = -1, col = -1;
  if(Serial.available() > 3) {
     int lin = Serial.read() - '0';
     Serial.read();
     int col = Serial.read() - '0';   
     Serial.read();
     Serial.print(lin);
     Serial.print(" ");
     Serial.print(col);
     Serial.print("\n");  
     if(lin >= 0 && lin <= 2 || col >=0 && col <= 2) {
       tableGame[lin][col] = checkPlayerTurn();
     }          
  }
}

void printScore() {
  lcd.setCursor(6, 0);
  lcd.print("X");
  lcd.setCursor(8, 0);
  lcd.print("O");
  lcd.setCursor(6, 1);
  lcd.print(xScore);
  lcd.setCursor(8, 1);
  lcd.print(yScore);
}

void loop() {
  printLines();
  serialRead();
  if(isEndGame()) {
    if(winner == X_TURN) 
      xScore++;
    else
      yScore++;
    initTable();
  }
  printScore();
}
