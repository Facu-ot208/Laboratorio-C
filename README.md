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
### Qué hace el programa
Desarrollamos un simulador por consola de la Situación-Problema 3 de la misión Artemis: la inyección translunar (TLI) de la nave Orion. En el escenario, la etapa superior ICPS impulsa a Orion desde una órbita terrestre baja (h = 192 km) hasta una velocidad de inyección de 10,9 km/s. Después se apagan los motores y la nave sigue su camino hacia la Luna, que está a una distancia media de 384.000 km, solo bajo la acción de la gravedad.
Pensamos el programa como una herramienta para explorar ese escenario. El usuario puede resolver cada uno de los apartados del enunciado (ley de inercia, energía cinética, trabajo mínimo y comparación de combustible) y, además, simular el viaje turno por turno para ver qué le pasa a Orion según la velocidad con la que sale. Todos los datos de entrada se pueden modificar, así que el programa responde a distintos valores y no solo a los del enunciado.

### Menú principal
Al iniciar, el programa muestra un menú. Se elige una opción escribiendo su número y presionando Enter, y al terminar cada opción se vuelve al menú.

**1**.	Configurar nave Orion: el usuario decide si usa los valores del enunciado (m = 26.000 kg, v = 10.900 m/s, h = 192.000 m) o si carga valores propios. Los valores propios se validan por rango: la masa debe ser mayor que cero, la velocidad debe estar entre 1.000 y 15.000 m/s y la altura entre 100.000 y 2.000.000 m.

**2**.	Apartado A: explica la ley de inercia aplicada a Orion.

**3**.	Apartado B: calcula la energía cinética inicial.

**4**.	Apartado C: calcula el punto de equilibrio gravitatorio y el trabajo externo mínimo por unidad de masa.

**5**.	Apartado D: justifica por qué la ida a la Luna requiere más combustible que el regreso.

**6**.	Simular viaje translunar: simulación por turnos.

**7**.	Reporte final: resumen de la nave y del resultado de la misión.

**0**.	Salir.

Si el usuario no configura nada, el programa arranca con los valores del enunciado, de modo que todas las opciones funcionan desde el principio.

### Simulación por turnos
La opción 6 es la parte interactiva del programa. En cada turno se muestra una pantalla con un dibujo de la nave en ASCII, la velocidad actual (en km/s), la distancia recorrida (en km) y una barra de progreso entre la Tierra y la Luna. Después el usuario elige entre avanzar el turno o abandonar la simulación. Si avanza, indica cuántas horas quiere simular, entre 0,5 y 48.

Para calcular el movimiento, en cada paso el programa evalúa la aceleración de la nave como la suma de la atracción de la Tierra (hacia atrás) y la de la Luna (hacia adelante):
a(r) = −G · M_Tierra / r² + G · M_Luna / (D − r)²
donde r es la distancia de la nave al centro de la Tierra. Con esa aceleración actualizamos posición y velocidad usando el método de Verlet de velocidad, con un paso de integración de 10 segundos. Elegimos ese método porque es de segundo orden y mantiene bien la energía en movimientos gravitatorios, y el paso de 10 s es lo bastante chico para que el resultado no cambie de forma apreciable al achicarlo.

**La simulación termina cuando ocurre alguno de estos casos:**

•	Llega al equilibrio: Orion alcanza el punto de equilibrio Tierra-Luna. Desde ahí domina la Luna y la nave cae hacia ella.

•	Regresa a la Tierra: la velocidad llega a cero antes del punto de equilibrio. Orion se detiene y la gravedad terrestre la hace volver.

•	Choca con la Tierra: la distancia queda menor que el radio terrestre. Con datos válidos este caso no debería darse, porque la nave se detiene antes de caer, pero lo dejamos como chequeo de seguridad.

•	Abandono: el usuario decide salir antes de que se resuelva el viaje.

Al terminar, el programa informa el resultado y muestra una tabla con la velocidad y la distancia al final de cada turno. Ese historial se guarda en arreglos, con un máximo de 200 turnos.

El resultado depende sobre todo de la velocidad de inyección. Con los 10.900 m/s del enunciado, Orion queda apenas corta del punto de equilibrio. Con velocidades algo mayores, llega.

### Organización del código
Dividimos el proyecto en módulos para que cada archivo tenga una responsabilidad clara. Esto nos permitió trabajar en paralelo sin pisarnos y facilita ubicar un error.

•	**main.c** tiene el menú, el ciclo principal y la lógica de cada turno de la simulación. No contiene fórmulas físicas, solo llama a las funciones de los otros módulos.

•	**simulador.h y simulador.c** concentran las constantes físicas, el struct Orion, el tipo EstadoVuelo, los cálculos de los apartados y el avance de la simulación.

•	**validaciones.h y validaciones.c** se encargan de leer números, enteros y opciones del teclado de forma segura.

•	**interfaz.h y dibujo.c** se encargan de lo visual: limpiar la pantalla según el sistema operativo, dibujar la nave y la barra de progreso, y armar el panel de cada turno.

### Estructuras, punteros y arreglos
Los datos de la nave se agrupan en un struct Orion con masa, velocidad, distancia al centro de la Tierra y altura. Pasamos la nave a las funciones por puntero: las que solo leen la nave la reciben como const Orion *, y las que la modifican, como avanzarTurno e inicializarNave, la reciben como Orion *. Así evitamos copiar el struct en cada llamada y dejamos en claro qué funciones pueden cambiar la nave.
Usamos arreglos para guardar el historial de velocidades y distancias de cada turno, y los recorremos con ciclos para armar la tabla final. El estado de la simulación se representa con un enum, lo que vuelve más legible el switch que muestra el resultado.

### Validaciones y manejo de errores
No usamos scanf para leer datos, porque ante una letra deja la entrada sin consumir y puede provocar un ciclo infinito. En su lugar leemos cada línea completa como texto con fgets y la convertimos con strtod (decimales) o strtol (enteros), revisando que se haya consumido toda la línea. Con eso el programa rechaza:

•	letras y texto sobrante, por ejemplo 12abc

•	líneas vacías

•	líneas de más de 100 caracteres

•	números fuera del rango representable, nan e inf

•	valores fuera del rango permitido para cada dato

•	decimales donde se espera un entero, por ejemplo 3,5 en el menú

Los decimales se pueden escribir con coma o con punto. Cada error muestra una advertencia con el formato [!] y el programa vuelve a pedir el dato. Si la entrada se cierra (por ejemplo con Ctrl + D), el programa termina.


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
