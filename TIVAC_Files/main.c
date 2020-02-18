int main()
{
  int x, y, z;
  
  // equal
  x = 1, y = 1;
  z = 5;
  if (x == y)   // Sets equal bit
    z++;
  if (x == y+1) // Clears equal bit
    z--;
  
  // overflow
  int maxVal = 2147483647;      // Maximum value represented in int format
  int overflowVal = maxVal + 1; // Sets overflow bit
  int x2 = overflowVal - 1; // Clears overflow bit
  
  // carry
  x = 2;      // 10
  y = x >> 1; // Clears Carry as 0 goes to carry bit
  y = y >> 1; // Sets Carry as 1 goes to carry bit
  
  // negative
  x = 5;
  y = 4;
  z = y - x; // Sets negative bit
  z = x - y; // Clears negative bit
  
  return 0;
}
