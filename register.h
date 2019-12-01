/**************************Lab1***************************************/
#define EXIT_SUCCESS 0
#define TATORIS 0x1
#define ENABLE_TIMER_0 0x00000001
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // Port F Clock Gating Control
#define RED 0x02
#define GREEN 0x08
#define BLUE 0x04
#define YELLOW 0xA
#define LIGHT_BLUE 0xC
#define VIOLET 0x6
#define WHITE 0xE
#define GPIO_LOCK               (*((volatile unsigned long *)0x40025520))

//Task 1
#define GPIO_LOCK_KEY            0x4C4F434B  // Unlocks the GPIO_CR register
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))

//Task 2
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))

/*****************************Lab2*************************************/

//Task 1


#define RCGC_TIMER              (*((volatile unsigned long *)0x400FE604))


//Timer 0
#define GPTM_CTL_0_R            (*((volatile unsigned long *)0x4003000C))
#define GPTM_CFG_0_R              (*((volatile unsigned long *)0x40030000))
#define GPTM_TAMR_0_R             (*((volatile unsigned long *)0x40030004))
#define GPTM_TAILR_0_R            (*((volatile unsigned long *)0x40030028))



#define GPTM_IMR_R              (*((volatile unsigned long *)0x40030018))
#define GPTM_RIS                (*((volatile unsigned long *)0x4003001C))
#define GPTM_ICR_R              (*((volatile unsigned long *)0x40030024))

#define EN0                     (*((volatile unsigned long *)0xE000E100))
#define EN0_TIMER               (*((volatile unsigned long *)0xE000E08C))
#define EN0_PORT_F              (*((volatile unsigned long *)0xE000E0B8))

//button
#define GPIO_F_ICR              (*((volatile unsigned long *)0x4002541C))
#define GPIO_A_ICR              (*((volatile unsigned long *)0x4000541C))
#define DIS_19                  (*((volatile unsigned long *)0xE000E180))
#define GPIOIM                  (*((volatile unsigned long *)0x40025410))

/********************Lab 3*****************************/

//Task 1\
//Phase-locked loop config
#define RCC                     (*((volatile unsigned long *)0x400FE060))
#define RCC2                    (*((volatile unsigned long *)0x400FE070))
#define RCGCADC                 (*((volatile unsigned long *)0x400FE638))

//ADC config
#define ADCACTSS                (*((volatile unsigned long *)0x40038000))

//#define ADCSSMUX                (*((volatile unsigned long *)0x40038040))
#define ADCEMUX                 (*((volatile unsigned long *)0x40038014))
#define ADCSSMUX3               (*((volatile unsigned long *)0x400380A0))
#define ADCSSCTL3              (*((volatile unsigned long *)0x400380A4))
#define ADCPSSI                 (*((volatile unsigned long *)0x40038028))
//ADC interrupt
#define ADCRIS                  (*((volatile unsigned long *)0x40038004))
#define ADCSSFIFO3              (*((volatile unsigned long *)0x400380A8))
#define ADCIM                   (*((volatile unsigned long *)0x40038008))
#define ADCISC                  (*((volatile unsigned long *)0x4003800C))
#define RIS                     (*((volatile unsigned long *)0x400FE050))



//Lab 3 task 2
#define SYSCTL_RCGCUART_R       (*((volatile unsigned long *)0x400FE618))
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
#define UART0_CTL_R             (*((volatile unsigned long *)0x4000C030))
#define UART0_IBRD_R            (*((volatile unsigned long *)0x4000C024))
#define UART0_FBRD_R            (*((volatile unsigned long *)0x4000C028))

#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))

#define UART0_LCRH_R            (*((volatile unsigned long *)0x4000C028))
#define UARTCC                  (*((volatile unsigned long *)0x4000CFC8))
#define UARTLCRH                (*((volatile unsigned long *)0x4000C02C))

#define UARTFR                  (*((volatile unsigned long *)0x4000C018))
#define UARTDR                  (*((volatile unsigned long *)0x4000C000))

