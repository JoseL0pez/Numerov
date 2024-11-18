#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000
#define XMIN -5.0
#define XMAX 5.0
#define DX ((XMAX - XMIN) / (N - 1))

// Función para calcular la energía esperada para un estado cuántico n
double expected_energy(int n) {
    return (n + 0.5);
}

// Función para calcular el potencial del oscilador armónico
double V(double x) {
    return 0.5 * x * x;
}


void numerov_method(double *psi, double E, int n) { 
    psi[0] = 0.0;  
    psi[1] = 0.001;  
    // Método Numerov para calcular psi[i] para cada x[i]
    for (int i = 1; i < N - 1; i++) {
        double x = XMIN + i * DX;
        double k = 2.0 * (E - V(x)); 

        // Aplicación del método de Numerov
        psi[i + 1] = (2 * psi[i] * (1 - 5.0 * DX * DX * k / 12.0) -
                      psi[i - 1] * (1 + DX * DX * k / 12.0)) /
                     (1 + DX * DX * k / 12.0);
    }
}

// Función para normalizar la función de onda
void normalize(double *psi) {
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        sum += psi[i] * psi[i] * DX;
    }
    double norm_factor = sqrt(sum);
    for (int i = 0; i < N; i++) {
        psi[i] /= norm_factor;
    }
}

int main(void) {
    double *psi = (double *)malloc(N * sizeof(double));
    if (psi == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria\n");
        return EXIT_FAILURE;
    }

    // Calcular los primeros 4 estados cuánticos
    for (int n = 0; n < 4; n++) {
        double E = expected_energy(n);  
        char filename[50];
        sprintf(filename, "datos_n%d.txt", n);

        numerov_method(psi, E, n);
        normalize(psi); 

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", filename);
            free(psi);
            return EXIT_FAILURE;
        }

        // Guardar los datos en el archivo
        fprintf(file, "# x\tPsi(x)\tPsi^2(x)\tV(x)\n");
        for (int i = 0; i < N; i++) {
            double x = XMIN + i * DX;
            fprintf(file, "%f\t%f\t%f\t%f\n", 
                    x, psi[i], psi[i] * psi[i], V(x));
        }

        fclose(file);
        printf("Estado n=%d: E=%.6f\n", n, E);
    }

    free(psi);
    return EXIT_SUCCESS;
}
