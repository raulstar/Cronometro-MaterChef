/*******************************************************************************
*              Sistema de navegaï¿½ï¿½o para robï¿½s autï¿½nomos
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
* Configurações para gravação *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#FUSES NOWDT, HS, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD
#use delay(clock=4000000)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Definição e inicialização dos port's *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#use fast_io(a)
#use standard_io(b)
#use fast_io(c)
#use fast_io(d)
//#use fast_io(b)

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Definição e inicialização das variáveis *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
long int tempo=0;
int cont=0;
int sensor1=0;
int sensor2=0;


Void zera(){
   if(input(pin_b0)==0)sensor1=1;
   if(input(pin_b1)==0)sensor2=1;
   
while((sensor1==1)||(sensor2==1)){
   if(sensor1==1){
   output_high(pin_d0);
   output_high(pin_d1);
   output_high(pin_d3);
   output_high(pin_d2);//pulso motor1
   delay_us(300);
   output_low(pin_d2);//pulso motor1 
   delay_us(300);    
   if(input(pin_b0)==1)sensor1=0;
   }
   if(sensor2==1){
   output_high(pin_d0);
   output_high(pin_d1);
   output_high(pin_d3);
   output_high(pin_d4);//pulso motor2
   delay_us(300);
   output_low(pin_d4);//pulso motor2
   delay_us(300);      
   if(input(pin_b1)==1)sensor2=0;
   }
   }
}

#int_ext
 
void Sinal(void){
zera();
cont=0;
disable_interrupts(INT_TIMER2);
output_low(pin_e0);//led 15
   output_low(pin_e1);//led 30
   output_low(pin_e2);//led 45
   output_low(pin_c0);//led 60
   output_low(pin_c1);//led 120
   output_low(pin_c2);//led 180
}

#int_TIMER2
void  TIMER2_isr(void){
static long acumulador=15;//15=estouro 2s
static int i=0;

   if(tempo!=0){   
   if(acumulador>0){
   acumulador--;
   }
   else{
   tempo--;
   acumulador=15;
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
   output_low(pin_d0);//habilita drive
   output_low(pin_e0);//led 15
   output_low(pin_e1);//led 30
   output_low(pin_e2);//led 45
   output_low(pin_c0);//led 60
   output_low(pin_c1);//led 120
   output_low(pin_c2);//led 180
   
   }
}

//360°/1,8º=200 passos p volta
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
set_tris_c(0b11111000);
set_tris_d(0b00000000);
set_tris_e(0b00000000);
output_low(pin_e0);
output_low(pin_e1);
output_low(pin_e2);
output_low(pin_d0);
output_low(pin_c0);
output_low(pin_c1);
output_low(pin_c2);
enable_interrupts(GLOBAL);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Loop principal *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
   while(TRUE){
   
      if((input(pin_a0)==1)&&(cont==0)){
      tempo=15;//450=15 minutos
      output_high(pin_e0);//led 15     
      }
      
      if((input(pin_a1)==1)&&(cont==0)){
      tempo=30;//1800=30 minutos
      output_high(pin_e1);//led 30
      }
      
      if((input(pin_a2)==1)&&(cont==0)){
      tempo=45;//4700=45 minutos
      output_high(pin_e2);//led 45
      }
      
      if((input(pin_a3)==1)&&(cont==0)){
      static int acum=0;
      
      if(acum==3){
      acum=0;
      }
      if(acum==2){
      tempo=180;//10800=180 minutos
      acum=3;
      output_low(pin_c0);//led 180
      output_low(pin_c1);//led 180
      output_high(pin_c2);//led 180
      delay_ms(600); 
      }
  
      if(acum==1){
      tempo=120;//7200=120 minutos
      acum=2;
      output_low(pin_c0);//led 120
      output_high(pin_c1);//led 120
      output_low(pin_c2);//led 120
      delay_ms(600); 
      }
      if(acum==0){
      tempo=60;//3600=60 minutos
      acum=1;
      output_high(pin_c0);//led 60
      output_low(pin_c1);//led 60
      output_low(pin_c2);//led 60      
      delay_ms(600);
      }
      
      }
      
      if((input(pin_a4)==1)&&(cont==0)){
      cont=1;
      output_high(pin_d0);//habilita drive
      output_high(pin_d1);//direcao 1
      output_high(pin_d3);//direcao 3 
      enable_interrupts(INT_TIMER2);
      }
      
      if((input(pin_a5)==1)&&(cont==0)){
      zera();
      }
   }
// FIM DO PROGRAMA
}

