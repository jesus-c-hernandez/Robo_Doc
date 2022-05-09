/**********************************************************************************
 * TITULO: Código ESP32 - FIREBASE
 * AUTOR: Jhimmy Astoraque Durán
 * DESCRIPCION: Este es el código del capítulo 6 de la serie ESP32 del canal
 * CANAL YOUTUBE: https://www.youtube.com/c/jadsatv
 * © 2020
 * *******************************************************************************/

#include <WiFi.h>
#include "FirebaseESP32.h"

// Credenciales wifi
#define WIFI_SSID "Mi 9T Pro"
#define WIFI_PASSWORD "Pollito_210"

// Credenciales Proyecto Firebase
#define FIREBASE_HOST "https://proyecto-final-sp-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "Yqd6Jx65dH0K6aEakfsUGg0a0WNEWF9vAyFj3AVg"

// Firebase Data object
FirebaseData firebaseData;

// Ruta en especifica del proyecto
String nodo = "/Robo_doc";

// Ruta del valor adelante
String adelantePath = "/adelante";
String adelanteValue = "0";

// Ruta del valor atras
String atrasPath = "/atras";
String atrasValue = "0";

// Ruta del valor derecha
String derechaPath = "/derecha";
String derechaValue = "0";

// Ruta del valor izquierda
String izquierdaPath = "/izquierda";
String izquierdaValue = "0";

// Constantes de los pines de salida
const int output18 = 18;
const int output19 = 19;
const int output21 = 21;
const int output22 = 22;

// ================== Variables globales =======================
// Variable iterator para los ciclos
boolean iterator = false;

void setup() 
{
  Serial.begin(115200);
  Serial.println();

  pinMode(output18, OUTPUT);
  digitalWrite(output18, LOW);

  pinMode(output19, OUTPUT);
  digitalWrite(output19, LOW);

  pinMode(output21, OUTPUT);
  digitalWrite(output21, LOW);

  pinMode(output22, OUTPUT);
  digitalWrite(output22, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectado al Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}


void loop() 
{
  //============= Inicio LECTURA Adelante =======================
  Firebase.getString(firebaseData, nodo + adelantePath);
  adelanteValue = firebaseData.stringData();
  //============= Fin LECTURA Adelante ==========================
  //================ Inicio LECTURA Atras =======================
  Firebase.getString(firebaseData, nodo + atrasPath);
  atrasValue = firebaseData.stringData();
  //================ Fin LECTURA Atras ==========================
  //============= Inicio LECTURA Derecha ========================
  Firebase.getString(firebaseData, nodo + derechaPath);
  derechaValue = firebaseData.stringData();
  //============= Fin LECTURA Derecha ===========================
    //============= Inicio LECTURA Izquierda ====================
  Firebase.getString(firebaseData, nodo + izquierdaPath);
  izquierdaValue = firebaseData.stringData();
  //============= Fin LECTURA Izquierda ==========================


  // ================== Inicio IF Adelante =======================
  if( adelanteValue == "1" ) {
    Serial.println("Adelante");
    digitalWrite(output18, HIGH);
  } else if ( adelanteValue == "0" ) {
    digitalWrite(output18, LOW);
  }
  // ===================== Fin IF Adelante =======================
  // ================== Inicio IF Atras ==========================
  if( atrasValue == "1" ) {
    Serial.println("Atras");
    digitalWrite(output19, HIGH);
  } else if ( atrasValue == "0" ) {
    digitalWrite(output19, LOW);
  }
  // ===================== Fin IF Atras =========================
  // ================== Inicio IF Derecha =======================
  if( derechaValue == "1" ) {
    Serial.println("Derecha");
    digitalWrite(output21, HIGH);
  } else if ( derechaValue == "0" ) {
    digitalWrite(output21, LOW);
  }
  // ===================== Fin IF Derecha ========================
  // ================== Inicio IF Izquierda ======================
  if( izquierdaValue == "1" ) {
    Serial.println("Izquierda");
    digitalWrite(output22, HIGH);
  }  else if ( izquierdaValue == "0" ) {
    digitalWrite(output22, LOW);
  }
  // ===================== Fin IF Izquierda ======================

  delay(20);
}