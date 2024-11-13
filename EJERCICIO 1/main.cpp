#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4096

int main() {
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        SIZE,
        NULL);

    if (hMapFile == NULL) {
        printf("Error al crear la memoria compartida (%d).\n", GetLastError());
        return 1;
    }

    char *shared_memory = (char *)MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        SIZE);

    if (shared_memory == NULL) {
        printf("Error al mapear la memoria compartida (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    strcpy(shared_memory, "Hello, child process!");
    printf("Mensaje en memoria compartida: %s\n", shared_memory);
    UnmapViewOfFile(shared_memory);
    CloseHandle(hMapFile);

    return 0;
}


/* ENUNCIADO
* Explicación paso a paso:
*
*Primero, es necesario importar las bibliotecas necesarias para la asignación de memoria y la creación de procesos.
*En este caso, no utilizaremos las bibliotecas <sys/mman.h> ni <sys/wait.h>, debido a que estas solo son
*utilizables en Linux/MacOS. Así pues, como opción para Windows usaremos <windows.h>.
*
*


*/