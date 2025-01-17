# AI-ATC
Artificial Intelligence meets RC Air Traffic Control. Based on Raspberry Pi 4 Model B 8GB


sudo apt-get update
sudo apt-get install libsdl2-dev
sudo apt-get install wiringpi
sudo apt-get install g++ RF24 

cd ~/'Pi 3b+ Base'

cd ~/rf24libs

g++ -o atc atc.cpp -lRF24 -lSDL2

g++ -o atc atc.cpp -L/home/atc/ -lRF24 -lSDL2


g++ -o atc atc.cpp -I/usr/local/include -L/usr/local/lib -lRF24 -lSDL2

g++ -o atc atc.cpp -I/usr/local/include -L/home/atc/ -lRF24 -lSDL2

g++ -o atc atc.cpp -I/usr/local/include -L/home/atc/rf24libs -lRF24 -lSDL2

g++ -o atc atc.cpp -I/usr/local/lib -L/home/atc/rf24libs -lRF24 -lSDL2

///////////////////////////////////
g++ -o atc atc.cpp -I/usr/local/lib -L/home/atc/rf24libs -lrf24 -lSDL2


7C:66:EF:28:79:D0


cd /'Pi 3b+ Base'/ && sudo ./atc


//////////////////////////////////////////

g++ ctest.cpp -o ctest -lhidapi-libusb


sudo bluetoothctl

agent on
default-agent

scan on

connect 7C:66:EF:28:79:D0


////////////////////////////////////////

## Initial setup


## Bluetoothctl controller Auto-connect
  1) Create .sh script file
    sudo nano /usr/local/bin/bt-autoconnect.sh

  2) Allow execution rights of .sh script
    sudo chmod +x /usr/local/bin/bt-autoconnect.sh

  3) Create a new Systemd .service file
    sudo nano /etc/systemd/system/bt-autoconnect.service
FILE_CONTENT_START: \EOL
[Unit]
Description=Bluetooth Controller Auto-connect
After=bluetooth.service
Wants=bluetooth.service

[Service]
ExecStart=/usr/local/bin/bt-autoconnect.sh
Restart=always

[Install]
WantedBy=multi-user.target
FILE_CONTENT_END:        
    
      

  5) Enable the service
    

## Compiling


## Executing





