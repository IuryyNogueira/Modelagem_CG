// Vertex Shader para renderização da cena com sombras
#version 120

varying vec4 shadowCoord;
varying vec3 normal;
varying vec3 lightDir;
varying vec3 viewDir;

uniform mat4 shadowMatrix;

void main() {
    // Posição no espaço da luz
    shadowCoord = shadowMatrix * gl_Vertex;
    
    // Normal transformada
    normal = normalize(gl_NormalMatrix * gl_Normal);
    
    // Direção da luz (assumindo GL_LIGHT0)
    vec3 worldPos = (gl_ModelViewMatrix * gl_Vertex).xyz;
    lightDir = normalize(gl_LightSource[0].position.xyz - worldPos);
    
    // Direção da câmera
    viewDir = normalize(-worldPos);
    
    // Posição final
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    // Passar coordenadas de textura
    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    // Passar cor do vértice
    gl_FrontColor = gl_Color;
}
