#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
//we also need to use material colors, might aswell do pbr.
//ok, lets do PBR
void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
    //FragColor = sqrt(FragColor) * cos(FragColor);

}
