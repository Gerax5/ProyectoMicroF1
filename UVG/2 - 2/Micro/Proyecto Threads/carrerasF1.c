#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random numbers
int random_number(int min_num, int max_num);

// Function to get tire type from user
int get_tire_type_from_user();

// Car structure
struct Car {
    char name[10];
    float currentSpeed;
    float originalSpeed;
    int tireType; // 0: soft, 1: medium, 2: hard
    int lapCount;
    int lapsBeforePitstop;
    float lapTime;
    float totalTime;
};

int main() {
    // Initialize random seed
    srand(time(NULL));

    // Initialize cars
    struct Car cars[8];
    for (int i = 0; i < 7; ++i) {
        sprintf(cars[i].name, "Car %d", i + 1);
        cars[i].originalSpeed = random_number(250, 300);
        cars[i].tireType = random_number(0, 2);
        cars[i].lapsBeforePitstop = cars[i].tireType == 0 ? 7 : (cars[i].tireType == 1 ? 11 : 14);
        cars[i].currentSpeed = cars[i].originalSpeed * (cars[i].tireType == 0 ? 1.5 : (cars[i].tireType == 1 ? 1 : 0.8));
        cars[i].lapTime = 4.7 / cars[i].currentSpeed;
        cars[i].lapCount = 0;
        cars[i].totalTime = 0.0;
    }

    // Initialize user's car
    strcpy(cars[7].name, "Player");
    cars[7].tireType = get_tire_type_from_user();
    cars[7].lapsBeforePitstop = cars[7].tireType == 0 ? 7 : (cars[7].tireType == 1 ? 11 : 14);
    cars[7].originalSpeed = random_number(250, 300);
    cars[7].currentSpeed = cars[7].originalSpeed * (cars[7].tireType == 0 ? 1.5 : (cars[7].tireType == 1 ? 1 : 0.8));
    cars[7].lapTime = 4.7 / cars[7].currentSpeed;
    cars[7].lapCount = 0;
    cars[7].totalTime = 0.0;

    // Simulate race
    omp_set_num_threads(8);
    #pragma omp parallel for
    for (int i = 0; i < 8; ++i) {
        int lapsCompleted = 0;

        while (lapsCompleted < 21)
        {            
            // Simulate pit stops
            if (lapsCompleted == cars[i].lapsBeforePitstop)
            {     
                if (i == 7) {
                    #pragma omp critical
                    {
                        cars[i].tireType = get_tire_type_from_user();
                        cars[i].lapsBeforePitstop += cars[i].tireType == 0 ? 7 : (cars[i].tireType == 1 ? 11 : 14);
                    }
                } else {
                    cars[i].tireType = random_number(0, 2);
                    cars[i].lapsBeforePitstop += cars[i].tireType == 0 ? 7 : (cars[i].tireType == 1 ? 11 : 14);
                }
                cars[i].currentSpeed = cars[i].originalSpeed * (cars[i].tireType == 0 ? 1.5 : (cars[i].tireType == 1 ? 1 : 0.8));
                cars[i].lapTime = 4.7 / cars[i].currentSpeed;
                Sleep(1000);
            }
            
            // Simulate lap time
            Sleep(cars[i].lapTime * 100000);
            cars[i].totalTime += cars[i].lapTime;
            lapsCompleted++;
            #pragma omp critical
            {
                printf("%s, Lap: %d, Lap Time: %f\n", cars[i].name, lapsCompleted, cars[i].lapTime);
            }
        }
    }

    // Display results
    printf("\nFinal Results:\n");
    for (int i = 0; i < 8; ++i) {
        printf("%s, Total Time: %f\n", cars[i].name, cars[i].totalTime);
    }

    return 0;
}

int random_number(int min_num, int max_num) {
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1;
    } else {
        low_num = max_num + 1;
        hi_num = min_num;
    }

    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

int get_tire_type_from_user() {
    int userInput;
    int scanResult;
    do {
        printf("PITSTOP\n");
        printf("Choose tire type (0: soft, 1: medium, 2: hard): ");
        scanResult = scanf("%d", &userInput);
        while(getchar() != '\n');
        if (scanResult == 0 || userInput < 0 || userInput > 2) {
            printf("Invalid input. Please enter a number between 0 and 2.\n");
        }
    } while (scanResult == 0 || userInput < 0 || userInput > 2);
    return userInput;
}