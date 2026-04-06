#include <stdint.h>
#include <stdio.h> // Has printf
#include "syscalls.h"

/* Pin Definitions */
#define LED_0 16
#define LED_1 17
#define LED_2 18
#define LED_3 19
#define LED_4 20
#define HEATING_CYCLES 6250000/3u // Aproximadamente 0.5 segundos 

/**
 * @brief Busy-wait for an exact number of core cycles.
 * @param cycles Number of cycles to delay.
 */
static inline void delay_cycles_exact(uint32_t cycles)
{
    __asm volatile(
        "1: \n"
        "sub %[c], %[c], #1 \n" // 1 cycle
        "bne 1b \n"             // 1-3 cycles (depends on branch)
        : [c] "+r"(cycles)
        :
        : "cc");
}

/**
 * @brief Print a string slowly, character by character.
 * @param str The string to print.
 */
void slow_print(const char *str)
{
    while (*str)
    {
        printf("%c", *str++);
        delay_cycles_exact(HEATING_CYCLES/100);  
    }
}


/**
 * @brief Configure LED GPIOs as outputs.
 */
void setup_leds(void)
{
    sys_gpio_dir(LED_0, 1);
    sys_gpio_dir(LED_1, 1);
    sys_gpio_dir(LED_2, 1);
    sys_gpio_dir(LED_3, 1);
    sys_gpio_dir(LED_4, 1);
}

/**
 * @brief Subsystem 1 task.
 */
void subsystem1(void)
{
    sys_gpio_dir(LED_0, 1);

     while (1) {
       sys_sem_wait(&sem_energia);
        sys_gpio_set(LED_0, 1);
        delay_cycles_exact(HEATING_CYCLES);
        sys_gpio_set(LED_0, 0);
        sys_sem_post(&sem_energia);
        
        sys_sem_wait(&sem_radio);
       // slow_print("[SUBSISTEMA 1] Calentamiento finalizado. Operacion nominal alcanzada. El subsistema ha completado exitosamente la fase de estabilizacion termica y se encuentra listo para iniciar la transmision de datos hacia la estacion terrestre. En este momento se estan recopilando metricas internas como temperatura de los modulos, niveles de voltaje en los circuitos principales, consumo energetico acumulado y estado general de los sensores. Adicionalmente, se estan ejecutando rutinas de verificacion para asegurar la integridad de los datos antes de su envio, incluyendo el calculo de checksums, validacion de buffers de memoria y sincronizacion de relojes internos del sistema. El modulo de comunicaciones ha establecido un enlace estable con la estacion base, y se estan ajustando dinamicamente los parametros de transmision para optimizar el ancho de banda disponible y minimizar la latencia. Durante este proceso, se monitorean continuamente posibles interferencias externas, variaciones en la señal y errores de transmision, aplicando mecanismos de correccion cuando es necesario. Asimismo, el sistema activa protocolos de redundancia que permiten reenviar paquetes perdidos y garantizar que la informacion critica llegue completa a su destino. Se mantiene un registro detallado de todas las operaciones realizadas, el cual sera almacenado en memoria no volatil para futuras auditorias del sistema. Finalmente, el subsistema reporta que se encuentra operando dentro de los parametros nominales establecidos y listo para continuar con las siguientes fases de la mision en orbita terrestre baja...\n");
        slow_print("[SUBSISTEMA 1] Calentamiento finalizado. Operación nominal alcanzada. Transfiriendo paquetes de telemetría y reportando estado actual a base terrestre...\n"); 
        sys_sem_post(&sem_radio);

    }
}

/**
 * @brief Subsystem 2 task.
 */
