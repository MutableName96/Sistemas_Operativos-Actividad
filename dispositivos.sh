#!/bin/bash

echo "Dispositivos de bloque:" > resumendispositivos.txt
lsblk >> resumendispositivos.txt

echo "" >> resumendispositivos.txt
echo "Dispositivos USB:" >> resumendispositivos.txt
lsusb >> resumendispositivos.txt

echo "" >> resumendispositivos.txt
echo "Dispositivos PCI:" >> resumendispositivos.txt
lspci >> resumendispositivos.txt

echo "" >> resumendispositivos.txt
echo "Dispositivos de entrada:" >> resumendispositivos.txt
cat /proc/bus/input/devices >> resumendispositivos.txt

echo "" >> resumendispositivos.txt
echo "Salidas de video:" >> resumendispositivos.txt
xrandr >> resumendispositivos.txt

echo "" >> resumendispositivos.txt
echo "Tarjetas de sonido:" >> resumendispositivos.txt
aplay -l >> resumendispositivos.txt

echo "La información se ha guardado en 'resumendispositivos.txt'."
#!/bin/bash
echo "Dispositivos de bloque:"
lsblk
echo "Dispositivos USB:"
lsusb
echo "Dispositivos PCI:"
lspci
echo "Dispositivos de entrada:"
cat /proc/bus/input/devices
echo "Salidas de video:"
xrandr
echo "Tarjetas de sonido:"
aplay -l

