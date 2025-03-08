import re
import csv

# Función para cargar el archivo HTML
def cargar_html(archivo):
    with open(archivo, "r", encoding="utf-8") as f:
        return f.read()

# Función para extraer nombres de productos y URLs de imágenes
def extraer_productos(html):
    regex_nombre = r'<div class="tab_item_name">(.*?)<\/div>'  
    regex_imagen = r'<img class="tab_item_cap_img" src="(.*?)"[^>]*(?:alt=".*?")?' 

    nombres = re.findall(regex_nombre, html)
    imagenes = re.findall(regex_imagen, html)

    return list(zip(nombres, imagenes))  

# Función para exportar los datos extraídos a un CSV
def exportar_csv(productos, archivo_salida):
    with open(archivo_salida, "w", newline="", encoding="utf-8") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["Nombre del Producto", "URL de la Imagen"]) 
        writer.writerows(productos) 

archivo_html = "data/SteamNovedades.html"  
archivo_csv = "data/productos.csv" 

# Cargar y procesar la página HTML
html_contenido = cargar_html(archivo_html)
productos_extraidos = extraer_productos(html_contenido)

# Exportar los productos a CSV
exportar_csv(productos_extraidos, archivo_csv)

print(f"Archivo CSV '{archivo_csv}' generado con {len(productos_extraidos)} productos.")
