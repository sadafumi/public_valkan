                              Capability Shader
               1:             ExtInstImport  "GLSL.std.450"
                              MemoryModel Logical GLSL450
                              EntryPoint Vertex 4  "main" 9 11 19 30
                              Source GLSL 400
                              SourceExtension  "GL_ARB_separate_shader_objects"
                              SourceExtension  "GL_ARB_shading_language_420pack"
                              Name 4  "main"
                              Name 9  "texcoord"
                              Name 11  "inTexCoords"
                              Name 17  "gl_PerVertex"
                              MemberName 17(gl_PerVertex) 0  "gl_Position"
                              MemberName 17(gl_PerVertex) 1  "gl_PointSize"
                              MemberName 17(gl_PerVertex) 2  "gl_ClipDistance"
                              Name 19  ""
                              Name 23  "buf"
                              MemberName 23(buf) 0  "mvp"
                              Name 25  "ubuf"
                              Name 30  "pos"
                              Decorate 9(texcoord) Location 0
                              Decorate 11(inTexCoords) Location 1
                              MemberDecorate 17(gl_PerVertex) 0 BuiltIn Position
                              MemberDecorate 17(gl_PerVertex) 1 BuiltIn PointSize
                              MemberDecorate 17(gl_PerVertex) 2 BuiltIn ClipDistance
                              Decorate 17(gl_PerVertex) Block
                              MemberDecorate 23(buf) 0 ColMajor
                              MemberDecorate 23(buf) 0 Offset 0
                              MemberDecorate 23(buf) 0 MatrixStride 16
                              Decorate 23(buf) Block
                              Decorate 25(ubuf) DescriptorSet 0
                              Decorate 25(ubuf) Binding 0
                              Decorate 30(pos) Location 0
               2:             TypeVoid
               3:             TypeFunction 2
               6:             TypeFloat 32
               7:             TypeVector 6(float) 2
               8:             TypePointer Output 7(fvec2)
     9(texcoord):      8(ptr) Variable Output
              10:             TypePointer Input 7(fvec2)
 11(inTexCoords):     10(ptr) Variable Input
              13:             TypeVector 6(float) 4
              14:             TypeInt 32 0
              15:     14(int) Constant 1
              16:             TypeArray 6(float) 15
17(gl_PerVertex):             TypeStruct 13(fvec4) 6(float) 16
              18:             TypePointer Output 17(gl_PerVertex)
              19:     18(ptr) Variable Output
              20:             TypeInt 32 1
              21:     20(int) Constant 0
              22:             TypeMatrix 13(fvec4) 4
         23(buf):             TypeStruct 22
              24:             TypePointer Uniform 23(buf)
        25(ubuf):     24(ptr) Variable Uniform
              26:             TypePointer Uniform 22
              29:             TypePointer Input 13(fvec4)
         30(pos):     29(ptr) Variable Input
              33:             TypePointer Output 13(fvec4)
         4(main):           2 Function None 3
               5:             Label
              12:    7(fvec2) Load 11(inTexCoords)
                              Store 9(texcoord) 12
              27:     26(ptr) AccessChain 25(ubuf) 21
              28:          22 Load 27
              31:   13(fvec4) Load 30(pos)
              32:   13(fvec4) MatrixTimesVector 28 31
              34:     33(ptr) AccessChain 19 21
                              Store 34 32
                              Return
                              FunctionEnd