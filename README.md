# Ópera Sistemática (Grupo 21)

## Laboratorio 02: Syscalls para acceso a VGA

### Integrantes:
- Carrara, Ángeles
- Castellano, Bruno
- Martinez Gavier, Lucía

### Mails
- [angeles.carrara@mi.unc.edu.ar](mailto:angeles.carrara@mi.unc.edu.ar "Carrara, Ángeles")
- [bruno.castellano@mi.unc.edu.ar](mailto:bruno.castellano@mi.unc.edu.ar "Castellano, Bruno")
- [lucia.m.gavier@mi.unc.edu.ar](mailto:lucia.m.gavier@mi.unc.edu.ar "Martinez Gavier, Lucía")

## ¿Cómo compilar y ejecutar?
Es necesario tener el emulador "qemu" instalado:
```shell
$ sudo apt-get install qemu-system-i386

$ git clone https://angeles_carrara@bitbucket.org/sistop-famaf/so21lab2g21.git
```
Una vez instalado, para compilar e iniciar xv6 con modo gráfico:
```shell
so21lab2g21/xv6-public$ make qemu [-j]
```

### Iniciar Juego TicTacToe
```shell
$ tictactoe
```
## Introducción

En este proyecto desarrollamos syscalls para xv6, principalmente relacionadas con VGA. Una vez implementadas estas, pudimos hacer un programa de usario que las utiliza.
Este se trata del clásico juego tic-tac-toe.

## Diseño

### Syscalls

Se implementaron las siguientes syscalls, relacionadas con VGA:

- `modeswitch()` cambia de modo '0' para cambiar a modo texto y '1' para modo gráfico.
- `plotpixel()` que grafica un píxel dada su posición y color.
- `plotrectangle()` que grafica un rectángulo dados la coordenada inicial (superior izquierda) y la final (inferior derecha), y el color.
- `printimage()` imprime una imagen (array de píxeles) dada su posición, tamaño del arreglo y escala.
- `printchar()` imprime un caracter, dada la coordenada inicial, color y tamaño.

Además, se implementó la syscall `getc()` (sin relación directa a VGA), que devuelve el siguiente input de teclado en el momento en que se da, sin esperar al siguiente `\n`.

### Modularización
Seguimos la estructura de las syscalls ya implementadas en xv6 y, como propuso la cátedra, modularizamos las relacionadas a VGA en un archivo aparte `vga.c`.

### Programas de usuario

- ### tictactoe:
    El programa comienza en modo texto, mostrando las instrucciones del juego. Una vez que recibe el caracter 'y', pasa a modo gráfico y muestra el tablero. Durante el transcurso del juego se espera a que se presione algun número del 1 al 9 para colocar las fichas en la posición correspondiente. Presionando 'q' se puede terminar la partida y volver a modo texto.

    Durante el juego, se deben elegir las celdas libres, pero en caso de que no se respete eso, se pinta la celda en rojo y se espera por un nuevo input (con la esperanza de que el usuario entienda que eso es trampa). Del mismo modo, si se ingresa un caracter que no es 'q' o un entero del 1 al 9 (inclusive), se pinta todo el tablero de rojo.

    Por otro lado, las fichas, así como una pequeña ilustración, son "imágenes" creadas a partir de arreglos de píxeles.

![Foto del programa en ejecución](https://imgur.com/NLDjssS.png)

![Foto del programa en ejecución](https://imgur.com/OevLXz0.png)

- ### moo
    ¿Have you mooed today?

    (Cortesía de Bruno Castellano)

## Seguridad
Al igual que las otras llamadas a sistema, hacemos un control de los argumentos en `sysproc.c`, previo a la llamada a la syscall en sí.

## Desarrollo

En la primera semana principalmente investigamos sobre VGA, y no trabajamos mucho sobre el código; sin embargo pudimos implementar la función vgainit y el cambio entre modos texto/gráfico.

Luego agregamos las syscalls plotpixel y plotrectangle, y decidimos hacer como programa de usuario una versión del tateti, basada en la historia para niños "La liebre y la tortuga".

Las siguientes semanas nos dedicamos puntualmente al desarrollo del programa de usuario tictactoe y pulimos detalles tanto visuales como funcionales. Además de agregar información útil para que cualquier usuario que no haya jugado nunca al tictactoe pueda entender su funcionamiento.

## Observaciones

Adoptamos un estilo de programación top-down en el proceso de creación del tictactoe.

Por falta de tiempo no pudimos incluir los arreglos grandes dentro del sistema de archivos. Sin embargo, como solución provisoria decidimos dejarlos aparte en un archivo .h .

## Herramientas
- Visual Studio Code © con la extensión *Live Share* para peer programming.
- Git con la plataforma *Bitbucket* para control de versiones.
- QEMU.
