
#include <Arduino.h>
// #include <SPI.h>
#include <SD.h>
// #include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define CS  10 // SD CS pina

#define OLED_RESET 7
Adafruit_SSD1306 display(OLED_RESET); // создаём объект "дисплей"






void setup() {

  uint64_t t = 0;
  uint8_t start = false;

  Serial.begin(9600);
  pinMode(CS, OUTPUT);
  // Инициализация OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // инициализация дисплея по интерфейсу I2C, адрес 0x3C
  display.clearDisplay(); // очистка дисплея
  display.setTextSize(1); // установка размера шрифта
  display.setTextColor(WHITE); // установка цвета текста
  display.setCursor(0, 0); // установка курсора в позицию X = 0; Y = 0
  display.print ("0_o"); // записываем в буфер дисплея нашу фразу
  display.display(); // и её выводим на экран

  // Инициализация SD
  if (!SD.begin(CS)) {
    display.println("SD error!");
    display.display();
    while (1);
  }
  File file = SD.open("/re3.txt", FILE_WRITE);
  
  if (file) {
    // file.println("hELLO");
    
    display.println("Ready to receive");
    display.display();

    while(1){

    if (Serial.available()) {

    start = true;
    t = millis();

    byte b = Serial.read();
    file.write(b);

    // Отображение байта в HEX
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Byte: 0x");
    if (b < 16) display.print('0');
    display.print(b, HEX);
    display.display();
  }
    
    if(start)
      if (millis() - t > 2000){
        file.close();
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Close file");
        display.display();
      }
        

  }


  }
  else{
    display.println("File error!");
    display.display();
    while (1);
  }



  
  
}

void loop() {
  
}

