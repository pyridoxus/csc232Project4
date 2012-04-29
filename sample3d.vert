void main()
{
       // Output texture coordinates
       gl_TexCoord[0]  = gl_MultiTexCoord0;

       // Position in clip space
       gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
}
