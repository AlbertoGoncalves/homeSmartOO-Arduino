/*
Mais tutoriais em http://viciadosemarduino.blogspot.com.br/
grupo no whatsApp "Viciados em Arduino" des de 27/04/2014
WhatsAppp +55 66 9691-3568
*/

int Columnas[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 22, 23};	 
int Filas[] = {A0, A2, A3, A4};

int RandFila;     //Variable para fila aleatoria
int RandColumna;  //Variable para columna aleatoria
	 
void setup()
{
int contador;
	 
for (int contador = 0; contador < 17; contador++){
	pinMode(Columnas[contador], OUTPUT); }
	 
for (int contador = 0; contador < 5; contador++){
	pinMode(Filas[contador], OUTPUT); }
}
	 
void loop()
{
RandLed();
}
	 
void RandLed()
{
RandFila = random(0,4);
RandColumna = random(0,16);
	 
digitalWrite(Filas[RandFila], HIGH);
digitalWrite(Columnas[RandColumna], HIGH);
	 
delay(50);
	 
digitalWrite(Filas[RandFila], LOW);
digitalWrite(Columnas[RandColumna], LOW);
	 
delay(70);
}
