/*******************************************************************************
*              Sistema de navega��o para rob�s aut�nomos
*                           Drive duplo PWM Servo
*                             Auto Robotica
*
* Cronometro Master Chef:   Marco de 2019                                Raul S F
********************************************************************************
********************************************************************************
* Historico
* Revisao 
* Revisao 
* Revisao 
********************************************************************************
*/

#include <16f877a.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Configura��es para grava��o *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD
#use delay(clock=20000000)


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Defini��o e inicializa��o dos port's *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#use fast_io(a)
#use standard_io(b)
#use fast_io(c)
#use fast_io(d)
//#use fast_io(b)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Defini��o e inicializa��o das vari�veis *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int tempo=0;
int cont=0;
int passo=0;
int flag_15=0;
int posiciona=0;

//Neste bloco est�o definidas as vari�veis globais do programa.
//Este programa n�o utiliza nenhuma vari�vel de usu�rio
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Constantes internas *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//A defini��o de constantes facilita a programa��o e a manuten��o.
//Este programa n�o utiliza nenhuma constante de usu�rio
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Declara��o dos flags de software *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//A defini��o de flags ajuda na programa��o e economiza mem�ria RAM.
//Este programa n�o utiliza nenhum flag de usu�rio

//360�/1,8�=200 passos p volta
//motor 200 passo/rev
//drive div 1/8
//1600 passos/rev
//1 passo = 2 segundos


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Configura��es do Microcontrolador *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void main ()
{
// configura CONFIG
setup_counters(RTCC_INTERNAL, WDT_2304MS);
// configura os TRIS
set_tris_a(0b00100000);
set_tris_b(0b00001111);
set_tris_c(0b10011001);
set_tris_d(0b00000000);
set_tris_e(0b00000000);
// inicializa os ports
porta=0x00; // limpa porta
portb=0x00; // limpa portb
portc=0x00; // limpa portc
portd=0x00; // limpa portd
porte=0x00; // limpa porte

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Loop principal *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
while(TRUE)
{
if((input(pin_a0)==1)&&(cont==0)){
tempo=15;
cont=1;
passo=15;
posiciona=1;
}
while(posiciona==1){
static long int poss=0;
   if(poss==0)poss=(passo*60);
   
}
}
// FIM DO PROGRAMA
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Fim do Programa *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
