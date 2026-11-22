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

## Enlaces del proyecto

- Repositorio publico: https://github.com/martinezlopezleydi29-png/entrega2-iot-arduino-bluetooth
- Circuito final de dos LED en Mokxi: https://app.mokxi.com/p/WYKZzVkyr_cD1bT1

Para abrir una copia desde archivo, usar el JSON de configuracion incluido.
Acceso al circuito comprobado sin iniciar sesion, en Chrome de incognito,
el 21 de noviembre de 2026. Se visualizaron el circuito de dos LED y el codigo.

## Evidencia y reproducibilidad

`evidencias/` contiene las nueve capturas funcionales iniciales y su CSV.
`evidencias/corridas_repetidas/` incorpora tres corridas nuevas de nueve
comandos: 27 respuestas coincidentes con las esperadas. Se reinicio la
simulacion entre corridas y se programaron envios con objetivo de 5 s.
Los 24 intervalos entre inicios de acciones estuvieron entre 4.989 y 5.010 s.
El reloj es el del computador y la automatizacion de interfaz; no mide
latencia de Bluetooth. El JSON conserva el texto de la interfaz observado
en cada paso; los TXT conservan los terminales completos. Tambien hay
CSV derivados, resumen y capturas de ambos LED encendidos y apagados.
No se midieron CPU/RAM ni propagacion de radio fisica.

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
