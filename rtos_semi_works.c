// This is the starter code for the RTOS Homework designed for
// CSE/ECE 474 Summer 19.
//
// Please read through the entire file and make sure
// you understand your tasks, the structure of the code,
// and the hints you are given (although you are not
// required to follow them)
//
// The only requirement is to use the three tasks specified
// in the main function. Feel free to add/delete the code we
// provided, though it is recommended to follow the hints.
//
// Here's the documentation page for FreeRTOS,
// you may want to look at it when doing this assignment.
// https://www.freertos.org/FreeRTOS-quick-start-guide.html

#include "FreeRTOS.h"
#include "task.h"


// Include your own header here.
#include "register.h"

// After skimming through the entire file,
// you might want to add some FSM states here.


// Hint:
//
// The following global variables are flags you may want to use
int pedestrian_status = 0;
int onoff_status = 0;


// Below are function prototypes for our RTOS task.
// You should not change the function declerations.
// However, you are allowed to add more helper functions
// as needed.

//LED initialization
void LED_Init(void);
void RED_LED_on(void);
void RED_LED_off(void);
void YELLOW_LED_on(void);
void YELLOW_LED_off(void);
void GREEN_LED_on(void);
void GREEN_LED_off(void);
void red_led_on(void);
void yellow_led_on(void);
void green_led_on(void);
void reset_led(void);

//Button initialization
void switch_Init();
unsigned long switch_input_1();
unsigned long switch_input_2();


// Initialize the GPIO Port for traffic light LEDs and user buttons
void GPIO_Init(void);

// Task function that checks the state of the pedestrian button.
// Keeps track of how many seconds the pedestrian button has been pressed.
// Once the user has pressed the pedestrian button for 2 seconds,
// it will set the global flag indicating the pedestrian button has been
// pressed
void Pedestrian(void *p);

// Task function that checks the state of the onoff button.
// Keeps track of how many seconds the onoff button has been pressed.
// Once the user has pressed the onoff button for 2 seconds,
// it will set the global flag indicating the onoff button has been
// pressed
void StartStop(void *p);

// Task function that represents your Finite State Machine.
// Keeps track of how many seconds the LED has been lighting on.
// It will update the state of the LED every 5 seconds or once there's
// button input
void Control(void *p);

// Helper function that represents your FSM.
// You are allowed to change this function decleration.
//
// Handles the traffic light state transition.
void FSM(void);


// Do not modify this function.
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName) {
  // This function can not return, so loop forever.  Interrupts are disabled
  // on entry to this function, so no processor interrupts will interrupt
  // this loop.
  while (1) {}
}


// Initialize FreeRTOS and start the tasks.
int main(void) {
  // STEP 1
  //
  // This is the beginning of the main function,
  // Initialize your system by setting up all the GPIO pins 
  // you'll be using
  
  GPIO_Init(); //initialize every GPIO for leds
 
  


  // STEP 2
  //
  // The code below creates three tasks.
  // Your task here is to assign priorities to the tasks.
  //
  // Think about which task(s) should be given the highest
  // priority and which should be given lower, it is possible to assign
  // the same priority to all the tasks though.
  //
  // Priorities are in range: [0, configMAX_PRIORITIES - 1], where
  // configMAX_PRIORITIES - 1 corresponds to the highest priority and
  // 0 corresponds to the lowest priority.
  // You can find configMAX_PRIORITIES defined in the file called FreeRTOSConfig.h
  // under the freertos_demo directory.
  //
  // You should not create more tasks. However, you are allowed to add as many
  // helper functions as you want.
  // xTaskCreate(Function Name,
  //             Descriptive Task Name,
  //             Stack Depth,
  //             Task Function Parameter,
  //             Priority,
  //             Task Handle);
  
//  xTaskCreate(StartStop, (const char *)"StartStopButton", 1024, NULL, , NULL);
//  xTaskCreate(Pedestrian, (const char *)"PedestrianButton", 1024, NULL, , NULL);
//  xTaskCreate(Control, (const char *)"Control FSM", 1024, NULL, , NULL);
  
  xTaskCreate(StartStop, (const char *)"StartStopButton", 1024, NULL, 14, NULL); //middle priority
  xTaskCreate(Pedestrian, (const char *)"PedestrianButton", 1024, NULL, 10, NULL); //maybe highest priority
  xTaskCreate(Control, (const char *)"Control FSM", 1024, NULL, 0, NULL); //lowest priority

  // Start the scheduler. This should not return.
  // The scheduler will do the scheduling and switch between
  // different tasks for you.
  // Refer to the lecture slides and RTOS documentation
  // page for more details about task scheduling and context switching.
  //
  // One important concept for context switching and task scheduling
  // is preemption. Think about what do preemptive and non-preemptive
  // means.
  //
  // Hint: Non-preemptive scheduling will allow other tasks to be scheduled
  // after the current task has entered the "waiting state". That is, in our context,
  // the current task will keep running until it reaches vTaskDelay 
  // (you'll see this in task functions).
  //
  // You can find in FreeRTOSConfig.h the setting of preemption
  // for the RTOS. Feel free to change this setting as needed.
  vTaskStartScheduler();

  // In case the scheduler returns for some reason, loop forever.
  while(1) {}
}

