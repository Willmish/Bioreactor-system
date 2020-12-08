#define ph_probe A1

#define F 9.6485309E+4 // Faraday's constant
#define R 8.31450 // universal gas constant
#define T 295.0 // room temperature in Kelvin
#define vmax 5000.0 
#define vs -2500.0


// I2C addresses for our pumps

#define acid 0b1000000
#define alkaline 0b1000001


// register numbers: https://moodle.ucl.ac.uk/pluginfile.php/3568654/mod_resource/content/1/PCA9685.pdf (page 9)

#define LED0_ON_L 6
#define LED1_ON_L 10
#define MODE 0
#define ENABLE_INCREMENT 0b0010000 // enable autoincrement
#define MAX_ON_TIME 4095 // we can have a maximum of 4095 asserted PWM steps 


void prepare_pca9685();
void pump_solute(int, byte);
float measure_ph();
