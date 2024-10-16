# Universidad de Antioquia  
## Programa de Ingeniería de Telecomunicaciones  
**Asignatura: Informática 2 Laboratorio Grupo 3**  
**Profesor: Jonhny Alexander Aguirre Morales**  

---

### Integrante del equipo de trabajo
- **Oscar Lopez Peñata**  
  Email: [oscar.lopezp@udea.edu.co](mailto:oscar.lopezp@udea.edu.co)

---

### Descripción del Proyecto

Este proyecto es parte de la **Práctica 3 de la Unidad 4** en la asignatura **Informática 2 Laboratorio**. El objetivo fue implementar un sistema en **C++** (sin el uso de librerías STL) para la codificación y decodificación de archivos de texto, así como la creación de un sistema de registro de usuarios para un cajero electrónico.

#### Codificación de Archivos
Se desarrollaron dos métodos de codificación que manipulan los bits de los caracteres de un archivo:
- **Método 1**: Se invierten los bits en bloques de n bits y se aplican reglas dependiendo de la cantidad de '1s' y '0s' en el bloque anterior.
- **Método 2**: Se realiza un desplazamiento circular de bits dentro de cada bloque.

#### Decodificación de Archivos
Un programa adicional permite revertir la codificación y restaurar los archivos a su formato de texto original, asegurando que puedan ser leídos por cualquier editor de texto.

#### Sistema de Registro de Usuarios para Cajero Electrónico
Este sistema permite:
- Acceso como administrador para registrar usuarios.
- Consultar saldo y retirar dinero, con un costo por cada transacción de 1000 COP.
- Actualización automática del saldo después de cada transacción. Las contraseñas de los usuarios se almacenan encriptadas.

### Objetivos del Laboratorio

1. Manipulación de cadenas de caracteres en C++.
2. Gestión de archivos utilizando C++.
3. Implementación de algoritmos de codificación y decodificación binaria.
4. Manejo de excepciones durante la manipulación de archivos y control de flujo en el sistema de registro de usuarios.

---

### Cómo clonar este repositorio

Para revisar el código y realizar pruebas locales, puedes clonar este repositorio ejecutando el siguiente comando en tu terminal:

```bash
git clone https://github.com/OskarLopez/Practica-3_Unidad-4_Informatica-2-Lab._UdeA-Teleco.git
