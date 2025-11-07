#ifndef ILUMINACAO_H
#define ILUMINACAO_H

#include <GL/gl.h>

enum TipoLuz {
    LUZ_SOL,
    LUZ_ALTAR,
    LUZ_LATERAL_ESQ,
    LUZ_LATERAL_DIR,
    LUZ_ENTRADA
};

class SistemaIluminacao {
private:
    bool luz_sol_ativa;
    bool luz_altar_ativa;
    bool luzes_laterais_ativas;
    bool luz_entrada_ativa;
    
    float hora_dia; // 0.0 = meia-noite, 12.0 = meio-dia, 24.0 = meia-noite
    float intensidade_global;
    
    void aplicar_luz_sol();
    void aplicar_luz_altar();
    void aplicar_luzes_laterais();
    void aplicar_luz_entrada();
    void aplicar_luzes_velas(); // Nova função para luzes das velas
    
public:
    SistemaIluminacao();
    
    // Configuração inicial
    void inicializar();
    
    // Atualizar iluminação baseada no tempo
    void atualizar(float delta_time);
    
    // Alternar luzes específicas
    void alternar_luz(TipoLuz tipo);
    void ligar_todas_luzes();
    void desligar_todas_luzes();
    
    // Sistema dia/noite
    void definir_hora(float hora); // 0-24
    float obter_hora() const { return hora_dia; }
    void avancar_tempo(float velocidade); // Para animação automática
    
    // Configurar materiais para objetos
    void configurar_material_madeira();
    void configurar_material_marmore();
    void configurar_material_metal();
    void configurar_material_tecido();
    void configurar_material_parede();
    
    // Iluminação global (radiosity fake)
    void aplicar_luz_indireta();
    void aplicar_ambient_occlusion(float x, float y, float z, float raio);
};

extern SistemaIluminacao sistema_iluminacao;

#endif