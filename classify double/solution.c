
#include <stdio.h>

#include <stdbool.h>

#include <stdint.h>

#include <stdlib.h>


uint64_t convertToUint64 (double number) {

    return *((uint64_t *)(&number));

}

double convertToDouble (uint64_t number) {

    return *((double *)(&number));

}

bool getBit (const uint64_t number, const uint8_t index) {

    /// Your code here...

    uint64_t mask = 1 << index;

    uint64_t temp = mask & number;

    temp >>= index;

    return temp;

}

bool checkForPlusZero (uint64_t number) {

    return number == 0x0000000000000000;

}

 

bool checkForMinusZero (uint64_t number) {

    return number == 0x8000000000000000;

}

bool checkForPlusInf (uint64_t number) {

    return((getBit(number,63) == 0) 
    && (((number << 1) >> 53) == 0x7ff) 
    && (((number << 12) >> 12) == 0));
 
}

bool checkForMinusInf (uint64_t number) {

    return((getBit(number,63) == 1) 
    && (((number << 1) >> 53) == 0x7ff) 
    && (((number << 12) >> 12) == 0));

}

bool checkForPlusNormal (uint64_t number) {

    return((getBit(number,63) == 0)
    && (((number << 1) >> 53) > 0)
    && (((number << 1) >> 53) < 0x7ff));

}

bool checkForMinusNormal (uint64_t number) {

    return((getBit(number,63) == 1)
    && (((number << 1) >> 53) > 0)
    && (((number << 1) >> 53) < 0x7ff));

}

bool checkForPlusDenormal (uint64_t number) {

        // return(!(number>>52));
    return((getBit(number,63) == 0) 
    && (((number << 1) >> 53) == 0));
}

bool checkForMinusDenormal (uint64_t number) {

        // return((number>>52) == 0x800);
    return((getBit(number,63) == 1) 
    && (((number << 1) >> 53) == 0));

}

bool checkForSignalingNan (uint64_t number) {

    return((((number << 1) >> 53) == 0x7ff) 
    && (((number << 12) >> 63) == 0));
    // && (getBit(number,51) == 0));

}

bool checkForQuietNan (uint64_t number) {

    return((((number << 1) >> 53) == 0x7ff) 
    && (((number << 12) >> 63) == 1));

}

void classify (double number) {

    //  printf("%016llx \n", convertToUint64(number));
    //  printf("sign: %x \n", getBit(convertToUint64(number),63));
    // printf("fracture: %016llx \n", ((convertToUint64(number) << 12) >> 63));
    //  printf("exponent: %03llx \n", ((convertToUint64(number) << 1) >> 53));
    //  printf("fracture: %012llx \n", ((convertToUint64(number) << 12) >> 12));
     
    if (checkForPlusZero(convertToUint64(number))) {

        printf("Plus zero\n");

    }

    else if (checkForMinusZero(convertToUint64(number))) {

        printf("Minus zero\n");

    }

    else if (checkForPlusDenormal(convertToUint64(number))) {

        printf("Plus Denormal\n");

    }

    else if (checkForMinusDenormal(convertToUint64(number))) {

        printf("Minus Denormal\n");

    }

    else if (checkForPlusInf(convertToUint64(number))) {

        printf("Plus inf\n");

    }

    else if (checkForMinusInf(convertToUint64(number))) {

        printf("Minus inf\n");

    }

    else if (checkForPlusNormal(convertToUint64(number))) {

        printf("Plus normal\n");

    }

    else if (checkForMinusNormal(convertToUint64(number))) {

        printf("Minus normal\n");

    }

    else if (checkForSignalingNan(convertToUint64(number))) {

        printf("Signailing NaN\n");

    }

    else if (checkForQuietNan(convertToUint64(number))) {

        printf("Quiet NaN\n");

    }

    else {

        printf("Error.\n");

    }

}
