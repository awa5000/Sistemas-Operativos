# Sistemas-Operativos
Proyecto del Curso de Sistemas Operativos Los equipos de trabajo implementarán un intérprete de comandos (tipo mini-shell) en C++ sobre Linux, demostrando dominio práctico de procesos, hilos, concurrencia y gestión de memoria, contenidos de la Unidad I.

Requerimientos

Para compilar y ejecutar este proyecto, necesitarás un entorno Linux o similar (como WSL en Windows) con las siguientes herramientas instaladas:

    Compilador de C++ g++ (versión compatible con C++17)

    Herramienta de automatización make (opcional, para usar el Makefile)

    Git (para el control de versiones)

Instrucciones de Compilación y Ejecución

Se ha proporcionado un script para automatizar y simplificar el proceso de compilación. Sigue estos pasos desde la terminal en la raíz del proyecto.

1. Dar Permisos de Ejecución al Script (Solo la primera vez)

Antes de poder usar el script, necesitas darle permisos de ejecución. Este comando solo es necesario ejecutarlo una vez.

chmod +x build.sh

2. Compilar el Proyecto

Para compilar todos los archivos fuente y generar el ejecutable mi_shell, simplemente ejecuta el script:

./build.sh

Si la compilación es exitosa, verás un mensaje de confirmación y se creará el archivo mi_shell.

3. Ejecutar la Mini-Shell

Una vez compilado, puedes iniciar tu intérprete de comandos con:

./mi_shell

Ahora verás el prompt mi_shell>  y podrás empezar a introducir comandos.