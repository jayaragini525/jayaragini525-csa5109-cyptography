from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

def encrypt_ecb(key, plaintext):
    cipher = AES.new(key, AES.MODE_ECB)
    padded_plaintext = pad(plaintext, AES.block_size)
    ciphertext = cipher.encrypt(padded_plaintext)
    return ciphertext

def decrypt_ecb(key, ciphertext):
    cipher = AES.new(key, AES.MODE_ECB)
    decrypted_text = cipher.decrypt(ciphertext)
    plaintext = unpad(decrypted_text, AES.block_size)
    return plaintext

def encrypt_cbc(key, plaintext, iv):
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded_plaintext = pad(plaintext, AES.block_size)
    ciphertext = cipher.encrypt(padded_plaintext)
    return ciphertext

def decrypt_cbc(key, ciphertext, iv):
    cipher = AES.new(key, AES.MODE_CBC, iv)
    decrypted_text = cipher.decrypt(ciphertext)
    plaintext = unpad(decrypted_text, AES.block_size)
    return plaintext

def encrypt_cfb(key, plaintext, iv):
    cipher = AES.new(key, AES.MODE_CFB, iv)
    ciphertext = cipher.encrypt(plaintext)
    return ciphertext

def decrypt_cfb(key, ciphertext, iv):
    cipher = AES.new(key, AES.MODE_CFB, iv)
    decrypted_text = cipher.decrypt(ciphertext)
    return decrypted_text

# Example usage
key = get_random_bytes(16)  # 128-bit key
iv = get_random_bytes(AES.block_size)

plaintext = b'This is a sample plaintext.'

# ECB
ecb_ciphertext = encrypt_ecb(key, plaintext)
ecb_decrypted_text = decrypt_ecb(key, ecb_ciphertext)

# CBC
cbc_ciphertext = encrypt_cbc(key, plaintext, iv)
cbc_decrypted_text = decrypt_cbc(key, cbc_ciphertext, iv)

# CFB
cfb_ciphertext = encrypt_cfb(key, plaintext, iv)
cfb_decrypted_text = decrypt_cfb(key, cfb_ciphertext, iv)

print(f'Original Text: {plaintext}')
print(f'ECB Decrypted Text: {ecb_decrypted_text}')
print(f'CBC Decrypted Text: {cbc_decrypted_text}')
print(f'CFB Decrypted Text: {cfb_decrypted_text}')
