#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

char tableGame[4][4];
int firstLine, secondLine;

void reinitTable() {
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      tableGame[i][j] = 0;
}

void tableTest() {
  tableGame[0][0] = 'X';
  tableGame[0][1] = 'O';
  tableGame[0][2] = 'X';

  tableGame[1][0] = 'O';
  tableGame[1][1] = 'O';
  tableGame[1][2] = 'X';

  tableGame[2][0] = 'O';
  tableGame[2][1] = 'O';
  tableGame[2][2] = 'O';
}

bool checkValidValues(char a, char b, char c) {
  if (a == b && b == c && (a == 'O' || a == 'X'))
    return true;
  return false;
}

bool checkGameState() {
  bool stateGame = true;
  for (int i = 0; i < 2; ++i)
    stateGame = stateGame && checkValidValues(tableGame[i][0], tableGame[i][1], tableGame[i][2]) && checkValidValues(tableGame[0][i], tableGame[1][i], tableGame[2][i]);
  return stateGame && checkValidValues(tableGame[0][0], tableGame[1][1], tableGame[2][2]) && checkValidValues(tableGame[0][2], tableGame[1][1], tableGame[2][0]);
}

void setup() {
  lcd.begin(16, 2);
  tableTest();
  firstLine = 0;
  secondLine = 1;

  pinMode(19, INPUT);  // RESET
  pinMode(20, INPUT);  // UP
  pinMode(21, INPUT);  // DOWN

  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);
  digitalWrite(21, HIGH);

  attachInterrupt(digitalPinToInterrupt(19), reset, CHANGE);
  attachInterrupt(digitalPinToInterrupt(20), moveUp, CHANGE);
  attachInterrupt(digitalPinToInterrupt(21), moveDown, CHANGE);
}

void printLine() {
  for(int i = 0; i < 3; ++i)
       
}

void moveUp() {
  lcd.print("UP");
}

void moveDown() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DOWN");
}

void reset() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RESET");
}

void loop() {
}
