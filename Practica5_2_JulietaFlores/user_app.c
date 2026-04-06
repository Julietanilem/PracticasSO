#include <stdint.h>
#include <stdio.h> // Has printf
#include "syscalls.h"

/* Pin Definitions */
#define LED_0 16
#define LED_1 17
#define LED_2 18
#define LED_3 19
#define LED_4 20

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
        putchar(*str++);
        fflush(stdout);
        delay_cycles_exact(20000);  
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
    setup_leds();

    while (1)
    {
        sys_gpio_set(LED_0, 1);
        slow_print("[SUBSISTEMA 1] Iniciando calentamiento de subsistema 1...\n");
        delay_cycles_exact(625000);
        sys_gpio_set(LED_0, 0);
        delay_cycles_exact(62500);
        //printf("[SUBSISTEMA 1] Calentamiento finalizado. Operacion nominal alcanzada. Transfiriendo paquetes de telemetria y reportando estado actual a base terrestre. Iniciando verificacion de integridad de datos, comprobando consistencia de buffers internos, sincronizando relojes del sistema, validando parametros de comunicacion y estableciendo enlace estable con la estacion base. Preparando envio de informacion critica del sistema, incluyendo metricas de temperatura, consumo energetico, estado de modulos internos y registros de actividad reciente. Ejecutando protocolos de redundancia para asegurar la correcta transmision de datos en condiciones adversas, verificando canales alternos de comunicacion y ajustando parametros de transmision en tiempo real para optimizar el rendimiento general del sistema satelital en orbita baja terrestre. Reintentando envio de paquetes perdidos, recalculando checksums, reconfigurando buffers de transmision, ajustando ventanas de envio y monitoreando latencia en el canal de comunicacion para mantener la estabilidad del enlace en presencia de interferencia externa...\n");
        slow_print("[SUBSISTEMA 1] Calentamiento finalizado. Operacion nominal alcanzada. El subsistema ha completado exitosamente la fase de estabilizacion termica y se encuentra listo para iniciar la transmision de datos hacia la estacion terrestre. En este momento se estan recopilando metricas internas como temperatura de los modulos, niveles de voltaje en los circuitos principales, consumo energetico acumulado y estado general de los sensores. Adicionalmente, se estan ejecutando rutinas de verificacion para asegurar la integridad de los datos antes de su envio, incluyendo el calculo de checksums, validacion de buffers de memoria y sincronizacion de relojes internos del sistema. El modulo de comunicaciones ha establecido un enlace estable con la estacion base, y se estan ajustando dinamicamente los parametros de transmision para optimizar el ancho de banda disponible y minimizar la latencia. Durante este proceso, se monitorean continuamente posibles interferencias externas, variaciones en la señal y errores de transmision, aplicando mecanismos de correccion cuando es necesario. Asimismo, el sistema activa protocolos de redundancia que permiten reenviar paquetes perdidos y garantizar que la informacion critica llegue completa a su destino. Se mantiene un registro detallado de todas las operaciones realizadas, el cual sera almacenado en memoria no volatil para futuras auditorias del sistema. Finalmente, el subsistema reporta que se encuentra operando dentro de los parametros nominales establecidos y listo para continuar con las siguientes fases de la mision en orbita terrestre baja...\n");

    }
}

/**
 * @brief Subsystem 2 task.
 */
void subsystem2(void)
{
    setup_leds();

    while (1)
    {
        sys_gpio_set(LED_1, 1);
        slow_print("[SUBSISTEMA 2] Calentamiento de subsistema 2 en progreso...\n");
        delay_cycles_exact(625000);
        sys_gpio_set(LED_1, 0);
        delay_cycles_exact(62500);
        //printf("[SUBSISTEMA 2] Calentamiento finalizado. Operacion nominal alcanzada. Transfiriendo paquetes de telemetria y reportando estado actual a base terrestre. Iniciando verificacion de integridad de datos, comprobando consistencia de buffers internos, sincronizando relojes del sistema, validando parametros de comunicacion y estableciendo enlace estable con la estacion base. Preparando envio de informacion critica del sistema, incluyendo metricas de temperatura, consumo energetico, estado de modulos internos y registros de actividad reciente. Ejecutando protocolos de redundancia para asegurar la correcta transmision de datos en condiciones adversas, verificando canales alternos de comunicacion y ajustando parametros de transmision en tiempo real para optimizar el rendimiento general del sistema satelital en orbita baja terrestre. Reintentando envio de paquetes perdidos, recalculando checksums, reconfigurando buffers de transmision, ajustando ventanas de envio y monitoreando latencia en el canal de comunicacion para mantener la estabilidad del enlace en presencia de interferencia externa...\n");
        slow_print("[SUBSISTEMA 2] Calentamiento finalizado. Operacion nominal alcanzada. El subsistema ha completado exitosamente la fase de estabilizacion termica y se encuentra listo para iniciar la transmision de datos hacia la estacion terrestre. En este momento se estan recopilando metricas internas como temperatura de los modulos, niveles de voltaje en los circuitos principales, consumo energetico acumulado y estado general de los sensores. Adicionalmente, se estan ejecutando rutinas de verificacion para asegurar la integridad de los datos antes de su envio, incluyendo el calculo de checksums, validacion de buffers de memoria y sincronizacion de relojes internos del sistema. El modulo de comunicaciones ha establecido un enlace estable con la estacion base, y se estan ajustando dinamicamente los parametros de transmision para optimizar el ancho de banda disponible y minimizar la latencia. Durante este proceso, se monitorean continuamente posibles interferencias externas, variaciones en la señal y errores de transmision, aplicando mecanismos de correccion cuando es necesario. Asimismo, el sistema activa protocolos de redundancia que permiten reenviar paquetes perdidos y garantizar que la informacion critica llegue completa a su destino. Se mantiene un registro detallado de todas las operaciones realizadas, el cual sera almacenado en memoria no volatil para futuras auditorias del sistema. Finalmente, el subsistema reporta que se encuentra operando dentro de los parametros nominales establecidos y listo para continuar con las siguientes fases de la mision en orbita terrestre baja...\n");

    
    }
}


