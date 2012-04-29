uniform sampler3D TexUnit;
void main()
{
       // Texel color
       vec3 tColor = vec3(texture( TexUnit, gl_TexCoord[0].rgb).rgb);

       // Result
       gl_FragColor = vec4( tColor, 1.0 );
}
