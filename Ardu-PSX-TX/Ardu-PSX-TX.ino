//============================================================
/* 
** DAY 42
** HARD_PRO : HIZBUL JIHAD AFANDI
** SOFT_PRO : RAHMAT HADI
** WIRING   : FIRMAN SASMITO
** LIBRARI.1: LIBRARI STICK PS2 DARI http://www.billporter.info/?p=240
** LIBRARI.2: LIBRARI VirtulWire http://www.open.com.au/mikem/arduino/VirtualWire.pdf UNTUK KOMUNIKASI DATA RF 
*/
//========================== BEGIN ===========================
#include <PS2X_lib.h>
    PS2X PS2;            //instansiasi class librari stick PS2
#include <VirtualWire.h>
/*
**============================================================
**||
** \\
**  =====================================================
*/
#define CLOCK     13 //warna BIRU
#define DATA      12 //warna COKLAT
#define COMMAND   11 //warna ORANGE
#define ATTENTION 10 //warna KUNING
#define TEMP_SENS A0 //PORT Analog Sensor LM35
#define LED       7  //led indikator tanda pengiriman data

const int TRANSMITER  = 9;
const int RECEIVER    = 8;
int NEW_TEMP_SENS;

byte count = 1;

int error         = 0;
byte type_stick   = 0;
byte vibrate      = 0;
int LY, LX, RY, RX;
int Ly, Lx, Ry, Rx;
void setup()
{
  //=====================================
  //  UNTUK CONFIGURASI STICK PS2
  //=====================================
  Serial.begin(115600);
  delay(500);
  error = PS2.config_gamepad(CLOCK, COMMAND, ATTENTION, DATA, false, false); //mensetup port untuk stick ps, dan check errornya
  if (error == 0)
  {
    Serial.println("Stick PS2 ditemukan, Configurasi Sukses !");
  }
  else if (error == 1)
  {
    Serial.println("Tidak Ada Stick Terdeteksi, Periksa Koneksi");
  }
  else if (error == 2)
  {
    Serial.println("Stick PS2 Yang Anda Gunakan Tidak Cocok");
  }
  type_stick = PS2.readType(); //digunakan untuk membaca tipe stick yg terpasang karena dlm librari terdapat stick husus untuk gitar hero
  switch (type_stick)
  {
    case 0: Serial.println("Unknown Controller Type"); break;
    case 1: Serial.println("DualShock Controller Found"); break;
  }
  //=====================================
  //  UNTUK CONFIGURASI PORT SENS LM35
  //=====================================
  pinMode(TEMP_SENS, INPUT);
  //=====================================
  //  UNTUK CONFIGURASI TRANSMITER
  //=====================================
  pinMode(TEMP_SENS, INPUT);  //setup port analog sensor LM35
  vw_set_tx_pin(TRANSMITER);  //setup port transmiter
  vw_set_rx_pin(RECEIVER);    //setup port receiver boleh tidak di variabelkn dan disetup
  vw_set_ptt_inverted(true);  //invert port untuk pengiriman(port bebas)
  vw_setup(1000);             //ready dlm 1000 ms
  pinMode(LED, OUTPUT);       //setup pin LED indikator tanda pengiriman
}
void baca_tempratur_dan_kirim()
{
  int VAL       = analogRead(TEMP_SENS);   //ambil data sensor LM35 dari port sensor (A0);
  NEW_TEMP_SENS = (VAL * 110) / 1024;      //proses kalibrasi, 110mV = Tgangan Refrensi, 1024 = 
  char BUFF[33] = {NEW_TEMP_SENS};         //tampung data sensor

  BUFF[33] = count;                        //array di naikkan indexnya dg count yg bernilai 1 jika data yg dikirim lebih dari 0 index
  digitalWrite(LED, HIGH);                 //nyalakan led tanda mulai pengiriman
  vw_send((uint8_t *)BUFF, strlen(BUFF));  //mulai kirim data yg tersimpan dalam VARIABEL Array
  vw_wait_tx();                            //berikan waktu tunda pengiriman yg sudah ditentukan dalam library
  digitalWrite(LED, LOW);                  //matikan LED indikator ketika menunggu pengiriman data berikutnya
  delay(1000);                             //kirim data dlm waktu 1000 ms
  count = count + 1;                       //tambahkan 1 index BUFF yg diatas
}
void main_program()
{
  /*=================================================================================
  **  KETERANGAN :
  **  read_gamepad(false, vibrate) : digunakan untuk membaca stick 
  **  * dan parameter didalamnya untuk mengatur vibrasi stick true : On, false : Off
  **  Button(PSB_PAD_) : Bisa Menahan Tombol
  **  ButtonPressed(PSB_PAD_) : Hanya Boleh Menekan 1x
  **  ButtonReleased(PSB_PAD_) : Ketika tombol dilepas
  **=================================================================================*/
  PS2.read_gamepad(false, vibrate);
  /*=================================================================================
  ** BUTTON ARAHNYA INI
  **=================================================================================*/
  if (PS2.Button(PSB_PAD_UP))Serial.println("TOMBOL ATAS DITAHAN");
  if (PS2.ButtonPressed(PSB_PAD_UP))Serial.println("TOMBOL ATAS HANYA DITEKAN");
  if (PS2.ButtonReleased(PSB_PAD_UP))Serial.println("TOMBOL ATAS DILEPAS");
  /*=================================================================================*/
  if (PS2.Button(PSB_PAD_LEFT))Serial.println("TOMBOL KIRI DITAHAN");
  if (PS2.ButtonPressed(PSB_PAD_LEFT))Serial.println("TOMBOL KIRI HANYA DITEKAN");
  if (PS2.ButtonReleased(PSB_PAD_LEFT))Serial.println("TOMBOL KIRI DILEPAS");
  /*=================================================================================*/
  if (PS2.Button(PSB_PAD_DOWN))Serial.println("TOMBOL BAWAH DITAHAN");
  if (PS2.ButtonPressed(PSB_PAD_DOWN))Serial.println("TOMBOL BAWAH HANYA DITEKAN");
  if (PS2.ButtonReleased(PSB_PAD_DOWN))Serial.println("TOMBOL BAWAH DILEPAS");
  /*=================================================================================*/
  if (PS2.Button(PSB_PAD_RIGHT))Serial.println("TOMBOL KANAN DITAHAN");
  if (PS2.ButtonPressed(PSB_PAD_RIGHT))Serial.println("TOMBOL KANAN HANYA DITEKAN");
  if (PS2.ButtonReleased(PSB_PAD_RIGHT))Serial.println("TOMBOL KANAN DILEPAS");
  /*=================================================================================
  ** BUTTON SEGITIGA, KOTAK, KALI, BULET
  =================================================================================*/
  if (PS2.Button(PSB_TRIANGLE))Serial.println("TOMBOL SEGITIGA DITAHAN");
  if (PS2.ButtonPressed(PSB_TRIANGLE))Serial.println("TOMBOL SEGITIGA HANYA DITAHAN");
  if (PS2.ButtonReleased(PSB_TRIANGLE))Serial.println("TOMBOL SEGITIGA DILEPAS");
  /*=================================================================================*/
  if (PS2.Button(PSB_SQUARE))Serial.println("TOMBOL KOTAK DITAHAN");
  if (PS2.ButtonPressed(PSB_SQUARE))Serial.println("TOMBOL KOTAK HANYA DITEKAN");
  if (PS2.ButtonReleased(PSB_SQUARE))Serial.println("TOMBOL KOTAK DILEPAS");
  /*=================================================================================*/
  if (PS2.Button(PSB_CROSS))Serial.println("TOMBOL KALI DITAHAN");
  if (PS2.ButtonPressed(PSB_CROSS))Serial.println("TOMBOL KALI HANYA DITEKAN");
  if (PS2.ButtonReleased(PSB_CROSS))Serial.println("TOMBOL KALI DILEPAS");
  /*=================================================================================*/
  if (PS2.Button(PSB_CIRCLE))Serial.println("TOMBOL BULET DITAHAN");
  if (PS2.ButtonPressed(PSB_CIRCLE))Serial.println("TOMBOL BULET HANYA DITEKAN");
  if (PS2.ButtonReleased(PSB_CIRCLE))Serial.println("TOMBOL BULET DILEPAS");
  /*=================================================================================
  ** ANALOG RX,RY,LX,LY
  ===================================================================================*/
  RY = (int) PS2.Analog(PSS_RY);
  RX = (int) PS2.Analog(PSS_RX);
  LY = (int) PS2.Analog(PSS_LY);
  LX = (int) PS2.Analog(PSS_LX);
  if (RY != Ry || RX != Rx)
  {
    Serial.print("R Stick Values:");
    Serial.print("RY = ");
    Serial.print(RY, DEC);
    Serial.print(",");
    Serial.print("RX = ");
    Serial.println(RX, DEC);
    digitalWrite(8, HIGH);
    delay(1000);
  }
  if (LY != Ly || LX != Lx)
  {
    Serial.print("L Stick Values:");
    Serial.print("LY = ");
    Serial.print(LY, DEC);
    Serial.print(",");
    Serial.print("LX = ");
    Serial.println(LX, DEC);
    delay(1000);
  }
  Ry = RY;
  Rx = RX;
  Ly = LY;
  Lx = LX;
  delay(100);
}
void loop()
{
}
