uniform sampler2D TexUnit;
void main()
{
       // Texel color
       vec3 tColor = vec3(texture2D( TexUnit, vec2(gl_TexCoord[0].st) ).rgb);

       // Result
       gl_FragColor = vec4( tColor, 1.0 );
}
