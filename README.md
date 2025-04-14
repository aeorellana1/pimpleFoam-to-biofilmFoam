# PIMPE_BIO - Solver para OpenFOAM

## Introducción

Este proyecto es una adaptación del solver `pimpleFoam` a `biofilmFoam` para la simulación de biofilms en OpenFOAM. 


### Funciones Principales:
- Resuelve las ecuaciones para el sustrato y la biomasa.
- Implementa una ecuación de transporte para cada uno de los componentes (biomasa y sustrato).
- Permite la interacción de estas especies a través de parámetros de difusividad y crecimiento.
  
### Archivos Principales:
1. **createFieldsBiofilm.H**: Crea los campos necesarios para la simulación, como la concentración de sustrato, la biomasa, y otros parámetros relacionados.
2. **CEqn.H**: Define la ecuación para el sustrato.
3. **MEqn.H**: Define la ecuación para la biomasa.

