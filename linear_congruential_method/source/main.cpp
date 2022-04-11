#include <iostream>
#include <vector>

#define X_AMOUNT 4
#define MAX_MOD 65535

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

/**
 * Calculate greatest common divisor
 * \param a, b unsigned numbers
 * \return greatest common divisor
 */
ushort gcd(ushort a, ushort b) {
    if (a == 0 || b == 0)
        return 0;

    if (a < b) {
        ushort temp = b;
        b = a;
        a = temp;
    }
    ushort remainder = b;

    do {
        b = remainder;
        remainder = a % b;
        a = b;
    } while (remainder != 0);
    return b;
}

/**
 * Calculate module inverse
 * \param num unsigned number
 * \param module ring base
 * \return num^-1
 */
ushort inverse(ushort num, ushort module) {
    int b1 = module, b2 = 0;
    int a1 = num, a2 = 1;

    while (a1 != 0) {
        int q = b1 / a1;
        int temp1 = b1 - q * a1;
        int temp2 = b2 - q * a2;
        b1 = a1;
        b2 = a2;
        a1 = temp1;
        a2 = temp2;
    }
    if (b1 != 1)
        throw std::runtime_error("Inverse does not exist");
    return (b2 + module) % module;
}

/**
 * Find max element in vector
 * \param vec vector
 * \result max elem in vec
 */
ushort maximum(std::vector<ushort> vec) {
    ushort max = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        if (max < vec[i])
            max = vec[i];
    }
    return max;
}

/**
 * Calculate determinate of matrix
 * \param matrix matrix 3x3
 * \result determinate
 */
ulong det(ushort matrix[3][3]) {
    return matrix[0][0] * matrix[1][1] * matrix[2][2]
        + matrix[0][1] * matrix[1][2] * matrix[2][0]
        + matrix[0][2] * matrix[1][0] * matrix[2][1]
        - matrix[0][2] * matrix[1][1] * matrix[2][0]
        - matrix[0][1] * matrix[1][0] * matrix[2][2]
        - matrix[0][0] * matrix[1][2] * matrix[2][1];
}

/**
 * Check solution
 * \param x vector
 * \param multiplier variable a in the task
 * \param increment variable c in the task
 * \param module variable m in the task
 * \return true, if solution correct
 */
bool check(std::vector<ushort> x, ushort multiplier, ushort increment, ushort module) {
    for (int i = 1; i < x.size(); i++) {
        if (x[i] != (multiplier * x[i - 1] + increment) % module)
            return false;
    }
    return true;
}

/**
 * Calculate next x
 * \param vec array of latest x
 * \return next x value
 * \throw std::runtime_error if next x could not calculate
 */
ushort getNext(std::vector<ushort> vec) {
    ushort matrix[3][3] = {
        {vec[0], vec[1], 1},
        {vec[1], vec[2], 1},
        {vec[2], vec[3], 1}
    };
    ulong determinate = abs(det(matrix));

    for (ushort module = maximum(vec) + 1; module < MAX_MOD; module++) {
        if (determinate % module)
            continue;
        
        ushort mul = (vec[2] - vec[1] + module) % module;
        ushort div = gcd(mul, (vec[1] - vec[0] + module) % module);
        try {
            mul = (mul / div * inverse(((vec[1] - vec[0]) / div + module) % module, module));
        } catch (std::runtime_error &exception) {
            continue;
        }
        ushort inc = (vec[1] - mul * vec[0] + module) % module;
        
        if (check(vec, mul, inc, module)) {
            return (mul * vec[vec.size() - 1] + inc) % module;
        }
    }
    throw std::runtime_error("Next vec does not exist");
}

int main() {
    std::vector<ushort> x;
    for (int i = 0; i < X_AMOUNT; i++) {
        uint num;
        std::cin >> num;
        x.push_back(num);
    }

    try {
        std::cout << getNext(x) << '\n';
    } catch (std::runtime_error &exception) {
        std::cout << exception.what();
    }
    return 0;
}