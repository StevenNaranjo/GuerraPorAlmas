import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders

def enviar_correo(destinatario, asunto, contenido, archivos_adjuntos=None):
    # Configuración del servidor SMTP
    servidor_smtp = 'smtp.gmail.com'
    puerto_smtp = 587
    remitente = 'asnaranjom@gmail.com'
    contraseña = 'rogv uarj gswu vzuc'

    # Creación del objeto de mensaje
    mensaje = MIMEMultipart()
    mensaje['From'] = remitente
    mensaje['To'] = destinatario
    mensaje['Subject'] = asunto

    # Agregar contenido al mensaje
    mensaje.attach(MIMEText(contenido, 'plain'))

    # Agregar archivos adjuntos al mensaje si se proporcionan
    if archivos_adjuntos:
        for archivo in archivos_adjuntos:
            adjunto = MIMEBase('application', 'octet-stream')
            with open(archivo, 'rb') as f:
                adjunto.set_payload(f.read())
            encoders.encode_base64(adjunto)
            adjunto.add_header('Content-Disposition', f'attachment; filename="{archivo}"')
            mensaje.attach(adjunto)

    # Conexión y envío del correo electrónico
    try:
        with smtplib.SMTP(servidor_smtp, puerto_smtp) as servidor:
            servidor.starttls()
            servidor.login(remitente, contraseña)
            servidor.send_message(mensaje)
        print('Correo electrónico enviado correctamente')
    except Exception as e:
        print('Error al enviar el correo electrónico:', str(e))


# Ejemplo de uso
destinatario = 'lfbenav@gmail.com'
#destinatario = 'asnaranjom@gmail.com'
asunto = 'Hola esto es una prueba'
contenido = '¡Hola! Estoy probando lo de enviar correos en python, que esta vara la tenemos que hacer para la progra de ED.'
archivos_adjuntos = ['/home/naranjo/Documents/GuerraPorAlmas/BatallaPorAlmas/archivo_adjunto.txt']

enviar_correo(destinatario, asunto, contenido, archivos_adjuntos)
