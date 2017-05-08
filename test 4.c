 /*
  * Author: Umut Berk Bilgiç
  * Bilkent University Computer Science - CS224 Lab 6
  * Following code displays the fibonacci sequence on a 4 digit seven segment
  *     display array. It spesifically utilizes a multiplexed seven segment
  *     display aray that is expandable.
  */
  
// init
int i, j, k, temp, cur, speed, counter;
int fib, dig_1, dig_2, dig_3, dig_4;

// LUT for seven segment display characters (0 to 9)
unsigned char seg[10]  = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

// LUT for anode values {1110, 1101, 1011, 0111}
unsigned char anode[4] = {0x07, 0x0B, 0x0D, 0x0E};

// MAIN
void main()
{
    // Set analog ports to digital and disable jtag
    AD1PCFG = 0xFFFF;
    DDPCON.JTAGEN = 0;
    
    // Se TRISx registers for the ports that will be used
    TRISD = 0x0000;
    TRISE = 0x0000;
    
    // Init. ports
    PORTE = 0x0000;
    PORTD = 0xFFFF;
    
    // elements for fibonacci addition
    i = 0;
    j = 1;
    
    // tracks which stage of fibonacci sequence the program is at
    cur = 1;
    
    // speed * 4 (ms) is the update time
    speed = 250;
    
    // counter for resetting the sequence
    counter = 0;
     
    while(1) // main loop
    {
         fib = i + j;
        
         // basic fibonacci calculation
         if (cur == 1)
         {
             i = i + j;
             cur = 0;
         }
         else
         {
             j = i + j;
             cur = 1;
         }
         
         counter++;
         
         // setup a temporary variable for digit calculation
         temp = fib;
         
         // calculate digit indexes
         dig_1 = temp % 10;
         temp = temp / 10;
         
         dig_2 = temp % 10;
         temp = temp / 10;
         
         dig_3 = temp % 10;
         temp = temp / 10;

         dig_4 = temp % 10;

         // show the same number k times
         for (k = 0; k < speed; k++)
         {
             // digit 1
             PORTD = ~seg[dig_1];
             PORTE = ~anode[0];
             Delay_ms(1);

             // digit 2
             PORTD = ~seg[dig_2];
             PORTE = ~anode[1];
             Delay_ms(1);

             // digit 3
             PORTD = ~seg[dig_3];
             PORTE = ~anode[2];
             Delay_ms(1);

             // digit 4
             PORTD = ~seg[dig_4];
             PORTE = ~anode[3];
             Delay_ms(1);
         }
         
         // reset fibonacci sequence if it gets too big for 4 digits
         if(counter == 19)
         {
             i = 0;
             j = 1;
             cur = 1;
             counter = 0;
         }
     }
}