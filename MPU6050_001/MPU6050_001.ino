//lib   Adafruit MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  // Инициализация MPU6050
  if (!mpu.begin()) {
    Serial.println("");
    Serial.println("Не удалось найти MPU6050芯片!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 найден!");

  // Настройка параметров датчика
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);   // Диапазон акселерометра: ±8g
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);        // Диапазон гироскопа: ±500 град/с
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);     // Ширина полосы фильтра: 21 Гц

  delay(100);
}

void loop() {
  // Получение новых данных с датчика
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Вывод сырых данных акселерометра и гироскопа
  Serial.print("Accel X: "); Serial.print(a.acceleration.x);
  Serial.print(", Y: "); Serial.print(a.acceleration.y);
  Serial.print(", Z: "); Serial.print(a.acceleration.z);
  Serial.print(" | Gyro X: "); Serial.print(g.gyro.x);
  Serial.print(", Y: "); Serial.print(g.gyro.y);
  Serial.print(", Z: "); Serial.println(g.gyro.z);

  // Простой расчет углов наклона (Pitch и Roll) из акселерометра
  float pitch = atan2(a.acceleration.y, a.acceleration.z) * 180 / PI;
  float roll = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180 / PI;

  Serial.print("Pitch: "); Serial.print(pitch);
  Serial.print(" | Roll: "); Serial.println(roll);
  Serial.println();

  delay(100); // Задержка для стабильности
}
