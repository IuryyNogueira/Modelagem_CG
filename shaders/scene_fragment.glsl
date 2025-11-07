// Fragment Shader para renderização da cena com sombras
#version 120

varying vec4 shadowCoord;
varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewDir;

uniform sampler2D shadowMap;
uniform sampler2D colorTexture;
uniform bool useTexture;
uniform float shadowBias;
uniform float shadowIntensity;

float calcShadow() {
    // Projetar coordenadas de sombra
    vec3 projCoords = shadowCoord.xyz / shadowCoord.w;
    
    // Transformar para [0,1]
    projCoords = projCoords * 0.5 + 0.5;
    
    // Fora do range da shadow map
    if (projCoords.z > 1.0 || projCoords.x < 0.0 || projCoords.x > 1.0 || 
        projCoords.y < 0.0 || projCoords.y > 1.0) {
        return 0.0; // Não está na sombra
    }
    
    // Profundidade mais próxima da luz
    float closestDepth = texture2D(shadowMap, projCoords.xy).r;
    
    // Profundidade atual
    float currentDepth = projCoords.z;
    
    // PCF (Percentage Closer Filtering) para sombras mais suaves
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(2048.0, 2048.0); // Tamanho do texel
    
    for(int x = -2; x <= 2; ++x) {
        for(int y = -2; y <= 2; ++y) {
            float pcfDepth = texture2D(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - shadowBias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 25.0; // 5x5 kernel
    
    return shadow * shadowIntensity;
}

void main() {
    // Normal normalizada
    vec3 N = normalize(normal);
    vec3 L = normalize(lightDir);
    vec3 V = normalize(viewDir);
    vec3 H = normalize(L + V); // Half vector para especular
    
    // Cor base
    vec4 baseColor;
    if (useTexture) {
        baseColor = texture2D(colorTexture, gl_TexCoord[0].st) * gl_Color;
    } else {
        baseColor = gl_Color;
    }
    
    // Iluminação ambiente
    vec4 ambient = gl_LightSource[0].ambient * baseColor;
    
    // Iluminação difusa
    float diffuseFactor = max(dot(N, L), 0.0);
    vec4 diffuse = gl_LightSource[0].diffuse * baseColor * diffuseFactor;
    
    // Iluminação especular
    float specularFactor = pow(max(dot(N, H), 0.0), gl_FrontMaterial.shininess);
    vec4 specular = gl_LightSource[0].specular * gl_FrontMaterial.specular * specularFactor;
    
    // Calcular sombra
    float shadow = calcShadow();
    
    // Aplicar sombra apenas nas componentes difusa e especular
    vec4 finalColor = ambient + (1.0 - shadow) * (diffuse + specular);
    
    gl_FragColor = finalColor;
}
