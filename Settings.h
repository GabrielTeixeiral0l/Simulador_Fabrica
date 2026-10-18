// =====================================================================
//  POO 2026/2027 - Trabalho Prático
//  Classe Settings: valores de configuração do simulador.
//
//  - Todos os valores referidos no enunciado devem ser obtidos daqui.
//  - Os valores podem ser alterados para testes, mas devem ser repostos
//    na versão entregue.
//  - Probabilidades em percentagem (0 a 100). Com 0, a perda nunca
//    acontece e a simulação torna-se determinística.
//  - Durações e períodos em instantes. Custos e valores em créditos.
//
//  Nota: "inline" (C++17) evita erros de linkagem quando uma constante
//  é usada por referência.
//        ->*** CLion deve estar configurado para C++17 ou superior. ***
// =====================================================================

#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
public:
    // ----- Ecrã (buffer interno da classe Ecra) -----
    inline static const int ecra_max_linhas = 40;
    inline static const int ecra_max_colunas = 80;

    // ----- Área da fábrica -----
    inline static const int fabrica_max_linhas = 26;
    inline static const int fabrica_max_colunas = 26;
    inline static const int fabrica_creditos_iniciais = 1000;

    // Geração aleatória (comando fabrica): número de posições de cada tipo
    inline static const int fabrica_num_crateras = 5;
    inline static const int fabrica_num_depositos_ferro = 8;
    inline static const int fabrica_num_depositos_silicio = 6;
    inline static const int fabrica_num_depositos_gelo = 6;

    // Quantidade inicial de matéria-prima em cada depósito (aleatória, inclusive)
    inline static const int deposito_quantidade_min = 40;
    inline static const int deposito_quantidade_max = 60;

    // ----- Máquinas (comum) -----
    inline static const int maquina_percentagem_venda = 50;   // % do custo devolvida ao vender
    inline static const int maquina_duracao_minima = 1;       // duração mínima de uma operação (com engenheiros)

    // ----- Perfuradora -----
    inline static const int perfuradora_custo = 100;
    inline static const int perfuradora_periodo = 3;                 // extrai 1 unidade a cada N instantes
    inline static const int perfuradora_capacidade = 1;              // itens por entregar que pode guardar
    inline static const int perfuradora_prob_perda = 40;             // % de o item extraído se perder
    inline static const int perfuradora_melhoria_reducao_prob = 10;  // pontos percentuais por melhoria
    inline static const int perfuradora_melhoria_custo = 15;

    // ----- Transportador -----
    inline static const int transportador_custo = 5;
    inline static const int transportador_capacidade = 1;

    // ----- Refinaria -----
    inline static const int refinaria_custo = 150;
    inline static const int refinaria_duracao = 4;

    // ----- Oficina -----
    inline static const int oficina_custo = 200;
    inline static const int oficina_duracao = 5;
    inline static const int oficina_receita_placas_ferro = 2;
    inline static const int oficina_receita_silicio_puro = 1;
    inline static const int oficina_receita_agua = 1;
    inline static const int oficina_receita_kits_produzidos = 1;
    inline static const int oficina_melhoria_reducao_duracao = 1;    // instantes a menos por melhoria
    inline static const int oficina_melhoria_custo = 30;
    inline static const int oficina_melhoria_max = 1;                // número máximo de melhorias

    // ----- Silo -----
    inline static const int silo_custo = 120;
    inline static const int silo_prob_perda = 20;                    // % de perder o item mais antigo, por instante
    inline static const int silo_melhoria_reducao_prob = 5;          // pontos percentuais por melhoria
    inline static const int silo_melhoria_custo = 50;

    // ----- Lançador -----
    inline static const int lancador_custo = 80;
    inline static const int lancador_recarga = 4;                    // envia 1 item a cada N instantes
    inline static const int lancador_prob_perda = 30;                // % de o item se perder no lançamento
    inline static const int lancador_melhoria_reducao_prob = 10;     // pontos percentuais por melhoria
    inline static const int lancador_melhoria_custo = 25;

    // ----- Engenheiros -----
    inline static const int engenheiro_custo_contratacao = 50;
    inline static const int engenheiro_salario = 1;                  // créditos por instante
    inline static const int engenheiro_reducao_duracao = 1;          // instantes a menos por engenheiro

    // ----- Itens: valor em créditos -----
    inline static const int valor_minerio_ferro = 2;
    inline static const int valor_silicio_bruto = 3;
    inline static const int valor_gelo = 1;
    inline static const int valor_placa_ferro = 8;
    inline static const int valor_silicio_puro = 10;
    inline static const int valor_agua = 4;
    inline static const int valor_kit_habitat = 120;
};

#endif // SETTINGS_H
