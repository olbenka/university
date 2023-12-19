def encrypt(message, key):

    rows = len(message) // key
    if len(message) % key != 0:
        rows += 1

    matrix = [[' ' for _ in range(key)] for _ in range(rows)]
    index = 0
    for i in range(rows):
        for j in range(key):
            if index < len(message):
                matrix[i][j] = message[index]
                index += 1

    encrypted_message = ""
    for j in range(key):
        for i in range(rows):
            encrypted_message += matrix[i][j]

    return encrypted_message


def decrypt(encrypted_message, key):
    rows = len(encrypted_message) // key
    if len(encrypted_message) % key != 0:
        rows += 1

    matrix = [[' ' for _ in range(key)] for _ in range(rows)]
    index = 0
    for j in range(key):
        for i in range(rows):
            if index < len(encrypted_message):
                matrix[i][j] = encrypted_message[index]
                index += 1

    decrypted_message = ""
    for i in range(rows):
        for j in range(key):
            decrypted_message += matrix[i][j]

    return decrypted_message


def caesar_cipher(text, shift):
    result = ""
    for char in text:
        if char.isalpha():
            # Определение регистра (верхний или нижний)
            is_upper = char.isupper()

            # Преобразование в верхний регистр для удобства работы
            char = char.upper()

            # Применение шифра Цезаря
            encrypted_char = chr((ord(char) + shift - ord('A')) % 26 + ord('A'))

            # Возврат к исходному регистру
            result += encrypted_char if is_upper else encrypted_char.lower()
        else:
            # Символы, не являющиеся буквами, остаются неизменными
            result += char

    return result

if __name__ == '__main__':
    print("Перестановка: ")
    print("Введите предложение: ")
    message = input()
    print("Введите ключ: ")
    key = int(input())

    encrypted_message = encrypt(message, key)
    print("Зашифрованное сообщение:", encrypted_message)

    decrypted_message = decrypt(encrypted_message, key)
    print("Расшифрованное сообщение:", decrypted_message)

    print("Цезарь: ")
    print("Введите сдвиг: ")
    shift_value = int(input())

    encrypted_text = caesar_cipher(message, shift_value)
    print("Зашифрованный текст:", encrypted_text)

    decrypted_text = caesar_cipher(encrypted_text, -shift_value)
    print("Расшифрованный текст:", decrypted_text)

