# Laboratorio-C
## Integrantes y Comisión:
  - Camnasio, Avril
  - Muñoa Gimenez, Ibel Eugenia
  - Muzzupappa, Nahir Helena
  - Otero, Nelson Facundo

## Escenario **Artemis** asignado:
  Situación - Problema 3: Inyección Translunar — TLI e Inercia en Trayectoria Libre (1.ª Ley de Newton y Energía)
  Estando en órbita baja (LEO), la etapa superior ICPS ejecuta la maniobra de Inyección Translunar (TLI), impulsando a la nave Orion hasta una velocidad de escape/inyección v_TLI = 10,9 km/s (10.900,0 m/s). Inmediatamente después del encendido, la etapa ICPS se desacopla y los motores principales se apagan por completo. La nave Orion (m = 26.000,0 kg) entra en una trayectoria de retorno libre (Free Return Trajectory) hacia la Luna, ubicada a una distancia media Tierra-Luna de D = 384.000,0 km (384.000.000,0 m).
  Reglas del juego
El objetivo es que Orion, con los motores apagados tras la inyección translunar, llegue al punto de equilibrio gravitatorio Tierra-Luna (a unos 345.700 km del centro de la Tierra), donde la Luna pasa a dominar.
El usuario configura la nave con los valores del enunciado (26.000 kg, 10.900 m/s, 192 km) o con los propios, dentro de rangos válidos. La velocidad de inyección es lo que más influye, porque una vez apagados los motores no se puede corregir la trayectoria.
La simulación avanza por turnos. En cada uno el usuario elige avanzar (A) o abandonar (S), y si avanza indica cuántas horas simular, entre 0,5 y 48. Termina cuando Orion llega al equilibrio (misión exitosa), cuando se detiene antes y regresa a la Tierra, o cuando el usuario abandona. Al final se muestra el resultado y el historial de cada turno.

## Breve detalle de funcionamiento


## Instrucciones claras de complicación y ejecución
El proyecto está escrito en C estándar (C99) y se compila con gcc. A continuación explicamos cómo prepararlo, compilarlo y ejecutarlo, y cómo probar sus funciones principales.

### Requisitos
•	Un compilador gcc. Se puede comprobar con gcc --version.
•	Opcionalmente make, que simplifica la compilación a un solo comando. Se puede comprobar con make --version.
•	Una terminal. El programa limpia la pantalla entre turnos y dibuja la nave en ASCII, así que conviene ejecutarlo desde una terminal real y no desde el botón de ejecutar de un editor.

En Linux y macOS, gcc y make suelen estar instalados o se instalan con el gestor de paquetes del sistema. En Windows recomendamos instalar MSYS2 (o MinGW) o usar WSL, que incluyen ambas herramientas.

### Obtener el código
Si todavía no se tiene el repositorio, se clona con:
**git clone https://github.com/Facu-ot208/Laboratorio-C.git
cd Laboratorio-C**
Todos los comandos siguientes se ejecutan desde esa carpeta.

### Compilación con make
Es la forma más simple. Desde la carpeta raíz:
**make**
El Makefile compila cada archivo .c por separado y los une en un ejecutable llamado artemis. Compila con las opciones -Wall -Wextra -std=c99 -g, que activan las advertencias del compilador y el estándar C99. La compilación no tiene que mostrar errores ni advertencias.
Para borrar los archivos generados:
make clean

### Compilación sin make
Si no se dispone de make, el proyecto se compila con un único comando:
**gcc -Wall -Wextra -std=c99 -g main.c simulador.c validaciones.c dibujo.c -o artemis -lm**

### Ejecución
En Linux y macOS:
**./artemis**
En Windows:
**artemis.exe**

Al iniciar aparece el menú principal. Se elige una opción escribiendo su número y presionando Enter. Después de cada opción, el programa pide presionar Enter para volver al menú. Para terminar se elige la opción 0.

### Registro detallado del uso de Inteligencia Artificial
Utilizamos inteligencia artificial como apoyo durante el desarrollo del trabajo. Las usamos sobre todo para verificar  (controlar lo que íbamos construyendo)
Cada vez que terminábamos una parte del programa, la sometíamos a revisión y notamos que la IA encontró pocos errores de sintaxis, pero sí errores de lógica, que fueron los que más nos sirvieron. Por ejemplo, detectó un ciclo infonito si se cerraba la entrada del programa, algo que nosotros no tomamos en cuenta.
Cuando nos estancamos en puntos específicos, también le pedimos ayuda, para entender un concepto o para resolver un problema concreto. Esas consultas y sus respuestas figuran en la tabla de más abajo. Todo lo que se sugirió lo revisamos, lo probamos y lo adaptamos antes de incluirlo en el proyecto
