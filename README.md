# 🎛 FaceDeck v1.0

![Version](https://img.shields.io/badge/version-v1.0-blue)
![Platform](https://img.shields.io/badge/platform-ESP32-green)
![Display](https://img.shields.io/badge/display-SSD1306-orange)
![License](https://img.shields.io/badge/license-MIT-lightgrey)
![Status](https://img.shields.io/badge/status-stable-success)

ESP32 StreamDeck with animated face UI and BLE keyboard support.

FaceDeck is a custom hardware project that works as a Bluetooth keyboard,
allowing you to launch apps, scripts, or commands using physical buttons,
while showing an animated face on a 128×64 OLED display.

---

## 📷 Preview

![preview](images/preview.png)

---

## ✨ Features

- 12 key stream deck
- BLE keyboard
- Animated face UI
- Popup text on key press
- Configurable key actions
- SSD1306 128×64 display
- INPUT_PULLUP wiring
- Works on Linux / Windows / macOS
- No extra software needed

---

## 🧠 How it works

ESP32 connects as Bluetooth keyboard.

Button pressed → shortcut sent → OS runs command  
OLED shows popup → face returns  

Example

Press key → shortcut → program runs → popup → face

---

## 🧩 Hardware

ESP32 DevKit  
SSD1306 OLED 128×64 I2C  
12 buttons  
USB power  

Optional

Mechanical switches  
Case  
Encoder  
RGB  

---

## 🔌 Wiring

OLED

VCC → 3.3V  
GND → GND  
SDA → GPIO21  
SCL → GPIO22  

Buttons

GPIO → button → GND

Pins

4   5   13  12  
14  27  26  25  
33  32  16  17  

Key order

| Key | GPIO |
|-----|------|
| 1 | 4 |
| 2 | 5 |
| 3 | 13 |
| 4 | 12 |
| 5 | 14 |
| 6 | 27 |
| 7 | 26 |
| 8 | 25 |
| 9 | 33 |
| 10 | 32 |
| 11 | 16 |
| 12 | 17 |

Buttons go to GND  
INPUT_PULLUP used

---

## ⌨️ Shortcuts

Create global shortcuts in your OS.

Example

Ctrl+Alt+1 → program  
Ctrl+Alt+2 → script  
Ctrl+Alt+3 → tool  
Ctrl+Alt+4 → terminal  

Linux

System Settings → Shortcuts → Global

Windows

AutoHotkey / shortcuts

macOS

Keyboard settings

---

## 📺 OLED UI

Idle → animated face  
Press key → popup text  
After delay → face returns  

Popup time can be changed in code.

---

## 💻 Firmware

File

FaceDeck.ino

Libraries

Adafruit GFX  
Adafruit SSD1306  
ESP32 BLE Keyboard  
Wire  

Install from Arduino Library Manager

---

## ⚙️ Build

Arduino IDE

Install ESP32 board  
Install libraries  
Select ESP32 DevKit  
Upload  

PlatformIO

platform = espressif32  
board = esp32dev  
framework = arduino  

---

## 🔧 Changing Commands

Open

FaceDeck.ino

Find

sendAction(int i)

Inside you will see

switch(i)
{
  case 0:
  case 1:
  case 2:
}

Each case = one button

Example send Ctrl + Alt + 1

bleKeyboard.press(KEY_LEFT_CTRL);
bleKeyboard.press(KEY_LEFT_ALT);
bleKeyboard.press('1');
bleKeyboard.releaseAll();

Example send single key

bleKeyboard.press('a');
bleKeyboard.releaseAll();

Example send function key

bleKeyboard.press(KEY_F1);
bleKeyboard.releaseAll();

Example send multiple keys

bleKeyboard.press(KEY_LEFT_CTRL);
bleKeyboard.press(KEY_LEFT_SHIFT);
bleKeyboard.press('s');
bleKeyboard.releaseAll();

Change popup text

popupText = "APP";

Upload again after editing.

---

## 🎮 Usage

Power ESP32  
Pair Bluetooth  
Press key  
Shortcut sent  
Program runs  
Face animates  

---

## 🚀 Future

Icons  
Profiles  
Menu  
RGB  
TFT  
SD card  
Encoder  
Sound  

---

## 📜 License

MIT

---

FaceDeck v1.0  
ESP32 StreamDeck with animated face UI
