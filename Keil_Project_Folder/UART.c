#include "tm4c123gh6pm.h"
#include "Bit_Utilies.h"
#include "UART.h"
#include "GPIO.h"

// UART5 INIT

void UART_init(){
				
    SYSCTL_RCGCUART_R |= 0x04; // CLOCK --> UART2
		SYSCTL_RCGCGPIO_R |= 0x08; // CLOCK --> PORTD
		while((SYSCTL_PRGPIO_R & 0x08) == 0){};
		GPIO_PORTD_AFSEL_R |= 0xC0;  // Enable alt function
		GPIO_PORTD_DEN_R |= 0xC0;
		GPIO_PORTD_AMSEL_R &= ~0xC0; // Disable analog on PD6, PD7
		GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & ~0xFF000000) | (0x11000000); // PD6, PD7 = U2RX, U2TX
	
	  CLR (UART2_CTL_R ,UART_CTL_UARTEN); // DISABLE UART
			
		UART2_IBRD_R = 104 ; // 104
    UART2_FBRD_R = 11 ; // (0.1667*64)+0.5
			
 	  while((SYSCTL_PRUART_R & 0x04) == 0){};  //this line
    
	
    
	
    SET(UART2_LCRH_R,UART_LCRH_WLEN_8); // WORDLENGTH = 3 (8bits)
    SET(UART2_LCRH_R,UART_LCRH_FEN); // FIFO ENABLE

	
		UART2_CTL_R |= UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE; //RE-ENABLE UART2, RX, TX
	  //SELECT TYPE OF ALTERNATE FUNC
	  
    
        // Digital enable on PD6, PD7
    
	
		
}
int UART_IsCharAvail()
{
   return ( ( UART2_FR_R & UART_FR_RXFE ) == 0 );
}

	// GET CHAR
char UART_GetChar() {
while( (UART2_FR_R & UART_FR_RXFE) != 0);
return (char) GET_REG(UART2_DR_R); //#0xff
}	
