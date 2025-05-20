import sys

def parse_file(file_path):
    data = {
        'id': None,
        'type': None,
        'speed': None,
        'text': None,
        'functions': []
    }

    in_func = False

    with open(file_path, 'rb') as f:  # Открываем файл в бинарном режиме
        for line in f:
            line = line.strip()
            if not line:
                continue

            # Декодируем строку (если нужно)
            try:
                line = line.decode('utf-8')
            except UnicodeDecodeError:
                continue  # Пропускаем бинарные строки, которые нельзя декодировать

            if line.startswith('ID='):
                data['id'] = line.split('=')[1].strip()
            elif line.startswith('TYPE='):
                data['type'] = line.split('=')[1].strip()
            elif line.startswith('SPEED='):
                data['speed'] = line.split('=')[1].strip()
            elif line.startswith('TEXT='):
                text_value = line.split('"')[1] if '"' in line else ''
                data['text'] = text_value
            elif line == 'FUNC':
                in_func = True
            elif line == 'END':
                in_func = False
            elif in_func:
                if line.startswith('F'):
                    func_name, rest = line.split('=', 1)
                    func_name = func_name.strip()
                    print(line)
                    
                    
                    # Разделяем строку по ';' (без очистки кавычек, так как это бинарные данные)
                    parts = rest.split(';')
                    if len(parts) != 3:
                        continue

                    # Парсим количество переменных (1-й байт)
                    num_vars = int.from_bytes(parts[0].encode('utf-8'), byteorder='little')
                    if not (1 <= num_vars <= 16): continue


                    # Парсим битовый вектор (n-й байт)
                    bits_vector = parts[1].encode('utf-8')
                    

                    # Парсим битовую маску (2 байта)
                    try:
                        bit_mask = int.from_bytes(parts[2].encode('utf-8'), byteorder='little')
                    except:
                        continue

                    func_data = {
                        'name': line.split('=')[0].strip(),
                        'num_vars': num_vars,
                        'bits_vector': bits_vector,
                        'bit_mask': bit_mask
                    }
                    data['functions'].append(func_data)

    return data


def print_data(data):
    print(f"ID: {data['id']}")
    print(f"TYPE: {data['type']}")
    print(f"SPEED: {data['speed']}")
    print(f"TEXT: {data['text']}")
    print("Функции:")
    for func in data['functions']:
        print(f"  {func['name']}:")
        print(f"    Количество переменных: {func['num_vars']}")
        print(f"    Битовая маска: 0x{func['bit_mask']:04x}")
        print(f"    Битовый вектор (hex): {func['bits_vector'].hex().upper()}")


if __name__ == '__main__':
    file_path = "test.bin"
    parsed_data = parse_file(file_path)
    print_data(parsed_data)