/**
 * @brief Subsystem 3 task.
 */
void subsystem3(void)
{
    setup_leds();

    while (1)
    {

        sys_gpio_set(LED_2, 1);
        slow_print("[SUBSISTEMA 3] Iniciando calentamiento de subsistema 3...\n");
         delay_cycles_exact(625000);
        sys_gpio_set(LED_2, 0);
        delay_cycles_exact(62500);
        //slow_print("[SUBSISTEMA 3] Calentamiento finalizado. Operacion nominal alcanzada. Transfiriendo paquetes de telemetria y reportando estado actual a base terrestre. Iniciando verificacion de integridad de datos, comprobando consistencia de buffers internos, sincronizando relojes del sistema, validando parametros de comunicacion y estableciendo enlace estable con la estacion base. Preparando envio de informacion critica del sistema, incluyendo metricas de temperatura, consumo energetico, estado de modulos internos y registros de actividad reciente. Ejecutando protocolos de redundancia para asegurar la correcta transmision de datos en condiciones adversas, verificando canales alternos de comunicacion y ajustando parametros de transmision en tiempo real para optimizar el rendimiento general del sistema satelital en orbita baja terrestre. Reintentando envio de paquetes perdidos, recalculando checksums, reconfigurando buffers de transmision, ajustando ventanas de envio y monitoreando latencia en el canal de comunicacion para mantener la estabilidad del enlace en presencia de interferencia externa...\n");
        slow_print("[SUBSISTEMA 3] Calentamiento finalizado. Operacion nominal alcanzada. El subsistema ha completado exitosamente la fase de estabilizacion termica y se encuentra listo para iniciar la transmision de datos hacia la estacion terrestre. En este momento se estan recopilando metricas internas como temperatura de los modulos, niveles de voltaje en los circuitos principales, consumo energetico acumulado y estado general de los sensores. Adicionalmente, se estan ejecutando rutinas de verificacion para asegurar la integridad de los datos antes de su envio, incluyendo el calculo de checksums, validacion de buffers de memoria y sincronizacion de relojes internos del sistema. El modulo de comunicaciones ha establecido un enlace estable con la estacion base, y se estan ajustando dinamicamente los parametros de transmision para optimizar el ancho de banda disponible y minimizar la latencia. Durante este proceso, se monitorean continuamente posibles interferencias externas, variaciones en la señal y errores de transmision, aplicando mecanismos de correccion cuando es necesario. Asimismo, el sistema activa protocolos de redundancia que permiten reenviar paquetes perdidos y garantizar que la informacion critica llegue completa a su destino. Se mantiene un registro detallado de todas las operaciones realizadas, el cual sera almacenado en memoria no volatil para futuras auditorias del sistema. Finalmente, el subsistema reporta que se encuentra operando dentro de los parametros nominales establecidos y listo para continuar con las siguientes fases de la mision en orbita terrestre baja...\n");

    }
}


/**
 * @brief Subsystem 4 task.
 */