void subsystem2(void)
{
    sys_gpio_dir(LED_1, 1);

    while (1) {
        sys_sem_wait(&sem_energia);
        sys_gpio_set(LED_1, 1);
        delay_cycles_exact(HEATING_CYCLES);
        sys_gpio_set(LED_1, 0);
        sys_sem_post(&sem_energia);
        
        sys_sem_wait(&sem_radio);
        //slow_print("[SUBSISTEMA 2] Calentamiento finalizado. Operacion nominal alcanzada. El subsistema ha completado exitosamente la fase de estabilizacion termica y se encuentra listo para iniciar la transmision de datos hacia la estacion terrestre. En este momento se estan recopilando metricas internas como temperatura de los modulos, niveles de voltaje en los circuitos principales, consumo energetico acumulado y estado general de los sensores. Adicionalmente, se estan ejecutando rutinas de verificacion para asegurar la integridad de los datos antes de su envio, incluyendo el calculo de checksums, validacion de buffers de memoria y sincronizacion de relojes internos del sistema. El modulo de comunicaciones ha establecido un enlace estable con la estacion base, y se estan ajustando dinamicamente los parametros de transmision para optimizar el ancho de banda disponible y minimizar la latencia. Durante este proceso, se monitorean continuamente posibles interferencias externas, variaciones en la señal y errores de transmision, aplicando mecanismos de correccion cuando es necesario. Asimismo, el sistema activa protocolos de redundancia que permiten reenviar paquetes perdidos y garantizar que la informacion critica llegue completa a su destino. Se mantiene un registro detallado de todas las operaciones realizadas, el cual sera almacenado en memoria no volatil para futuras auditorias del sistema. Finalmente, el subsistema reporta que se encuentra operando dentro de los parametros nominales establecidos y listo para continuar con las siguientes fases de la mision en orbita terrestre baja...\n");
        slow_print("[SUBSISTEMA 2] Calentamiento finalizado. Operación nominal alcanzada. Transfiriendo paquetes de telemetría y reportando estado actual a base terrestre...\n ");
        sys_sem_post(&sem_radio);

    }
}


/**
 * @brief Subsystem 3 task.
 */
void subsystem3(void)
{
    sys_gpio_dir(LED_2, 1);
   
    while (1) {
        sys_sem_wait(&sem_energia);
        sys_gpio_set(LED_2, 1);
        delay_cycles_exact(HEATING_CYCLES);
        sys_gpio_set(LED_2, 0);
        sys_sem_post(&sem_energia);
        
        sys_sem_wait(&sem_radio);
        //slow_print("[SUBSISTEMA 3] Calentamiento finalizado. Operacion nominal alcanzada. El subsistema ha completado exitosamente la fase de estabilizacion termica y se encuentra listo para iniciar la transmision de datos hacia la estacion terrestre. En este momento se estan recopilando metricas internas como temperatura de los modulos, niveles de voltaje en los circuitos principales, consumo energetico acumulado y estado general de los sensores. Adicionalmente, se estan ejecutando rutinas de verificacion para asegurar la integridad de los datos antes de su envio, incluyendo el calculo de checksums, validacion de buffers de memoria y sincronizacion de relojes internos del sistema. El modulo de comunicaciones ha establecido un enlace estable con la estacion base, y se estan ajustando dinamicamente los parametros de transmision para optimizar el ancho de banda disponible y minimizar la latencia. Durante este proceso, se monitorean continuamente posibles interferencias externas, variaciones en la señal y errores de transmision, aplicando mecanismos de correccion cuando es necesario. Asimismo, el sistema activa protocolos de redundancia que permiten reenviar paquetes perdidos y garantizar que la informacion critica llegue completa a su destino. Se mantiene un registro detallado de todas las operaciones realizadas, el cual sera almacenado en memoria no volatil para futuras auditorias del sistema. Finalmente, el subsistema reporta que se encuentra operando dentro de los parametros nominales establecidos y listo para continuar con las siguientes fases de la mision en orbita terrestre baja...\n");
        slow_print("[SUBSISTEMA 3] Calentamiento finalizado. Operación nominal alcanzada. Transfiriendo paquetes de telemetría y reportando estado actual a base terrestre...\n");
        sys_sem_post(&sem_radio);

    }
    
}


/**
 * @brief Subsystem 4 task.
 */
