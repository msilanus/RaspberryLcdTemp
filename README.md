# Mesure de distance 

La mesure s'effectue au moyen d'un capteur de température 18B20 de chez Dalla et l'affichage est réalisé sur écran LCD RGB i2c 16x2 sur une Raspberry.

# L'afficheur
![Afficheur](lcd-2x16-i2c.jpg)

# le capteur de température
![Capteur de température](18B20_Temerature_Sensor.png)

# cross-compilation
arm-unknown-linux-gnueabihf-g++ C18B20.cpp ci2c.cpp rgb_lcd.cpp main.cpp -o iot -pthread -std=c++11

# Utilisation avec websocketd
./websocketd --port=8080 --staticdir=. ./iot

Dans un navigateur : http://ip_raspberry:8080
![Websocket](websocketd2.png)

