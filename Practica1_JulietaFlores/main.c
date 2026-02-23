#include <stdint.h>

// === MAPA DE MEMORIA ( RP2040 Datasheet ) ===

// 1. SUBSYSTEM RESETS ( Base : 0 x4000C000 )
// Controla que perifericos estan despiertos o dormidos .
#define RESETS_BASE 0x4000C000
#define RESETS_RESET (*(volatile uint32_t *) (RESETS_BASE + 0x0))
#define RESETS_DONE (*(volatile uint32_t *) (RESETS_BASE + 0x8))

// 2. IO BANK 0 ( Base : 0 x40014000 )
// Controla la funcion logica de los pines ( GPIO , UART , etc ) .
#define IO_BANK0_BASE 0x40014000
// El pin 16 tiene un offset de 0x084
// El pin 17 tiene un offset de 0x08c
// El pin 18 tiene un offset de 0x094
// El pin 19 tiene un offet de 0x09c
#define GPIO16_CTRL (*( volatile uint32_t *) (IO_BANK0_BASE + 0x084))
#define GPIO17_CTRL (*( volatile uint32_t *) (IO_BANK0_BASE + 0x08c))
#define GPIO18_CTRL (*( volatile uint32_t *) (IO_BANK0_BASE + 0x094))
#define GPIO19_CTRL (*( volatile uint32_t *) (IO_BANK0_BASE + 0x09c))

// 3. SINGLE - CYCLE IO ( SIO ) ( Base : 0 xD0000000 )
// Controla el estado alto / bajo de los pines de forma rapida .
#define SIO_BASE 0xD0000000
#define SIO_GPIO_OE (*(volatile uint32_t *) (SIO_BASE + 0x020)) // Output Enable
#define SIO_GPIO_OUT (*(volatile uint32_t *) (SIO_BASE + 0x010)) // Output Value

// Los pines que vamos a usar:
#define LED_PIN_16 16
#define LED_PIN_17 17
#define LED_PIN_18 18
#define LED_PIN_19 19


void espera(int t){
  for (volatile int x = 0; x < t; x ++) {
	  for (volatile int i = 0; i < 500000; i ++) ;
  }
}

// ---- Esta función muesta un número n 
void numero(int n){
  // Apagamos todos los GPIO
  SIO_GPIO_OUT &= 0;

  // Esperamos ~0.5 segundos
  espera(15);

  // Alineamos el número con el primer GPIO (el GPIO 16) y lo escribimos 
  SIO_GPIO_OUT |= (n  << LED_PIN_16);

  // Mostramos por ~1 segundos
  espera(30);
}

int main(){
  // --- PASO 1: BOOTSTRAPPING ( Despertar Hardware ) ---
  // Debemos quitar el Reset a dos componentes :
  // Bit 5: IO_BANK0 ( Logica de pines )
  // Bit 8: PADS_BANK0 ( Electricidad de pines )
  // Escribimos 0  IO_BANK0 en esos bits para sacarlos del reset .
  RESETS_RESET &= ~((1 << 5) | (1 << 8));

  // Esperamos hasta que el hardware confirme que desperto
  while ((RESETS_DONE & ((1 << 5) | (1 << 8))) != ((1 << 5) | (1 << 8)));

  // --- PASO 2: CONFIGURACION ---
  // Seleccionamos la Funcion 5 ( SIO - Software Control ) para los pines 16, 17, 18 y 19
  GPIO16_CTRL = 5;
  GPIO17_CTRL = 5;
  GPIO18_CTRL = 5;
  GPIO19_CTRL = 5;

  // Habilitamos los pines 16,17,18 y 19 como SALIDA en el SIO

  SIO_GPIO_OE |= (1 << LED_PIN_16);
  SIO_GPIO_OE |= (1 << LED_PIN_17);
  SIO_GPIO_OE |= (1 << LED_PIN_18);
  SIO_GPIO_OE |= (1 << LED_PIN_19);

  int num_cuenta[9] = {3,2,1,0,8,8,6,4,2};

  // --- PASO 3: BUCLE INFINITO ( Kernel Loop ) ---
  while (1) {
    // Cada número de mi número de cuenta debe ser mostrado
	  for(int i=0; i<9;i++){
      numero(num_cuenta[i]); 
	  }
  }
  return 0;
}