void subsystem4(void)
{
    sys_gpio_dir(LED_3, 1);

    while (1) {
        sys_sem_wait(&sem_energia);
        sys_gpio_set(LED_3, 1);
        delay_cycles_exact(HEATING_CYCLES);
        sys_gpio_set(LED_3, 0);
        sys_sem_post(&sem_energia);
        
        sys_sem_wait(&sem_radio);
        //slow_print("[SUBSISTEMA 4] Calentamiento finalizado. Operacion nominal alcanzada. El subsistema ha completado exitosamente la fase de estabilizacion termica y se encuentra listo para iniciar la transmision de datos hacia la estacion terrestre. En este momento se estan recopilando metricas internas como temperatura de los modulos, niveles de voltaje en los circuitos principales, consumo energetico acumulado y estado general de los sensores. Adicionalmente, se estan ejecutando rutinas de verificacion para asegurar la integridad de los datos antes de su envio, incluyendo el calculo de checksums, validacion de buffers de memoria y sincronizacion de relojes internos del sistema. El modulo de comunicaciones ha establecido un enlace estable con la estacion base, y se estan ajustando dinamicamente los parametros de transmision para optimizar el ancho de banda disponible y minimizar la latencia. Durante este proceso, se monitorean continuamente posibles interferencias externas, variaciones en la señal y errores de transmision, aplicando mecanismos de correccion cuando es necesario. Asimismo, el sistema activa protocolos de redundancia que permiten reenviar paquetes perdidos y garantizar que la informacion critica llegue completa a su destino. Se mantiene un registro detallado de todas las operaciones realizadas, el cual sera almacenado en memoria no volatil para futuras auditorias del sistema. Finalmente, el subsistema reporta que se encuentra operando dentro de los parametros nominales establecidos y listo para continuar con las siguientes fases de la mision en orbita terrestre baja...\n");
        slow_print("[SUBSISTEMA 4] Calentamiento finalizado. Operación nominal alcanzada. Transfiriendo paquetes de telemetría y reportando estado actual a base terrestre...\n");
        sys_sem_post(&sem_radio);

    }
}

/**
 * @brief Subsystem 5 task.
 */
void subsystem5(void)
{
   sys_gpio_dir(LED_4, 1);

     while (1) {
       sys_sem_wait(&sem_energia);
        sys_gpio_set(LED_4, 1);
        delay_cycles_exact(HEATING_CYCLES);
        sys_gpio_set(LED_4, 0);
        sys_sem_post(&sem_energia);
        
        sys_sem_wait(&sem_radio);
        //slow_print("[SUBSISTEMA 5] Calentamiento finalizado. Operacion nominal alcanzada. El subsistema ha completado exitosamente la fase de estabilizacion termica y se encuentra listo para iniciar la transmision de datos hacia la estacion terrestre. En este momento se estan recopilando metricas internas como temperatura de los modulos, niveles de voltaje en los circuitos principales, consumo energetico acumulado y estado general de los sensores. Adicionalmente, se estan ejecutando rutinas de verificacion para asegurar la integridad de los datos antes de su envio, incluyendo el calculo de checksums, validacion de buffers de memoria y sincronizacion de relojes internos del sistema. El modulo de comunicaciones ha establecido un enlace estable con la estacion base, y se estan ajustando dinamicamente los parametros de transmision para optimizar el ancho de banda disponible y minimizar la latencia. Durante este proceso, se monitorean continuamente posibles interferencias externas, variaciones en la señal y errores de transmision, aplicando mecanismos de correccion cuando es necesario. Asimismo, el sistema activa protocolos de redundancia que permiten reenviar paquetes perdidos y garantizar que la informacion critica llegue completa a su destino. Se mantiene un registro detallado de todas las operaciones realizadas, el cual sera almacenado en memoria no volatil para futuras auditorias del sistema. Finalmente, el subsistema reporta que se encuentra operando dentro de los parametros nominales establecidos y listo para continuar con las siguientes fases de la mision en orbita terrestre baja...\n");
        slow_print("[SUBSISTEMA 5] Calentamiento finalizado. Operación nominal alcanzada. Transfiriendo paquetes de telemetría y reportando estado actual a base terrestre...\n");
        sys_sem_post(&sem_radio);

    }
}

/*
sudo dnf install screen
sudo usermod -aG dialout $USER
newgrp dialout
ls /dev/ttyACM*
screen /dev/ttyACM29 115200
*/