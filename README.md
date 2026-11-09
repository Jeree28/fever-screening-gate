# Automatic Fever Screening Gate

A microcontroller-based body-temperature screening system that automatically opens or locks an access gate.
Built and simulated in [Wokwi](https://wokwi.com/projects/466249826940109825).

## How it works
1. Press the button to start a screening.
2. The DHT22 sensor reads the temperature and shows it on the I2C LCD.
3. **≤ 37.0 °C (normal):** green LED on, servo gate opens (90°), LCD shows `AKSES BUKA`.
4. **> 37.0 °C (fever):** red LED on, buzzer alarm, gate stays locked, LCD shows `AKSES KUNCI`.
5. The system counts total people screened and total fever cases, and logs every result to the Serial Monitor.

## Components
Arduino, DHT22 temperature sensor, servo motor (gate), 16x2 I2C LCD, red/green LEDs, buzzer, push button.

## Run it
Open the [Wokwi project](https://wokwi.com/projects/466249826940109825) and press **Start Simulation**, or copy `sketch.ino` into Arduino IDE.

## Background
Extends the Arduino temperature-monitoring design from Pratama & Permana, *Simulasi Permodelan Menggunakan Sensor Suhu Berbasis Arduino*, Edu Elektrika Journal, 2021, by adding an access gate, alarm, and screening counters.

## Author
Jeremi Saragih, Politeknik Elektronika Negeri Surabaya
