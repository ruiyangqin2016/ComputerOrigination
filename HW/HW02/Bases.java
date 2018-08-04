/**
 * CS 2110 Summer 2018 HW2
 * Part 2 - Coding with bases
 *
 * @author Ruiyang Qin
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not declare any objects, other than String in select methods.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   decimalStringToInt.
 * - You may declare exactly one String variable each in intToBinaryString and
 *   and intToHexString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
        int returnNumber = 0;
        int pow = 1;
        for (int i = binary.length() - 1; i >= 0; i--) {
            if (binary.charAt(i) == '1') {
                if (i == binary.length() - 1) {
                    returnNumber += 1;
                } else {
                    returnNumber += pow;
                }
            }
            pow += pow;
        }
        return returnNumber;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("123"); // => 123
     *
     * You may use multiplication, division, and modulus in this method.
     */
    public static int decimalStringToInt(String decimal)
    {
        int returnNumber = 0;
        for (int i = 0; i < decimal.length(); i++) {
            int number = decimal.charAt(i) - 48;
            returnNumber = returnNumber * 10 + number;
        }
        return returnNumber;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     * The input string will only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: hexStringToInt("A6"); // => 166
     */
    public static int hexStringToInt(String hex)
    {
        int returnNumber = 0;
        int hexPow = 1;
        int count = 4;
        int iIncrement = 0;
        for (int i = hex.length() - 1; i >= 0; i--) {
            if(hex.charAt(i) <58) { // 0 1 2 3 4 5 6 7 8 9
                int number = hex.charAt(i) - 48;
                returnNumber = returnNumber + (number << iIncrement);
            } else { // A(10) B(11) C(12) D(13) E(14) F(15)
                int number = hex.charAt(i) - 55;
                returnNumber = returnNumber + (number << iIncrement);
            }
            hexPow = 0 ^ (1 << count);
            count += 4;
            iIncrement += 4;
        }
        return returnNumber;
    }

    /**
     * Convert a int into a String containing ASCII characters (in binary).
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToBinaryString(7); // => "111"
     *
     * You may declare one String variable in this method.
     */
    public static String intToBinaryString(int binary)
    {
        String holdBits = "";
        if (binary == 0) {
            holdBits = "0";
        }
        while (binary != 0) {
            if ((binary & 0x1) == 0x1) {
                holdBits = "1" + holdBits;
            } else {
                holdBits = "0" + holdBits;
            }
            binary = binary >> 1;
        }

        return holdBits;
    }

    /**
     * Convert a int into a String containing ASCII characters (in hexadecimal).
     * The output string should only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToHexString(166); // => "A6"
     *
     * You may declare one String variable in this method.
     */
    public static String intToHexString(int hex)
    {
        String holdBits = "";
        if (hex == 0) {
            holdBits = "0";
        }
        while (hex != 0) {
            int bitNumber = hex & 0xF;
            if(bitNumber < 10) { // 0 1 2 3 4 5 6 7 8 9
                holdBits = (char)(bitNumber + 48) + holdBits;
            } else { // A(10) B(11) C(12) D(13) E(14) F(15)
                holdBits = (char)(bitNumber + 55) + holdBits;
            }
            hex = hex >> 4;
        }

        return holdBits;
    }
}
