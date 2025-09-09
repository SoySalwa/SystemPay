# The System Pay

## Descripción:

Es un sistema de pago programado en el lenguaje de programación C++ para dispositivos de escritorio Windows y Linux, es un sistema para la gestión de registros estudiantil.

## Propósito:

Agilizar, automatizar el proceso de pago y decir adiós a los registros manuales de una vez por todas, con el fin de poder registrar, obtener y almacenar de manera sencilla y rapida los registros de cada estudiante.

Está pensado para ser un sistema eficiente y de calidad para el Centro Educativo, el SPCEA no puede perdonarse ningún dato faltante o sobrante, su trabajo es mantener un pago seguro y adecuado a cada costo.

## Características

- 🖨 **Impresión**: Tiene la capacidad de generar e imprimir un recibo.

---

## Tecnologías Utilizadas

- **Lenguajes:** C++
- **Bases de Datos:** Mongocxx (Base de datos de MongoDB para C++).
- **Compilacion:** Cmake, make

---

## Compilar en Windows
### Requisitos
    MinGW con compatible con Qt6
    MongoCXX

```bash
git clone --recursive https://github.com/mongodb/mongo-cxx-driver.git
cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=C:/mongo-cxx-driver ../mongo-cxx-driver
cmake --build . --config Release --target install
```
Luego en el proyecto

```bash
cmake -G "MinGW Makefiles" -S . -B build
cmake --build build
```
---

## Requisitos del Sistema

- Sistema Operativo: Windows 10 o Superior
- Memoria Ram: 4gb o superior.

---

## Capturas de Pantalla

Incluye capturas de pantalla o gifs para mostrar la aplicación en acción.

---

## Detalles Adicionales

- Actualmente se encuentra en una versión inestable.
- Su versión actual es 0.1.0-Alpha.
