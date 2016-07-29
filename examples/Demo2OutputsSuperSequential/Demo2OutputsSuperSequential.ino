// based on http://www.efeitonerd.com.br/2012/09/super-sequencial-de-leds.html
#include "Arduino.h"
#include "IToOutputModule595.h"

const uint8_t qt_modules = 4; // 4 modules
IToOutputModule595 outs(2, 3, qt_modules); // (pino de data, pino de clock, quantidade de módulos)

int totalSaidas = 32; //Até 32 saídas com 4 registradores.
int totalSequencias = 10;

void setup() {
	outs.ResetAll(); // desliga todas as saidas
}

void loop() {
	for (int i=1; i<=totalSequencias; i++){
		for (int j=0; j<3; j++){
			sequencia(i);
		}
	}
}
//------------------------------
void sequencia(int s){
	switch (s){
	case 1:
		s1();
		break;
	case 2:
		s2();
		break;
	case 3:
		s3();
		break;
	case 4:
		s4();
		break;
	case 5:
		s5();
		break;
	case 6:
		s6();
		break;
	case 7:
		s7();
		break;
	case 8:
		s8();
		break;
	case 9:
		s9();
		break;
	case 10:
		s10();
		break;
	}
}

//------------------------------
void AcendeTodos(){
	for (int i = 0; i < totalSaidas; ++i){
		outs.SetOutput(i, HIGH);
	}
}

//------------------------------
void ApagaTodos(){
	for (int i = 0; i < totalSaidas; ++i){
		outs.SetOutput(i, HIGH);
	}
}

//------------------------------
void s1(){
	int t1 = 10;
	ApagaTodos();
	//Acende um por um.
	for (int i = 0; i < totalSaidas; ++i){
		outs.SetOutput(i, HIGH);
		delay(t1);
	}
	//Apaga um por um.
	for (int i = 0; i < totalSaidas; ++i){
		outs.SetOutput(i, LOW);
		delay(t1);
	}
}

//------------------------------
void s2(){
	int t1 = 10;
	ApagaTodos();
	//Acende um por um.
	for (int i = 0; i < totalSaidas; ++i){
		outs.SetOutput(i, HIGH);
		delay(t1);
	}
	//Apaga um por um.
	for (int i = 0; i < totalSaidas; ++i){
		outs.SetOutput(i, LOW);
		delay(t1);
	}
	//Acende um por um. (inverso)
	for (int i = totalSaidas - 1; i >= 0; --i){
		outs.SetOutput(i, HIGH);
		delay(t1);
	}
	//Apaga um por um. (inverso)
	for (int i = totalSaidas - 1; i >= 0; --i){
		outs.SetOutput(i, LOW);
		delay(t1);
	}
}

//------------------------------
void s3(){
	//ABRE E FECHA.
	int t1 = 10;
	ApagaTodos();
	for (int i = 0; i < totalSaidas / 2; ++i){
		outs.SetOutput(i, HIGH);
		outs.SetOutput(totalSaidas - 1 - i, HIGH);
		delay(t1);
	}
	for (int i=0; i<(totalSaidas/2)-1; i++){
		outs.SetOutput(i, LOW);
		outs.SetOutput(totalSaidas - 1 - i, LOW);
		delay(t1);
	}
	for (int i = (totalSaidas / 2) - 2; i >= 0; --i){
		outs.SetOutput(i, HIGH);
		outs.SetOutput(totalSaidas - 1 - i, HIGH);
		delay(t1);
	}
	for (int i = (totalSaidas / 2) - 1; i > 0; --i){
		outs.SetOutput(i, LOW);
		outs.SetOutput(totalSaidas - 1 - i, LOW);
		delay(t1);
	}
}

//------------------------------
void s4(){
	//POLÍCIA
	int t1 = 1;
	ApagaTodos();
	//Lado 1 acesso. (piscando)
	for (int j = 0; j < totalSaidas / 4; ++j){
		for (int i = 0; i < totalSaidas / 2; ++i){
			outs.SetOutput(i, HIGH);
		}
		delay(t1);
		for (int i=0; i<totalSaidas/2; i++){
			outs.SetOutput(i, LOW);
		}
		delay(t1);
	}
	//Lado 2 acesso. (piscando)
	for (int j = 0; j < totalSaidas / 4; ++j){
		for (int i = totalSaidas / 2; i < totalSaidas; ++i){
			outs.SetOutput(i, HIGH);
		}
		delay(t1);
		for (int i = totalSaidas / 2; i < totalSaidas; ++i){
			outs.SetOutput(i, LOW);
		}
		delay(t1);
	}
}

//------------------------------
void s5(){
	//FLASHS UM POR UM
	int t1 = 5;
	int t2 = 50;
	ApagaTodos();
	for (int i = 0; i < totalSaidas; ++i){
		outs.SetOutput(i, HIGH);
		delay(t1);
		outs.SetOutput(i, LOW);
		delay(t2);
	}
}

//------------------------------
void s6(){
	//FLASHS RANDOMICOS
	randomSeed(analogRead(0));  //Para o random nao repetir a sequencia.
	int t1 = 10;
	int t2 = 40;
	int p = random(totalSaidas);
	ApagaTodos();
	for (int i = 0; i < 35; ++i){
		outs.SetOutput(p, HIGH);
		delay(t1);
		outs.SetOutput(p, LOW);
		delay(t2);
		p = random(totalSaidas);
	}
}

//------------------------------
void s7(){
	int t1 = 1;
	for (int i=0; i<2; i++){
		AcendeTodos();
		delay(t1);
		ApagaTodos();
		delay(500);
	}
}

//------------------------------
void s8(){
	//CORRE NUM EFEITO MEIO 3D. :)
	int t1 = 10;
	ApagaTodos();
	for (int i=1; i<totalSaidas; i++){
		outs.SetOutput(i - 2, LOW);
		outs.SetOutput(i - 1, LOW);
		outs.SetOutput(i, HIGH);
		delay(t1);
		outs.SetOutput(i, LOW);
		outs.SetOutput(i - 1, HIGH);
		delay(t1);
	}
}

//------------------------------
void s9(){
	int t1 = 100;
	for (int x=0; x<3; x++){
		for (int i=0; i<totalSaidas; i++){
			if (i%2 == 0){
				outs.SetOutput(i, HIGH);
			}
			else{
				outs.SetOutput(i, LOW);
			}
		}
		delay(t1);
		for (int i=0; i<totalSaidas; i++){
			if (i%2 == 0){
				outs.SetOutput(i, LOW);
			}
			else{
				outs.SetOutput(i, HIGH);
			}
		}
		delay(t1);
	}
}

//------------------------------
void s10(){
	int t1 = 3;
	int t2 = 100;
	ApagaTodos();
	delay(t2);
	for (int x=0; x<totalSaidas; x++){
		for (int i=0; i<totalSaidas-x; i++){
			if (i != 0){
				outs.SetOutput(i - 1, LOW);
			}
			outs.SetOutput(i, HIGH);
			delay(t1);
		}
	}
	delay(t1);
	outs.SetOutput(0, HIGH);

	delay(t2);
	for (int x=0; x<totalSaidas; x++){
		for (int i=0; i<totalSaidas-x; i++){
			if (i != 0){
				outs.SetOutput(i - 1, HIGH);
			}
			outs.SetOutput(i, LOW);
			delay(t1);
		}
	}
	delay(t1);
	outs.SetOutput(0, LOW);
	delay(t1);
}
