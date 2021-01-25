# MPICH-Ejemplos
Usar MPICH

La URL de base para obtener información de mpich es: https://www.mpich.org/

Para instalar mpich remítase a: https://www.mpich.org/static/downloads/3.4/mpich-3.4-installguide.pdf

Para usar mpich remítase a: https://www.mpich.org/static/downloads/3.4/mpich-3.4-userguide.pdf

# Rápidamente...

La siguiente guía asume que tiene al menos un par de equipos, físicos o virtuales, Ubuntu 20+ server interconectados (pueden al menos hacer ping entre ellos) y sin restricciones de firewalls (ej: sudo ufw status --> ufw inactive)

## Instalación:

> sudo apt install mpich

podría ser necesario verificar que esté instalado gcc (>sudo apt install gcc)

Debe tener instalado y activo el servidor ssh

> sudo apt install openssh-server
> sudo service sshd start

Es necesario que todos los equipos del clúster conozcan las IPs de los otros. Regístrelas en el /etc/hosts de todos los equipos.

Es necesario que todos los equipos puedan conectarse entre ellos por ssh, sin poner clave de usuario. Revise: https://github.com/daoc/Instrucciones/blob/master/Ubuntu.md#conectarse-por-ssh-sin-password

Puede ser útil tener un directorio compartido por todos los equipos (samba, nfs, ...), al cual se acceda en el mismo path.

En dicho directorio incluirá los programas y datos que usará, así como un archivo donde incluirá los nombres de todos los equipos en su clúster; este archivo suele llamarse "machinefile", y tendrá un nombre por línea, opcionalmente seguido por dos puntos y el número de procesos a ejecutarse ahí. Ej:
```
equipo1
equipo2:3
equipo3:2
```
## Ejecución...
