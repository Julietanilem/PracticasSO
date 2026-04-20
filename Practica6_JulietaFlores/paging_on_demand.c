#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paging_on_demand.h"

#define MAX_FRAMES 128
#define MAX_PROCESSES 10
#define MAX_PAGES 64

typedef struct {
    int pid;
    int v_page;
    int is_page_table;
    int last_use;
} frame_info_t;

frame_info_t ram_frames[MAX_FRAMES];
int total_ram_frames = 0;
int demand_paging_timer = 0;

typedef struct {
    int pid;
    int page_table[MAX_PAGES]; // Maps v_page to frame index (-1 if not in RAM)
    int total_pages;
} process_demand_t;

process_demand_t demand_processes[MAX_PROCESSES];
int demand_process_count = 0;

void init_demand_system(int frames) {
    total_ram_frames = (frames > MAX_FRAMES) ? MAX_FRAMES : frames;
    for (int i = 0; i < MAX_FRAMES; i++) {
        ram_frames[i].pid = -1;
        ram_frames[i].is_page_table = 0;
        ram_frames[i].last_use = 0;
    }
    demand_process_count = 0;
    printf("SYSTEM: Demand Paging initialized with %d frames\n", total_ram_frames);
}

int find_free_frame() {
    // TODO: Alumno - Buscar un frame vacio (donde pid == -1)
    // done
    for (int i = 0; i < total_ram_frames; i++) {
        if (ram_frames[i].pid == -1) {
            return i;
        }
    }


    return -1;
}

int evict_frame() {
    int victim = -1;

    // TODO: Alumno - Implementar algoritmo de desalojo LRU Global
    int min_time = 1e9;

    for (int i = 0; i < total_ram_frames; i++) {
        if (ram_frames[i].pid != -1 && ram_frames[i].is_page_table == 0) {
            if (ram_frames[i].last_use < min_time) {
                min_time = ram_frames[i].last_use;
                victim = i;
            }
        }
    }

    // TODO: Alumno - IMPORTANTE: No desalojar frames que sean tablas de paginas (is_page_table == 1)

    if (victim != -1) {
        printf("EVICT: Frame %d (PID %d, Page %d) removed from RAM\n",
               victim,
               ram_frames[victim].pid,
               ram_frames[victim].v_page);

        // TODO: Alumno - Actualizar la tabla de paginas del proceso que perdio el frame
        int pid = ram_frames[victim].pid;
        int page = ram_frames[victim].v_page;

        for (int i = 0; i < demand_process_count; i++) {
            if (demand_processes[i].pid == pid) {
                demand_processes[i].page_table[page] = -1;
                break;
            }
        }

        ram_frames[victim].pid = -1;
        ram_frames[victim].v_page = -1;
        ram_frames[victim].is_page_table = 0;
        ram_frames[victim].last_use = 0;
    }

    return victim;
}


void load_process(int pid, int pages) {
    if (demand_process_count >= MAX_PROCESSES) return;

    // TODO: Alumno - Reservar un frame para la tabla de paginas del proceso
    int pt_frame = find_free_frame();

    if (pt_frame == -1) {
        pt_frame = evict_frame();
    }

    // TODO: Alumno - Marcar el frame como is_page_table = 1 para que sea persistente (pinned)
    if (pt_frame != -1) {
        ram_frames[pt_frame].pid = pid;
        ram_frames[pt_frame].v_page = -1;
        ram_frames[pt_frame].is_page_table = 1;
        ram_frames[pt_frame].last_use = demand_paging_timer;
    }

    if (pt_frame != -1) {
        demand_processes[demand_process_count].pid = pid;
        demand_processes[demand_process_count].total_pages = pages;

        for (int i = 0; i < MAX_PAGES; i++) {
            demand_processes[demand_process_count].page_table[i] = -1;
        }

        printf("LOAD: PID %d loaded. Page Table pinned at Frame %d\n", pid, pt_frame);
        demand_process_count++;
    }
}

void access_page(int pid, int v_page) {
    demand_paging_timer++;

    // TODO: Alumno - Buscar el proceso y verificar si la pagina esta en RAM
    int proc = -1;

    for (int i = 0; i < demand_process_count; i++) {
        if (demand_processes[i].pid == pid) {
            proc = i;
            break;
        }
    }

    if (proc == -1) return;

    // TODO: Alumno - Si esta en RAM (HIT), solo actualizar last_use
    int frame = demand_processes[proc].page_table[v_page];

    if (frame != -1) {
        ram_frames[frame].last_use = demand_paging_timer;
        printf("ACCESS: PID %d, Page %d -> Hit at Frame %d\n", pid, v_page, frame);
        return;
    }

    // TODO: Alumno - Si no esta (PAGE FAULT), buscar frame libre o desalojar uno
    printf("PAGE FAULT: PID %d, Page %d not in RAM\n", pid, v_page);

    int new_frame = find_free_frame();

    if (new_frame == -1) {
        new_frame = evict_frame();
    }

    // TODO: Alumno - Cargar la pagina (PAGE IN) y actualizar tablas
    if (new_frame != -1) {
        ram_frames[new_frame].pid = pid;
        ram_frames[new_frame].v_page = v_page;
        ram_frames[new_frame].is_page_table = 0;
        ram_frames[new_frame].last_use = demand_paging_timer;

        demand_processes[proc].page_table[v_page] = new_frame;

        printf("PAGE IN: PID %d, Page %d loaded into Frame %d\n",
               pid, v_page, new_frame);
    }
}


void simulate_demand_paging() {
    char line[256];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\r\n")] = 0;
        if (line[0] == '\0' || line[0] == '#') continue;

        int val, pid, pages, v_page;
        if (sscanf(line, "RAM_CONFIG FRAMES %d", &val) == 1) {
            init_demand_system(val);
        } else if (sscanf(line, "LOAD PID %d PAGES %d", &pid, &pages) == 2) {
            load_process(pid, pages);
        } else if (sscanf(line, "ACCESS PID %d V_PAGE %d", &pid, &v_page) == 2) {
            access_page(pid, v_page);
        }
    }
}
