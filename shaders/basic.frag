#version 330 core

in vec3 vColor;
in vec2 vUV;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform float uMix;

void main()
{
    vec3 texColor = texture(uTexture, vUV).rgb;
    FragColor = vec4(mix(vColor, texColor, uMix), 1.0);
}