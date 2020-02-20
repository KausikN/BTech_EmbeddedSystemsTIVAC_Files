int main()
{
  int x, y, z;
  
  // equal
  x = 5, y = 5;
  z = 5;
  if (x == y)                   // Sets equal bit
    z++;
  if (x == y+1)                 // Clears equal bit
    z--;
  
  // negative
  x = 5;
  y = 4;
  z = y - x;                    // Sets negative bit
  z = x - y;                    // Clears negative bit
  
  // carry
  x = 4;                        // 100 in binary
  y = x >> 2;                   // Clears Carry as 0 goes to carry bit
  y = y >> 1;                   // Sets Carry as 1 goes to carry bit

  // overflow
  int maxVal = 2147483647;      // Maximum value represented in int format
  int overflowVal = maxVal + 1; // Sets overflow bit
  int x2 = overflowVal - 1;     // Clears overflow bit
  
  return 0;
}
