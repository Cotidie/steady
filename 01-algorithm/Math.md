# Math
Here explains a set of mathematical theorems frequently used in problem solving. 

## GCD, LCM
 Euclidean Algorithm is largely used to get GCD(Greatest Common Divisor) and LCM(Least Common Multiplier). Once we get GCD, `LCD(a, b)` will be:
    `LCD = GCD * (a / GCD) * (b / GCD)`

### Algorithm
![Euclidean](https://i.imgur.com/ruLGHtH.png)  
1. Get remainder `r` of `a % b` 
2. Repeat division between `b` and `r`
3. If `r` is zero, then `b` is the `GCD(a, b)`
   - `LCD(a, b) = a*b / GCD(a, b)`

### Python Code
```py
def gcd(a, b):
  if b == 0:
    return a:
  else:
    return gcd(b, (a % b))
```

## Chinese Remainder
![Chinese Remainder](https://i.imgur.com/0ywAIur.png)  
Chinese Remainer problem is about finding an `x` where it satisfies multiple modulo conditions. Moduli must be coprime to prevent from getting into a cycle in calculation. While manual trials would work, **extended euclidean algorithm** can be used for optimization.

### Algorithm
![algorithm](https://i.imgur.com/81ZYgth.png)  
1. Ensure all the moduli are coprimes. If not, break into coprimes.
    - Otherwise it will fall into a cycle in the step 3.
    - ex) `10 (mod 24)` into `10 mod 8` and `10 mod 3`
2.  Let `x` be the sum of moduli like the picture above.
3.  For each modulus, multiply until it meets modulo condition.
    - ex) x mod 4 ≡ 3, then multiply it by 2. Now `x` is `x = 4*5 + 3*5*2 + 3*4` 
