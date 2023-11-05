import random

# Leer el contenido del archivo en una lista
with open('nombresfinales.txt', 'r', encoding='utf-8') as file:
    lineas = file.read().splitlines()

# Mezclar el orden de las líneas
random.shuffle(lineas)

# Escribir las líneas en el mismo archivo o en uno nuevo
with open('tu_archivo_revuelto.txt', 'w', encoding='utf-8') as file:
    for linea in lineas:
        file.write(linea + '\n')

print('Contenido del archivo revuelto y guardado en "tu_archivo_revuelto.txt".')