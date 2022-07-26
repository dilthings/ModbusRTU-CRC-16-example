/* Working example of calculating Modbus RTU checksum
* Dilan 26-Jul-2022 
* Original code from https://www.cyberforum.ru/csharp-beginners/thread2329096.html and other websites
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compute the MODBUS RTU CRC
int16_t ModRTU_CRC(char* buf, int len)
{
  u_int16_t crc = 0xFFFF;
  
  for (int pos = 0; pos < len; pos++) {
    crc ^= (u_int16_t)buf[pos];          // XOR byte into least sig. byte of crc
  
    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;  
}

int main(int argc, char *argv[]){

    if (argc < 2){
        printf("Usage: crc16 <hex char xxxxxxxxxxx>");
    }

    printf("String = %s  length = %ld --> ModbusRTU - CRC16 = 0x%02hX\n", argv[1], strlen(argv[1]), ModRTU_CRC(argv[1], strlen(argv[1])));

    return 0;
}


