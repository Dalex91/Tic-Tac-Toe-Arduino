
char tableGame[3][3];

void reinitTable() {
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      table[i][j] = 0;
}

bool checkValidValues(char a, char b, char c) {
  if (a == b && b == c && (a == 'O' || a == 'X'))
    return true;
  return false;
}

bool checkGameState() {
  bool stateGame = true; 
  for(int i = 0; i < 2; ++i)
    stateGame = stateGame && checkValidValues(a[i][0], a[i][1], a[i][2]) && checkValidValues(a[0][i], a[1][i], a[2][i]);
  return stateGame && checkValidValues(a[0][0], a[1][1], a[2][2]) && checkValidValues(a[0][2], a[1][1], a[2][0]);
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
