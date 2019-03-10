#define A 0
#define C 1
#define T 2
#define G 3
// Function to convert a number from given base 'b'
// to decimal
int charToInt(char c){
    if(c=='A'){
        return A;
    }
    if(c=='C'){
        return C;
    }
    if(c=='G'){
        return G;
    }
    if(c=='T'){
        return T;
    }
    return 4;
}

int toDeci(string str, int base)
{
    int len = (str).length();
    int power = 1; // Initialize power of base
    int num = 0;  // Initialize result
    int i;

    // Decimal equivalent is str[len-1]*1 +
    // str[len-1]*base + str[len-1]*(base^2) + ...
    for (i = len - 1; i >= 0; i--)
    {
        // A digit in input number must be
        // less than number's base
        if (charToInt(str[i]) >= base)
        {
           printf("Invalid Number");
           return -1;
        }

        num += charToInt(str[i]) * power;
        power = power * base;
    }

    return num;
}



    // for (size_t i = 0; k1 - i + 1 >= k; i++) {
    //     string kmer = k1mer.substr(i, k);
    // }
