#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 outDirection;

uniform sampler2D screenTexture;

void main()
{    
    //FragColor = vec4(vec3(1 - texture(screenTexture, TexCoords)), 1.0);
    //FragColor = vec4(1,0,0,1);
    FragColor = outDirection;
}