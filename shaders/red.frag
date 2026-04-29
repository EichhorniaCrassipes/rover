uniform sampler2D texture;

void main()
{
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    gl_FragColor = vec4(color.rgb * vec3(0.9, 0.2, 0.3), color.a * 0.75);
}