/**********************************************************************/
void LED_Init(void)
 {
    volatile unsigned long delay;        
    SYSCTL_RCGC2_R |= 0x01;              //activate clock for port A
    delay = SYSCTL_RCGC2_R;              //allow time for clock to start
    GPIO_PORTA_PCTL_R &= ~0xF00FF000;    //regular GPIO
    
    
    GPIO_PORTA_AMSEL_R &= ~0x98;         //disable analog function of PA2, PA4, PA3
    GPIO_PORTA_DIR_R |= 0x98;            //set PA2, PA4, and PA3 to output
    GPIO_PORTA_AFSEL_R &= ~0x98;         //regular port function
    GPIO_PORTA_DEN_R |= 0x98;            //enable digital output on PA2, PA4, PA3
}

  //turn on RED LED connected to PA3
void RED_LED_on(void) 
{
    GPIO_PORTA_DATA_R |= 0x08; 
}
  
  //turn off RED LED connected to PA3
void RED_LED_off(void) 
{
    GPIO_PORTA_DATA_R &= ~0x08;
}

//turn on YELLOW LED connected to PA4
void YELLOW_LED_on(void) 
{
    GPIO_PORTA_DATA_R |= 0x10;
}
  
  //turn off YELLOW LED connected to PA4
  void YELLOW_LED_off(void) 
{
    GPIO_PORTA_DATA_R &= ~0x10;
}

//turn on GREEN LED connected to PA7
void GREEN_LED_on(void) 
{
    GPIO_PORTA_DATA_R |= 0x80;
}
  
  //turn off GREEN LED connected to PA7
  
  void GREEN_LED_off(void) 
{
    GPIO_PORTA_DATA_R &= ~0x80;
}

//Turn on the RED LED
void red_led_on(void)
{
  RED_LED_on();  
  GREEN_LED_off(); 
  YELLOW_LED_off();
  
  //Adding delay to make the transition between each LED more observable
  for (int i = 0; i < 1000000; i++) {}
  for (int i = 0; i < 1000000; i++) {}
}

//Turn on the GREEN LED
void green_led_on(void)
{
  RED_LED_off();  
  GREEN_LED_on(); 
  YELLOW_LED_off();
  
  //Adding delay to make the transition between each LED more observable
  for (int i = 0; i < 1000000; i++) {}
  for (int i = 0; i < 1000000; i++) {}
}

//Turn on the YELLOW LED
void yellow_led_on(void)
{
  RED_LED_off();  
  GREEN_LED_off(); 
  YELLOW_LED_on();
  
  //Adding delay to make the transition between each LED more observable
  for (int i = 0; i < 1000000; i++) {}
  for (int i = 0; i < 1000000; i++) {}

}

//Turn off all the led
void reset_led(void)
{
  RED_LED_off();  
  GREEN_LED_off(); 
  YELLOW_LED_off();
  
  //Adding delay to make the transition between each LED more observable
  for (int i = 0; i < 1000000; i++) {}
  for (int i = 0; i < 1000000; i++) {}
}

///////////////////////////////////////////////////////////////////////////
void switch_Init(void)
{
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000001; //activate clock for port A
  
  delay = SYSCTL_RCGC2_R; //allow time for clock to start
  GPIO_PORTA_PCTL_R &= ~0x0FF00000; //PCTL GPIO on PA5, PA6
  
  GPIO_PORTA_AMSEL_R &= ~0x60; //disable analog on PA5, PA6
  GPIO_PORTA_DIR_R &= ~0x60; //set PA5 and PA6 to input
  GPIO_PORTA_AFSEL_R &= ~0x60; //PA5 regular port function
  GPIO_PORTA_DEN_R |= 0x60; //enable PA5 and PA6 as digital port
}

//enable switch 1 when pressed
unsigned long switch_input_1(void)
{
  return (GPIO_PORTA_DATA_R & 0x20); //
  //0x20 (pressed) or 0 (not pressed)
}


//enable switch 2 when pressed
unsigned long switch_input_2(void)
{
  return (GPIO_PORTA_DATA_R & 0x40); //0x40 (pressed) or 0 (not pressed)
}

/*************************************************/
void GPIO_Init() {
  // STEP 3
  //
  // Initialize your GPIO Port for traffic light LEDs
  // and user buttons
  LED_Init();
  switch_Init();
}

/********************************************************/

