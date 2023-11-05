import requests
from bs4 import BeautifulSoup

# URL base de la página web
url_base = 'https://www.todopapas.com/nombres'
nombres = []  # Lista para almacenar los nombres
pagina_actual = 1

while True:
    # Construir la URL de la página actual
    if pagina_actual == 1:
        url = url_base
    else:
        url = f'{url_base}/{pagina_actual}'

    # Realizar la solicitud GET a la URL
    response = requests.get(url)

    # Comprobar si la solicitud fue exitosa
    if response.status_code == 200:
        # Analizar el contenido HTML de la página
        soup = BeautifulSoup(response.text, 'html.parser')

        # Buscar todos los elementos <a> con el atributo "title"
        nombres_pagina = [a.get('title') for a in soup.find_all('a', {'title': True})]

        if not nombres_pagina:
            # Si no se encontraron más nombres, terminar el bucle
            break

        # Agregar los nombres de la página actual a la lista de nombres
        nombres.extend(nombres_pagina)

        # Ir a la siguiente página
        pagina_actual += 1
    else:
        print(f'Error al realizar la solicitud a la página web: {url}')
        break

# Guardar los nombres en un archivo de texto
with open('nombres.txt', 'w', encoding='utf-8') as file:
    for nombre in nombres:
        file.write(nombre + '\n')

print(f'Se extrajeron {len(nombres)} nombres y se guardaron en nombres.txt')