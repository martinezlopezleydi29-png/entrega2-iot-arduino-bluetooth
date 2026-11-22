# Control de dos LED con Arduino UNO y HC-05 simulado

Entrega 2 del modulo Internet de las cosas, Politecnico Grancolombiano.
Docente: Jesus Antonio Figueroa Guerrero.

## Integrantes

- Leydi Adriana Martinez Lopez
- Christian David Lancheros Martinez
- Veronica Mora Ceron
- Juan Camilo Bellon
- Danyela Vivian Munza Suarez

## Reproducir el circuito

1. Abrir Mokxi y usar Save > Open JSON or SPICE.
2. Seleccionar `configuracion/Entrega2_HC05_dos_LED.mokxi.json`.
3. Pulsar Run y abrir el panel Bluetooth del HC-05.
4. Emparejar y conectar si la interfaz lo solicita.
5. Enviar un comando por vez, con CR+LF.

El proyecto nativo contiene el codigo y el circuito completo. La UART
del HC-05 opera a 1200 baudios, 8N1; el puerto de diagnostico de Arduino,
a 115200. El modulo usa RX Arduino D2, TX D3 y STATE D4. El verde usa D9
y el rojo D10, cada uno con una resistencia de 220 ohmios.

| Comando | Accion |
| --- | --- |
| V / v | Encender / apagar el verde |
| R / r | Encender / apagar el rojo |
| A | Apagar ambos |
| status | Consultar las salidas |
| hola | Probar el rechazo de una entrada invalida |

## Enlaces por completar antes de publicar la entrega

- URL publica de este repositorio: aun no publicada.
- URL directa del circuito final de dos LED en Mokxi: pendiente de verificar.

El editor general `https://app.mokxi.com/` no identifica una copia del circuito.
La publicacion del ZIP no crea por si sola un repositorio ni un enlace al simulador.

## Evidencia y reproducibilidad

`evidencias/` contiene nueve capturas originales del 21/11/2026 y un CSV
de observaciones funcionales. No son mediciones periodicas de rendimiento.
La plantilla de corridas adicionales tiene solo encabezados: no se han
ejecutado esas corridas ni fabricado marcas temporales. El protocolo
propuesto esta descrito en el articulo.

`articulo/` contiene LaTeX IEEEtran y figuras incorporadas; compilar main.tex.
Las figuras se recortaron de las capturas sin alterar estados ni respuestas.

## Procedencia

Adaptado del ejemplo Bluetooth lamp de Mokxi:
https://mokxi.com/projects/bluetooth-lamp

Se conservaron sus rutinas UART por software y se anadio un segundo LED,
los comandos de control, la consulta de estados y el control de longitud.
El trabajo no atribuye al grupo la autoria del ejemplo original.

## Limitaciones

Se verifica un modelo serial del HC-05. No hay radio fisica, medicion de
alcance, interferencias o validacion de seguridad de Bluetooth. El dialogo
de emparejamiento corresponde a la interfaz del simulador.
