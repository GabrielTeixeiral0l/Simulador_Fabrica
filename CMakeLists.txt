cmake_minimum_required(VERSION 4.3)
project(simulador)

set(CMAKE_CXX_STANDARD 20)

add_executable(simulador main.cpp
        Ecra.cpp
        Ecra.h
        Terreno.cpp
        Terreno.h
        Solo.cpp
        Solo.h
        Cratera.cpp
        Cratera.h
        Deposito.cpp
        Deposito.h
        Silo.cpp
        Silo.h
        Maquina.cpp
        Maquina.h
        Perfuradora.cpp
        Perfuradora.h
        Transportador.cpp
        Transportador.h
        Refinaria.cpp
        Refinaria.h
        Oficina.cpp
        Oficina.h
        MaquinaSilo.cpp
        MaquinaSilo.h
        Lancador.cpp
        Lancador.h
        Fabrica.cpp
        Fabrica.h
        Simulador.cpp
        Simulador.h
        Comando.cpp
        Comando.h
        ComandoCarrega.cpp
        ComandoCarrega.h
        ComandoCria.cpp
        ComandoCria.h
        ComandoInfo.cpp
        ComandoInfo.h
        ComandoExec.cpp
        ComandoExec.h
        ComandoSair.cpp
        ComandoSair.h
        Settings.h)
