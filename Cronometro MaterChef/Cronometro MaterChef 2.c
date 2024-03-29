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
#use delay(clock=4000000)

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
long int tempo=0;
int cont=0;
int flag_15=0;
int posiciona=0;
int sensor=0;
int pronto=0;
long int pos=0;

Void zera(){
   if(input(pin_b0)==0)sensor=1;
while(sensor==1){
   output_high(pin_d0);
   output_high(pin_d1);
   output_high(pin_d3);
   output_high(pin_d2);
   output_high(pin_d4);
   delay_ms(1);
   output_low(pin_d2); 
   output_low(pin_d4);
   delay_ms(1);
   if(input(pin_b0)==1)sensor=0;
   
   }
   sensor=0;
}

#int_ext
 
void Sinal(void){
zera();
cont=0;
disable_interrupts(INT_TIMER2);
}

#int_TIMER2
void  TIMER2_isr(void){
static long acumulador=2;//15=estouro 2s
static long segundo=0;
static int i=0;

   if(tempo!=0){
   tempo--;
   if(acumulador>0){
   acumulador--;
   }
   else{
   acumulador=2;
      if(i==0){
      output_high(pin_d2); 
      output_high(pin_d4);
      i=1;
      }
      else{
      output_low(pin_d2); 
      output_low(pin_d4);
      i=0;
      }
      }
   
   }
   else{
   cont=0;
   disable_interrupts(INT_TIMER2);
   output_low(pin_e0);//led 15
   output_low(pin_e1);//led 30
   output_low(pin_e2);//led 45
   
   }
}

//360�/1,8�=200 passos p volta
//motor 200 passo/rev
//drive div 1/8
//1600 passos/rev
//1 passo = 2 segundos

void main(void) {
setup_timer_2(T2_DIV_BY_16,255,16);//65,5ms
disable_interrupts(INT_TIMER2);
ext_int_edge(L_TO_H);      // init interrupt triggering for button press
enable_interrupts(INT_EXT);;

disable_interrupts(INT_CCP1);
setup_comparator(NC_NC_NC_NC);
setup_vref(FALSE);
set_tris_a(0b11111111);
set_tris_b(0b11000001);
set_tris_c(0b11111111);
set_tris_d(0b00000000);
set_tris_e(0b00000000);
output_low(pin_e0);
output_low(pin_e1);
output_low(pin_e2);
output_low(pin_d0);
enable_interrupts(GLOBAL);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Loop principal *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
   while(TRUE){
   
      if((input(pin_a0)==1)&&(cont==0)){
      tempo=30;//450=15 minutos
      output_high(pin_e0);//led 15
      output_low(pin_e1);//led 30
      output_low(pin_e2);//led 45
      output_high(pin_d0);//habilita drive
      output_high(pin_d1);//direcao 1
      output_high(pin_d3);//direcao 3     
      }
      
      if((input(pin_a1)==1)&&(cont==0)){
      tempo=60;//900=30 minutos
      output_low(pin_e0);//led 15
      output_high(pin_e1);//led 30
      output_low(pin_e2);//led 45
      output_high(pin_d0);//habilita drive
      output_high(pin_d1);//direcao 1
      output_high(pin_d3);//direcao 3
      }
      
      if((input(pin_a2)==1)&&(cont==0)){
      tempo=90;//900=45 minutos
      output_low(pin_e0);//led 15
      output_low(pin_e1);//led 30
      output_high(pin_e2);//led 45
      output_high(pin_d0);//habilita drive
      output_high(pin_d1);//direcao 1
      output_high(pin_d3);//direcao 3
      }
      
      if((input(pin_a4)==1)&&(cont==0)){
      cont=1;
      enable_interrupts(INT_TIMER2);
      }
      
      if((input(pin_a5)==1)&&(cont==0)){
      zera();
      }
   }
// FIM DO PROGRAMA
}

