import binascii

flag = b'40BYTECTF{?IS-THAT-DATA-I-SEE?}'
key = 0x42
#hex_flag = [118, 70, 4, 93, 9, 76, 15, 91, 29, 102, 89, 16, 67, 28, 72, 0, 65, 21, 56, 124, 61, 105, 40, 119, 62, 19, 64, 5, 64, 127, 2]
hex_flag = [0x76, 0x46, 0x4, 0x5d, 0x9, 0x4c, 0xf, 0x5b, 0x1d, 0x66, 0x59, 0x10, 0x43, 0x6e, 0x3a, 0x72, 0x33, 0x67, 0x4a, 0xe, 0x4f, 0x1b, 0x5a, 0x77, 0x3e, 0x13, 0x40, 0x5, 0x40, 0x7f, 0x2]

def encrypt(flag, key):
    result = list()
    prev = key
    for b in flag:
        b = b ^ prev;
        prev = b;
        result.append(b)
    print("Hex encrypt:")
    print('[{}]'.format(', '.join(hex(x) for x in result)))
    result = bytes(result)
    return result

def decrypt(flag, key):
    result = list()
    prev = key
    for b in flag: # iter flag bytes
        c = b ^ prev; # xor
        prev = b;
        result.append(c)
    result = bytes(result)
    return result

if __name__ == '__main__':
    print("Generating flag from...")
    print("Flag: {}".format(flag))
    print("Key: {}".format(key))
    encrypted = encrypt(flag, key)
    print("Encrypted: {}".format(encrypted))
    decrypted = decrypt(encrypted, key)
    print("Decrypted: {}".format(decrypted))
    decrypted = decrypt(bytes(hex_flag), key)
    print("Hex: {}".format(hex_flag))
    print("Decrypted hex: {}".format(decrypted))
