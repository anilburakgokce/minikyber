def modexp(base, exp, mod):
    if exp < 0:
        print("Exponent is less than 0!")
        return -1
    if mod < 0:
        print("Mod is less than 0!")
        return -1
    if base < 0:
        print("Base is less than 0!")
        return -1
    if base == 0:
        return 0
    if base > mod:
        base = base % mod

    res = 1
    for i in range(exp):
        res = (res * base) % mod
    return res


q = 3329
n = 32

root = 0
root_set = False
for i in range(q):
    res = modexp(i, n//2, q)
    if(res == (q - 1)):
        root = i
        root_set = True
        break

print("root = " + (str(i) if root_set else "is not found!"))