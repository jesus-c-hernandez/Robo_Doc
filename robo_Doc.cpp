/**********************************************************************************
 * TITULO: Código Robo-Doc (Sistemas Programables)
 * AUTORES:   Jesus Saul Castañeda Hernandez
 *            Jaime Daniel Cruz Bustamante
 *            Citlaly Carolina Medina Gonzales
 *            Eli Uziel Montes Perez
 *            Carlos Eduardo Davila Silva
 *            Beto
 * DESCRIPCION: Este es el codigo del proyecto final de la materia de sistemas
 *              programables (Robo Doc) impartida por la Ing. Lamia Hamdam en el
 *              Instituto Tecnologico de la Laguna
 * © 2022
 * *******************************************************************************/

// ==================================== Librerias ===============================
#include <WiFi.h>
#include "FirebaseESP32.h"

// ============================================================================
// ==================================== Credenciales ===============================
// Credenciales wifi
//#define WIFI_SSID "Mi 9T Pro"
//#define WIFI_PASSWORD "Pollito_210"

#define WIFI_SSID "HUAWEI-2105WC"
#define WIFI_PASSWORD "asdasd123"

// Credenciales base de datos Firebase
#define FIREBASE_HOST "https://proyecto-final-sp-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "Yqd6Jx65dH0K6aEakfsUGg0a0WNEWF9vAyFj3AVg"
// ============================================================================
// ============================ Nodos y Rutas de Firebase =======================

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

// ============================================================================
// ================== Constantes de los pines de salida =======================
// Constantes de los pines de salida del lado izquierdo
const int out18 = 18; // Pin que controla el sentido del giro del lado A
const int out19 = 19; // Pin que controla el sentido del giro del lado A
const int ena21 = 21; // Pin que controla la velocidad del lado A

// Constantes de los pines de salida del lado derecho
const int out12 = 12; // Pin que controla el sentido del giro del lado B
const int out13 = 13; // Pin que controla el sentido del giro del lado B
const int ena14 = 14; // Pin que controla la velocidad del lado B

// ============================================================================
// ========================= Variables globales ==============================

// ============================================================================
// ================================== Setup ===================================
void setup()
{
  Serial.begin(115200);
  Serial.println();

  // Modos de pin del lado A
  pinMode(out18, OUTPUT);
  pinMode(out19, OUTPUT);
  pinMode(ena21, OUTPUT);

  // Modos de pin del lado B
  pinMode(out12, OUTPUT);
  pinMode(out13, OUTPUT);
  pinMode(ena14, OUTPUT);

  // Conexion del modulo a la red WIFI
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
  // Se imprime la direccion IP
  Serial.println(WiFi.localIP());

  // Conexion a la base de datos de Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}
// ============================================================================
// ================================== Loop ===================================
void loop()
{
  int direccion = lecturaDatos(); // Lectura de datos de firebase para el movimiento

  if (direccion != 0) 
    switch (direccion)
    {
    case 1:
      adelante(40);
      break;
      case 2:
      atras(40);
      break;
      case 3:
      giroDerecha(40);
      break;
      case 4:
      giroIzquierda(40);
      break;
    default:
      break;
    }

  delay(20);
}
// ============================================================================
// =============================== Lectura Datos ==============================
int lecturaDatos()
{
  //============= Inicio LECTURA Adelante =======================
  Firebase.getString(firebaseData, nodo + adelantePath);
  adelanteValue = firebaseData.stringData();
  if (adelanteValue == 1)
    return 1;
  //============= Fin LECTURA Adelante ==========================
  //================ Inicio LECTURA Atras =======================
  Firebase.getString(firebaseData, nodo + atrasPath);
  atrasValue = firebaseData.stringData();
  if (atrasValue == 1)
    return 2;
  //================ Fin LECTURA Atras ==========================
  //============= Inicio LECTURA Derecha ========================
  Firebase.getString(firebaseData, nodo + derechaPath);
  derechaValue = firebaseData.stringData();
  if (derechaValue == 1)
    return 3;
  //============= Fin LECTURA Derecha ===========================
  //============= Inicio LECTURA Izquierda ====================
  Firebase.getString(firebaseData, nodo + izquierdaPath);
  izquierdaValue = firebaseData.stringData();
  if (izquierdaValue == 1)
    return 4;
  //============= Fin LECTURA Izquierda ==========================
  return 0;
}
// ============================================================================
// ============================== Funcion adelante ============================
void adelante(int speed)
{
  // ====================== Giro a la derecha (adelante) del lado A =================
  digitalWrite(ena21, speed); // Velocidad del lado A
  digitalWrite(out18, HIGH);
  digitalWrite(out19, LOW);
  // ============================================================================
  // ====================== Giro a la izquierda (adelante) del lado B ==============
  digitalWrite(ena14, speed); // Velocidad del lado B
  digitalWrite(out12, LOW);
  digitalWrite(out13, HIGH);
  // ============================================================================
}
// ============================================================================
// ================================= Funcion atras ===============================
void atras(int speed)
{
  // ======================= Giro a la izquierda (atras) del lado A =================
  digitalWrite(ena21, speed); // Velocidad del lado A
  digitalWrite(out18, LOW);
  digitalWrite(out19, HIGH);
  // ============================================================================
  // ======================== Giro a la derecha (atras) del lado B =================
  digitalWrite(ena14, speed); // Velocidad del lado B
  digitalWrite(out12, HIGH);
  digitalWrite(out13, LOW);
  // ============================================================================
}
// ============================================================================
// ================================= Funcion derecha ===============================
void giroDerecha(int speed)
{
  // ======================= Giro a la izquierda (atras) del lado A =================
  digitalWrite(ena21, speed); // Velocidad del lado A
  digitalWrite(out18, LOW);
  digitalWrite(out19, HIGH);
  // ============================================================================
  // =====================Giro a la izquierda (adelante) del lado B ==============
  digitalWrite(ena14, speed); // Velocidad del lado B
  digitalWrite(out12, LOW);
  digitalWrite(out13, HIGH);
  // ============================================================================
}
// ==============================================================================
// =============================== Funcion izquierda =============================
void giroIzquierda(int speed)
{
  // ====================== Giro a la derecha (adelante) del lado A =================
  digitalWrite(ena21, speed); // Velocidad del lado A
  digitalWrite(out18, HIGH);
  digitalWrite(out19, LOW);
  // ============================================================================
  // ======================== Giro a la derecha (atras) del lado B =================
  digitalWrite(ena14, speed); // Velocidad del lado B
  digitalWrite(out12, HIGH);
  digitalWrite(out13, LOW);
  // ============================================================================
}
// ==============================================================================
