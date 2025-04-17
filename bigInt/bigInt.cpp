#include <iostream>

class BigInt {
private:
    bool isNegative;
    int* digitArray;
    int digitNumber;
    int capacity;
    void trimZeros();
public:
    int getLength();
    BigInt();
    BigInt(const char *);
    void print();
    BigInt operator+(BigInt);
    BigInt operator-(BigInt);
    void operator=(BigInt);

};

int BigInt::getLength() {
    return capacity;
}

void BigInt::trimZeros() {
    int size = capacity;
    for (int i = capacity ; i >= 0 && digitArray[i]!= 0; i--) {
        size--;

    }
    capacity = size;
}

BigInt::BigInt() {
    isNegative = false;
    
}

BigInt::BigInt(const char* str) {
    int len =0;
    while (str[len]) {
        len++;
    }
    capacity = len;
    digitArray = new int[capacity];
    for (int i = 0; i < len; i++) {
        digitArray[i] = str[len - i - 1] - '0';
    }
}

void BigInt::print() {
    for(int i=capacity -1 ; i >=0 ; i--){
        std::cout << digitArray[i];
    }
}

BigInt BigInt::operator+(BigInt next) {
    BigInt result("0");
    int maxLength;
    if (capacity > next.getLength()) {
        maxLength = capacity;
        result.capacity = maxLength;
    }
    else {
        maxLength = next.getLength();
        result.capacity = maxLength;
    }

    result.capacity = maxLength + 1;
    result.digitArray = new int[result.capacity]();

    int carry = 0;

    for (int i = 0; i < result.capacity; i++) {
        int a = (i < capacity) ? digitArray[i] : 0;
        int b = (i < next.capacity) ? next.digitArray[i] : 0;
        int sum = a + b + carry;
        carry = sum / 10;
        result.digitArray[i] = sum % 10;
    }

    result.trimZeros();
    return result;
    
}

BigInt BigInt::operator-(BigInt next) {
    BigInt result("0");
    int maxLength;
    if (capacity > next.getLength()) {
        maxLength = capacity;
        result.capacity = maxLength;
    }
    else {
        maxLength = next.getLength();
        result.capacity = maxLength;
    }

    result.capacity = maxLength + 1;
    result.digitArray = new int[result.capacity]();

    int borrow = 0;

    for (int i = 0; i < result.capacity; i++) {
        int a = (i < capacity) ? digitArray[i] : 0;
        int b = (i < next.capacity) ? next.digitArray[i] : 0;
        a -= borrow;
        
        if (b > a) {
            a += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result.digitArray[i] = a - b;
        
    }

    result.trimZeros();
    return result;

}

void BigInt::operator=(BigInt next) {
    capacity = next.capacity;
    digitArray = new int[next.capacity];
    for (int i = 0; i < next.capacity; i++) {
        digitArray[i] = next.digitArray[i];
    }
}


int main()
{
    BigInt bigint("9999999999999999999910");
    BigInt num2("2");
    BigInt num3("0");
    num3 = bigint + num2;
    num3.print();

    std::cout << '\n';

    num3 = bigint - num2;
    num3.print();
    
}
