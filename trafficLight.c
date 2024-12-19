#define NS_RED    (1 << 5) 
#define NS_YELLOW (1 << 4) 
#define NS_GREEN  (1 << 3) 
#define EW_RED    (1 << 2) 
#define EW_YELLOW (1 << 1) 
#define EW_GREEN  (1 << 0) 

#define GREEN_DURATION 500
#define YELLOW_DURATION 200
#define RED_DURATION 500
#define RED_OVERLAP_DURATION 500

#define DDRB *((volatile unsigned char*)0x24)
#define PORTB *((volatile unsigned char*)0x25)

void delay_ms(unsigned long ms) {
    volatile unsigned long i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 800; j++) {
        }
    }
}

int main() {
    DDRB = 0xFF;

    while (1) {
      
      	//NS: RED | EW: RED
      	PORTB = NS_RED | EW_RED;
        delay_ms(RED_DURATION);
      
      	//NS: RED & YELLOW | EW: RED
      	PORTB = NS_RED | NS_YELLOW | EW_RED;
      	delay_ms(YELLOW_DURATION);
      
      	//NS: GREEN | EW: RED
      	PORTB = NS_GREEN | EW_RED;
        delay_ms(GREEN_DURATION);
      
      	//NS: GREEN & YELLOW | EW: RED
      	PORTB = NS_GREEN | NS_YELLOW | EW_RED;
        delay_ms(YELLOW_DURATION);
      
      	//NS: RED | EW: RED (OVERLAP DURATION)
      	PORTB = NS_RED | EW_RED;
      	delay_ms(RED_OVERLAP_DURATION);
      
      	//NS: RED | EW: RED & YELLOW
      	PORTB = NS_RED | EW_RED | EW_YELLOW;
      	delay_ms(YELLOW_DURATION);
      
      	//NS: RED | EW: GREEN
      	PORTB = NS_RED | EW_GREEN;
      	delay_ms(GREEN_DURATION);
      
      	//NS: RED | EW: GREEN & YELLOW
      	PORTB = NS_RED | EW_GREEN | EW_YELLOW;
      	delay_ms(YELLOW_DURATION);
      
    }
}
