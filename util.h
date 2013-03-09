#ifndef UTIL_H
#define UTIL_H

// Enum para representar codigos de erro
typedef enum
{
    sucesso = 0,
    erroAlocacao = 1,
    erroMatrizNaoInvertivel = 2
}Status;

// Macro que verifica se um status eh sucesso
#define OK(status)(*status == sucesso)

#endif
