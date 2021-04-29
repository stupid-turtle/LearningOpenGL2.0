#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

float offset = 1.0 / 300.0;

void main()
{
    // 正常 Normal
    //FragColor = texture(texture1, TexCoords);
    
    // 反相 Inversion
    //FragColor = vec4(vec3(1.0 - texture(texture1, TexCoords)), 1.0);

    // 灰度 Grayscale
    /*vec4 color = texture(texture1, TexCoords);
    float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
    FragColor = vec4(average, average, average, 1.0);*/

    // 核效果 Kernel / 模糊 Blur / 边缘检测 Edge detection
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset),
        vec2( 0.0f,    offset),
        vec2( offset,  offset),
        vec2(-offset,  0.0f),
        vec2( 0.0f,    0.0f),
        vec2( offset,  0.0f),
        vec2(-offset, -offset),
        vec2( 0.0f,   -offset),
        vec2( offset, -offset)
    );

    float kernel[9] = float[](
        -1.0, -1.0, -1.0,
        -1.0,  9.0, -1.0,
        -1.0, -1.0, -1.0
    );

    float blur[9] = float[](
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16
    );

    float edgeDetection[9] = float[](
        1.0,  1.0, 1.0,
        1.0, -8.0, 1.0,
        1.0,  1.0, 1.0
    );

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(texture1, TexCoords.st + offsets[i]));
    }
    vec3 color = vec3(0.0);
    for (int i = 0; i < 9; i++)
    {
        //color += sampleTex[i] * kernel[i];
        //color += sampleTex[i] * blur[i];
        color += sampleTex[i] * edgeDetection[i];
        //if (i == 4) color += sampleTex[i];
    }

    FragColor = vec4(color, 1.0);
}