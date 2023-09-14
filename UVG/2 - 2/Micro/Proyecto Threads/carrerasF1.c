#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
//#include <unistd.h> 
#include <windows.h> //para windows

int random_number(int min_num, int max_num);

struct carro{
    char nombreCarro[10];
    float velocidadActual;
    float velocidadOriginal;
    int tipoLlanta; //0 soft, 1 m, 2h
    int numeroVueltas;
    float tiempoVuelta;
    float tiempoAcumulativo;
};


int main(){
    bool flagInicio = true;
    struct carro carros[8];
    char carName[10];
    for (size_t i = 0; i < sizeof(carros)/sizeof(carros[0]); i++)
    {
        char carName[10];
        sprintf(carName, "Carro %d",(i+1));
        float velocidadActual;
        float velocidadOriginal  =  random_number(250,300)*1.0;
        int tipoLlanta = random_number(0,2);
        if(tipoLlanta == 0){
            velocidadActual = velocidadOriginal*1.5;
        }else if(tipoLlanta ==1){
            velocidadActual = velocidadOriginal*1;
        }else{
            velocidadActual = velocidadOriginal*0.8;
        }
        struct carro carroN = {0};
        strcpy(carroN.nombreCarro, carName);
        carroN.velocidadActual = velocidadActual;
        carroN.velocidadOriginal = velocidadOriginal;
        carroN.tipoLlanta = tipoLlanta;
        carroN.tiempoVuelta = 4.7/velocidadActual;
        carros[i] = carroN;
    }

    for (int i = 0; i < sizeof(carros)/sizeof(carros[0]); i++)
    {
        printf("%s\n",carros[i].nombreCarro);
    }

    printf("Struct 1:\n\ti = %s, f = %f\n",
        carros[0].nombreCarro, carros[0].velocidadActual);

    omp_set_num_threads(8);
    #pragma omp parallel for
    for (int i = 0; i < 8; i++) {  
        double t1 = omp_get_wtime();
        for (int j = 0; j <= 21; j++)
        {
            if((carros[i].tipoLlanta == 0) && (j == 7)){
                Sleep(1000);
            }else if((carros[i].tipoLlanta == 1) && (j == 11)){
                Sleep(1000);
            }else if((carros[i].tipoLlanta == 2) && (j == 14)){
                Sleep(1000);
            }
            Sleep(carros[i].tiempoVuelta*100);
            printf("%s, Vuelta: %d\n",carros[i].nombreCarro,j);
        }
        double t2 = omp_get_wtime();
        carros[i].tiempoAcumulativo = (t2-t1);
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s, Tiempo Total: %f\n",carros[i].nombreCarro,carros[i].tiempoAcumulativo);
    }
    
}


int random_number(int min_num, int max_num)
    {
        int result = 0, low_num = 0, hi_num = 0;

        if (min_num < max_num)
        {
            low_num = min_num;
            hi_num = max_num + 1; // include max_num in output
        } else {
            low_num = max_num + 1; // include max_num in output
            hi_num = min_num;
        }

        srand(time(NULL));
        result = (rand() % (hi_num - low_num)) + low_num;
        return result;
    }