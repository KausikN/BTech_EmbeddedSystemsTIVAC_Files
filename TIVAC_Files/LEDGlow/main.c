int main()
{
    // C Bit - Carry Checking bit

    int valueX = 8;
    int result;
    result = valueX >> 3;               // This sets(Clears) Carry Bit as 0
    result = result >> 1;               // This sets Carry Bit as 1

    return 0;
}