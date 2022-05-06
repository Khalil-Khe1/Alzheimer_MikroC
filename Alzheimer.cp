#line 1 "C:/Personal Files/Proteus Simulations/Alzheimer/Alzheimer.c"
#line 1 "c:/program files/mikroc/mikroc pro for pic/include/stdio.h"
#line 1 "c:/program files/mikroc/mikroc pro for pic/include/stdlib.h"







 typedef struct divstruct {
 int quot;
 int rem;
 } div_t;

 typedef struct ldivstruct {
 long quot;
 long rem;
 } ldiv_t;

 typedef struct uldivstruct {
 unsigned long quot;
 unsigned long rem;
 } uldiv_t;

int abs(int a);
float atof(char * s);
int atoi(char * s);
long atol(char * s);
div_t div(int number, int denom);
ldiv_t ldiv(long number, long denom);
uldiv_t uldiv(unsigned long number, unsigned long denom);
long labs(long x);
int max(int a, int b);
int min(int a, int b);
void srand(unsigned x);
int rand();
int xtoi(char * s);
#line 1 "c:/program files/mikroc/mikroc pro for pic/include/string.h"





void * memchr(void *p, char n, unsigned int v);
int memcmp(void *s1, void *s2, int n);
void * memcpy(void * d1, void * s1, int n);
void * memmove(void * to, void * from, int n);
void * memset(void * p1, char character, int n);
char * strcat(char * to, char * from);
char * strchr(char * ptr, char chr);
int strcmp(char * s1, char * s2);
char * strcpy(char * to, char * from);
int strlen(char * s);
char * strncat(char * to, char * from, int size);
char * strncpy(char * to, char * from, int size);
int strspn(char * str1, char * str2);
char strcspn(char * s1, char * s2);
int strncmp(char * s1, char * s2, char len);
char * strpbrk(char * s1, char * s2);
char * strrchr(char *ptr, char chr);
char * strstr(char * s1, char * s2);
char * strtok(char * s1, char * s2);
#line 7 "C:/Personal Files/Proteus Simulations/Alzheimer/Alzheimer.c"
sbit LCD_RS at RD4_bit;
sbit LCD_EN at RD5_bit;
sbit LCD_D4 at RD0_bit;
sbit LCD_D5 at RD1_bit;
sbit LCD_D6 at RD2_bit;
sbit LCD_D7 at RD3_bit;

sbit LCD_RS_Direction at TRISD4_bit;
sbit LCD_EN_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD0_bit;
sbit LCD_D5_Direction at TRISD1_bit;
sbit LCD_D6_Direction at TRISD2_bit;
sbit LCD_D7_Direction at TRISD3_bit;

unsigned int adc;
int i;
int aux;
int timer;
char str[2];
char med[2][20];
char lcdstr[30];

void interrupt(){
 INTCON.INTF=0;
 for(i = 0; i < 6; i++){
 PORTC.RC0 =~ PORTC.RC0;
 Delay_ms(500);
 }

}

void main() {

 TRISA = 0xFF;
 OPTION_REG.INTEDG = 1;
 INTCON.GIE = 1;
 INTCON.INTE = 1;
 TRISB1_bit = 1;
 TRISB4_bit = 1;
 TRISB5_bit = 1;
 TRISC = 0;

 ADC_Init();
 adc = 0;
 aux = 0;
 timer = 0;


 strcpy(med[0], "Ebixa 10mg 2/J");
 strcpy(med[1], "Aricept 10mg 3/J");
 for(i = 0; i < 14; i++){
 EEPROM_Write(0x02 + i, med[0][i]);
 aux = 0x02 + i;
 }
 for(i = 0; i < 16; i++){
 EEPROM_Write(aux + i + 1, med[1][i]);
 }
 aux = 0;

 PORTC.RC0 = 0x00;

 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 while(1){
 adc = (ADC_Read(0) / 2) - 1;
 PORTC.RC0 = 0x00;
 ByteToStr(adc, str);
 if(PORTB.B1 == !aux){
 Lcd_Cmd(_LCD_CLEAR);
 aux = PORTB.B1;
 if((timer != 3)&&(timer != 8)){
 Lcd_Out(1, 1, "Ghassen");
 Lcd_Out(2, 1, "Have a good time.");
 }
 if(timer == 3){
 Lcd_Out(1, 1, "Temperature");
 Lcd_Out(2, 1, str);
 }
 if(timer == 8){
 for(i = 0; i < 14; i++){
 lcdstr[i] = EEPROM_Read(0x02 + i);
 aux = 0x02 + i;
 }
 Lcd_Out(1, 1, lcdstr);
 for(i = 0; i < 16; i++){
 lcdstr[i] = EEPROM_Read(aux + i + 1);
 }
 Lcd_Out(2, 1, lcdstr);
 aux = PORTB.B1;
 timer = -1;
 }
 timer++;
 }
 if(PORTB.B4 == 0){
 PORTC.RC3 = 1;
 PORTC.RC4 = 0;
 Delay_ms(2000);
 PORTC.RC3 = 0;
 }
 else if(PORTB.B5 == 0){
 PORTC.RC3 = 0;
 PORTC.RC4 = 1;
 Delay_ms(2000);
 PORTC.RC4 = 0;
 }
 }
}
