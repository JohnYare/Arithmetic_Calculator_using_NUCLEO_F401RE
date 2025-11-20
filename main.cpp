#include "mbed.h"
#include "TextLCD.h"
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>

DigitalOut ROW1 (PA_6);
DigitalOut ROW2 (PA_7);
DigitalOut ROW3 (PB_6);
DigitalOut ROW4 (PC_7);
DigitalIn COL1 (PA_9, PullUp);
DigitalIn COL2 (PA_8, PullUp);
DigitalIn COL3 (PB_10, PullUp);
DigitalIn COL4 (PB_4, PullUp);


int col_scan(void);
char keypad_scan (void);

//TextLCD lcd(RS, E, D4, D5, D6, D7);                          // RS, E, D4-D7, LCDType=LCD16x2, BL=NC, E2=NC, LCDTCtrl=HD44780
TextLCD lcd(PA_0, PA_1, PA_4, PB_0, PC_1, PC_0);

extern "C" int add_asm(int operand_1, int operand_2);
extern "C" int sub_asm(int operand_1, int operand_2);
extern "C" int mul_asm(int operand_1, int operand_2);
extern "C" int div_asm(int operand_1, int operand_2);

int main() {
    bool valid_number = false;
    string numString = "";
    stringstream convertToInt;
    int numInt;
    char key = 'n';
    int operand_1;
    int operand_2;
    
    while(1) {
        valid_number = false;
        // Get the first operand        
        while (valid_number == false) {
            lcd.cls();
            lcd.printf("NO 1: ");
            
            while (key != '#') {
                key = keypad_scan();
                wait(0.3);
                
                if (key != 'n' && key != '#'){ 
                    if (key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*') {                
                        numString += key;                    
                        lcd.printf("%c", key);
                        wait(0.3);
                    }
                    
                    else {
                        lcd.cls();
                        lcd.printf("ERROR");
                        wait(1);
                        numString = "";
                        break;
                    }
                
                }
                
            }
        if (numString.size() > 0) {    
        convertToInt.clear(); //clears the content of stringstream object
        convertToInt.str(numString); //transfers string content into stringstream object
        convertToInt >> numInt; //outputs integer from stringstream object 
        valid_number = true;
        operand_1 = numInt;
        }
        }  

        // Get the second operand
        valid_number = false;
        key = 'n';
        numString = "";        
        
        while (valid_number == false) {
            lcd.cls();
            lcd.printf("NO 2: ");

            while (key != '#') {
                key = keypad_scan();
                wait(0.3);
                
                if (key != 'n' && key != '#'){ 
                    if (key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*') {                
                        numString += key;                    
                        lcd.printf("%c", key);
                        wait(0.3);
                    }
                    
                    else {
                        lcd.cls();
                        lcd.printf("ERROR");
                        wait(1);
                        numString = "";
                        break;
                    }
                
                }
            }
            if (numString.size() > 0) {    
            convertToInt.clear(); //clears the content of stringstream object
            convertToInt.str(numString); //transfers string content into stringstream object
            convertToInt >> numInt; //outputs integer from stringstream object 
            valid_number = true;
            operand_2 = numInt;
            }
        }

        
        // Get the operation
        valid_number = false;
        key = 'n';
        numString = "";      
        
        while (valid_number == false) {
            lcd.cls();
            lcd.printf("SELECT OPERATOR: ");
            
            key = keypad_scan();
            wait (0.3);
            if (key != 'n') {
                if (key == 'A'){
                    lcd.cls();
                    lcd.printf("%d + %d = %d", operand_1, operand_2, add_asm(operand_1, operand_2));
                    
                    wait(2);
                    valid_number = true;
                }
            
                if (key == 'B'){
                    lcd.cls();
                    lcd.printf("%d - %d = %d", operand_1, operand_2, sub_asm(operand_1, operand_2));
                    wait(2);
                    valid_number = true;
                }

                if (key == 'C'){
                    lcd.cls();
                    lcd.printf("%d * %d = %d", operand_1, operand_2, mul_asm(operand_1, operand_2));
                    wait(2);
                    valid_number = true;
                }

                if (key == 'D'){
                    lcd.cls();
                    lcd.printf("%d / %d = %d", operand_1, operand_2, div_asm(operand_1, operand_2));
                    wait(2);
                    valid_number = true;
                }

                if (key != 'A' && key != 'B' && key != 'C' && key != 'D'){
                    lcd.cls();
                    lcd.printf("ERROR");
                    wait(2);
                    numString = ""; 
                }
            }
        }
    }
}

int col_scan (void) {
    if (COL1 == 0){
        return 0;
    }
    else if (COL2 == 0){
        return 1;
    }
    else if (COL3 == 0){
        return 2;
    }
    else if (COL4 == 0){
        return 3;
    }
    else {
    return 5;
    }
}
char keypad_scan (void) {
char key_map[4][4] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

    for (int i = 1; i <= 4; ++i) {
        if (i == 1) {
            ROW1 = 0; 
            ROW2 = ROW3 = ROW4 = 1;
        }
        if (i == 2) {
            ROW1 = ROW3 = ROW4 = 1;
            ROW2 = 0;
        }
        if (i == 3) {
            ROW3 = 0;
            ROW1 = ROW2 = ROW4 = 1;
        }
        if (i == 4) {
            ROW4 = 0;
            ROW1 = ROW2 = ROW3 = 1;
        }
     
        int row = i - 1;
        int col = col_scan();
        if (col == 0) {
            return key_map[row][col];
        }
        if (col == 1) {
            return key_map[row][col];
        }
        if (col == 2) {
            return key_map[row][col];
        }
        if (col == 3) {
            return key_map[row][col];
        }
    
    }
    return 'n';
}