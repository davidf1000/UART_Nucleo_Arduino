# UART_Nucleo_Arduinoadd 
Documentation Uart or serial communication protocol for Nucleo-Arduino
Untuk pengiriman data, ada dua metode : 
Serial.write => 
Kelebihan :
kirim data byte , di receive dalam bentuk byte juga
kekurangan : 
gabisa kirim karakter selain angka(gabisa bikin selipan character untuk seperate antar data) 
Serial.Print => 
Kelebihan : 
- Bisa kirim 1 string langsung, tapi diterima di nucleo tetep harus satu" dalam 
bentuk ASCII code (int), bisa tinggal di convert ke char . 

So far masih pake Serial.Print dari mega ke nucleo, works fine di 9600 baud rate 
In the future bakal dicoba baud rate yang lebih tinggi ( 115200>>)

Kendala : 
- Buffer serial size nya 64 byte (64 char) , kemungkinan ada cara buat expand serial buffer size nya 
- Udah bisa nerima 1 String full dari mega ke nucleo , tapi belom dicoba buat nge seperate tiap data di dalam
1 string buat dimasukin ke variabel sensor 
- Cara kerja : 
Nucleo interrupt minta data -> nucleo ngirim ke mega ( misal : mau data sensor ping , kirim kode 1 )
-> mega respon, read sensor yang disuruh , dimasukin ke dalam string , and start and end effector nya biar ngehindarin ada data nyasar yang masuk ke dalam string. Misal : 
< SENSOR1,SENSOR2,SENSOR3,DLL> ---> string max size 64 
Nucleo nerima tiap satu" , diconvert ke char , lalu dibikin 1 string lagi tanpa start & end effector 
Lalu dibikin algoritma buat nge-extract data di string buat dimasukin ke dalam variabel sensor ,
Termasuk jika DATA float , misal "23,232" , harus bisa di ubah ke float di dalam algoritma 
