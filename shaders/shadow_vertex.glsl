// Vertex Shader para renderização da shadow map
#version 120

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
