#include <iostream>
#include "segy.h"

int main () {
	
	segy sgy;
	sgy.OpenFile("npr3_field.sgy");
    sgy.PrintTextHeader();
	sgy.PrintBinaryHeader();
    sgy.PrintTraceHeader();
}
