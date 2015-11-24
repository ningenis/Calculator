// Kalkulator perkalian dua angka pada Arduino
#include ≺liquidcrystal.h≻ // Library untuk LCD
#include ≺keypad.h≻ // Library untuk Keypad

const int numRows = 4; // Jumlah Baris pada Keypad
const int numCols = 3; // Jumlah Baris pada Keypad
const int debounceTime = 20; // Waktu kestabilan switch pada Keypad

const int numRow = 2; //Jumlah Baris pada LCD
const int numCol = 16; //Jumlah Kolom pada LCD

// Inisialisasi library dengan angka pada interface pin
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Definisi Keymap pada Keypad
const char keymap[numRows][numCols] = {
{ '1', '2', '3' } ,
{ '4', '5', '6' } ,
{ '7', '8', '9' } ,
{ '*', '0', '=' }
};

// Array untuk baris dan kolom pin pada keypad
const int rowPins[numRows] = { 0, 2, 3, 4 }; // Baris 0-3
const int colPins[numCols] = { 5, 6, 7 }; // Kolom 0-2

//Deklarasi Variabel pada Kalkulator
boolean valOnePresent = false;
boolean next = false;
boolean final = false;
String num1, num2;
long int ans;
char op;
long int key1;
char oper;
long int key2;

void setup()
{
  Serial.begin(9600);
  for (int row = 0; row < numRows; row++)
  {
    pinMode(rowPins[row],INPUT); // Set pin baris sebagai masukan
    digitalWrite(rowPins[row],HIGH); // Menyalakan Pull-Up
  }
  for (int column = 0; column < numCols; column++)
  {
    pinMode(colPins[column],OUTPUT); // Set pin kolom sebagai keluaran
    // Untuk penulisan
    digitalWrite(colPins[column],HIGH); // Buat semua kolom tidak aktif
  }
  lcd.begin(numCol, numRow); // Mulai membuat tampilan di LCD
  lcd.print("CALCULATOR"); // Pesan pada LCD.
  lcd.setCursor(0, 1); // Set cursor pada kolom 0, baris 1 untuk tampilan angka
}

void loop()
{
  char key = getKey(); //Mendapatkan key dari keypad
  //Pembacaan angka pertama dan angka kedua
  if ((key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0')){
    if (valOnePresent != true){
      num1 = num1 + key;
      int numLength1 = num1.length();
      lcd.setCursor(0, 1); 
      lcd.print(num1);
    }
    else {
      num2 = num2 + key;
      int numLength2 = num2.length();
      lcd.setCursor(num1.length()+1, 1);
      lcd.print(num2);
      final = true;
    }
  }
  // Pembacaan Operator
  else if (valOnePresent == false && (key == '*')){
    if (valOnePresent == false){
      valOnePresent = true;
      op = key;
      lcd.setCursor(num1.length(), 1); 
      lcd.print(op);
    }
  }
  // Operasi Penghitungan
  else if (final == true && key == '='){
    if (op == '*'){
      ans = num1.toInt() * num2.toInt();
    }    
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(ans);
  }
}

// Fungsi mendapatkan key dari tombol keypad yang ditekan
char getKey()
{
  char key = 0; // Inisialisasi nilai awal key
  for(int column = 0; column < numCols; column++)
  {
    digitalWrite(colPins[column],LOW); // Aktifkan kolom
    for(int row = 0; row < numRows; row++) // Periksa semua baris
    // Tombol/Key ditekan.
    {
      if(digitalRead(rowPins[row]) == LOW) // Pemeriksaan tombol, apakah ditekan atau tidak
      {
        delay(debounceTime); // debounce
        while(digitalRead(rowPins[row]) == LOW)
          ; // Menunggu key untuk dilepaskan
          key = keymap[row][column]; // Key yang ditekan
      }
    }
    digitalWrite(colPins[column],HIGH); // Deaktivasi kolom.
  }
  return key; // Mengembalikan nilai key
}
