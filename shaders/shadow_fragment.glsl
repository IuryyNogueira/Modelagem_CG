// Fragment Shader para renderização da shadow map
#version 120

void main() {
    // Apenas escrever a profundidade
    gl_FragColor = vec4(gl_FragCoord.z);
}
