#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/exception.h"
#include "scheduler.h"

// Registros de control del SysTick (Timer de hardware integrado en ARM Cortex-M)
#define SYSTICK_CTRL (*(volatile uint32_t *)0xE000E010)
#define SYSTICK_LOAD (*(volatile uint32_t *)0xE000E014)
#define SYSTICK_VAL  (*(volatile uint32_t *)0xE000E018)


// Wrappers de Ensamblador (Manejadores de excepciones)
extern void wrapper_svc(void);
extern void isr_pendsv(void);

// Prototipos de las tareas de usuario (definidas en user_app.c)
extern void subsystem1(void);
extern void subsystem2(void);
extern void subsystem3(void);
extern void subsystem4(void);
extern void subsystem5(void);

// Semáforos del kernel
semaphore_t sem_radio = { .count = 1, .head = 0, .tail = 0 };
semaphore_t sem_energia = { .count = 3, .head = 0, .tail = 0 };


int main() {
    // 1. Inicializar I/O Estándar (Habilita printf y lectura por cable USB)
    stdio_init_all();


    // 2. Registrar los manejadores de Excepciones del Sistema Operativo
    // SVC (ID 11) maneja las Syscalls solicitadas por las tareas
    exception_set_exclusive_handler((enum exception_number)11, wrapper_svc);
    // PendSV (ID 14) maneja el Cambio de Contexto asíncrono
    exception_set_exclusive_handler((enum exception_number)14, isr_pendsv);

    // 3. Inicializar el Process Stack Pointer (PSP) a 0.
    // Esto le avisa al ensamblador que iniciamos en modo Idle (sin tareas de usuario previas)
    __asm volatile ("msr psp, %0" : : "r" (0));

    // 4. Registrar tareas en el Scheduler (inician en estado DORMANT, esperando al usuario)
    task_create(0, subsystem1);
    task_create(1, subsystem2);
    task_create(2, subsystem3);
    task_create(3, subsystem4);
    task_create(4, subsystem5);


  
  


    // 5. Configurar e iniciar SysTick
    // Para un reloj de 125MHz, contar 1,250,000 ciclos equivale a 10 milisegundos
    SYSTICK_LOAD = 1250000 - 1; 
    SYSTICK_VAL = 0;
    // 0x07 = Habilita el Timer, habilita la Interrupción, y usa la fuente de reloj principal
    SYSTICK_CTRL = 0x07; 

    // Esperar la conexión 
    while (!stdio_usb_connected()) {
        printf("Esperando conexión USB...\n");
        for(volatile int i=0; i < 1000000; i++){
            for (volatile int j=0; j < 100; j++);
        }
    }
    printf("Conexión USB establecida.\n");

    printf("Kernel de la Practica 5 Iniciado.\n");
    printf("Envia 1, 2, 3 o 4 por la terminal USB para encolar tareas.\n");
    // 6. Bucle Idle (El sistema descansa hasta que SysTick lo despierte)
    while (1) {
        __asm volatile ("wfi"); // Wait For Interrupt (Detiene el reloj del CPU para ahorrar energía)
    }

    return 0;
}