void subsystem4(void)
{
    setup_leds();

    while (1)
    {
        sys_gpio_set(LED_3, 1);
        slow_print("[SUBSISTEMA 4] Iniciando calentamiento de subsistema 4...\n");
        delay_cycles_exact(625000);
        sys_gpio_set(LED_3, 0);
        delay_cycles_exact(62500);
        //slow_print("[SUBSISTEMA 4] Calentamiento finalizado. Operacion nominal alcanzada. Transfiriendo paquetes de telemetria y reportando estado actual a base terrestre. Iniciando verificacion de integridad de datos, comprobando consistencia de buffers internos, sincronizando relojes del sistema, validando parametros de comunicacion y estableciendo enlace estable con la estacion base. Preparando envio de informacion critica del sistema, incluyendo metricas de temperatura, consumo energetico, estado de modulos internos y registros de actividad reciente. Ejecutando protocolos de redundancia para asegurar la correcta transmision de datos en condiciones adversas, verificando canales alternos de comunicacion y ajustando parametros de transmision en tiempo real para optimizar el rendimiento general del sistema satelital en orbita baja terrestre. Reintentando envio de paquetes perdidos, recalculando checksums, reconfigurando buffers de transmision, ajustando ventanas de envio y monitoreando latencia en el canal de comunicacion para mantener la estabilidad del enlace en presencia de interferencia externa...\n");
        slow_print("[SUBSISTEMA 4] Calentamiento finalizado. Operacion nominal alcanzada. El subsistema ha completado exitosamente la fase de estabilizacion termica y se encuentra listo para iniciar la transmision de datos hacia la estacion terrestre. En este momento se estan recopilando metricas internas como temperatura de los modulos, niveles de voltaje en los circuitos principales, consumo energetico acumulado y estado general de los sensores. Adicionalmente, se estan ejecutando rutinas de verificacion para asegurar la integridad de los datos antes de su envio, incluyendo el calculo de checksums, validacion de buffers de memoria y sincronizacion de relojes internos del sistema. El modulo de comunicaciones ha establecido un enlace estable con la estacion base, y se estan ajustando dinamicamente los parametros de transmision para optimizar el ancho de banda disponible y minimizar la latencia. Durante este proceso, se monitorean continuamente posibles interferencias externas, variaciones en la señal y errores de transmision, aplicando mecanismos de correccion cuando es necesario. Asimismo, el sistema activa protocolos de redundancia que permiten reenviar paquetes perdidos y garantizar que la informacion critica llegue completa a su destino. Se mantiene un registro detallado de todas las operaciones realizadas, el cual sera almacenado en memoria no volatil para futuras auditorias del sistema. Finalmente, el subsistema reporta que se encuentra operando dentro de los parametros nominales establecidos y listo para continuar con las siguientes fases de la mision en orbita terrestre baja...\n");

    }
}

/**
 * @brief Subsystem 5 task.
 */
void subsystem5(void)
{
    setup_leds();

    while (1)
    {
        sys_gpio_set(LED_4, 1);
       
        slow_print("[SUBSISTEMA 5] Iniciando calentamiento de subsistema 5...\n");
        delay_cycles_exact(625000);
        sys_gpio_set(LED_4, 0);
        delay_cycles_exact(62500);
        // slow_print("[SUBSISTEMA 5] Calentamiento finalizado. Operacion nominal alcanzada. Transfiriendo paquetes de telemetria y reportando estado actual a base terrestre. Iniciando verificacion de integridad de datos, comprobando consistencia de buffers internos, sincronizando relojes del sistema, validando parametros de comunicacion y estableciendo enlace estable con la estacion base. Preparando envio de informacion critica del sistema, incluyendo metricas de temperatura, consumo energetico, estado de modulos internos y registros de actividad reciente. Ejecutando protocolos de redundancia para asegurar la correcta transmision de datos en condiciones adversas, verificando canales alternos de comunicacion y ajustando parametros de transmision en tiempo real para optimizar el rendimiento general del sistema satelital en orbita baja terrestre. Reintentando envio de paquetes perdidos, recalculando checksums, reconfigurando buffers de transmision, ajustando ventanas de envio y monitoreando latencia en el canal de comunicacion para mantener la estabilidad del enlace en presencia de interferencia externa...\n");
        slow_print("[SUBSISTEMA 5] Calentamiento finalizado. Operacion nominal alcanzada. El subsistema ha completado exitosamente la fase de estabilizacion termica y se encuentra listo para iniciar la transmision de datos hacia la estacion terrestre. En este momento se estan recopilando metricas internas como temperatura de los modulos, niveles de voltaje en los circuitos principales, consumo energetico acumulado y estado general de los sensores. Adicionalmente, se estan ejecutando rutinas de verificacion para asegurar la integridad de los datos antes de su envio, incluyendo el calculo de checksums, validacion de buffers de memoria y sincronizacion de relojes internos del sistema. El modulo de comunicaciones ha establecido un enlace estable con la estacion base, y se estan ajustando dinamicamente los parametros de transmision para optimizar el ancho de banda disponible y minimizar la latencia. Durante este proceso, se monitorean continuamente posibles interferencias externas, variaciones en la señal y errores de transmision, aplicando mecanismos de correccion cuando es necesario. Asimismo, el sistema activa protocolos de redundancia que permiten reenviar paquetes perdidos y garantizar que la informacion critica llegue completa a su destino. Se mantiene un registro detallado de todas las operaciones realizadas, el cual sera almacenado en memoria no volatil para futuras auditorias del sistema. Finalmente, el subsistema reporta que se encuentra operando dentro de los parametros nominales establecidos y listo para continuar con las siguientes fases de la mision en orbita terrestre baja...\n");

    
    }
}

/*
sudo dnf install screen
sudo usermod -aG dialout $USER
newgrp dialout
ls /dev/ttyACM*
screen /dev/ttyACM29 115200
*/