def is_prime(num):
    if num < 2:
        return False
    for i in range(2, int(num**0.5) + 1):
        if num % i == 0:
            return False
    return True

def find_primes():
    n = 3599
    for p in range(2, n):
        if is_prime(p) and n % p == 0:
            q = n // p
            if is_prime(q):
                return p, q

def extended_gcd(a, b):
    if a == 0:
        return b, 0, 1
    else:
        g, x, y = extended_gcd(b % a, a)
        return g, y - (b // a) * x, x

def modinv(a, m):
    g, x, y = extended_gcd(a, m)
    if g != 1:
        raise Exception('Modular inverse does not exist')
    else:
        return x % m

# Given values
e = 31
n = 3599

# Calculate p and q
p, q = find_primes()

# Calculate phi(n)
phi_n = (p - 1) * (q - 1)

# Calculate private key
d = modinv(e, phi_n)

print("p =", p)
print("q =", q)
print("Private key (d) =", d)