void StartStop(void *p) {
  // Hint:
  //
  // Static variable will only be decleared once and
  // will retain its last assigned value until the entire
  // program exits
  static int curr_onoff_tick_time = 0;
  static int prev_onoff_tick_time = 0;

  // xTaskGetTickCount() will return the count of ticks
  // since the Task Scheduler started (i.e. your program starts executing).
  //
  // The tick rate (configTICK_RATE_HZ) is defined in FreeRTOSConfig.h,
  // the default rate is 1000 (1KHz), so one tick is equivalent to 1 ms
  //
  // It is similar to the timer we used before, but you'll
  // need to calculate the time elapsed by taking the difference
  // between curr_tick and prev_tick.
  curr_onoff_tick_time = xTaskGetTickCount();

  // STEP 4
  //
  // Complete the implementation of this task function.
  // It checks whether the StartStop button has been
  // pressed for 2 seconds and needs to set the global flags accordingly
  //
  // Task function should never return so is typically
  // implemented as an infinite loop
  //
  // The vTaskDelay(n) will cause the task to enter Blocked state
  // for n system clock ticks. i.e. the task is unblocked
  // after n systicks and will enter Ready State to be arranged for
  // running
  while (1) {
    curr_onoff_tick_time = xTaskGetTickCount();

    // Check whether the user switch is pressed.
    //
    // If the switch has been pressed for 2 or more seconds,
    // set the global flag to 1 and set the prev_tick to be equal
    // to curr_tick (clear the timer). Otherwise clear the global flag.
    //
    // If the user switch is not pressed, clear the global flag and
    // set the prev_tick to curr_tick.
    if (switch_input_1() == 0x20) { // replace this condition checking with something else
      if (curr_onoff_tick_time - prev_onoff_tick_time >= 2000) {
        onoff_status = 1; // Set the global flag
        prev_onoff_tick_time = curr_onoff_tick_time; // Clear the timer
      }
      else {
        onoff_status = 0; // Clear the global flag
      }
    } else {
      onoff_status = 0;// Clear the global flag
      prev_onoff_tick_time = curr_onoff_tick_time; // Clear the timer
    }

    vTaskDelay(1);  
  }
}

void Pedestrian(void *p) {
  static int curr_ped_tick_time = 0;
  static int prev_ped_tick_time = 0;

  // STEP 5
  //
  // Complete the implementation of this task function.
  // It checks whether the pedestrian button has been pressed for
  // 2 seconds and update the global flag accordingly.
  //
  // Implement this based on the StartStop function.
  while (1) {
    curr_ped_tick_time = xTaskGetTickCount();
    
    if (switch_input_2() == 0x40) {
      if (curr_ped_tick_time - prev_ped_tick_time >= 2000) {
        pedestrian_status = 1; //set the global pedestrian flag
        prev_ped_tick_time =  curr_ped_tick_time; //clear the timer
      }
      else {
        pedestrian_status = 0; //clear the global flag
      }
    } else{
      pedestrian_status = 0; //clear the global flag
      prev_ped_tick_time =  curr_ped_tick_time; //clear the timer
    }
    
    vTaskDelay(1);
  }
}

void Control(void *p) {
  static int curr_led_tick_time = 0;
  static int prev_led_tick_time = 0;

  // STEP 6
  //
  // Complete the implementation of this task function.
  // It represents your Finite State Machine.
  while (1) {
    curr_led_tick_time = xTaskGetTickCount();

    // If the led has been lighting up for 5 or more seconds,
    // or if any of the button flag has been set, switch to the
    // corresponding next state and reset the led tick.
    //if (1) {  // replace this condition checking with something else
      // Reset the led tick
      // Switch to next state
    //}
    
    if ((curr_led_tick_time - prev_led_tick_time >= 5000) || pedestrian_status || onoff_status) {
      prev_led_tick_time = curr_led_tick_time; //reset the led tick
      FSM(); //switch to the next state
    }
    vTaskDelay(1);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Define state of the FSM
typedef enum state{
    stop,
    go,
    warn
} state;


//define the event of the FSM
typedef enum event{
  execute,
  halt,
} event;



void FSM(void) {
  // STEP 7
  //
  // Copy your previous FSM implementation into this function.
  // This function will be called by the control task function.
  
  
  event x = halt; //default
  state next_state = go; //default
  state s = stop; //default
  
  while (1) {
    //First state (STOP)
    if (s == stop && next_state == go) {
      
        //if neither of the switch is pressed or switch 1 is pressed
        if ((switch_input_1() == 0x20 && switch_input_2() == 0x0) || x == execute) {
          
          red_led_on(); //red led on
         
          //next state
          s = go;
          next_state = warn;
        }
        
        //turn off all leds
        else {
          reset_led();
        }
    } 
    
    //Second state (GO)
    if ((s == go) && (next_state == warn)) {
      
      //if switched 1 is pressed when being at the green
      if (switch_input_1() == 0x20 && switch_input_2() == 0x0) {
        reset_led(); //turn off all led
        s = stop;  //default
        next_state = go; //default
        x = halt;
      } 
      
      //otherwise, turn on green light
      else {
        green_led_on();
       
        s = warn;
        next_state = stop;
        x = execute;
      }
    } 
    
    //Third state (WARN)
    if (s == warn && next_state == stop) {
      
      //if switch 2 is pressed, turn on yellow light
      if (switch_input_1() == 0x0 && switch_input_2() == 0x40) {
        yellow_led_on();
      }
      //otherwise, go back to stop state
      s = stop;
      next_state = go;
    }
  }
}
/////////////////////////////////////////////////////////////////////





