
#include "wireless.h"

void wireless_part_number(void){

	printf("Part Number: %d\n", CC2500_read_one(0x30|0xC0));

}

