#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <wiringx.h>

#define IR_GPIO_PIN  7  // Replace with the actual GPIO pin connected to your IR receiver

// Simulated data for testing
uint16_t irData[] = {9000, 4500, 560, 560, 560, 1690, 560, 560, 560, 560, 560, 1690};

// Function to capture raw IR data
void captureIRData(uint16_t* data, size_t size) {

	int SWITCH = 14;
	pinMode(SWITCH, PINMODE_INPUT);
    for (size_t i = 0; i < size; ++i) {
        while (digitalRead(SWITCH) == LOW ) {}  // Wait for the start of a pulse
        
        uint16_t duration = 0;
        while (digitalRead(SWITCH)== 1) {   // Measure pulse duration
            // Adjust the delay based on your system's clock speed
            // This is a very basic delay; a more accurate timing method is recommended
            delayMicroseconds(10);
            duration += 10;  // Accumulate the duration
        }
        
        data[i] = duration;  // Store the duration in the array
    }
}

// Function to process captured IR data (decode logic would go here)
void processIRData(uint16_t* data, size_t size) {
    printf("IR Data: ");
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // Add your decoding logic here
}

int main() {
    // Simulated IR data (replace this with actual data from your IR receiver)
    size_t dataSize = sizeof(irData) / sizeof(irData[0]);
	int DUO_LED = 15;
	int SWITCH = 14;
	


    if(wiringXSetup("duo", NULL) == -1) {
        wiringXGC();
        return -1;
    }

    if (wiringXValidGPIO(DUO_LED) != 0){
	    printf("invalid GPIO out");
    }

    pinMode(DUO_LED, PINMODE_OUTPUT);
    pinMode(SWITCH, PINMODE_INPUT);
    //Capture data
    captureIRData(

    // Process the IR data
    processIRData(irData, dataSize);

    return 0;
}

