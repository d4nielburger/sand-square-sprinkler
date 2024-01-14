# sand-square-sprinkler
System to control water sprinklers and manage the water reservoir.
![Artwork](./doc/overview-dalle.png)

## Table of Contents
- [sand-square-sprinkler](#sand-square-sprinkler)
  - [Table of Contents](#table-of-contents)
  - [System Overview](#system-overview)
  - [Controller Block Diagram](#controller-block-diagram)
  - [Responsibilities](#responsibilities)
  - [ToDo](#todo)
    - [STM](#stm)
    - [Raspi - Server](#raspi---server)
    - [Webclient](#webclient)
    - [Carrier PCB](#carrier-pcb)
  - [Requirements](#requirements)
    - [GUI](#gui)

## System Overview
![System](doc/overview-1.png)
## Controller Block Diagram
![Block Diagram](doc/overview-2.png)

## Client

Die Vue App hat für jede Pumpenstuereung ein eigenes Component. Die Garagen-, Sprinkler- und Schlauchsteurung ist ein einzelner Button, welcher den aktuellen Status toggelt und posted diesen. Bei der Tank Fill Component haben wir drei Buttons um auszuwählen welcher Tank gefüllt werden soll und dieser wird in der API hinterlegt. Über einen Socket wird die Verbindung mit der API hergestellt. Gibt es einen Status änderung werden die einzelnen Components automatisch geupdated und gegebenfalls die Buttons gändert. Die Buttons zeigen den aktuellen Status an und werden erst geändert wenn sich der Status in der API ändert und nicht direkt beim klicken.
